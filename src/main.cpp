/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// g++ -std=c++17 *.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
//
// Note:    If your compiler does not support -std=c++17, 
//      then try -std=c++14 then -std=c++11.
//      
// HOW TO RUN
//
// ./App


// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <map>
#include <string.h> // for memset
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "UDPNetworkServer.hpp"
#include "UDPNetworkClient.hpp"
#include <list>


/*! \brief  Call any initailization functions here.
*       This might be for example setting up any
*       global variables, allocating memory,
*       dynamically loading any libraries, or
*       doing nothing at all.
*       
*/
void initialization(void){
    std::cout << "Starting the App" << std::endl;
}




/*! \brief  The update function presented can be simplified.
*       I have demonstrated two ways you can handle events,
*       if for example we want to add in an event loop.
*  @param app is an app object     
*/
void update(App& app){
	// Update our canvas
	sf::Event event;
    
    app.GetWindow().setActive(false);
    

    // If the instance of the app is not a server
    // in other words, it's a client
    // Then run recieveData, which essencially fetches shared data
    std::string username;
        if(!app.isServer ){
            myPacket p ;
            p = app.udpClient->receiveData();
            if (p.getDataSize() > 0){
                // Declare different components of the command
                std::string type_of_commandx;
                int x_cor;
                int y_cor;
                int prev_x_cor;
                int prev_y_cor;
                std::string color;
                // parse out all components of the packet to clone to a command
                if (p >> username >> type_of_commandx >> x_cor >> y_cor >> prev_x_cor >> prev_y_cor >> color) {
                        Command* newCmd = new Draw (type_of_commandx,app,x_cor,y_cor,prev_x_cor,prev_y_cor,color);
                        app.AddCommand(newCmd);
                }
            }
        }


	while(app.GetWindow().pollEvent(event) && !app.isServer){
		if(event.type == sf::Event::MouseButtonPressed){			
			// Modify the pixel
			app.mouseX = event.mouseMove.x; 
			app.mouseY = event.mouseMove.y; 
			app.GetImage().setPixel(app.mouseX,app.mouseY,sf::Color::White);
		}
	}

	// We can otherwise handle events normally
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !app.isServer){
       
		sf::Vector2i coordinate = sf::Mouse::getPosition(app.GetWindow());
       
        Command* newCmd = new Draw ("draw",app,coordinate.x,coordinate.y,app.pmouseX,app.pmouseY, app.color);
        if(!app.isServer){
            myPacket pNew = myPacket();
            app.AddCommand(newCmd);
            app.udpClient->sendCommand(newCmd);
            std::cout << "This Client is Sending a new Command" << std::endl;
        }
	}
    
	// escape key to exit program
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !app.isServer){
		exit(EXIT_SUCCESS);
	}
	
	//if z, then call the undo command from App's Execute
	if(event.type==sf::Event::KeyReleased && !app.isServer) {
        std::cout <<"In line 121" << std::endl;
		if(event.key.code==sf::Keyboard::Z) {
			std::cout <<"calling undo"<<std::endl;
            app.udpClient->sendCommand(new Draw("undo",app));
            app.AddCommand(new Draw("undo",app));
		}

	}
	// //if y, then call the redo command from App's Execute
	if(event.type==sf::Event::KeyReleased && !app.isServer) {
		if(event.key.code==sf::Keyboard::Y) {
			std::cout <<"calling redo"<<std::endl;
            app.udpClient->sendCommand(new Draw("redo",app));
			app.AddCommand(new Draw("redo",app));
		}
	}
	
	// Where was the mouse previously before going to the next frame
	app.pmouseX = app.mouseX;
	app.pmouseY = app.mouseY;
}



/*! \brief  The draw call 
*   @param app is an App object
*/
void draw(App& app){
	// Static variable 
	static int refreshRate = 0;
	++refreshRate;	// Increment 
	// We load into our texture the modified pixels	
	// But we only do so every 10 draw calls to reduce latency of transfer
	// between the GPU and CPU.
	// Ask yourself: Could we do better with sf::Clock and refresh once
	// every 'x' frames? 
	if(refreshRate>10){
		app.GetTexture().loadFromImage(app.GetImage());	
		refreshRate =0;
	}
}


/*! \brief  The startServer call starts a server
*           The server listens to a port and accepts clients
*   @param app is an App object
*/
void startServer(App* app){
    UDPNetworkServer* newServer = new UDPNetworkServer("Server Name",sf::IpAddress::getLocalAddress(),50000);
    app->udpServer = newServer;
    // Create a server 
    // Run the server on local network for now
	app->udpServer->start();
    while (true){
       myPacket p;
       p =app->udpServer->listener();
    }

}


/*! \brief  The startClietn call starts a client
*           The client sends commands to a server
*   @param app is an App object
*/
void startClient(App* app){
    // Create a client and have them join
    std::string uname;
    unsigned short port;
    std::cout << "Enter your username:";
    std::cin >> uname;
    std::cout << "Which port will you try? (e.g. 50001-50010):";
    std::cin >> port;
    // FIXME Ideally in a real world application, a client would
    // never have to 'guess' which ports are open on a server.
    // One could improve this code by communicating with the server
    // what ports are 'open' for connection in the 'joinServer' function.
    // For now, we will create clients that can simply join however!
    UDPNetworkClient* newClient = new UDPNetworkClient(uname,port);
    app->udpClient = newClient;
    app->udpClient->joinServer(sf::IpAddress::getLocalAddress(),50000);
    app->udpClient->setUsername(uname);
    app->udpClient->sendString("Hello, "+uname+" is joining!");
  
}


/*! \brief  The start App call starts a App
*          
*   @param app is an App object
*/
void startApp (App* app){
    // Call any setup function
    // Passing a function pointer into the 'init' function.
    // of our application.
    app->Init(&initialization);
    // Setup your keyboard
    app->UpdateCallback(&update);
    // Setup the Draw Function
    app->DrawCallback(&draw);
    // Call the main loop function
    app->Loop();
    // Destroy our app
    app->Destroy();
}
 

/*! \brief  The entry point into our program.
*       
*/
int main(){
    App* app =  new App();
    // Stores a role of either a server or client user.
    std::string role;

    // Set the role
    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    // The std::cin function records the '\n' character,
    // so I instead just look at the first character of
    // the user input.
    // A 'trim' function may be more ideal.
    if(role[0] == 's'){
        app->isServer = true;
        startServer(app);
    }else if(role[0] == 'c'){
        app->isServer= false;
        startClient(app);
        startApp(app);
    }
    return 0;
}

