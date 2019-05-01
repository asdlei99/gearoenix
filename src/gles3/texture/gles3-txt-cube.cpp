#include "gles3-txt-cube.hpp"
#ifdef GX_USE_OPENGL_ES3
#include "../../render/texture/rnd-txt-png.hpp"
#include "../../system/stream/sys-stm-stream.hpp"
#include "../../system/sys-log.hpp"
#include "../gles3-engine.hpp"

#define FACES_COUNT 6

gearoenix::gles3::texture::Cube::Cube(core::Id my_id, system::stream::Stream* file, Engine* eng, core::sync::EndCaller<core::sync::EndCallerIgnore> end)
    : render::texture::Cube(my_id, eng)
{
    std::vector<std::vector<unsigned char>> img_data(FACES_COUNT);
    unsigned int imgw, imgh;
    render::texture::PNG::decode(file, img_data[0], imgw, imgh);
    for (int i = 1; i < FACES_COUNT; ++i) {
        unsigned int iimgw, iimgh;
        render::texture::PNG::decode(file, img_data[i], iimgw, iimgh);
        if (imgw != iimgw || imgh != iimgh)
            UNEXPECTED;
    }
    static const GLenum faces[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    };
    std::function<void()> loadf = [&, imgw, imgh, img_data, end]() -> void {
        glGenTextures(1, &texture_object);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_object);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //GL_MIRRORED_REPEAT
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        for (int i = 0; i < FACES_COUNT; ++i) {
            glTexImage2D(faces[i], 0, GL_RGBA, imgw, imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img_data[i].data());
        }
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        (void)end;
    };
    eng->add_load_function(loadf);
}

gearoenix::gles3::texture::Cube::~Cube()
{
    if (texture_object == 0)
        return;
    const GLuint c_texture_object = texture_object;
    render_engine->add_load_function([c_texture_object] {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glDeleteTextures(1, &c_texture_object);
    });
    texture_object = 0;
}

void gearoenix::gles3::texture::Cube::bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_object);
}

#endif