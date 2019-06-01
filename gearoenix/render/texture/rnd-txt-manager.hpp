#ifndef GEAROENIX_RENDER_TEXTURE_MANAGER_HPP
#define GEAROENIX_RENDER_TEXTURE_MANAGER_HPP
#include "../../core/cache/cr-cache-file.hpp"
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "../../math/math-vector.hpp"
#include <map>
#include <memory>

namespace gearoenix {
namespace system::stream {
    class Stream;
}
namespace render {
    namespace engine {
        class Engine;
    }
    namespace texture {
        class Cube;
        class Texture;
        class Texture2D;
        class Manager {
        protected:
            engine::Engine* const e;
            core::cache::File<Texture> cache;
            std::map<math::Vec4, core::Id> color_4d_id_t2d;
            std::map<math::Vec3, core::Id> color_3d_id_t2d;
            std::map<math::Vec2, core::Id> color_2d_id_t2d;
            std::map<core::Real, core::Id> color_1d_id_t2d;
            std::map<math::Vec4, core::Id> color_4d_id_cube;
            std::map<math::Vec3, core::Id> color_3d_id_cube;
            std::map<math::Vec2, core::Id> color_2d_id_cube;

        public:
            Manager(system::stream::Stream* s, engine::Engine* e) noexcept;
            ~Manager() noexcept = default;
            std::shared_ptr<Texture2D> get_2d(const math::Vec4& color, core::sync::EndCaller<Texture2D>& c) noexcept;
            std::shared_ptr<Texture2D> get_2d(const math::Vec3& color, core::sync::EndCaller<Texture2D>& c) noexcept;
            std::shared_ptr<Texture2D> get_2d(const math::Vec2& color, core::sync::EndCaller<Texture2D>& c) noexcept;
            std::shared_ptr<Texture2D> get_2d(core::Real value, core::sync::EndCaller<Texture2D>& c) noexcept;
            std::shared_ptr<Cube> get_cube(const math::Vec4& color, core::sync::EndCaller<Cube>& c) noexcept;
            std::shared_ptr<Cube> get_cube(const math::Vec3& color, core::sync::EndCaller<Cube>& c) noexcept;
            std::shared_ptr<Cube> get_cube(const math::Vec2& color, core::sync::EndCaller<Cube>& c) noexcept;
            std::shared_ptr<Texture> get_gx3d(core::Id id, core::sync::EndCaller<Texture>& c) noexcept;
        };
    }
}
}
#endif
