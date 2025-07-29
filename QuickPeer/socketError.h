#pragma once
#ifndef SOCKETERROR_H
#define SOCKETERROR_H
#include <string>
enum class SocketError
{
	ConnectFailed,                // Failed to connect to the server
	ListenFailed,                 // Failed to start listening for incoming connections
	AcceptFailed,                 // Failed to accept an incoming connection
	BindFailed,                   // Failed to bind the socket to an address
	SendFailed,                   // Failed to send data through the socket
	ReadFailed,                   // Failed to read data from the socket
	 
	InvalidSocket,                // The socket is invalid or has been closed
	DisconnectWithoutHandling,    // The socket was disconnected without proper handling
};
#endif