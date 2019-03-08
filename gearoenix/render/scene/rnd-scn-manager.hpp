#ifndef GEAROEMIX_RENDER_SCENE_MANAGER_HPP
#define GEAROEMIX_RENDER_SCENE_MANAGER_HPP
#include <memory>

namespace gearoenix {
namespace system {
    namespace stream {
        class Stream;
    }
}
namespace render {
    namespace engine {
        class Engine;
    }
    namespace scene {
        class Scene;
        class Manager {
        protected:
            const std::shared_ptr<engine::Engine> e;
            const std::shared_ptr<system::stream::Stream> s;

        public:
            Manager(const std::shared_ptr<system::stream::Stream>& s, const std::shared_ptr<engine::Engine>& e);
            ~Manager();
            std::shared_ptr<Scene> get(const core::Id mid, const core::sync::EndCaller<Scene> c);
        };
    }
}
}
#endif
