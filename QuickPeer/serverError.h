#pragma once

#ifndef SERVER_HANDLER_H
enum class ServerError
{
	ClientUnhanledDisconnect,              // Client disconnected without proper handling
	ClientSentInvaildData,                 // Client sent data that is not recognized or is malformed

	ReadError,                             // Error occurred while reading data from the client
	WriteError,                            // Error occurred while writing data to the client

	BufferOverflow,                        // Buffer overflow occurred while processing data
};
#define	SERVER_HANDLER_H
#endif