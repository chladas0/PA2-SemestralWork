//
// Created by chladas on 4/27/23.
//

#pragma once

#include "string"

/**
 *      Simple class to hold functions to colorize strings. It adds escape sequence to the string
 *      to make it colorful and then another sequence to reset it.
 */
class CColorizer
{
public:
    /// colorizes the string to the red color
    static std::string Red(const std::string & str);

    /// colorizes the string to the green color
    static std::string Green(const std::string & str);

    /// colorizes the string to the grey color
    static std::string Grey(const std::string & str);

    /// colorizes the string to the blue color
    static std::string Blue(const std::string &str);
};
