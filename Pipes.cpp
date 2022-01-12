/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: Pipes.cpp
    Date: 6/29/20
***********************************************************************/

#include "Pipes.h"

/***********************************************************************
    function: executeProgram
    Notes: This function will run one program with it's flags. It is done
    by creating an array of char* and start pulling tokens from the index
    provided up to the num_args given and add NULL at the end.
    I/O: input parameters: This function takens in 3 parameters. tokens
    which is a vector of strings which has all the commands and arguments,
    index which gives the starting index to start extracting tokens from
    the vector and an int num_args that gives the number of tokens to store
    from the vector.
         output parameters: none
***********************************************************************/
void executeProgram(std::vector<std::string> tokens, int index, int num_args)
{
    char* args[num_args + 1];
    for(int i = 0; i < num_args;i++)
    {
        strcpy(args[i],tokens[index].c_str());
        index++;
    }
    args[num_args] = NULL;
    
    // checks if the file is executable
    if(isExecutable(args[0]))
    {
        // checks which execve to use
        if(args[0][0] == '/' || args[0][0] == '.')
        {
            execve(args[0],args,NULL);
        }
        else
        {
            execvp(args[0],args);
        }
    }
    exit(0);
}

/***********************************************************************
    function: runCommands
    Notes: This function runs all the commands provided by the tokens
    vector.
    I/O: input parameters: This function has 3 parameters. An int called
    num_of_commands which is the number of commands inside the vector of
    strings called tokens, and a vector of ints called args_per_command
    which gives the arguments each command has.
         output parameters: none
***********************************************************************/
void runCommands(int num_of_commands, std::vector<int> args_per_command,std::vector<std::string> tokens)
{
    int fd[num_of_commands - 1][2];
    for(int i = 0; i < num_of_commands - 1;i++)
    {
        pipe(fd[i]);
    }

    std::vector<int> list_of_childs;
    // if the number of commands is greater than 1 
    // work through the file descriptors and directing
    // the input and the output pipes into where they 
    // need to send the data
    int index = 0;
    for(int i = 0; i < num_of_commands;i++)
    {
        int pid = fork();
        list_of_childs.push_back(pid);
        if(pid == 0)
        {
            if(num_of_commands > 1)
            {
                if(i == 0)
                {
                    // the first child process will need to output
                    // it's data into the next child instead of printing
                    // to console
                    dup2(fd[0][1], STDOUT_FILENO);
                }
                else if(i == num_of_commands - 1)
                {
                    // the last child only needs to get it's input
                    // from the previous child and will output
                    // to the terminal
                    dup2(fd[num_of_commands - 2][0], STDIN_FILENO);
                }
                else
                {
                    // all the middle children will need to take
                    // input from the previous children
                    // and output their data to the next child
                    dup2(fd[i - 1][0], STDIN_FILENO);
                    dup2(fd[i][1], STDOUT_FILENO);
                }
                // close all the pipes as none are needed
                for(int i = 0; i < num_of_commands - 1; i++)
                {
                    close(fd[i][0]);
                    close(fd[i][1]);
                }  
            }
            executeProgram(tokens,index,args_per_command[i]);
        }
        else
        {
            // keeps track of which command it is on
            index += (args_per_command[i] + 1);
        }
    }
    
    // close the pipes created in the main process
    for(int i = 0; i < num_of_commands - 1; i++)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
    
    // waiting for children
    for(int i = 0; i < list_of_childs.size();i++)
    {
        waitpid(list_of_childs[i], NULL, 0);
    }
    
    return;
}



