#ifndef GEAROENIX_CORE_GC_RANGE_HPP
#define GEAROENIX_CORE_GC_RANGE_HPP
namespace gearoenix {
namespace core {
    namespace list {
        template <typename T>
        class Node;
    }
    namespace gc {
        class Object;
        class Range {
        private:
        protected:
        public:
            list::Node<Object*>* start = nullptr;
            list::Node<Object*>* end = nullptr;
            Range(list::Node<Object*>* start, list::Node<Object*>* end);
            Range();
            void operator=(const Range& r);
        };
    }
}
}
#endif // GEAROENIX_CORE_GC_RANGE_HPP
