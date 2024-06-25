#ifndef COOL_FUNCTIONS
#define COOL_FUNCTIONS
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <chrono>  // for std::chrono
#include <thread>  // for std::this_thread::sleep_for

using namespace std;

/*
A no operation
*/
void nop();

/*
Clears screen, also does some cool output
*/
void coolOutput(string wah);

/*
Does some cool output
*/
void coolOutputNoClear(string wah);

/*
Scary output ooo, also clears screen
*/
void oooScaryOutput(string wah);

/*
Pauses this many seconds
*/
void waitThisLong(int x);

#endif