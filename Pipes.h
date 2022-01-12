#pragma once

/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: Pipes.h
    Date: 6/29/20
***********************************************************************/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <string.h>
#include "FileCheck.h"

void runCommands(int num_of_commands, std::vector<int> args_per_command,std::vector<std::string> tokens);
void executeProgram(std::vector<std::string> tokens, int index, int num_args);