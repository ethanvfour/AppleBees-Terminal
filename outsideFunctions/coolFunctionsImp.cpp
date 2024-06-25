#include "coolFunctions.h"

void nop()
{
    // a nop
}

void coolOutput(string wah)
{
    cout << "\033[2J\033[1;1H" << flush;
    for (int i = 0; i < wah.length(); i++)
    {
        cout << wah[i] << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void coolOutputNoClear(string wah)
{
    for (int i = 0; i < wah.length(); i++)
    {
        cout << wah[i] << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void oooScaryOutput(string wah)
{
    cout << "\033[2J\033[1;1H" << flush;
    for (int i = 0; i < wah.length(); i++)
    {
        cout << wah[i] << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void waitThisLong(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(x));
}