#include "peer.h"
#include <fstream>

bool PeerClient::SendString( std::string& message )
{
	return Send<std::string>( message );
}

bool PeerClient::SendInt( int value )
{
	return Send<int>( value );
}

bool PeerClient::SendFloat( float value )
{
	return Send<float>( value );
}

bool PeerClient::SendDouble( double value )
{
	return Send<double>( value );
}

bool PeerClient::SendBool( bool value )
{
	return Send<bool>( value );
}

bool PeerClient::SendFile( const std::string& filePath )
{
	// Open the file
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		return false;
	}
	// Read the file content into a string
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	// Send the file content
	
	return Send<std::string>( fileContent );
}

template<typename T>
bool PeerClient::Send( const T &value )
{
	return send( socket, reinterpret_cast<const char *>(&value), sizeof( T ), 0 ) != SOCKET_ERROR;
}

void PeerClient::Disconnect()
{
	closesocket( socket );
}