#include <common.h>
#include <ctime>

namespace rand
{

  //Returns a uint seed from the second time since epoch
  inline uint time_seed();

  //Linear Congruential Generator
  //Modulus is m = 2^32 which a uint overflow is equivalent to
  uint lcg(uint seed, uint multiplier = 1103515245, uint increment = 12345);

  //Normalized Linear Congruential Generator, yields a float in [0, 1[
  float lcg_normalized(uint seed);
  double lcg_normalized_double(uint seed);

  //Linear Congruential Generator in a range, yields an int in [min, max]
  int lcg_range(int min, int max, uint seed);

}

//Implementation of inline functions
namespace rand
{

  inline uint time_seed(){
    return static_cast<uint>(time(NULL));
  }

}
