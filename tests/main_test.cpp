/**
 *  @file   main_test.cpp 
 *  @brief  Unit Tests for our program
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

#define CATCH_CONFIG_MAIN

// #include "catch_amalgamated.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include <iostream>
#include <string>
#include <map>
#include "catch.hpp"

void initialization(void){
    std::cout << "Starting the App" << std::endl;
}
/*! \brief  Initialize and destroy the program
*       
*/
TEST_CASE("init and destroy"){  
    App testAppObj;
    testAppObj.Init(&initialization);
    // Destroy our app
    testAppObj.Destroy();
}
 /*! \brief Undo and redo stack size test
 *      
 */
TEST_CASE("check if you can call redo before an undo") {
    App testAppObj;
   testAppObj.Init(&initialization);
   testAppObj.AddCommand(new Draw("redo",testAppObj));
   int test = testAppObj.GetUndoSize();
   REQUIRE(test==0);
}
/*! \brief check if right command is being called 
*       
*/
TEST_CASE("check if the right command is being called") {
    App testAppobj;
    Draw testDrawObj("undo",testAppobj);
    testAppobj.Init(&initialization);
    auto test = testDrawObj.get_command();
    REQUIRE(test=="undo");
}
/*! \brief check if undo color is white 
*       
*/
TEST_CASE("check if undo color is white") {
    App testAppobj;
    testAppobj.Init(&initialization);
    testAppobj.AddCommand(new Draw("draw",testAppobj,100,100,0,0));
    testAppobj.AddCommand(new Draw("undo",testAppobj));
    auto col = testAppobj.GetImage().getPixel(100,100);
    REQUIRE(col==sf::Color::White);
}


TEST_CASE("EXTRA Feature: check if redo color is Red") {
    App testAppobj;
    testAppobj.Init(&initialization);
    testAppobj.AddCommand(new Draw("draw",testAppobj,200,200,0,0, "red_alt_1"));
    
    auto col = testAppobj.GetImage().getPixel(200,200);
    auto col1 = testAppobj.GetImage().getPixel(200+1,200+1);
    auto col2 = testAppobj.GetImage().getPixel(200-1,200-1);
    // std::cout << "col = " << col << std::endl;
    REQUIRE(col==sf::Color::Red);
    REQUIRE(col1==sf::Color::Red);
    REQUIRE(col2==sf::Color::Red);
}


TEST_CASE("EXTRA Feature: check if draw color is green") {
    App testAppobj;
    testAppobj.Init(&initialization);
    testAppobj.AddCommand(new Draw("draw",testAppobj,200,200,0,0, "green_alt_1"));
    
    auto col = testAppobj.GetImage().getPixel(200,200);
    auto col1 = testAppobj.GetImage().getPixel(200+1,200+1);
    auto col2 = testAppobj.GetImage().getPixel(200-1,200-1);
    // std::cout << "col = " << col << std::endl;
    REQUIRE(col==sf::Color::Green);
    REQUIRE(col1==sf::Color::Green);
    REQUIRE(col2==sf::Color::Green);
}


TEST_CASE("EXTRA Feature: check if draw color is blue") {
    App testAppobj;
    testAppobj.Init(&initialization);
    testAppobj.AddCommand(new Draw("draw",testAppobj,200,200,0,0, "blue_alt_1"));
    
    auto cola = testAppobj.GetImage().getPixel(200,200);
    auto colb = testAppobj.GetImage().getPixel(200+1,200+1);
    auto colc = testAppobj.GetImage().getPixel(200-1,200-1);
    // std::cout << "col = " << col << std::endl;
    REQUIRE(cola==sf::Color::Blue);
    REQUIRE(colb==sf::Color::Blue);
    REQUIRE(colc==sf::Color::Blue);

}

TEST_CASE("Networking Test: Check Client can send a command and server can reciev a command"){
    App* app =  new App();
    UDPNetworkServer* newServer = new UDPNetworkServer("Server Name",sf::IpAddress::getLocalAddress(),50000);
    app->udpServer = newServer;
	app->udpServer->start();
    std::string uname = "test";
    unsigned short port = 50001;
    UDPNetworkClient* newClient = new UDPNetworkClient(uname,port);
    Command* newCmd = new Draw ("draw",*app, 1,1,1,1, "red");
    app->udpClient = newClient;
    app->udpClient->joinServer(sf::IpAddress::getLocalAddress(),50000);
    app->udpClient->sendCommand(newCmd);
    myPacket recieved_p;
    while(recieved_p.getDataSize() == 0){
        recieved_p =app->udpServer->listener();
    }
    REQUIRE(recieved_p.getDataSize()>0);
}


