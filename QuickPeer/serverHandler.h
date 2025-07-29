#pragma once

#include <string>

#include "socketError.h"

#ifndef QUICKPEER_SERVERTYPE_H
class ServerHandler 
{
public:
	virtual void OnStarted() = 0;                                                       // Called when the server starts successfully
	virtual void OnStopped() = 0;                                                       // Called when the server stops successfully
	virtual void OnError( const std::string& errorMessage, SocketError errorType ) = 0; // Called when an error occurs, with a message and an error type
	virtual void OnClientConnect( void* client ) = 0;                                   // Called when a client connects, with a pointer to the client
	virtual void OnClientDisconnect( void* client ) = 0;                                // Called when a client disconnects, with a pointer to the client
	virtual void OnClient( void* client ) = 0;                                              // Called when a client is handled, with a pointer to the client
};
#define QUICKPEER_SERVERTYPE_H
#endif