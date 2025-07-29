#pragma once
#include <winsock.h>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <thread>

#include "serverHandler.h"
#include "serverType.h"
#include "serverState.h"
#include "peer.h"

class PeerServer
{
private: 
	SOCKET sock;                                                      // Socket for the server
	sockaddr_in serverAddress;                                        // Address of the server
	int port;                                                         // Port number for the server
	ServerType type;                                                  // Type of server (TCP or UDP)
	WSAData wsaData;                                                  // WSA data structure for Winsock
	void setState( ServerState newState );                            // Set the current state of the server
	bool isRunning;                                                   // Flag to check if the server is running
	int maxClients = 100;
	std::list<PeerClient*> clients;                                   // List of connected clients
	void checkAvaliablity();                                          // Checks to see if any clients are disconnected if so delete them from list. and close there sockets.

public:
	ServerHandler* Handler;                                           // Handler for server events
	ServerState State;                                                // Current state of the server

	PeerServer( sockaddr_in address, int port, ServerType type );     // Constructor to initialize the server with address, port, and type
	void Start();                                                     // Start the server
	void Stop();                                                      // Stop the server
	void BroadcastString( std::string& message );                     // Broadcast a string message to all clients
	void SetMaxClients( int maxClients );                             // Set the maximum number of clients allowed
	void Cleanup();                                                   // Clean up the server resources
	void SendTo( PeerClient* client, char* data );                    // Send raw data to a specific client
};