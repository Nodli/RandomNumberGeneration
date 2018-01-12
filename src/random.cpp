#include <common.h>
#include <random.h>
#include <iostream>

namespace rand
{

  uint lcg(uint seed, uint multiplier, uint increment){
    seed *= multiplier;
    seed += increment;
    return seed;
  }

  float lcg_normalized(uint seed){
    seed = lcg(seed);
    uint max_seed = -1; //2^32 - 1
    //Division by 2^32 while avoiding overflow, necessary with 32bit float
    return 0.5f * static_cast<float>(seed)
                / static_cast<float>((max_seed - 1) / 2 + 1);

  }

  double lcg_normalized_double(uint seed){
    seed = lcg(seed);
    uint max_seed = -1; //2^32 - 1
    //Division by 2^32 while avoiding overflow, using 64bit double
    return static_cast<double>(seed) / (static_cast<double>(max_seed) + 1);

  }

  int lcg_range(int min, int max, uint seed){
    return min + static_cast<int>(lcg_normalized(seed)
                                  * static_cast<float>(max));
  }

}
