#ifndef GEAROENIX_RENDER_TEXTURE_SAMPLE_HPP
#define GEAROENIX_RENDER_TEXTURE_SAMPLE_HPP
#include "rnd-txt-filter.hpp"
#include "rnd-txt-wrap.hpp"
namespace gearoenix::render::texture {
struct SampleInfo {
    Filter::Id min_filter = Filter::LINEAR_MIPMAP_NEAREST;
    Filter::Id mag_filter = Filter::LINEAR_MIPMAP_NEAREST;
    Wrap::Id wrap_s = Wrap::REPEAT;
    Wrap::Id wrap_t = Wrap::REPEAT;
    Wrap::Id wrap_r = Wrap::REPEAT;
};
}
#endif
