#ifndef GEAROENIX_GLC3_BUFFER_UNIFORM_HPP
#define GEAROENIX_GLC3_BUFFER_UNIFORM_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_CLASS_3
#include "../../render/buffer/rnd-buf-uniform.hpp"
#include <vector>
namespace gearoenix::glc3 {
namespace engine {
    class Engine;
}
namespace buffer {
    class Uniform : public render::buffer::Uniform {
    private:
        std::vector<unsigned char> data;

    public:
        Uniform(std::size_t s, engine::Engine* e) noexcept;
        ~Uniform() noexcept final = default;
        void update(const void* src) noexcept final;
        const void* get_data() const noexcept final;
        void* get_data() noexcept final;
    };
}
}
#endif
#endif