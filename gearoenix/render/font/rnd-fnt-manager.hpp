#ifndef GEAROEMIX_RENDER_FONT_MANAGER_HPP
#define GEAROEMIX_RENDER_FONT_MANAGER_HPP
#include "../../core/cr-types.hpp"
#include "../../core/sync/cr-sync-end-caller.hpp"
#include <memory>

namespace gearoenix {
namespace system {
    namespace stream {
        class Stream;
    }
}
namespace render {
    class Engine;
    namespace font {
        class Font;
        class Manager {
        protected:
            Engine* e = nullptr;
            const std::shared_ptr<system::stream::Stream> s;

        public:
            Manager(const std::shared_ptr<system::stream::Stream>& s, Engine* e);
            ~Manager();
            std::shared_ptr<Font> get(core::Id mid, core::sync::EndCaller<Font> c);
        };
    }
}
}
#endif
