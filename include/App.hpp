/** 
 *  @file   App.hpp 
 *  @brief  App class interface
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef APP_HPP 
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include "Command.hpp"
#include "UDPNetworkClient.hpp"
#include "UDPNetworkServer.hpp"

// Project header files
// #include ...

// Singleton for our Application called 'App'.
class App{
private:
// Member variables
	 std::stack<Command*> m_undo;
	 std::stack<Command*> m_commands_stack;
	// Main image	
	 sf::Image* m_image= new sf::Image;
	// Create a sprite that we overaly
	// on top of the texture.
	 sf::Sprite* m_sprite= new sf::Sprite;
	// Texture sent to the GPU for rendering
	 sf::Texture* m_texture = new sf::Texture;
	// Our rendering window
     sf::RenderWindow* m_window = nullptr;
	 
	// Member functions
	// Default constructor which is hidden in the Singleton
	
	// Store the address of our funcion pointer
	// for each of the callback functions.	

	//pointers to the callback 
	std::function<void(void)> m_initFunc;
    std::function<void(App& app)> m_updateFunc;
    std::function<void(App& app)> m_drawFunc;

public:
	App();
	// Member Variables	
	// Keeps track of the previous mouse and current mouse positions
	// 'pmouse' is where the mouse previously was.
	// 'mouse' records where the mouse currently is.
	// Note: Occassinally I break my rules of always having a getter/setter
	//	 function for each member variable if there's reason to.
	//   	 There is some overhead associated with calling these functions,
	// 	 and even with 'inline' there is no gaureentee that the functions
	//  	 do get inlined. Other commercial and open source APIs seem
	// 	 to do this on occassion--use your disgression and expression to
	// 	 make an informed choice if exposuing these variables is safe, fast,
	// 	 and going to be more maintainable in the long run. In the end--it's 
	// 	 still risky to expose anything as public.
	unsigned int pmouseX=0, pmouseY=0, mouseX=0, mouseY=0;
	int command_size, command_index;
	
	UDPNetworkClient* udpClient;
	UDPNetworkServer* udpServer;

	bool isServer;
	bool isActive;

	std::string color = "red";
	// Member functions
	//for the assignment, we may be required to refactor some of these member functions
	void 	AddCommand(Command* c);
	void 	ExecuteCommand();
	int GetStackSize();
	int GetUndoSize();

	//these are all just getters to ensure singleton; one image, one texture, and one window
	sf::Image& GetImage();
	sf::Texture& GetTexture();
	sf::RenderWindow& GetWindow();

	void Destroy();
	
	//this is an example of a function pointer 
	//void Init(void (*initFunction)(void));
	void Init(std::function<void(void)> m_initFunc);
	void UpdateCallback(std::function<void(App& app)> m_updateFunc);
	void DrawCallback(std::function<void(App& app)> m_drawFunc);
	void Loop();

};


#endif
