#include "phs-bd-body.hpp"

gearoenix::physics::body::Body::Body(const Behaviour::Type body_type, const std::shared_ptr<Transferable>& body_obj)
    : body_type(body_type)
    , body_obj(body_obj)
{
}

gearoenix::physics::body::Body::~Body()
{
}

gearoenix::physics::body::Body::Behaviour::Type gearoenix::physics::body::Body::get_type() const
{
    return body_type;
}

const std::shared_ptr<gearoenix::physics::Transferable>& gearoenix::physics::body::Body::get_body_obj() const
{
    return body_obj;
}