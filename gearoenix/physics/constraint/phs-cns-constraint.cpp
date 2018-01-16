#include "phs-cns-constraint.hpp"
#include "../../system/sys-file.hpp"
#include "../../system/sys-log.hpp"
#include "phs-cns-placer.hpp"

gearoenix::physics::constraint::Constraint::Constraint(Type t)
    : t(t)
{
}

gearoenix::physics::constraint::Constraint::~Constraint()
{
}

gearoenix::physics::constraint::Constraint* gearoenix::physics::constraint::Constraint::read(system::File* f, core::EndCaller<core::EndCallerIgnore> c)
{
    Type t;
    f->read(t);
    switch (t) {
    case PLACER:
        return new Placer(f, c);
    default:
        UNEXPECTED;
    }
}

gearoenix::physics::constraint::Placer* gearoenix::physics::constraint::Constraint::to_placer()
{
    if (t == PLACER)
        return reinterpret_cast<Placer*>(this);
    return nullptr;
}

const gearoenix::physics::constraint::Placer* gearoenix::physics::constraint::Constraint::to_placer() const
{
    if (t == PLACER)
        return reinterpret_cast<const Placer*>(this);
    return nullptr;
}
