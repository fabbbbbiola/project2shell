# shell

by James Ko and Fabiola Radosav

Features:
	Parses and executes commands
	Prints current working directory
	Handles input with command list

Attempted:
	To split commands on quotes and semicolons
	To print a current working directory prompt in linux format. Couldn't figure out how to separate it so that the "/"s and the unnecessary directory info wouldn't print.
	Could not get pipes to work

Bugs:
			
	
Files & Function Headers:
input.c
	Handles the input and turns it into a readable line
	/*======== char* get_input() ==========
	Inputs:  void
	Returns: char* temp 

	Gets input in a string and copies it into a new string with null ending
	If input is not available or unreadable, returns error message
	====================*/

command.c
	
	/*======== char ** serparate_on()==========
	Inputs:  char *needle
		 char* input
		 size_t* sepv_size
	Returns: Array of strings with parsed commands 

	====================*/

	/*======== void exec_command() ==========
	Inputs:  command cmd
	Returns: void

	Executes commands read from parsed string
	====================*/

input_handler.c
	
	/*======== void handle_input() ==========
	Inputs:  char* input
	Returns: void 

	
	====================*/	
