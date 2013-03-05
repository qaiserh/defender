/* File: randomness.cpp
   Author: Richard Eisenberg (eir@cis)
   Desc: demonstrates generating random numbers
*/

#include <cstdlib> // <-- this is the library for randomness

using namespace std;

// Call this function once before generating any random numbers
// Do not call it again!
// It uses your computer's clock to ensure that your program gets fresh
// random numbers.
void init_rand()
{
  srand(time(NULL));
}

// Returns a random number between 0 (inclusive) and limit (exclusive)
int rand_up_to(int limit)
{
  return (int)((double)rand() / RAND_MAX * limit);
}
