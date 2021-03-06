
/* Copyright (c) 2014-2015, Human Brain Project
 *                          Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 *                          Stefan.Eilemann@epfl.ch
 */

#ifndef ZEQ_SUBSCRIBER_H
#define ZEQ_SUBSCRIBER_H

#include <zeq/receiver.h> // base class

#include <vector>

namespace zeq
{

namespace detail { class Subscriber; }

/**
 * Subscribes to Publisher to receive events.
 *
 * Not thread safe.
 *
 * Example: @include tests/subscriber.cpp
 */
class Subscriber : public Receiver
{
public:
    /**
     * Create and subscribe to one or more publishers.
     *
     * A subscription to a non-existing publisher is valid. It will start
     * receiving events once the other publisher(s) is(are) publishing.
     *
     * @param uri publishing URI in the format scheme://[*|host|IP|IF][:port]
     * @throw std::runtime_error when the subscription failed.
     */
    ZEQ_API explicit Subscriber( const servus::URI& uri );

    /*
     * Create a shared subscription to one or more publishers.
     *
     * A receive on any Subscriber of a shared group will work on all
     * subscribers and call the registered handlers. Note to implementer: wrap
     * zmg_context in a shared_ptr object used by all instances.
     *
     * @param uri publishing URI in the format scheme://[*|host|IP|IF][:port]
     * @param shared another receiver to share data reception with.
     * @throw std::runtime_error when the subscription failed.
     */
    ZEQ_API Subscriber( const servus::URI& uri, Receiver& shared );

    /** Destroy this subscriber and withdraw any subscriptions. */
    ZEQ_API ~Subscriber();

    /**
     * Register a new callback for an event.
     *
     * Only one callback per event is possible in the current implementation.
     *
     * @param event the event type of interest
     * @param func the callback function on receive of event
     * @return true if callback could be registered
     */
    ZEQ_API bool registerHandler( const uint128_t& event,
                                  const EventFunc& func );

    /**
     * Deregister a callback for an event.
     *
     * @param event the event type of interest
     * @return true if callback could be deregistered
     */
    ZEQ_API bool deregisterHandler( const uint128_t& event );

    /**
     * Subscribe a ZeroBuf object to receive updates from any connected
     * publisher.
     *
     * Every update will be directly applied on the ZeroBuf object during
     * receive(). To track updates on the object, notifyUpdated() is called
     * accordingly.
     *
     * The subscribed object instance has to be valid until unsubscribe().
     *
     * @param zerobuf the ZeroBuf object to update on receive()
     * @return true if subscription was successful, false otherwise
     */
    ZEQ_API bool subscribe( zerobuf::Zerobuf& zerobuf );

    /**
     * Unsubscribe a ZeroBuf object to stop applying updates from any connected
     * receiver.
     *
     * @param zerobuf the ZeroBuf object to stop updating on receive()
     * @return true if removal of subscription was successful, false otherwise
     */
    ZEQ_API bool unsubscribe( const zerobuf::Zerobuf& zerobuf );

private:
    detail::Subscriber* const _impl;

    // Receiver API
    void addSockets( std::vector< detail::Socket >& entries ) final;
    void process( detail::Socket& socket ) final;
    void update() final;
    void addConnection( const std::string& uri ) final;
};

}

#endif
