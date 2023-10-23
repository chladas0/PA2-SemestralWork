//
// Created by chladas on 4/27/23.
//

#include "CCommandHandler.h"


//----------------------------------------------------------------------------------------------------------------------
bool CCommandHandler::ValidCommand(const std::string &command)
{
    return m_Commands.count(command);
}
//----------------------------------------------------------------------------------------------------------------------
int CCommandHandler::ConvertCommand(const std::string &command)
{
    return m_Commands[command];
}
//----------------------------------------------------------------------------------------------------------------------
CCommandHandler::CCommandHandler(const std::map<std::string, int> &commands)
    : m_Commands(commands)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCommandHandler::CCommandHandler()
    : CCommandHandler({
        {"quit", -1},
        {"save", -2},
        {"help", -3}
    })
{
}
//----------------------------------------------------------------------------------------------------------------------