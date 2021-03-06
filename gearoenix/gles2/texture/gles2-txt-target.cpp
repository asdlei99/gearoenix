#include "gles2-txt-target.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../core/asset/cr-asset-manager.hpp"
#include "../../core/cr-function-loader.hpp"
#include "../../gl/gl-constants.hpp"
#include "../../gl/gl-loader.hpp"
#include "../../render/texture/rnd-txt-image.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-app.hpp"
#include "../../system/sys-log.hpp"
#include "../engine/gles2-eng-engine.hpp"
#include "../gles2.hpp"
#include "gles2-txt-sample.hpp"

#ifdef GX_DEBUG_GLES2
#define GX_DEBUG_GLES2_TARGET
#endif

void gearoenix::gles2::texture::Target::state_init() const noexcept
{
#ifdef GX_DEBUG_GLES2_TARGET
    gl::Loader::check_for_error();
#endif
    gl::Loader::clear_color(0.0f, 0.0f, 0.0f, 0.0f);
    gl::Loader::enable(GL_CULL_FACE);
    gl::Loader::cull_face(GL_BACK);
    gl::Loader::enable(GL_BLEND);
    gl::Loader::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gl::Loader::enable(GL_DEPTH_TEST);
    gl::Loader::enable(GL_SCISSOR_TEST);
    gl::Loader::enable(GL_STENCIL_TEST);
    gl::Loader::viewport(0, 0, static_cast<gl::sizei>(clipping_width), static_cast<gl::sizei>(clipping_height));
    gl::Loader::scissor(0, 0, static_cast<gl::sizei>(clipping_width), static_cast<gl::sizei>(clipping_height));
#ifdef GX_DEBUG_GLES2_TARGET
    gl::Loader::check_for_error();
#endif
}

gearoenix::gles2::texture::Target::Target(const core::Id my_id, engine::Engine* const e) noexcept
    : render::texture::Target(my_id, e)
{
}

gearoenix::gles2::texture::Target::Target(engine::Engine* const e) noexcept
    : render::texture::Target(core::asset::Manager::create_id(), e)
{
#ifdef GX_DEBUG_GLES2
    gl::Loader::check_for_error();
#endif
    img_width = e->get_system_application()->get_window_width();
    img_height = e->get_system_application()->get_window_height();
    clipping_width = static_cast<core::Real>(img_width);
    clipping_height = static_cast<core::Real>(img_height);
    gl::Loader::get_integerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    gl::Loader::get_integerv(GL_RENDERBUFFER_BINDING, &depth_buffer);
    state_init();
#ifdef GX_DEBUG_GLES2
    gl::Loader::check_for_error();
#endif
}

std::shared_ptr<gearoenix::gles2::texture::Target> gearoenix::gles2::texture::Target::construct(
    core::Id my_id,
    engine::Engine* e,
    const std::vector<render::texture::Info>& infos,
    unsigned int w,
    unsigned int h,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
{
    const std::shared_ptr<Target> result(new Target(my_id, e));
    result->img_width = w;
    result->img_height = h;
    result->clipping_width = static_cast<core::Real>(w);
    result->clipping_height = static_cast<core::Real>(h);
    result->texture_objects.resize(infos.size());
    if (infos.size() != 1)
        GXLOGF("GLES2 backend only supports 1 color attachment.");
    if (infos[0].f != render::texture::TextureFormat::D16)
        GXLOGF("GLES2 backend only supports 16bits depth attachment right now.");
    e->get_function_loader()->load([result, call, infos] {
        gl::Loader::gen_framebuffers(1, reinterpret_cast<gl::uint*>(&(result->framebuffer)));
        gl::Loader::gen_renderbuffers(1, reinterpret_cast<gl::uint*>(&(result->depth_buffer)));
        gl::Loader::bind_renderbuffer(GL_RENDERBUFFER, result->depth_buffer);
        gl::Loader::renderbuffer_storage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, result->img_width, result->img_height);
        gl::Loader::bind_framebuffer(GL_FRAMEBUFFER, result->framebuffer);
        gl::Loader::framebuffer_renderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, result->depth_buffer);
        gl::Loader::gen_textures(static_cast<gearoenix::gl::sizei>(result->texture_objects.size()), result->texture_objects.data());
        for (std::size_t i = 0; i < result->texture_objects.size(); ++i) {
            const auto& txt_info = infos[i];
            const auto& txt_fmt = txt_info.f;
            const auto& txt = result->texture_objects[i];
            if (txt_fmt == render::texture::TextureFormat::D16) {
                gl::Loader::bind_texture(GL_TEXTURE_2D, txt);
                gl::Loader::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGB, result->img_width, result->img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                gl::Loader::framebuffer_texture_2d(GL_FRAMEBUFFER, static_cast<gearoenix::gl::enumerated>(GL_COLOR_ATTACHMENT0 + i), GL_TEXTURE_2D, txt, 0);
            } else {
                GXUNEXPECTED
            }
        }
        if (gl::Loader::check_framebuffer_status(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            GXLOGF("Failed to create render target!")
        result->state_init();
    });
    return result;
}

gearoenix::gles2::texture::Target::~Target() noexcept
{
    if (texture_objects.size() == 0) // This is main render-target
        return;
    const auto cf = framebuffer;
    const auto cr = depth_buffer;
    render_engine->get_function_loader()->load([cf, cr, this] {
        if (cf != -1)
            gl::Loader::delete_framebuffers(1, reinterpret_cast<const gl::uint*>(&cf));
        if (cr != -1)
            gl::Loader::delete_renderbuffers(1, reinterpret_cast<const gl::uint*>(&cr));
        gl::Loader::delete_textures(static_cast<gearoenix::gl::sizei>(texture_objects.size()), texture_objects.data());
    });
}

void gearoenix::gles2::texture::Target::bind() const noexcept
{
    if (-1 != depth_buffer)
        gl::Loader::bind_renderbuffer(GL_RENDERBUFFER, depth_buffer);
    gl::Loader::bind_framebuffer(GL_FRAMEBUFFER, framebuffer);
    gl::Loader::viewport(0, 0, static_cast<gl::sizei>(clipping_width), static_cast<gl::sizei>(clipping_height));
    gl::Loader::scissor(0, 0, static_cast<gl::sizei>(clipping_width), static_cast<gl::sizei>(clipping_height));
    gl::Loader::enable(GL_DEPTH_TEST);
    gl::Loader::depth_mask(GL_TRUE);
    if (texture_objects.size() == 0)
        gl::Loader::clear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    else
        gl::Loader::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void gearoenix::gles2::texture::Target::bind_textures(const std::vector<gl::enumerated>& texture_units) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (texture_units.size() != texture_objects.size())
        GXLOGF("Different size for texture units is not acceptable.")
#endif
    for (std::size_t i = 0; i < texture_objects.size(); ++i) {
        gl::Loader::active_texture(GL_TEXTURE0 + texture_units[i]);
        gl::Loader::bind_texture(GL_TEXTURE_2D, texture_objects[i]);
    }
}
#endif
