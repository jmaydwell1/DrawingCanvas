/**
 *  @file   Packet.cpp
 *  @brief  Packet object stores packets of information for networking.
 *  @author Mike and Team 18
 *  @date   
 ***********************************************/

#include <SFML/Network.hpp>
#include "Command.hpp"

/*!
 * Write a command into packet.
 * @param &packet packet to store information
 * @param command the command to implement on the App
 * @return the original packet with command written
 */
sf::Packet &operator<<(sf::Packet &packet, const Command *command) {
    return packet << command;
}

/*!
 * Extract a command from packet.
 * @param &packet packet to store information
 * @param command the command to implement on the App
 * @return the original packet with command extracted
 */
sf::Packet &operator>>(sf::Packet &packet, const Command *command) {
    return packet >> command;
}
