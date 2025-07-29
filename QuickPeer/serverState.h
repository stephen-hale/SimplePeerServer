#pragma once

#ifndef QUICKPEER_SERVERSTATE_H
#define QUICKPEER_SERVERSTATE_H
enum class ServerState
{
	Stopped,   // The server is stopped
	Started,   // The server is started and running
	SettingUp, // The server is in the process of setting up
	WaitingForClients, // The server is waiting for clients to connect
};
#endif