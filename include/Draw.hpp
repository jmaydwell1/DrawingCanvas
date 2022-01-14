/** 
 *  @file   Draw.hpp 
 *  @brief  Drawing actions interface. 
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
// Project header files

#include "Command.hpp"
#include "iostream"
#include "App.hpp"

// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
// 
// In our Draw class note that we have also explicitly marked the
// functions as 'override' to indicate that these functions are
// overriding the behavior of functions in a base class 
// that are implemented as virtual.


class Draw: public Command{
	private:
	App drawAppObj;
	
	
	public:
	bool execute() override;
	bool undo() override;
	int x_cor=0;
	int y_cor=0;
	int prev_x_cor = 0;
	int prev_y_cor = 0;
	std::string type_of_commandx= "";
	bool check_if_equal(const Command* c) override;
	std::string color;

	std::string get_command();

	//the following args are important so from Main, we can easily create a new command (Draw),
	//and pass in the appropriate args for the command. 
	//having default arguments for some so Draw can be constructed without  passing all args
	Draw(std::string type_of_command, 
						App& appObj, 
						int x_cor=0, 
						int y_cor=0, 
						int prev_x_cor=0, 
						int prev_y_cor=0,
						std::string color="red") 

	: 
	 x_cor(x_cor),
	 y_cor(y_cor), 
	 prev_x_cor(prev_x_cor),
	 prev_y_cor(prev_y_cor),
	 type_of_commandx(type_of_command),
	 drawAppObj(appObj),
	 color(color){};
}
;

#endif
