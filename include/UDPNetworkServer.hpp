#ifndef UDP_NETWORK_SERVER_HPP
#define UDP_NETWORK_SERVER_HPP

// We are going to build a UDP Server abstracted
// over SFML's sockets. We can think of this as a 'Network Manager' class for us.
// Building a general network manager is really cool, because
// we can reuse it for other projects. And depending on our domain,
// we can potentially write this part of the code in a completely
// different language. Remember, in our networking application we
// are just passing data back and forth between two endpoints after all.

// Some nice resources to learn more about packet sending can be found:
// https://www.sfml-dev.org/tutorials/2.5/network-packet.php


// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Command.hpp"

// Other standard libraries
#include <string>
#include <vector>
#include "Packet.hpp"

// Create a non-blocking UDP server
class UDPNetworkServer{
public:
    // Default Constructor
    UDPNetworkServer();
    // Second Constructor
    UDPNetworkServer(std::string name,sf::IpAddress address, unsigned short port);
    // Default Destructor
    ~UDPNetworkServer();

    // Start the server
    int start();
    // Stops the server from running and removes all clients
    int stop();

    int sendPacket(myPacket p, unsigned short senderPort);

    myPacket listener();
private:

    // What to do when the client joins the server
    int handleClientJoining(unsigned short clientPort, sf::IpAddress clientIpAddress);
    // What to do when the client leaves the server
    int handleClientLeaving();
   
	// Name for our server
	std::string m_name; 
    // Flag for if the server should stop.
    bool m_start;
    // Ip Address for our UDP Server
    sf::IpAddress m_ipAddress;
    unsigned short m_port;
    // A UDP Socket for our server
    sf::UdpSocket m_socket;

    // A data structure to hold all of the clients.
	// The first parameter is the port from which 
	// data was received.
	// The second is the IpAddress of the client.
    std::map<unsigned short, sf::IpAddress> m_activeClients;
    // A data structure to hold all of the packets
    std::vector<myPacket> m_packetHistory;
    // A data structure to hold all of the messages sent
    std::vector<std::string> m_sentHistory;


};

#endif
