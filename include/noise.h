#ifndef H_NOISE
#define H_NOISE

#include <random>
#include <common.h>
#include <vector.h>

namespace noise
{

	/**
	 * \brief Returns /steps/ independant values of White Noise
	 * \details Values are taken from an Uniform Distribution.
	 */
	float* white_uniform(std::default_random_engine& generator, uint steps, float* out);

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

	//TODO: Refactor this as a usable Perlin Noise

	/**
	 * \brief Generates random unitary gradient vectors
	 */
	fvec2* gradient2D(std::default_random_engine& generator, uint size, fvec2* out);
	/**
	 * \brief Builds a 2D Perlin Noise using a 2D Gradient Map
	 * \details Reference: http://flafla2.github.io/2014/08/09/perlinnoise.html
	 * \param[in] gradient2D Array of unitary vectors, must have a size of (gridsize.x + 1, gridisze.y + 1)
	 *							as it stores the gradient vectors in the corner of the grid cells.
	 * \param[in] gridsize Number of cells per row & column
	 */
	float perlin2D(const fvec2& coord, const fvec2* gradient2D, const uivec2& gridsize);

}

//TODO: Refactor these as a class / namespace for further use

namespace grid
{
	//TODO: Rename these functions to be reusable in another context
	uint* get_corner_global_id(const fvec2& coord, const uivec2& gradientsize, uint* out);
	fvec2* get_corner_global_coord(const fvec2& coord, fvec2* out);

	/**
	 * \brief Interpolated /values/ at coord
	 * \details /values/ are the values at the corners on a regular cartesian grid of size (1x1)
	 * 			/Values/ are given in clockwise order starting from the top left corner
	 */
	float bilinear_interpolation(const float* values, const fvec2& coord);
	float evaluator_function(float value);
}
#endif