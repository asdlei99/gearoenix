#include "gles3-txt-target.hpp"
#ifdef GX_USE_OPENGL_ES3
#include "../../core/asset/cr-asset-manager.hpp"
#include "../../core/cr-function-loader.hpp"
#include "../../gl/gl-constants.hpp"
#include "../../gl/gl-loader.hpp"
#include "../../render/texture/rnd-txt-png.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-app.hpp"
#include "../../system/sys-log.hpp"
#include "../engine/gles3-eng-engine.hpp"
#include "../gles3.hpp"
#include "gles3-txt-sample.hpp"

#ifdef GX_DEBUG_GLES3
#define GX_DEBUG_GLES3_TARGET
#endif

void gearoenix::gles3::texture::Target::state_init() const noexcept
{
    gl::Loader::clear_color(0.0f, 0.0f, 0.0f, 0.0f);
    gl::Loader::enable(GL_CULL_FACE);
    gl::Loader::cull_face(GL_BACK);
    gl::Loader::enable(GL_BLEND);
    gl::Loader::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gl::Loader::enable(GL_DEPTH_TEST);
    gl::Loader::enable(GL_SCISSOR_TEST);
    gl::Loader::enable(GL_STENCIL_TEST);
    gl::Loader::viewport(0, 0, static_cast<gl::sizei>(img_width), static_cast<gl::sizei>(img_height));
    gl::Loader::scissor(0, 0, static_cast<gl::sizei>(img_width), static_cast<gl::sizei>(img_height));
}

gearoenix::gles3::texture::Target::Target(engine::Engine* const e) noexcept
    : render::texture::Target(core::asset::Manager::create_id(), e)
{
    const auto* sys_app = e->get_system_application();
    img_width = sys_app->get_width();
    img_height = sys_app->get_height();
    gl::Loader::get_integerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    gl::Loader::get_integerv(GL_RENDERBUFFER_BINDING, &depth_buffer);
    state_init();
}

gearoenix::gles3::texture::Target::Target(
    core::Id my_id,
    engine::Engine* e,
    render::texture::TextureFormat::Id f,
    render::texture::SampleInfo s,
    unsigned int w,
    unsigned int h,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
    : render::texture::Target(my_id, e)
{
    img_width = w;
    img_height = h;
    const SampleInfo sample_info = SampleInfo(s);
    /// TODO: correct this
    if (f != render::texture::TextureFormat::R_FLOAT16)
        GXLOGF("GLES3 engine only supports depth");
    e->get_function_loader()->load([this, sample_info, call] {
        gl::Loader::gen_framebuffers(1, reinterpret_cast<gl::uint*>(&framebuffer));
        gl::Loader::gen_renderbuffers(1, reinterpret_cast<gl::uint*>(&depth_buffer));
        gl::Loader::bind_renderbuffer(GL_RENDERBUFFER, depth_buffer);
        gl::Loader::renderbuffer_storage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, img_width, img_height);
        gl::Loader::bind_framebuffer(GL_FRAMEBUFFER, framebuffer);
        gl::Loader::gen_textures(1, &texture_object);
        gl::Loader::bind_texture(GL_TEXTURE_2D, texture_object);
        gl::Loader::framebuffer_renderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);
        gl::Loader::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl::Loader::tex_parameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl::Loader::framebuffer_texture_2d(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_object, 0);
        if (gl::Loader::check_framebuffer_status(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            GXLOGF("Failed to create render target!")
        state_init();
    });
}

gearoenix::gles3::texture::Target::~Target() noexcept
{
    if (texture_object == 0) // This is main render-target
        return;
    const auto cf = framebuffer;
    const auto cr = depth_buffer;
    const auto ct = texture_object;
    render_engine->get_function_loader()->load([cf, cr, ct] {
        gl::Loader::delete_framebuffers(1, reinterpret_cast<const gl::uint*>(&cf));
        gl::Loader::delete_renderbuffers(1, reinterpret_cast<const gl::uint*>(&cr));
        gl::Loader::delete_textures(1, &ct);
    });
}

void gearoenix::gles3::texture::Target::bind() const noexcept
{
    gl::Loader::bind_renderbuffer(GL_RENDERBUFFER, depth_buffer);
    gl::Loader::bind_framebuffer(GL_FRAMEBUFFER, framebuffer);
    gl::Loader::viewport(0, 0, static_cast<gl::sizei>(img_width), static_cast<gl::sizei>(img_height));
    gl::Loader::scissor(0, 0, static_cast<gl::sizei>(img_width), static_cast<gl::sizei>(img_height));
    gl::Loader::enable(GL_DEPTH_TEST);
    gl::Loader::depth_mask(GL_TRUE);
    if (texture_object == 0)
        gl::Loader::clear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    else
        gl::Loader::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

#endif