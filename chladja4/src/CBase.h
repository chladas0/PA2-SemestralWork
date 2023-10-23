//
// Created by chladas on 4/7/23.
//
#pragma once

#include <iostream>
#include <sstream>
#include "fstream"

/// constant for AI to determine if defensive move should be played
constexpr int BASE_THRESHOLD = 20;


/**
 *      This class represents player's base. The are information about state of the base
 *      and when the base is completed or destroyed
 */
class CBase
{
public:
       CBase() = default;
       /**
        *   Method that display's information about base.
        */
       void display() const;
        /**
         *  Method that initializes base from given file.
         * @param configFile - file to initialize base from
         */
       void initFromFile (std::ifstream & configFile);
       /**
        *   Method that check if the base is completed
        * @return - true if completeness >= win bound, false otherwise
        */
       [[nodiscard]] bool isCompleted () const;
       /**
       *   Method that check if base is destroyed
       * @return - true if completeness <= loose bound, false otherwise
       */
       [[nodiscard]] bool isDestroyed () const;
       /**
        * Method that checks if the defensive move should be played.
        * @return true if the completeness is less that threshold from
        * win or lose bound. False otherwise.
        */
       [[nodiscard]] bool shouldPlayDefenseCard() const;
       /**
        *   Method that modifies completeness. It adds the amount to
        *   the completeness.
        * @param amount
        */
       void modifyCompleteness(int amount);
       /**
        * Method that saves base into file
        * @param saveFile
        */
       void Serialize (std::ofstream & saveFile) const;
private:
    /// says how much is base completed
    int    m_Completeness;
    /// if completeness goes above this bound the game is won
    int    m_WinBound;
    /// if completeness goes under this bound the game is lost
    int    m_LoseBound;
};