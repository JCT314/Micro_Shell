#pragma once

/***********************************************************************
    Name:           Jose Toscano - cssc2103

    Class: CS 570, Spring 2020
    Professor: Professor Leonard
    Project: Assignment #2, MicroShell
    File: ProcessString.h
    Date: 6/29/20
***********************************************************************/

#include <string.h>
#include <vector>
#include <string>

std::vector<std::string> getTokens(std::string str);
std::string removeExtraSpaces(std::string str);
int getCommandTotal(std::vector<std::string> tokens);
std::vector<int> getArgsPerCommand(std::vector<std::string> tokens);