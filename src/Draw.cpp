/** 
 *  @file   Draw.cpp 
 *  @brief  Draw implementation, all drawing actions are commands. 
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
// #include ...
// Project header files
#include "Draw.hpp"
#include "iostream"
#include <list>

/*! \brief 	Purpose of this execue is to draw the pixel 
*		at the right place on canvas
*		
*/
bool Draw::execute(){
	if(Draw::y_cor < 0) {
		return false;
	}
	if(Draw::x_cor < 0) {
		return false;
	}
	// App app;
	// sf::Vector2i coordinate = sf::Mouse::getPosition(app.GetWindow());
    // sf::CircleShape point(50);
    // point.setPosition(coordinate.x, coordinate.y);
    // std::list<sf::CircleShape> circles;
    // circles.push_back(point);
    // point.setFillColor(sf::Color::Yellow);
	if (this->color == "red1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Red);
	}
	if (this->color == "blue1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Blue);
	}
	if (this->color == "green1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Green);
	}
	if (this->color == "black1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Black);
	}
	if (this->color == "red_alt_1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Red);
	}
	if (this->color == "blue_alt_1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Blue);
	}
	if (this->color == "green_alt_1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Green);
	}
	if (this->color == "black_alt_1") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Black);
	}
	if (this->color == "red_alt_2") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+2,Draw::y_cor+2,sf::Color::Red);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-2,Draw::y_cor-2,sf::Color::Red);
	}
	if (this->color == "blue_alt_2") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+2,sf::Color::Blue);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-2,sf::Color::Blue);
	}
	if (this->color == "green_alt_2") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+2,sf::Color::Green);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-2,sf::Color::Green);
	}
	if (this->color == "black_alt_2") {
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+1,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-1,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor+1,Draw::y_cor+2,sf::Color::Black);
		Draw::drawAppObj.GetImage().setPixel(Draw::x_cor-1,Draw::y_cor-2,sf::Color::Black);
	}
	return true;
}

/*! \brief 	Here, we undo by simply adding "white"
*	to the last location on canvas
*/
bool Draw::undo(){
	Draw::drawAppObj.GetImage().setPixel(Draw::x_cor,Draw::y_cor,sf::Color::White);
	return true;
}

//this is necessary so App, we can see which command is being added
/*! \brief 	Here, get the type of Draw command (draw, undo or redo)
*	to execute. This is used in App.Cpp
*/
std::string Draw::get_command() {
	return Draw::type_of_commandx;
}


//check if coordinates are the same or not for us to draw
//this was done in the update function of main first, but moving it here
/*! \brief 	Here, we ensure we're not drawing on same coordinate again
* @param c the other command compared to	
*/
bool Draw::check_if_equal(const Command* c){
	if(&c != nullptr) {
		const Draw* t_p = dynamic_cast<const Draw*>(c);
		//if it's draw, check to ensure it does not have same coordinates
		if(t_p->type_of_commandx=="draw") {
			if(t_p->x_cor==this->x_cor && t_p->y_cor==this->y_cor) {
				return true;
			}
		}
	}
	return false;
}
