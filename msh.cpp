/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: msh.cpp
    Date: 6/29/20
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <pwd.h>
#include "FileCheck.h"
#include "Pipes.h"
#include "ProcessString.h"

void print_prompt();
std::string get_commands();


/***********************************************************************
    Main function.
***********************************************************************/
int main()
{
    bool flag = true;
    while(flag)
    {
        std::string str_of_commands = get_commands();

        if(str_of_commands.compare("exit") == 0)
        {
            std::cout << "Goodbye. Exiting..." << std::endl;
            flag = false;
        }
        else
        {
            // parses the string of commands into tokens to be held into 
            // a vector to be easier to pull which command and its respective
            // flags is next when running the runCommands method
            std::vector<std::string> command_tokens = getTokens(str_of_commands);
            int num_commands = getCommandTotal(command_tokens);
            std::vector<int> args_per_cmd = getArgsPerCommand(command_tokens);
            runCommands(num_commands,args_per_cmd, command_tokens);
        }
    } 
}

/***********************************************************************
    function: print_prompt()
    Notes: prints the user name followed by a %(ex: cssc2103% )
    I/O: input parameters: Does not contain any input parameters.
         output parameters: none
***********************************************************************/
void print_prompt()
{
    struct passwd *passwd;
    passwd = getpwuid ( getuid()); 
    std::cout << passwd->pw_name;
    std::cout << "% ";
}

/***********************************************************************
    function: get_commands()
    Notes: Gets the commands and arguments the user wants from the user
    as a string.
    I/O: input parameters: Does not contain any input parameters.
         output parameters: Returns a std::string which is the string
         of commands and arguments.
***********************************************************************/
std::string get_commands()
{
    std::string input = "";
    print_prompt();
    std::getline(std::cin,input);
    while(input.length() == 0)
    {
        print_prompt();
        std::getline(std::cin,input);
    }
    return input;
}