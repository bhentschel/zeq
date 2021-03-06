
/* Copyright (c) 2015, Human Brain Project
 *                     grigori.chevtchenko@epfl.ch
 */

#include "eventDescriptor.h"
#include "detail/eventDescriptor.h"

namespace zeq
{

EventDescriptor::EventDescriptor( const std::string& restName,
                                  const uint128_t& eventType,
                                  const std::string& schema,
                                  const EventDirection eventDirection )
    : _impl( new detail::EventDescriptor( restName, eventType, schema, eventDirection ))
{}

EventDescriptor::EventDescriptor( EventDescriptor&& rhs )
    : _impl( rhs._impl )
{
    rhs._impl = 0;
}

EventDescriptor::~EventDescriptor()
{
    delete _impl;
}

const std::string& EventDescriptor::getRestName() const
{
    return _impl->restName;
}

const uint128_t& EventDescriptor::getEventType() const
{
    return _impl->eventType;
}

const std::string& EventDescriptor::getSchema() const
{
    return _impl->schema;
}

EventDirection EventDescriptor::getEventDirection() const
{
    return _impl->eventDirection;
}

}
