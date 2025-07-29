#pragma once

#ifndef QUICKPEER_SERVERCLIENT_H
#define QUICKPEER_SERVERCLIENT_H

#include <winsock.h>
#include <string>

class PeerClient
{
private:
	sockaddr_in address;
	SOCKET socket;

public:
	PeerClient( sockaddr_in addr, SOCKET sock )
		: address( addr ), socket( sock ) {
	}                                                            // Constructor to initialize the client with address and socket

	SOCKET getSocket() { return socket; }                        // Get the socket associated with the client
	sockaddr_in getAddress() { return address; }                 // Get the address associated with the client
	std::string getAddress2() { inet_ntoa( address.sin_addr ); } // Get the address as a string

	void SendString( std::string& message );                      // Send a string message to the server
	void SendInt( int value );                                    // Send an integer value to the server
	void SendFloat( float value );                                // Send a float value to the server
	void SendDouble( double value );                              // Send a double value to the server
	void SendBool( bool value );                                  // Send a boolean value to the server
	void SendFile( const std::string& filePath );                 // Send a file to the server
	
	void Send( char* data );                                      // Send raw data to the server.
	void Disconnect();                                            // Disconnect the client from the server
};
#endif