#include "glc3-eng-engine.hpp"
#ifdef GX_USE_OPENGL_CLASS_3
#include "../../core/asset/cr-asset-manager.hpp"
#include "../../core/event/cr-ev-event.hpp"
#include "../../core/event/cr-ev-sys-system.hpp"
#include "../../core/event/cr-ev-window-resize.hpp"
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "../../gl/gl-constants.hpp"
#include "../../gl/gl-loader.hpp"
#include "../../physics/phs-engine.hpp"
#include "../../render/camera/rnd-cmr-camera.hpp"
#include "../../render/pipeline/rnd-pip-manager.hpp"
#include "../../render/scene/rnd-scn-scene.hpp"
#include "../../system/sys-app.hpp"
#include "../../system/sys-log.hpp"
#include "../buffer/glc3-buf-manager.hpp"
#include "../buffer/glc3-buf-uniform.hpp"
#include "../command/glc3-cmd-buffer.hpp"
#include "../command/glc3-cmd-manager.hpp"
#include "../pipeline/glc3-pip-manager.hpp"
#include "../sync/glc3-sy-semaphore.hpp"
#include "../texture/glc3-txt-2d.hpp"
#include "../texture/glc3-txt-cube.hpp"
#include "../texture/glc3-txt-target.hpp"

gearoenix::glc3::engine::Engine::Engine(system::Application* const sys_app, const render::engine::Type::Id engine_type) noexcept
    : render::engine::Engine(sys_app, engine_type)
{
    pipeline_manager = new pipeline::Manager(this);
}

std::shared_ptr<gearoenix::glc3::engine::Engine> gearoenix::glc3::engine::Engine::construct(system::Application* const sys_app, const render::engine::Type::Id engine_type) noexcept
{
    std::shared_ptr<Engine> e(new Engine(sys_app, engine_type));
    e->buffer_manager = new buffer::Manager(e.get());
    e->command_manager = new command::Manager();
    e->main_render_target = std::shared_ptr<render::texture::Target>(new texture::Target(e.get()));
    return e;
}

gearoenix::glc3::engine::Engine::~Engine() noexcept
{
    terminate();
}

void gearoenix::glc3::engine::Engine::update() noexcept
{
    gl::Loader::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    render::engine::Engine::update();
}

void gearoenix::glc3::engine::Engine::terminate() noexcept
{
    render::engine::Engine::terminate();
}

gearoenix::render::sync::Semaphore* gearoenix::glc3::engine::Engine::create_semaphore() const noexcept
{
    return new sync::Semaphore();
}

gearoenix::render::texture::Texture2D* gearoenix::glc3::engine::Engine::create_texture_2d(
    const core::Id id,
    const void* data,
    const render::texture::TextureFormat::Id f,
    const render::texture::SampleInfo s,
    const unsigned int img_width,
    const unsigned int img_height,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
{
    return new texture::Texture2D(id, this, data, f, s, img_width, img_height, call);
}

gearoenix::render::texture::Cube* gearoenix::glc3::engine::Engine::create_texture_cube(
    const core::Id id,
    const void* data,
    const render::texture::TextureFormat::Id f,
    const render::texture::SampleInfo s,
    const unsigned int aspect,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
{
    return new texture::Cube(id, this, data, f, s, aspect, call);
}

gearoenix::render::texture::Target* gearoenix::glc3::engine::Engine::create_render_target(
    core::Id id,
    const std::vector<render::texture::Info>& infos,
    unsigned int width,
    unsigned int height,
    const gearoenix::core::sync::EndCaller<gearoenix::core::sync::EndCallerIgnore>& call) noexcept
{
    return new texture::Target(id, this, infos, width, height, call);
}

void gearoenix::glc3::engine::Engine::submit(
    const std::size_t,
    const render::sync::Semaphore* const* const,
    const std::size_t cmds_count,
    const render::command::Buffer* const* const cmds,
    const std::size_t,
    const render::sync::Semaphore* const* const) noexcept
{
    for (std::size_t i = 0; i < cmds_count; ++i)
        reinterpret_cast<const command::Buffer*>(cmds[i])->play();
}

#endif
