#include "rnd-scn-scene.hpp"
#include "../../audio/au-audio.hpp"
#include "../../audio/au-manager.hpp"
#include "../../core/asset/cr-asset-manager.hpp"
#include "../../physics/accelerator/phs-acc-bvh.hpp"
#include "../../physics/body/phs-bd-body.hpp"
#include "../../physics/collider/phs-cld-collider.hpp"
#include "../../physics/constraint/phs-cns-constraint.hpp"
#include "../../physics/constraint/phs-cns-manager.hpp"
#include "../../system/sys-app.hpp"
#include "../buffer/rnd-buf-framed-uniform.hpp"
#include "../camera/rnd-cmr-camera.hpp"
#include "../camera/rnd-cmr-manager.hpp"
#include "../engine/rnd-eng-engine.hpp"
#include "../light/rnd-lt-directional.hpp"
#include "../light/rnd-lt-light.hpp"
#include "../light/rnd-lt-manager.hpp"
#include "../material/rnd-mat-material.hpp"
#include "../mesh/rnd-msh-mesh.hpp"
#include "../model/rnd-mdl-manager.hpp"
#include "../model/rnd-mdl-model.hpp"
#include "../pipeline/rnd-pip-manager.hpp"
#include "../shader/rnd-shd-shader.hpp"
#include "../skybox/rnd-sky-skybox.hpp"

static const std::shared_ptr<gearoenix::render::camera::Camera> null_camera = nullptr;
static const std::shared_ptr<gearoenix::audio::Audio> null_audio = nullptr;
static const std::shared_ptr<gearoenix::render::light::Light> null_light = nullptr;
static const std::shared_ptr<gearoenix::render::model::Model> null_model = nullptr;
static const std::shared_ptr<gearoenix::physics::constraint::Constraint> null_constraint = nullptr;

gearoenix::render::scene::Scene::Scene(
    const core::Id my_id,
    const Type t,
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>&) noexcept
    : core::asset::Asset(my_id, core::asset::Type::SCENE)
    , scene_type_id(t)
    , uniform_buffers(new buffer::FramedUniform(static_cast<unsigned int>(sizeof(Uniform)), e))
    , static_accelerator(new gearoenix::physics::accelerator::Bvh())
    , dynamic_accelerator(new gearoenix::physics::accelerator::Bvh())
    , e(e)
{
}

