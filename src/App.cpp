/** 
 *  @file   App.cpp 
 *  @brief  Main class for program
 *  @author Mike and Monil 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// Including Nuclear Dependencies
#define GL_SILENCE_DEPRECATION
#define NK_SFML_GL2_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400


// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <cassert>
#include <stack>
#include <queue>
#include<iostream>
#include <ostream>
// Project header files
#include "App.hpp"
#include "Draw.hpp"
// Nuclear GUI
#include "nuklear.h"
#define NK_SFML_GL2_IMPLEMENTATION
#include "nuklear_sfml_gl2.h"
#include <list>


App appObj;


/*!
 * \brief This is a constructor that starts an App instance.
 * 
 */
App::App(){}


/*! \brief Purpose of this method is to
*		add the command to our stack and then just
*		call execute, which would do the command
*/
//everytime we add a command, this function will be called
void App::AddCommand(Command* c){
	
	//add the command to the stack
	m_commands_stack.push(c);
	
	//call execute
	ExecuteCommand();
}


/*! \brief The purpose of this function is to	
*		use the command_stack to take in the
*		top most command, figure out what type
*		of conmmand it is, and then perform the command. 
*/

//this simple "recieves" the command from Add, checks which one is it through Draw,
//and calls the appropriate command through Draw. 
void App::ExecuteCommand(){
	//get the latest command that is in the stack, so we can deal with it one by one
	Command* c = m_commands_stack.top();
	//check if that top most command is draw, undo, or redo.
	std::string command_type = dynamic_cast<Draw*>(c)->get_command();
	
	//if undo do this
	if (command_type == "undo") {
	//remove the most recently added command from the stack as we're undoing
	m_commands_stack.pop();

	//then, get the top most command, hold it and put it in the undo stack which can be
	//later used for redo
	if(m_commands_stack.size()>0) {
		Command* t_c = m_commands_stack.top();
		m_commands_stack.pop();

		//push the top most command to the undo stack now and then perform undo
		m_undo.push(t_c);
		t_c ->undo();
	}
}

if(command_type=="draw") {
	//draw and then remove from undo stack
	c->execute();
	while(!m_undo.empty()){
		m_undo.pop();
	}
}

if (command_type == "redo") {
	//remove the most recently added command from the stack
	m_commands_stack.pop();
	
	//check if there's anything in the undo stack for us to redo
	if(m_undo.size()>0) {

		Command* t_c = m_undo.top();
		m_undo.pop();

		//push the top most command to the command stack so we can redo
		m_commands_stack.push(t_c);

		//"redo" is just putting the pixels back on so we can use execute.
		t_c ->execute();
	}
}
}



/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*		
*/
sf::Image& App::GetImage(){
	return *m_image;

}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*		
*/
sf::Texture& App::GetTexture(){
	return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*		
*/
sf::RenderWindow& App::GetWindow(){
	return *m_window;
}

/*! \brief 	Destroy we manually call at end of our program.
*		
*/
void App::Destroy(){
	delete m_image;
	delete m_sprite;
	delete m_texture;
}




//Nuclear GUI Global Variables
enum {RED, BLACK,GREEN,BLUE,WHITE,RED_ALT1,BLACK_ALT1,GREEN_ALT1,BLUE_ALT1,RED_ALT2,BLACK_ALT2,GREEN_ALT2,BLUE_ALT2};
static int op = RED;

/*! \brief This is a layout spec member variable
*
* @param ctx is a context object
* @param bg is a object that's associated with color in the Nuclear GUI
*/
void drawLayout(struct nk_context* ctx, struct nk_colorf& bg){

    /* GUI */
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 320, 320),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);
        // if (nk_button_label(ctx, "button"))
        //     fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "red", op == RED)){
            op = RED;
        }
        if (nk_option_label(ctx, "black", op == BLACK)){
             op = BLACK;
        }
        if (nk_option_label(ctx, "green", op == GREEN)){
             op = GREEN;
        }
        if(nk_option_label(ctx,"blue",op == BLUE)){
            op = BLUE;
        }
		if(nk_option_label(ctx,"eraser",op == WHITE)){
            op = WHITE;
		}
		if(nk_option_label(ctx,"red alt 1",op == RED_ALT1)){
            op = RED_ALT1;
		}
		if(nk_option_label(ctx,"black alt 1",op == BLACK_ALT1)){
            op = BLACK_ALT1;
		}
		if(nk_option_label(ctx,"green alt 1",op == GREEN_ALT1)){
            op = GREEN_ALT1;
		}
		if(nk_option_label(ctx,"blue alt 1",op == BLUE_ALT1)){
            op = BLUE_ALT1;
		}
		if(nk_option_label(ctx,"red alt2",op == RED_ALT2)){
            op = RED_ALT2;
		}
		if(nk_option_label(ctx,"black alt2",op == BLACK_ALT2)){
            op = BLACK_ALT2;
		}
		if(nk_option_label(ctx,"green alt2",op == GREEN_ALT2)){
            op = GREEN_ALT2;
		}
		if(nk_option_label(ctx,"blue alt2",op == BLUE_ALT2)){
            op = BLUE_ALT2;
		}
    }
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    nk_end(ctx);
}


