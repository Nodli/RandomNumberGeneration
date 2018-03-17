#include <iostream>
#include <common.h>
#include <random.h>

uint rand::lcg(uint& seed, uint multiplier, uint increment){
  seed *= multiplier;
  seed += increment;
  return seed;
}

float rand::lcg_normalized_float(uint& seed){
  seed = lcg(seed);
  uint max_seed = -1; //2^32 - 1
  //Division by 2^32 while avoiding overflow, necessary with 32bit float
  return 0.5f * static_cast<float>(seed)
              / static_cast<float>((max_seed - 1) / 2 + 1);

}

double rand::lcg_normalized_double(uint& seed){
  seed = lcg(seed);
  uint max_seed = -1; //2^32 - 1
  //Division by 2^32 while avoiding overflow, using 64bit double
  return static_cast<double>(seed) / (static_cast<double>(max_seed) + 1);

}

int rand::lcg_range_int(int min, int max, uint& seed){
  float generated_number = lcg_normalized_float(seed);
  seed = lcg(seed);
  return min + static_cast<int>(generated_number * static_cast<float>(max
                                                                      - min));
}

float rand::lcg_range_float(float min, float max, uint& seed){
  float generated_number = lcg_normalized_float(seed);
  return min + generated_number * (max - min);
}
