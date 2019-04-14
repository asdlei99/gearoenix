#include "rnd-pip-resource-set.hpp"
#include "../buffer/rnd-buf-framed-uniform.hpp"
#include "../camera/rnd-cmr-camera.hpp"
#include "../graph/node/rnd-gr-nd-forward-pbr-directional-shadow.hpp"
#include "../light/rnd-lt-light.hpp"
#include "../material/rnd-mat-material.hpp"
#include "../mesh/rnd-msh-mesh.hpp"
#include "../model/rnd-mdl-model.hpp"
#include "../scene/rnd-scn-scene.hpp"

gearoenix::render::pipeline::ResourceSet::~ResourceSet() {}

#define GXHELPER(c, cc) \
    void gearoenix::render::pipeline::ResourceSet::set_##c(const std::shared_ptr<c::cc>& o) { c##_uniform_buffer = o->get_uniform_buffers()->get_buffer(); }

GXHELPER(scene, Scene)
GXHELPER(camera, Camera)

void gearoenix::render::pipeline::ResourceSet::set_light(const std::shared_ptr<light::Light>& l)
{
    const std::shared_ptr<buffer::FramedUniform>& fub = l->get_uniform_buffers();
    if (fub == nullptr)
        light_uniform_buffer = nullptr;
    else
        light_uniform_buffer = fub->get_buffer();
}

GXHELPER(model, Model)

void gearoenix::render::pipeline::ResourceSet::set_mesh(const std::shared_ptr<mesh::Mesh>& m)
{
    msh = m;
}

void gearoenix::render::pipeline::ResourceSet::set_material(const std::shared_ptr<material::Material>& m)
{
    material_uniform_buffer = m->get_uniform_buffers()->get_buffer();
    color = m->get_color();
    metallic_roughness = m->get_metallic_roughness();
    normal = m->get_normal();
    emissive = m->get_emissive();
}

#undef GXHELPER

void gearoenix::render::pipeline::ResourceSet::clean()
{
    scene_uniform_buffer = nullptr;
    camera_uniform_buffer = nullptr;
    light_uniform_buffer = nullptr;
    model_uniform_buffer = nullptr;
    material_uniform_buffer = nullptr;
    node_uniform_buffer = nullptr;
    msh = nullptr;
    color = nullptr;
    metallic_roughness = nullptr;
    normal = nullptr;
    emissive = nullptr;
}
