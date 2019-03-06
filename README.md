# CPP Coding Challenge
 
Write two programs - server and client - in C or C++.  
 
They must implement the following behaviour: 
 
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

