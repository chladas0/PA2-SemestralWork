#include <iostream>
#include "CGame.h"

int main()
{
    CGame game;
    try {
        game.run();
        return 0;
    }
    catch (const std::logic_error & e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const std::runtime_error & e){
        std::cout << e.what() << std::endl;
        return 2;
    }
}
