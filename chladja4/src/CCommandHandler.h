//
// Created by chladas on 4/27/23.
//

#pragma once

#include "iostream"
#include "map"


/**
 *      Function that holds commands and corresponding integer values.
 */
class CCommandHandler
{
public:
    /// creates instance with map of strings and corresponding values
    explicit CCommandHandler(const std::map<std::string, int> &commands);

    explicit CCommandHandler();
    /**
     *  Method that check if command is in command map
     * @param command - string to be validated
     * @return true = valid, false otherwise
     */
    bool ValidCommand(const std::string & command);
    /**
     *  Method that converts command into int
     * @param command - string to be converted
     * @return int representing the command
     */
    int ConvertCommand(const std::string & command);

private:
    /// map of commands to corresponding values
    std::map<std::string, int>            m_Commands;
};