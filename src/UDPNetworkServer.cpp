#include "UDPNetworkServer.hpp"
#include "Draw.hpp"

#include <iostream>
#include "Packet.cpp"



/*! Here we are going to 'name' our server and specify the address and port.
* It might seem a little weird to specify our own address, but we will want
* to use this information so we know where data is being received from.
* The port again we get to choose, as long as it is not previously being used
* we can use it.
* @param name name of the server
* @param address the address of the server
* @param port the port of the server 
*/
UDPNetworkServer::UDPNetworkServer(std::string name, sf::IpAddress address,unsigned short port){
	m_name = name;
	m_ipAddress = address;
	m_port = port;
	std::cout << "Server Constructor" << std::endl;
}

// Our destructor
UDPNetworkServer::~UDPNetworkServer(){
	std::cout << "Server Destructor" << std::endl;
}

/*! Start the server
*
* Here we are going to start a non-blocking UDP server.
* We'll bind to a port to see if it is available. If it is,
* then we are going to run the server forever.
*
* The key to our server will be that we are going to listen
* to where clients are communicating from, and store that information
* in a map.
*/
int UDPNetworkServer::start(){
	std::cout << "Starting UDP Network server" << std::endl;
	// Attempt to bind to a port
    int status;
    if(status = (m_socket.bind(m_port) !=sf::Socket::Done)){
		std::cout << "Unable to bind -- Error: " << status << std::endl;
        return status;
	}
    
	// Start the server
    // TODO In the future you may add reason to stop or pause the server
    // as other possible states.
	m_start = true;

    // We are going to create a non-blocking UDP server..
    m_socket.setBlocking(false);
}

std::string user_name;
myPacket UDPNetworkServer::listener(){
       // When a connection is made to our server, we get some amount of bytes
        // We store the clients ip and port that is connected
        // FIXME for now '128' is a magic number we have 'guessed' is big enough
        myPacket in;
		sf::IpAddress senderIp;
		size_t received;
		unsigned short senderPort;
		// If the server receives a message
		// then we want to broadcast that message out to
		// all potential folks who have joined our server.
		if(m_socket.receive(in, senderIp, senderPort) == sf::Socket::Done){
		    
            // Declare the components of the packet that is recieved
            
            std::string type_of_commandx;
            int x_cor;
            int y_cor;
            int prev_x_cor;
            int prev_y_cor;
            std::string color;
            // Print out to check all components of the packet that is recieved
            std::cout << "Server recieved the following Command Packet from " << user_name << std::endl;
            if (in >> user_name >> type_of_commandx >> x_cor >> y_cor >> prev_x_cor >> prev_y_cor >> color) {
                std::cout << "Command sender : " << user_name << " | " 
                <<  "Command Type : " << type_of_commandx << " | " 
                <<  "Command x coord : " << x_cor << " | " 
                <<  "Command y coord : " << y_cor << " | "  
                <<  "Command y color : " << color << " | "  
                <<  "\n" << std::endl;           
            }
            // Check if this is the first message sent by the client
            // by iterating through all of our current clients.
            // If we reach the end of the map, then we know this is a
            // new client.
            std::map<unsigned short, sf::IpAddress>::iterator clientIterator;
            clientIterator = m_activeClients.find(senderPort);
            if(clientIterator == m_activeClients.end()){
                std::cout << "First time joiner!" << std::endl;
                handleClientJoining(senderPort,senderIp); 
                // Add client to our activeClients map so we can send them more
                // messages that come in
                m_activeClients[senderPort] = senderIp;
            }
            // TODO: What happens if lots of messages are sent all at once?
            // Could this be a bottleneck?
            // One such fix, is to ha   ve each client joined as a separate thread
            // for the server which receives messages. 1 socket thus per connection
            // and then we may then also have a lock on any shared data structures.
  
        

            m_packetHistory.push_back(in);
            std::cout << "total messages: " << m_packetHistory.size() << std::endl;
            // We create an iterator that looks through our map
            // For each of our clients we are going to send to them
            // (including the client that just joined) the message that
            // was just received.
            std::map<unsigned short, sf::IpAddress>::iterator ipIterator;
            // for(ipIterator = m_activeClients.begin(); ipIterator != m_activeClients.end(); ipIterator++){
            //     m_socket.send(in, ipIterator->second, ipIterator->first);
            // }
            sendPacket(in, senderPort);
		}
        return in;
}


// Stops the server from running and removes all clients
int UDPNetworkServer::stop(){
    m_start = false;
}

/*!
* This function sends a packet from the server to all clients that are not the original sender
* @param p the packet sent to the client
* @param senderPort the original client's port
*/
int UDPNetworkServer::sendPacket(myPacket p, unsigned short senderPort) {
    std::map<unsigned short, sf::IpAddress>::iterator ipIter;
    for (ipIter = m_activeClients.begin(); ipIter != m_activeClients.end(); ipIter++) {
        if (ipIter->first != senderPort )
        {
            std::cout << "sending data to" << ipIter->first << std::endl;
            m_socket.send(p, ipIter->second, ipIter->first);
        }
    }
    return 0;
}


/*! Typically we'll want to update the client to get the log
* of all of the things that have happened.
* For a 'painting' application this is likely appropriate, for
* other applicatinos (e.g. a game) this may not be necessary.
* @param clientPort the port of the client that's joining
* @param clientIpAddress the ip address of the client that's joining
*/
int UDPNetworkServer::handleClientJoining(unsigned short clientPort, 
                                         sf::IpAddress clientIpAddress){
    std::cout << "Updating new client" << std::endl;
    // Iterate through every message sent and send it to the client.
    for(int i= 0; i < m_sentHistory.size(); i++){
        char in[128];
        m_socket.send(m_sentHistory[i].c_str(),
                      m_sentHistory[i].length()+1,  
                      clientIpAddress,
                      clientPort);
    }
}


