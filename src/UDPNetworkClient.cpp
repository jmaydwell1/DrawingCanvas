#include "UDPNetworkClient.hpp"
#include "Draw.hpp"
#include <iostream>

/*! Default Constructor
* In our constructor, we will want to setup our clients
* 1.) username
* 2.) port
*
* Then we will bind a socket to this port for which we will
* communicate over.
* Our UDPNetworkClient will be non-blocking by default
* @param username is a string that is given to name a Client
* @param port is the port of a client
*/ 
UDPNetworkClient::UDPNetworkClient(std::string username, unsigned short port){
    m_username = username;
	m_port = port;
    // Setup a socket for a UDP connection
    // Multiple computers can have the same port
    // However, the IP addresses would need to be different.
    // Listening to a port
    m_socket.bind(m_port);
    // By default socket is non-blocking
    m_socket.setBlocking(false);
}

// Default Destructor
UDPNetworkClient::~UDPNetworkClient(){
}

/*! Join a server
* For this function, we will setup the server for which we will attempt to communicate
* Since this is a UDP network, we will keep things quite simple, meaning
* we will not do any error checking to see if the server even exists.
* We simply try to send messages to a server.
*/
int UDPNetworkClient::joinServer(sf::IpAddress serverAddress, unsigned short serverPort){
    std::cout << "UDPClient will attemp to join server: " << std::endl;
    m_serverIpAddress = serverAddress;
    m_serverPort = serverPort;
}

/*! Send data to server
* Now is the fun part, for which we will attempt to send
* some data to the UDPNetworkServer.
*
* In this example, we will try to send over commands.
* @param c is a Command object
*/
int UDPNetworkClient::sendCommand(Command* c){

	myPacket p;
    // First convert the command into a draw
    Draw* d = dynamic_cast<Draw*>(c);
   
    // Store all the components of a the draw in side a packet
      p
        << m_username 
        << d->type_of_commandx 
        << d->x_cor 
        << d->y_cor 
        << d->prev_x_cor
        << d->prev_y_cor
        << d->color;
    
    // Send out the packet
    if(m_socket.send(p, m_serverIpAddress, m_serverPort) != sf::Socket::Done){
        // If the sending results in an error
        std::cout << "Client error? Wrong IP?" << std::endl; 
    }else{
        // else If the sending is successful
        std::cout << "Client(" << m_username << ") successfully sent packet to server at port : " << m_serverPort << std::endl;
        std::cout << "Client Name : " << m_username << " | " 
        << "Command Type : " << d->type_of_commandx << " | " 
        << "Command x coord : " << d->x_cor << " | " 
        << "Command y coord : " << d->y_cor << " | " 
        <<  "\n"<< std::endl;     
    }

    return 0;
}

/*! Send 'string' data to server
* As an alternative, we may want to send string messages to the server.
* This can be a quick way to log, or perhaps 'chat' with the server
* @param s is a string that is sent to a server
*/
int UDPNetworkClient::sendString(std::string s){
    if(s.length() <= 0){
        return -1;
    }
    // Here we send a specific string
    // Let's keep things interesting by forcing the client to
    // append their user name to the message they send.
    s+= " (from "+ m_username+")";

    // Note that we are sending this message to our server:serverPort
    // Note that we add 1 more charater for the NULL terminator on our string
    if(m_socket.send(s.c_str(),s.length()+1, m_serverIpAddress, m_serverPort) == sf::Socket::Done){
        std::cout << "Client(" << m_username << ") sending packet" << std::endl;
    }

}


/*! Receive data from the server
*
* As a client, we will receive data from our server.
* Clients can send '2' types of messages to server given our API.
* One type is a string, the other is our custom packet.
* We will handle both.
*
* FIXME Depending on how you want to handle returning of data
* you can modify the return type.
*/
myPacket UDPNetworkClient::receiveData(){
    // 1.) Situation 1 -- we receive a packet from sendCommand
    // Create a temporary packet and see
    // if something was received from our server
    myPacket in;

    // 2.) Situation 2 -- we receive a string from sendString
    // This situation is a little bit simpler, in that we can
    // received a fixed size message from the server.
    // For now '128' is a magic number FIXME and make me something configurable
    // :)
	// char in[128];
    // size_t received;

    sf::IpAddress copyAddress = m_serverIpAddress;
    unsigned short copyPort = m_serverPort;
	if(m_socket.receive(in,copyAddress,copyPort) == sf::Socket::Done){
        if (in.getDataSize()>0) {
	        std::cout << "Recieved a Packet from Server " << std::endl;
        }
	}
	return in;
}

// Return our username
std::string UDPNetworkClient::getUsername(){
    return m_username;
}

// Set our username
int UDPNetworkClient::setUsername(std::string name){
    m_username = name;
}

