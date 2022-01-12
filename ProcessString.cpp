/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: ProcessString.cpp
    Date: 6/29/20
***********************************************************************/

#include "ProcessString.h"

/***********************************************************************
    function: getTokens
    Notes: Separates the string str into tokens which are either a command,
    a argument or a pipe(|).
    I/O: input parameters: This function takes in one parameter which is
    a string called str which is the string given by the  user that has
    the commands they wish to run.
         output parameters: This function returns a vector of strings
         which has all the tokens.
***********************************************************************/
std::vector<std::string> getTokens(std::string str)
{
    size_t pos = 0;
    std::string token;
    std::string delimiter = " ";
    std::vector<std::string> list_of_tokens;
    std::vector<int> args_per_command;

    // trim whitespace from left and right side
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last - first + 1));

    // ensure each token has one space between
    str = removeExtraSpaces(str);

    // store all the commands with arguments in a vector list
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        list_of_tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    
    token = str.substr(0,str.length());
    list_of_tokens.push_back(token);

    return list_of_tokens;
}

/***********************************************************************
    function: removeExtraSpaces
    Notes: This functions removes all extra spaces from a string so that
    there are no leading or trailing white spaces and there is only one
    space between each argument, pipe, and command.
    I/O: input parameters: This function takes in one parameter which is
    a string called str. str is the string that will be adjusted.
         output parameters: This function returns a string which is 
         the newly formatted string.
***********************************************************************/
std::string removeExtraSpaces(std::string str)
{  
    int i = 1;
  
    while(i < str.length())
    {
        if(str.at(i) == ' ' && str.at(i - 1) == ' ')
        {
            str.erase(i,1);
        }
        else
        {
            i++;
        }
    }

    return str; 
}

/***********************************************************************
    function: getCommandTotal
    Notes: This function gets the total commands that are inside a vector
    of tokens by searching for the pipes(|).
    I/O: input parameters: This function has one parameter which is a 
    vector of strings called tokens.
         output parameters: This function returns an int which is the 
         number of commands a vector of tokens has.
***********************************************************************/
int getCommandTotal(std::vector<std::string> tokens)
{
    int num_of_commands = 1;

    for(int i = 0; i < tokens.size(); i++)
    {
        std::string str1 = tokens.at(i);
        if(str1.compare("|") == 0)
        {
            num_of_commands++;
        }
    }

    return num_of_commands;
}

/***********************************************************************
    function: getArgsPerCommand
    Notes: This functions runs how many arguments each command has.
    I/O: input parameters: This function has one parameter which is a
    a vector of strings called tokens.
         output parameters: This function returns a vector of ints
         which holds how many arguments each command has.
***********************************************************************/
std::vector<int> getArgsPerCommand(std::vector<std::string> tokens)
{
    std::vector<int> args_per_command;
    int count = 0;

    for(int i = 0; i < tokens.size(); i++)
    {
        std::string str1 = tokens.at(i);
        if(str1.compare("|") == 0)
        {
            args_per_command.push_back(count);
            count = 0;
        }
        else
        {
            count++;
        }
    }

    args_per_command.push_back(count);
    return args_per_command;
}