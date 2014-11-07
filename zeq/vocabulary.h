
/* Copyright (c) 2014, Human Brain Project
 *                     Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 */

#ifndef ZEQ_VOCABULARY_H
#define ZEQ_VOCABULARY_H

#include <zeq/types.h>

namespace zeq
{

/**
 * An application specific vocabulary of supported events including their
 * serialization. The implementation is dependend on a certain serialization
 * backend, which is flatbuffers by default. Events in the vocabulary are
 * identified by a 128 bit unique identifier, which should be created through
 * lunchbox::make_uint128() using a unique string formed using the fully
 * qualified class name, including namespaces, of the event, e.g.,
 * lunchbox::make_uint128( "mynamespace::ExcitingEvent" ).
 */
namespace vocabulary
{
using lunchbox::make_uint128;

/** @group The supported event types by this vocabulary */
//@{
static const uint128_t EVENT_EXIT( make_uint128( "zeq::ExitEvent" ));
static const uint128_t EVENT_CAMERA( make_uint128( "zeq::CameraEvent" ));
static const uint128_t EVENT_SELECTION( make_uint128( "zeq::SelectionEvent" ));
static const uint128_t EVENT_INVALID( make_uint128( "zeq::InvalidEvent" ));
//@}

/**
 * Serialize the given camera matrix into an Event of type camera.
 * The matrix to be serialized and sent to other instances is the one
 * used in the application to transform from world coordinate space into
 * camera space. Microns are assumed as unit and it has the BBP circuit
 * as reference.
 * @param matrix the 4x4 camera matrix in OpenGL data layout
 * @return the serialized event
 */
Event serializeCamera( const std::vector< float >& matrix );

/**
 * Deserialize the given camera event into the 4x4 matrix.
 * The matrix received and deserialized is the one used in the application
 * to transform from world coordinate space into camera space.
 * Microns are assumed as unit and it has the BBP circuit as reference.
 * @param camera the camera event generated by serializeCamera()
 * @return the 4x4 camera matrix in OpenGL data layout
 */
std::vector< float > deserializeCamera( const Event& camera );

/**
 * Serialize the given selection into an Event of type selection.
 * @param selection vector of ids (uint)
 * @return the serialized event
 */
Event serializeSelection( const std::vector< unsigned int >& selection );

/**
 * Deserialize the given selection event into the vector of ids.
 * @param selection the selection event generated by serializeSelection()
 * @return the vector of ids (uint)
 */
std::vector< unsigned int > deserializeSelection( const Event& selection );

}
}

#endif
