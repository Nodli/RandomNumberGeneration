#include <common.h>

namespace noise
{

  //White Noise
  float* white(uint& seed, uint steps, float* out);

  //Brownian Noise / Red Noise
  float* brownian(uint& seed, uint steps, float* out);
  float* brownian_min_max(float min, float max, float amplitude,
                          uint& seed, uint steps, float* out);

  //Pink noise - http://www.firstpr.com.au/dsp/pink-noise/

  //Perlin noise
  float* perlin(uint& seed, uint steps, float* out);

}
