#ifndef UDP_NETWORK_CLIENT_HPP
#define UDP_NETWORK_CLIENT_HPP

// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Command.hpp"
#include "Packet.hpp"

// Other standard libraries
#include <string>
#include <vector>

// Create a non-blocking UDPClient
// This clien will provide a way to connect with some server
// and send information to that server.
class UDPNetworkClient{
public:
    // Default constructor
    UDPNetworkClient();
    // Second Constructor
    UDPNetworkClient(std::string username, unsigned short port);
    // Default Destructor
    ~UDPNetworkClient();
    // Our client can attempt a UDP connection to join
    // any server so long as we know the server address and the server port.
    // Once joined, we can send commands.
    int joinServer(sf::IpAddress serverAddress, unsigned short serverPort);
    // Send data to server
    int sendCommand(Command* c);
    // Send String to server
    // We are going to provide a way to just send strings of information
    // to our server.
    int sendString(std::string s);
    // Receive data from the server
    // Additionally, we will want to be able to receive data from the
    // server that we have connected to. Ideally we are doing this
    // within a 'main loop' in our client so we do not miss any information
    // while we are connected.
    myPacket receiveData();

    // Get username
    std::string getUsername();
    // Set username
    int setUsername(std::string name);
    // Get IPAddress
    sf::IpAddress getIpAddress();
    // Get client Port
    int getPort();

private:
    // Information about our user and connection
    std::string m_username;
    // The port which we will try to communicate from
    unsigned short m_port;
    // Our clients IP Address
    sf::IpAddress m_ipAddress;
    // The server port which we will try to send information through
	unsigned short m_serverPort;
    // The server Ip address for which we will send information to.
    sf::IpAddress m_serverIpAddress;
	// A UDP Socket for our client to create an end-to-end communication
    // with another machine in the world.
    sf::UdpSocket m_socket;
};

#endif
