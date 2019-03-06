#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;


int main() 
{
	// initailise Windows socket (ws)
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int port = 54000;

	int wsIsOk = WSAStartup(ver, &wsData);
	if (wsIsOk != 0)
	{
		cerr << "Unable to initalise Windows socket. Quitting." << endl;
		return 0;
	}

	// create socket
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0); // socket parameters using IPv4, TCP Stream, protocol
	if (listenSocket == INVALID_SOCKET)
	{
		cerr << "Unable to create socket. Quitting." << endl;
		WSACleanup();
		return 0;
	}

	// bind IP and port to listenSocket
	sockaddr_in link;
	link.sin_family = AF_INET;
	link.sin_port = htons(port); // host to network short
	link.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listenSocket, (sockaddr*)&link, sizeof(link));

	// tell WinSock to use socket for listening
	listen(listenSocket, 20); // max 20 connections backlogged

	// accept incoming client connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(listenSocket, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Client socket invalid. Quitting." << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}

	char host[NI_MAXHOST]; // client name
	char service[NI_MAXSERV]; // connected port 
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	// close listening socket to only have 1 client
	closesocket(listenSocket);

	// while loop: accept and send hash message back
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0); // collect client message
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting." << endl;
			return 0;
		}
		
		if (bytesReceived == 0)
		{
			cerr << "Client disconnected." << endl;
			break;
		}

		// hash client message using sha1

		send(clientSocket, buf, bytesReceived + 1, 0); // echo message back to client
	}

	// close socket
	closesocket(clientSocket);	

	// cleanup Windows socket
	WSACleanup();
	return 0;
}