/*! \brief This is the Init Funnction
*
* @param initFunc is a function pointer set in main.cpp
*/
void App::Init(std::function<void(void)> initFunc){
	// Create our window
	m_window = new sf::RenderWindow(sf::VideoMode(600,400),"Mini-Paint alpha 0.0.2",sf::Style::Titlebar);
	m_window->setVerticalSyncEnabled(true);
	// Create an image which stores the pixels we will update
	m_image->create(600,400,sf::Color::White);
	assert(m_image != nullptr && "m_image != nullptr");
	// Create a texture which lives in the GPU and will render our image
	m_texture->loadFromImage(*m_image);
	assert(m_texture != nullptr && "m_texture != nullptr");
	// Create a sprite which is the entity that can be textured
	m_sprite->setTexture(*m_texture);
	assert(m_sprite != nullptr && "m_sprite != nullptr");
	// Set our initialization function to perform any user
	// initialization
	//in this function pointer, we're storing the address/pointer of this init function
	//this means our App singleton class knows about this intialization -> ok, why is this important?
	m_initFunc = initFunc;
}

/*! \brief 	Set a callback function which will be called
*		each iteration of the main loop before drawing.
*	@param updateFunction is a function pointer set in main.cpp	
*/
void App::UpdateCallback(std::function <void(App& app)> updateFunction){
	m_updateFunc = updateFunction;
	
}

/*! \brief 	Set a callback function which will be called
*		each iteration of the main loop after update.
*   @param drawFunction is a function pointer set in main.cpp
*/
//change this
void App::DrawCallback(std::function<void(App& app)> drawFunction){
	m_drawFunc = drawFunction;
}



