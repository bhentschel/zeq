
/* Copyright (c) 2014, Human Brain Project
 *                     Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 *                     Stefan.Eilemann@epfl.ch
 */

#define BOOST_TEST_MODULE zeq_subscriber

#include "broker.h"

#include <servus/servus.h>

using namespace zeq::vocabulary;

BOOST_AUTO_TEST_CASE(test_subscribe)
{
    zeq::Subscriber subscriber( test::buildURI( "localhost" ));
}

BOOST_AUTO_TEST_CASE(test_invalid_subscribe)
{
    BOOST_CHECK_THROW( zeq::Subscriber subscriber(
                           servus::URI( "uri//localhost" )),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeq::Subscriber subscriber2( servus::URI( "uri" )),
                       std::runtime_error );
}

BOOST_AUTO_TEST_CASE(test_registerhandler)
{
    zeq::Subscriber subscriber( test::buildURI( "localhost" ));
    BOOST_CHECK( subscriber.registerHandler( EVENT_ECHO,
                       std::bind( &test::onEchoEvent, std::placeholders::_1 )));
}

BOOST_AUTO_TEST_CASE(test_deregisterhandler)
{
    zeq::Subscriber subscriber( test::buildURI( "localhost" ));
    BOOST_CHECK( subscriber.registerHandler( EVENT_ECHO,
                       std::bind( &test::onEchoEvent, std::placeholders::_1 )));
    BOOST_CHECK( subscriber.deregisterHandler( EVENT_ECHO ));
}

BOOST_AUTO_TEST_CASE(test_invalid_registerhandler)
{
    zeq::Subscriber subscriber( test::buildURI( "localhost" ));
    BOOST_CHECK( subscriber.registerHandler( EVENT_ECHO,
                       std::bind( &test::onEchoEvent, std::placeholders::_1 )));
    BOOST_CHECK( !subscriber.registerHandler( EVENT_ECHO,
                       std::bind( &test::onEchoEvent, std::placeholders::_1 )));
}

BOOST_AUTO_TEST_CASE(test_invalid_deregisterhandler)
{
    zeq::Subscriber subscriber( test::buildURI( "localhost" ));
    BOOST_CHECK( !subscriber.deregisterHandler( EVENT_ECHO ));
    BOOST_CHECK( subscriber.registerHandler( EVENT_ECHO,
                       std::bind( &test::onEchoEvent, std::placeholders::_1 )));
    BOOST_CHECK( !subscriber.deregisterHandler(zeq::vocabulary::EVENT_EXIT ));
}

BOOST_AUTO_TEST_CASE(test_not_implemented_servus )
{
    if( servus::Servus::isAvailable( ) )
        return;

    const servus::URI uri( test::buildPublisherURI( ));
    BOOST_CHECK_THROW( zeq::Subscriber subscriber( uri ), std::runtime_error );
}
