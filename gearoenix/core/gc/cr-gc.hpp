#ifndef GEAROENIX_CORE_GC_GC_HPP
#define GEAROENIX_CORE_GC_GC_HPP
#include "cr-gc-object.hpp"
#include <map>
#include <mutex>
namespace gearoenix {
namespace core {
    namespace list {
        template <typename T>
        class List;
        template <typename T>
        class Node;
    }
    namespace gc {
        class Range;
        class Gc : public Object {
            friend class Object;

        private:
            // size -> offset -> range
            std::map<unsigned int, std::map<unsigned int, Range>> free_ranges;
            std::mutex lock;
            // is owner of objects
            list::List<Object*>* objects;
            void remove_range(const Range& r);
            void add_range(const Range& r);
            void deallocate(Object* obj);
            void initialize();

        protected:
        public:
            void allocate(Object* obj);
            Gc(unsigned int size, Gc* parent = nullptr);
            virtual ~Gc();
            list::List<Object*>* get_objects();
        };
    }
}
}
#endif // GEAROENIX_CORE_GC_GC_HPP
