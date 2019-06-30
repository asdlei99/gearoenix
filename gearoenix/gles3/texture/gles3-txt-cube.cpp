#include "gles3-txt-cube.hpp"
#ifdef GX_USE_OPENGL_ES3
#include "../../core/cr-function-loader.hpp"
#include "../../core/cr-static.hpp"
#include "../../gl/gl-constants.hpp"
#include "../../gl/gl-loader.hpp"
#include "../../render/texture/rnd-txt-png.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-log.hpp"
#include "../engine/gles3-eng-engine.hpp"
#include "gles3-txt-2d.hpp"
#include "gles3-txt-sample.hpp"

static constexpr auto GX_GLES3_MIN_TEXCUBE_ASPECT = 16;

static const gearoenix::gl::enumerated FACES[] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
};

gearoenix::gles3::texture::Cube::Cube(
    const core::Id my_id,
    engine::Engine* const engine,
    const void* const data,
    const render::texture::TextureFormat::Id f,
    const render::texture::SampleInfo s,
    const unsigned int aspect,
    const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept
    : render::texture::Cube(my_id, engine)
{
    const SampleInfo sample_info = SampleInfo(s);
    gl::uint cf;
    const gl::sizei gaspect = GX_GLES3_MIN_TEXCUBE_ASPECT < aspect ? static_cast<gl::sizei>(aspect) : GX_GLES3_MIN_TEXCUBE_ASPECT;
#ifdef GX_DEBUG_GLES3
    if (aspect != 1 && aspect < GX_GLES3_MIN_TEXCUBE_ASPECT)
        GXLOGF("Unsupported image aspect in GLES2 for cube texture id: " << my_id);
#endif
    std::uint8_t** pixels = nullptr;
    if (f == render::texture::TextureFormat::RGBA_FLOAT32 && aspect == 1) {
        cf = GL_RGBA;
        const gl::sizei pixel_size = gaspect * gaspect * 4;
        const auto* const rdata = reinterpret_cast<const core::Real*>(data);
        pixels = new std::uint8_t*[GXCOUNTOF(FACES)];
        std::uint8_t p[4];
        p[0] = static_cast<std::uint8_t>(rdata[0] * 255.1f);
        p[1] = static_cast<std::uint8_t>(rdata[1] * 255.1f);
        p[2] = static_cast<std::uint8_t>(rdata[2] * 255.1f);
        p[3] = static_cast<std::uint8_t>(rdata[3] * 255.1f);
        for (int fi = 0; fi < static_cast<int>(GXCOUNTOF(FACES)); ++fi) {
            pixels[fi] = new std::uint8_t[pixel_size];
            for (gl::sizei i = 0; i < pixel_size;)
                for (int j = 0; j < 4; ++j, ++i)
                    pixels[fi][i] = p[j];
        }
    } else
        GXLOGF("Unsupported/Unimplemented setting for cube texture with id " << my_id)
    engine->get_function_loader()->load([this, gaspect, pixels, cf, sample_info, call] {
        gl::Loader::gen_textures(1, &texture_object);
        gl::Loader::bind_texture(GL_TEXTURE_CUBE_MAP, texture_object);
        gl::Loader::tex_parameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, sample_info.mag_filter);
        gl::Loader::tex_parameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, sample_info.min_filter);
        gl::Loader::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, sample_info.wrap_s);
        gl::Loader::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, sample_info.wrap_t);
        for (int fi = 0; fi < static_cast<int>(GXCOUNTOF(FACES)); ++fi) {
            gl::Loader::tex_image_2d(FACES[fi], 0, static_cast<gl::sint>(cf), gaspect, gaspect, 0, cf, GL_UNSIGNED_BYTE, pixels[fi]);
        }
        gl::Loader::check_for_error();
        gl::Loader::generate_mipmap(GL_TEXTURE_CUBE_MAP);
        // It clears the errors, some drivers does not support mip-map generation for cube texture
        gl::Loader::get_error();
        for (int fi = 0; fi < static_cast<int>(GXCOUNTOF(FACES)); ++fi) {
            delete[] pixels[fi];
        }
        delete[] pixels;
    });
}

gearoenix::gles3::texture::Cube::~Cube() noexcept
{
    if (texture_object == 0)
        return;
    const gl::uint c_texture_object = texture_object;
    render_engine->get_function_loader()->load([c_texture_object] {
        gl::Loader::bind_texture(GL_TEXTURE_CUBE_MAP, 0);
        gl::Loader::delete_textures(1, &c_texture_object);
    });
    texture_object = 0;
}

void gearoenix::gles3::texture::Cube::bind(gl::enumerated texture_unit) const noexcept
{
    gl::Loader::active_texture(GL_TEXTURE0 + texture_unit);
    gl::Loader::bind_texture(GL_TEXTURE_CUBE_MAP, texture_object);
}

#endif
