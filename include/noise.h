#ifndef H_NOISE
#define H_NOISE

#include <random>
#include <common.h>

namespace noise
{

	/**
	 * \brief Returns /steps/ independant values of White Noise
	 * \details Values are taken from an Uniform Distribution.
	 */
	float* white(std::default_random_engine& generator, uint steps, float* out);

	/**
	 * \brief Returns /steps/ independant values of White Noise
	 * \details Values are taken from a Standard Normal Distribution.
	 */
	float* white_normal(std::default_random_engine& generator, uint steps, float* out);

	/**
	 * \brief Returns /steps/ iterations of a Random Walk
	 * \details The step values are taken from a Standard Normal Distribution 
	 */
	float* random_walk(std::default_random_engine& generator, uint steps, float* out);

	/**
	 * \brief Random Walk in the range [min; max]
	 * \details Uses Rejection Sampling to stay in the range.
	 */
	float* random_walk_min_max(std::default_random_engine& generator, float min, float max, uint steps, float* out);

	/**
	 * \brief Builds a Brownian Bridge with a zero mean using a Random Walk.
	 * \details The Brownian Bridge is built in place
	 */
	float* brownian_bridge(uint steps, float* random_walk);
	/**
	 * \brief Builds a Brownian Bridge connecting two values using a Random walk
	 * \details Sampling of a linear curve between the two points using the values of the Brownian Noise.
	 *			Reference: https://twitter.com/gabrielpeyre/status/968038241927614464
	 */
	float* brownian_bridge_between_values(float start_value, float end_value, uint steps, float* brownian_values);

	//Pink noise - http://www.firstpr.com.au/dsp/pink-noise/

	//Perlin noise
	float* perlin(std::default_random_engine& generator, uint steps, float* out);

}

#endif