#include "peer.h"
#include <fstream>

void PeerClient::SendString( std::string& message )
{
	send( socket, message.c_str(), static_cast<int>(message.size()), 0 );
}

void PeerClient::SendInt( int value )
{
	send( socket, reinterpret_cast<const char*>(&value), sizeof( value ), 0 );
}

void PeerClient::SendFloat( float value )
{
	send( socket, reinterpret_cast<const char*>(&value), sizeof( value ), 0 );
}

void PeerClient::SendDouble( double value )
{
	send( socket, reinterpret_cast<const char*>(&value), sizeof( value ), 0 );
}

void PeerClient::SendBool( bool value )
{
	char data = value ? 1 : 0; // Convert bool to char (1 for true, 0 for false)
	send( socket, &data, sizeof( data ), 0 );
}

void PeerClient::SendFile( const std::string& filePath )
{
	// Open the file
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		return;
	}
	// Read the file content into a string
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	// Send the file content
	send( socket, fileContent.c_str(), static_cast<int>(fileContent.size()), 0 );
}

void PeerClient::Send( char* data )
{
	send( socket, data, sizeof(data), 0);
}

void PeerClient::Disconnect()
{
	closesocket( socket );
}