/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*		
*/
void App::Loop()
{
	sf::ContextSettings settings(24, 8, 4, 2, 2);
	sf::RenderWindow gui_window(sf::VideoMode(600,400), "GUI Window",sf::Style::Default,settings);
	gui_window.setVerticalSyncEnabled(true);
	// gui_window.setActive(true);
	glViewport(0, 0, gui_window.getSize().x, gui_window.getSize().y);
	struct nk_context *ctx;
	ctx = nk_sfml_init(&gui_window);
	// Load Fonts: if none of these are loaded a default font will be used
	//Load Cursor: if you uncomment cursor loading please hide the cursor
	struct nk_font_atlas *atlas;
	nk_sfml_font_stash_begin(&atlas);
	nk_sfml_font_stash_end();
	// Setup a color for the nuklear gui
	struct nk_colorf bg;
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 0.5f;
	
	// Call the init function
	m_initFunc();
	// Start the main rendering loop

	while (m_window->isOpen() && gui_window.isOpen())
	{
		sf::Event event;
		
        nk_input_begin(ctx);
	 	while (gui_window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				nk_sfml_shutdown();
				gui_window.close();
				exit(EXIT_SUCCESS);
			}else if (event.type==sf::Event::KeyReleased) {
				if(event.key.code==sf::Keyboard::Escape){
					nk_sfml_shutdown();
					gui_window.close();
					exit(EXIT_SUCCESS);
				}
			}
			nk_sfml_handle_event(&event);
		}
		nk_input_end(ctx);
		drawLayout(ctx, bg);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			// Capture mouse coordinates
			sf::Vector2i coords = sf::Mouse::getPosition(*m_window);
			if(coords.x < WINDOW_WIDTH && coords.y < WINDOW_HEIGHT && coords.x > 0 && coords.y > 0){
				// Now we can modify our image based on the mouse position
				// and our current paint brush.

				int color = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
				if(op==RED){
					this->color = "red1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Red);
				}
				
				if(op==BLACK){
					this->color = "black1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Black);
					
				}
				if(op==GREEN){
					this->color = "green1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Green);
				}
				if(op==BLUE){
					this->color = "blue1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Blue);
				}
				if(op==WHITE){
					this->color = "white";
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::White);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::White);
					m_image->setPixel(coords.x+2,coords.y+2,sf::Color::White);
					m_image->setPixel(coords.x-2,coords.y-2,sf::Color::White);
				}
				if(op==RED_ALT1){
					this->color = "red_alt_1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Red);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Red);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Red);
					
				}
				if(op==BLACK_ALT1){
					this->color = "black_alt_1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Black);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Black);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Black);
				}

				if(op==GREEN_ALT1){
					this->color = "green_alt_1";
					m_image->setPixel(coords.x,coords.y,sf::Color::Green);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Green);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Green);
				}		
				if(op==BLUE_ALT1){
					this->color = "blue_alt_1 ";
					m_image->setPixel(coords.x,coords.y,sf::Color::Blue);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Blue);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Blue);
				}
				if(op==RED_ALT2){
					this->color = "red_alt_2";
					m_image->setPixel(coords.x,coords.y,sf::Color::Red);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Red);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Red);
					m_image->setPixel(coords.x+2,coords.y+2,sf::Color::Red);
					m_image->setPixel(coords.x-2,coords.y-2,sf::Color::Red);
					
				}
				if(op==BLACK_ALT2){
					this->color = "black_alt_2";
					m_image->setPixel(coords.x,coords.y,sf::Color::Black);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Black);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Black);
					m_image->setPixel(coords.x+2,coords.y+2,sf::Color::Black);
					m_image->setPixel(coords.x-2,coords.y-2,sf::Color::Black);
					
				}
				if(op==GREEN_ALT2 || this->color == "green_alt_2"){
					this->color = "green_alt_2";
					m_image->setPixel(coords.x,coords.y,sf::Color::Green);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Green);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Green);
					m_image->setPixel(coords.x+2,coords.y+2,sf::Color::Green);
					m_image->setPixel(coords.x-2,coords.y-2,sf::Color::Green);
					
				}
				if(op==BLUE_ALT2){
					this->color = "blue_alt_2";
					m_image->setPixel(coords.x,coords.y,sf::Color::Blue);
					m_image->setPixel(coords.x+1,coords.y+1,sf::Color::Blue);
					m_image->setPixel(coords.x-1,coords.y-1,sf::Color::Blue);
					m_image->setPixel(coords.x+2,coords.y+2,sf::Color::Blue);
					m_image->setPixel(coords.x-2,coords.y-2,sf::Color::Blue);
				}
				// We load into our texture the modified mpixels
				m_texture->loadFromImage(*m_image);
			}
		}
		// gui_window.setActive(true);
		gui_window.clear();
		glClearColor(bg.r, bg.g, bg.b, bg.a);
		glClear(GL_COLOR_BUFFER_BIT);
		nk_sfml_render(NK_ANTI_ALIASING_ON);
		gui_window.display();
		nk_sfml_render(NK_ANTI_ALIASING_ON);

		// Clear the window
		m_window->clear();
		// Updates specified by the user
		m_updateFunc(*this);
		// Additional drawing specified by user
		m_drawFunc(*this);
		// Update the texture
		// Note: This can be done in the 'draw call'
		// Draw to the canvas

		m_window->draw(*m_sprite);
		// Display the canvas
		m_window->display();
	}
}

	int App::GetStackSize() {
		return m_commands_stack.size();
	}
	int App::GetUndoSize() {
		return m_undo.size();
	}

