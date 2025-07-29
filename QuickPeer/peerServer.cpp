#include "peerServer.h"


void PeerServer::setState( ServerState newState )
{
	this->State = newState;
}

void PeerServer::checkAvaliablity()
{
	for (auto client : clients)
	{
		if (send( client->getSocket(), "ping", 4, 0 ) == SOCKET_ERROR)
		{
			if (Handler != NULL)
			{
				Handler->OnError( "Client disconnected without handling", SocketError::DisconnectWithoutHandling );
			}

			closesocket( client->getSocket() );
			clients.remove( client );
			delete client;
		}
	}
}

PeerServer::PeerServer( sockaddr_in address, int port, ServerType type )
{
	this->serverAddress = address;
	this->port = port;
	this->type = type;
	this->clients = std::list<PeerClient*>();

	setState( ServerState::SettingUp );

	int wsa = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );

	if (wsa < 0)
	{
		if (Handler != NULL)
		{
			Handler->OnError( "Failed to initialize Winsock", SocketError::InvalidSocket );
			exit( 1 );
		}
	}
	else
	{
		switch (type)
		{
			case ServerType::Tcp:
				this->sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
				break;
			case ServerType::Udp:
				this->sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
				break;
		}

		if (sock == INVALID_SOCKET)
		{
			WSACleanup();
			
			if (Handler != NULL)
			{
				Handler->OnError( "Failed to initialize socket", SocketError::InvalidSocket );
				exit( 1 );
			}
		}
	}
}

void PeerServer::Start()
{
	if(bind(sock, (sockaddr*)&serverAddress, sizeof(serverAddress) ) == SOCKET_ERROR)
	{
		if (Handler != NULL)
		{
			Handler->OnError( "Failed to bind socket", SocketError::BindFailed );
			exit(1);
		}
	}

	listen( sock, SOMAXCONN );

	setState( ServerState::Started );

	if(Handler != NULL)
	{
		Handler->OnStarted();
	}

	while (isRunning)
	{
		setState( ServerState::WaitingForClients );

		sockaddr_in clientAddress;
		int clientSize = sizeof( clientAddress );
		SOCKET clientSocket = accept( sock, (sockaddr*)&clientAddress, &clientSize );

		if(clientSocket == INVALID_SOCKET)
		{
			if (Handler != NULL)
			{
				Handler->OnError( "Failed to accept client connection", SocketError::AcceptFailed );
				continue;
			}
		}

		PeerClient* client = new PeerClient( clientAddress, clientSocket );

		if (Handler != NULL)
		{
			Handler->OnClientConnect( &client );
		}

		clients.push_back( client );

		std::thread clientThread( [this, client]() {
			if (Handler != NULL)
			{
				Handler->OnClient( client );
			}

			std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
			setState( ServerState::WaitingForClients );

			if (Handler != NULL)
			{
				Handler->OnClientDisconnect( client );
			}
			delete client;
		} );

		clientThread.detach();
	}
}

void PeerServer::Stop()
{
	WSACleanup();
	setState( ServerState::Stopped );
	if (Handler != NULL)
	{
		Handler->OnStopped();
	}
	for (auto client : clients)
	{
		closesocket( client->getSocket() );
		clients.remove( client );
		if (client != nullptr)
		{
			delete client;
		}
	}

	closesocket( sock );
}

void PeerServer::BroadcastString( std::string& message )
{
	checkAvaliablity();

	for (auto client : clients)
	{
		if (send( client->getSocket(), message.c_str(), message.size(), 0 ) == SOCKET_ERROR)
		{
			if (Handler != NULL)
			{
				Handler->OnError( "Failed to send message to client", SocketError::SendFailed );
			}
		}
	}
}

void PeerServer::SetMaxClients( int maxClients )
{
	this->maxClients = maxClients;
}

void PeerServer::Cleanup()
{
	Stop();
	for (auto client : clients)
	{
		client->Disconnect();
		clients.remove( client );
	}
}

void PeerServer::SendTo( PeerClient* client, char* data )
{
	if( client == nullptr || client->getSocket() == INVALID_SOCKET )
	{
		if (Handler != NULL)
		{
			Handler->OnError( "Invalid client socket", SocketError::InvalidSocket );
		}
		return;
	}
	send( client->getSocket(), data, sizeof( data ), 0 );
}
