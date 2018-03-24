#ifndef H_NOISE
#define H_NOISE

#include <random>
#include <common.h>

namespace noise
{

	//White Noise
	float* white(std::default_random_engine& generator, uint steps, float* out);

	//Brownian Noise / Red Noise
	float* brownian(std::default_random_engine& generator, float start, uint steps, float* out);
	float* brownian_min_max(std::default_random_engine& generator, float min, float max, float amplitude, uint steps, float* out);
	float* brownian_bridge(std::default_random_engine& generator, )

	//Pink noise - http://www.firstpr.com.au/dsp/pink-noise/

	//Perlin noise
	float* perlin(std::default_random_engine& generator, uint steps, float* out);

}

#endif