//
// Created by chladas on 4/27/23.
//

#include "CColorizer.h"


//----------------------------------------------------------------------------------------------------------------------
std::string CColorizer::Red(const std::string & str)
{
    return "\033[1;31m" + str + "\033[0m";
}
//----------------------------------------------------------------------------------------------------------------------
std::string CColorizer::Green(const std::string & str)
{
    return "\033[1;32m" + str + "\033[0m";
}
//----------------------------------------------------------------------------------------------------------------------
std::string CColorizer::Grey(const std::string &str)
{
    return "\033[37m" + str + "\033[0m";
}
//----------------------------------------------------------------------------------------------------------------------
std::string CColorizer::Blue(const std::string & str)
{
    return "\033[34m"  + str + "\033[0m";
}
//----------------------------------------------------------------------------------------------------------------------
