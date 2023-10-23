//
// Created by chladas on 5/7/23.
//

#include "../src/CBase.h"
#include "../src/CColorizer.h"
#include "../src/CBaseChange.h"
#include "../src/CCard.h"

int main ()
{
    //--------------------------------------------- test-0 -------------------------------------------------------------
    CBase testBase;

    std::ofstream testOut("test.txt");
    testOut << 40 << "," << 0 << "," << 100 << std::endl << std::endl;
    testOut.close();

    std::ifstream testIn("test.txt");
    std::cout   << "Test 0 - base init - valid | ";

    try{
        testBase.initFromFile(testIn);
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    catch (...) {
        std::cout << CColorizer::Red("Failed");
        std::remove("test.txt");
    }
    //--------------------------------------------- test-1 -------------------------------------------------------------
    CBaseChange testChange;

    std::cout << "Test 1 - base change init - valid | ";

    try{
        std::istringstream issTest(",100");
        testChange.Read(issTest);
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    catch(...)
    {
        std::cout << CColorizer::Red("Failed")<< std::endl;
        std::remove("test.txt");
    }
    //--------------------------------------------- test-2 -------------------------------------------------------------
    CCard testCard;

    std::ofstream testOut2("test.txt");
    testOut2 << "Refiller" << "," << "Crystals" << "," << 10 << "|" << 0 << "," << 6 << "|f," << 2 << std::endl;
    testOut2.close();

    std::ifstream testIn2("test.txt");
    std::cout   << "Test 2 - card init - valid | ";

    try {
        testCard.initFromFile(testIn2, {"Magician"}, {"Crystals"});
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    catch (...)
    {
        std::cout << CColorizer::Red("Failed") << std::endl;
        std::remove("test.txt");
    }
    //--------------------------------------------- test-3 -------------------------------------------------------------
    std::shared_ptr<CCard> testCard3 = std::make_shared<CCard>();

    std::ofstream testOut3("test.txt");
    testOut3 << "Refiller" << "," << "Crystals" << "," << 10 << "|" << 0 << "," << 6 << "|" << "f" << "," << 2 << std::endl;
    testOut3.close();

    std::ifstream testIn3("test.txt");
    std::cout   << "Test 3 - card operator = | ";

    try {
        testCard3->initFromFile(testIn3, {"Magician"}, {"Crystals"});

        CCard x = *testCard3;

        if(x.getEffects()[0] == testCard3->getEffects()[0])
            std::cout << CColorizer::Red("Failed") << std::endl;
        else
            std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    catch (...)
    {
        std::cout << CColorizer::Red("Failed") << std::endl;
        std::remove("test.txt");
    }

    //--------------------------------------------- test-4 -------------------------------------------------------------
    CBase testBase4;

    std::ofstream testOut4("test.txt");
    testOut4 << 40 << "," << 0 << 100 << std::endl << std::endl;
    testOut4.close();

    std::ifstream testIn4("test.txt");
    std::cout   << "Test 4 - base init - missing indent | ";

    try{
        testBase4.initFromFile(testIn4);
        std::cout << CColorizer::Red("Failed");
        std::remove("test.txt");
    }
    catch (...) {
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    //--------------------------------------------- test-5 -------------------------------------------------------------
    CBaseChange testChange5;

    std::cout << "Test 5 - base change init - missing value | ";

    try{
        std::istringstream issTest5(",");
        testChange5.Read(issTest5);
        std::cout << CColorizer::Red("Failed")<< std::endl;
        std::remove("test.txt");
    }
    catch(...)
    {
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    //--------------------------------------------- test-6 -------------------------------------------------------------
    CCard testCard6;

    std::ofstream testOut6("test.txt");
    testOut6 << "Refiller" << "," << "," << 10 << "|" << 0 << "," << 6 << "|f," << 2 << std::endl;
    testOut6.close();

    std::ifstream testIn6("test.txt");
    std::cout   << "Test 6 - card init - missing resource | ";
    try {
        testCard6.initFromFile(testIn6, {"Test"}, {"Test"});
        testCard6.Display();
        std::cout << CColorizer::Red("Failed") << std::endl;
        std::remove("test.txt");
    }
    catch (...)
    {
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
    //--------------------------------------------- test-7 -------------------------------------------------------------
    CCard testCard7;

    std::ofstream testOut7("test.txt");
    testOut7 << "Refiller" << "," << "Crystals"<< "," << 10 << "|" << 0 << "," << 6 << "|f," << 2 << std::endl;
    testOut7.close();

    std::ifstream testIn7("test.txt");
    std::cout   << "Test 7 - card init - unknown resource | ";
    try {
        testCard7.initFromFile(testIn7, {"Test"}, {"Weapons"});
        std::cout << CColorizer::Red("Failed") << std::endl;
        std::remove("test.txt");
    }
    catch (...)
    {
        std::cout << CColorizer::Green("OK") << std::endl;
        std::remove("test.txt");
    }
}
