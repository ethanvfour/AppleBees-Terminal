#ifndef COOL_FUNCTIONS
#define COOL_FUNCTIONS
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <chrono>  // for std::chrono
#include <thread>  // for std::this_thread::sleep_for



/*
A no operation
*/
void nop();

/*
Clears screen, also does some cool output
*/
void coolOutput(std::string wah);

/*
Does some cool output
*/
void coolOutputNoClear(std::string wah);

/*
Scary output ooo, also clears screen
*/
void oooScaryOutput(std::string wah);

/*
Pauses this many seconds
*/
void waitThisLong(int x);

#endif