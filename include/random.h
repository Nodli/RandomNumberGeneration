#include <common.h>
#include <ctime>

namespace rand
{

  //Returns an uint seed from the second time since epoch
  inline uint time_seed();

  //Linear Congruential Generator
  //Modulus is m = 2^32 which a uint overflow is equivalent to
  uint lcg(uint& seed, uint multiplier = 1103515245u, uint increment = 12345u);

  //Normalized Linear Congruential Generators - value in [0, 1[
  float lcg_normalized_float(uint& seed);
  double lcg_normalized_double(uint& seed);

  //Linear Congruential Generator in a range - value in [min, max]
  int lcg_range_int(int min, int max, uint& seed);
  float lcg_range_float(float min, float max, uint& seed);

}

//Implementation of inline functions
inline uint rand::time_seed(){
  return static_cast<uint>(time(NULL));
}
