#include <string>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	string ip = "127.0.0.1"; // IP address of server
	int port = 54000; // Port number that server listens on

					  // initailise Windows socket (ws)
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsIsOk = WSAStartup(ver, &wsData);
	if (wsIsOk != 0)
	{
		cerr << "Unable to initalise Windows socket. Quitting." << endl;
		return 0;
	}

	// create socket
	SOCKET connSocket = socket(AF_INET, SOCK_STREAM, 0); // socket parameters using IPv4, TCP Stream, protocol
	if (connSocket == INVALID_SOCKET)
	{
		cerr << "Unable to create socket. Quitting." << endl;
		WSACleanup();
		return 0;
	}

	// bind IP and port to listenSocket
	sockaddr_in link;
	link.sin_family = AF_INET;
	link.sin_port = htons(port); // host to network short
	inet_pton(AF_INET, ip.c_str(), &link.sin_addr);

	// connect to server
	int connResult = connect(connSocket, (sockaddr*)&link, sizeof(link));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Unable to connect. Quitting." << endl;
		closesocket(connSocket);
		WSACleanup();
		return 0;
	}

	// do-while loop to send and receive data
	char buf[4096];
	string userInput;

	do
	{
		cout << "> Please enter plaintext to be hashed by the SHA1 Algorithm." << endl;
		getline(cin, userInput);

		if (userInput.size() > 0) // ensuring there is input by user
		{
			int sendResult = send(connSocket, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(connSocket, buf, 4096, 0);
				// bytesReceived = 0 if client disconnects, = -1 if error
				// so only output response if everything is connected and working 
				if (bytesReceived > 0)
				{
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);

	// close socket
	closesocket(connSocket);

	// cleanup Windows socket
	WSACleanup();

	return 0;
}