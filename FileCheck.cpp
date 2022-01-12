/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: FileCheck.cpp
    Date: 6/29/20
***********************************************************************/

#include "FileCheck.h"

/***********************************************************************
    function: isExecutable
    Notes: This function finds out if the given file_name is executable
    or even exists. It will print out a message if the file does not exist
    or if the file does exist but isn't exectuable.
    I/O: input parameters: This function takes one parameter which is a
    char pointer called name.
         output parameters: This function returns a bool which is 1
         if the file name is an executable and 0 if it is not.
***********************************************************************/
bool isExecutable(char* name)
{
    const char *file = name;
    bool is_executable = false;
    bool does_exist = false;
    
    if(name[0] != '.' && name[0] != '/')
    {
        char *dup = strdup(getenv("PATH"));
        char *temp = dup;
        char *ptr = NULL;
        const char *slash = "/";
        
        // goes through each path in side the $PATH variable
        // and will set the is_executable flag to true if the 
        // program can be run at any point and does_exist
        // if at any point the full path contains a file
        do {
            ptr = strchr(temp, ':');
            if (ptr != NULL) {
                ptr[0] = 0;
            }
            char* full_path = NULL;
            full_path = (char*)malloc(strlen(temp) + strlen(file) + 2);
            strcpy(full_path,temp);
            strcat(full_path,slash);
            strcat(full_path,file);

            if(access(full_path, F_OK) != -1)
            {
                if(access(full_path, X_OK) != -1)
                {
                    is_executable = true;
                }
                does_exist = true; 
            }
            temp = ptr + 1;
        } while (ptr != NULL);

        free(dup);
    }
    else
    {
        // checks if the file exists and/or is
        // executable but this side only applies
        // to file_names that start with a ./
        // or already contain the absolute path
        if(access(name, F_OK) != -1)
        {
            if(access(name, X_OK) != -1)
            {
                is_executable = true;
            }
            does_exist = true; 
        }
    }

    // prints out useful messages about the file
    if(!does_exist)
    {
        std::cout << "File " << name << " does not exist." << std::endl;
    }
    else if(!is_executable)
    {
        std::cout << "File " << name << " does exist but is not executable." << std::endl;
    }

    return is_executable;
}
