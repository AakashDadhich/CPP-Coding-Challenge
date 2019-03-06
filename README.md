# CPP Coding Challenge

This repository contains the code for a client-server interaction in which the client sends a plaintext message and receives the corresponding SHA-1 hash from the server. The original briefing can be seen below the build instructions. 

[It should be noted that this is a Windows-only solution.]

1. To build and run this software, first download or clone the repository to your local system. 

2. Open CPPCodingChallenge/Server.sln. Once opened, right-click the 'Source Files' folder within the Solution Explorer, and Add->Existing Item->sha1.hpp. Repeat for sha1.cpp. Now, run the solution.

3. Open CPPCodingChallenge/CPPCodingChallengeClient/Client.sln. Run the solution. 

4. Align the command prompts either side of each other. On the server's window, you should now see that a client has connect to a certain port. Within the client's window, you are prompted to enter some text. Press enter to get the corresponding hash value back.

5. It can be observed that the server will receive the message, and print out the hash value. This same hash value can then be observed in the client's window. 

[Note: Occasionally the client's message will hang. Simply restart both the client & server and it will work as normal. ]

# Original Briefing: 

Write two programs - server and client - in C or C++. They must implement the following behaviour: 
 
Server: 

•	Listens for client connections o Accepts 20 concurrent client connections (within this limit other clients must not wait) 

•	Reads a NULL ending ASCII string from the client 

•	Runs a hashing algorithm (md5, sha1 or similar) on the input for 10000 times (every round takes the result of the previous as input)

•	Sends the result back to the client 
 
Client: 

•	Accepts user input 

•	Sends data to the server 

•	Waits for reply 

•	Prints answer 
 
Code should be provided in a zip file or through a link to a remote repository containing the program sources along with some instructions on how to build and run the software. 

