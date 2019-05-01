#include "gles2-txt-sample.hpp"
#include "../../system/sys-log.hpp"

gearoenix::gles2::texture::SampleInfo::SampleInfo()
{
}

gearoenix::gles2::texture::SampleInfo::SampleInfo(const render::texture::SampleInfo& o)
{
    switch (o.mag_filter) {
    case render::texture::Filter::NEAREST:
        mag_filter = GL_NEAREST;
        break;
    case render::texture::Filter::LINEAR:
        mag_filter = GL_LINEAR;
        break;
    default:
        GXUNEXPECTED;
        break;
    }
    switch (o.min_filter) {
    case render::texture::Filter::NEAREST:
        min_filter = GL_NEAREST_MIPMAP_NEAREST;
        break;
    case render::texture::Filter::LINEAR:
        min_filter = GL_LINEAR_MIPMAP_LINEAR;
        break;
    default:
        GXUNEXPECTED;
        break;
    }
    const auto fun = [](render::texture::Wrap::Id w) {
        switch (w) {
        case render::texture::Wrap::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case render::texture::Wrap::MIRROR:
            return GL_MIRRORED_REPEAT;
        case render::texture::Wrap::REPEAT:
            return GL_REPEAT;
        default:
            GXUNEXPECTED;
            break;
        }
    };
    wrap_s = fun(o.wrap_s);
    wrap_t = fun(o.wrap_t);
    wrap_r = fun(o.wrap_r);
}