gearoenix::render::scene::Scene::Scene(
    const core::Id my_id,
    const Type t,
    system::stream::Stream* const f,
    engine::Engine* const e,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
    : core::asset::Asset(my_id, core::asset::Type::SCENE)
    , scene_type_id(t)
    , uniform_buffers(new buffer::FramedUniform(static_cast<unsigned int>(sizeof(Uniform)), e))
    , static_accelerator(new gearoenix::physics::accelerator::Bvh())
    , dynamic_accelerator(new gearoenix::physics::accelerator::Bvh())
    , e(e)
{
    core::asset::Manager* const astmgr = e->get_system_application()->get_asset_manager();
#define GX_HELPER(x, n, cls)                                                            \
    {                                                                                   \
        const std::shared_ptr<n::Manager>& mgr = astmgr->get_##x##_manager();           \
        std::vector<core::Id> ids;                                                      \
        f->read(ids);                                                                   \
        if (!ids.empty()) {                                                             \
            core::sync::EndCaller<n::cls> call([c](const std::shared_ptr<n::cls>&) {}); \
            for (const core::Id id : ids)                                               \
                add_##x(mgr->get_gx3d(id, call));                                       \
        }                                                                               \
    }

    GX_HELPER(camera, camera, Camera)
    GX_HELPER(audio, audio, Audio)
    GX_HELPER(light, light, Light)
    GX_HELPER(model, model, Model)
    if (f->read_bool()) {
        core::Id skybox_id = 0;
        f->read(skybox_id);
    }
    GX_HELPER(constraint, physics::constraint, Constraint)

#undef GX_HELPER

    if (f->read_bool()) {
        GXUNIMPLEMENTED
    }

    GXLOGD("Number of models is: " << models.size())
    GXLOGD("Number of lights is: " << lights.size())
    GXLOGD("Number of cameras is: " << cameras.size())
}

gearoenix::render::scene::Scene::~Scene() noexcept
{
    audios.clear();
    cameras.clear();
    constraints.clear();
    lights.clear();
    models.clear();
    static_colliders.clear();
    dynamic_colliders.clear();
    skybox = nullptr;
    GXLOGD("Scene " << asset_id << " deleted.")
}

void gearoenix::render::scene::Scene::add_camera(const std::shared_ptr<camera::Camera>& o) noexcept
{
    const core::Id oid = o->get_asset_id();
#ifdef GX_DEBUG_MODE
    if (cameras.find(oid) != cameras.end()) {
        GXLOGE("Error overriding of a camera with same Id: " << oid)
    }
#endif
    cameras[oid] = o;
}

void gearoenix::render::scene::Scene::add_audio(const std::shared_ptr<audio::Audio>& o) noexcept
{
    const core::Id oid = o->get_asset_id();
#ifdef GX_DEBUG_MODE
    if (audios.find(oid) != audios.end()) {
        GXLOGE("Error overriding of a audio with same Id: " << oid)
    }
#endif
    audios[oid] = o;
}

void gearoenix::render::scene::Scene::add_light(const std::shared_ptr<light::Light>& o) noexcept
{
    const core::Id oid = o->get_asset_id();
#ifdef GX_DEBUG_MODE
    if (lights.find(oid) != lights.end()) {
        GXLOGE("Error overriding of a light with same Id: " << oid)
    }
#endif
    lights[oid] = o;
}

const std::shared_ptr<gearoenix::render::light::Light>& gearoenix::render::scene::Scene::get_light(const core::Id id) const noexcept
{
    const auto& find = lights.find(id);
    if (lights.end() == find) {
        return null_light;
    }
    return find->second;
}

void gearoenix::render::scene::Scene::add_model(const std::shared_ptr<model::Model>& m) noexcept
{
    std::function<void(const std::shared_ptr<model::Model>&)> travm = [&travm, this ](const std::shared_ptr<model::Model>& mdl) noexcept
    {
        auto& children = mdl->get_children();
        const core::Id mid = mdl->get_asset_id();
#ifdef GX_DEBUG_MODE
        if (models.find(mid) != models.end()) {
            GXLOGE("Error overriding of a model with same Id: " << mid)
        }
#endif
        mdl->set_scene(this);
        models[mid] = mdl;
        for (auto& c : children)
            travm(c.second);
    };

    travm(m);
    models_changed = true;
}

const std::shared_ptr<gearoenix::render::model::Model>& gearoenix::render::scene::Scene::get_model(const core::Id model_id) const noexcept
{
    const auto& find = models.find(model_id);
    if (models.end() == find) {
        return null_model;
    }
    return find->second;
}

void gearoenix::render::scene::Scene::add_constraint(const std::shared_ptr<physics::constraint::Constraint>& c) noexcept
{
    const core::Id cid = c->get_asset_id();
#ifdef GX_DEBUG_MODE
    if (constraints.find(cid) != constraints.end()) {
        GXLOGE("Error overriding of a constraint with same Id: " << cid)
    }
#endif // GX_DEBUG_MODE
    constraints[cid] = c;
}

const std::shared_ptr<gearoenix::physics::constraint::Constraint>& gearoenix::render::scene::Scene::get_constraint(const core::Id constraint_id) const noexcept
{
    const auto& find = constraints.find(constraint_id);
    if (constraints.end() == find) {
        return null_constraint;
    }
    return find->second;
}

void gearoenix::render::scene::Scene::update() noexcept
{
    if (models_changed) {
        models_changed = false;
        dynamic_colliders.clear();
        static_colliders.clear();
        for (auto& im : models) {
            auto& mdl = im.second;
            auto* const cld = mdl->get_collider();
            if (cld != nullptr && mdl->get_enability() == core::State::Set) {
                if (mdl->get_dynamicity()) {
                    dynamic_colliders.push_back(cld);
                } else {
                    static_colliders.push_back(cld);
                }
            }
        }
        static_accelerator->reset(static_colliders);
    }
    dynamic_accelerator->reset(dynamic_colliders);

    unsigned int dirc = 0;
    for (const auto& il : lights) {
        const light::Light* const l = il.second.get();
        if (l->is_shadow_caster())
            continue;
        {
            const auto* const dl = dynamic_cast<const light::Directional*>(l);
            if (dl != nullptr && dirc < GX_MAX_DIRECTIONAL_LIGHTS) {
                uniform.directional_lights_color[dirc] = math::Vec4(dl->get_color(), 0.0f);
                uniform.directional_lights_direction[dirc] = math::Vec4(dl->get_direction(), 0.0f);
                ++dirc;
                continue;
            }
        }
    }
    uniform.lights_count[0] = static_cast<core::Real>(dirc);
    uniform_buffers->update(&uniform);
}

std::optional<std::pair<gearoenix::core::Real, gearoenix::physics::collider::Collider*>> gearoenix::render::scene::Scene::hit(const math::Ray3& r, core::Real d_min) const noexcept
{
    const auto hs = static_accelerator->hit(r, d_min);
    const auto d_min_l = std::nullopt == hs ? d_min : hs.value().first;
    const auto hd = dynamic_accelerator->hit(r, d_min_l);
    if (std::nullopt == hd)
        return hs;
    return hd;
}
