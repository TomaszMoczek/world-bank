#include <iostream>

#include "world_bank.h"

int main (int argc, char* argv[])
{
    try
    {
        world_bank::world_bank world_bank;
        if (world_bank.enumerate())
        {
            world_bank.analyse();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
