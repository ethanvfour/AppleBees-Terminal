#include "coolFunctions.h"

void nop()
{
    // a nop
}

void coolOutput(std::string wah)
{
    std::cout << "\033[2J\033[1;1H" << std::flush;
    for (int i = 0; i < wah.length(); i++)
    {
        std::cout << wah[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void coolOutputNoClear(std::string wah)
{
    for (int i = 0; i < wah.length(); i++)
    {
        std::cout << wah[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void oooScaryOutput(std::string wah)
{
    std::cout << "\033[2J\033[1;1H" << std::flush;
    for (int i = 0; i < wah.length(); i++)
    {
        std::cout << wah[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void waitThisLong(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(x));
}