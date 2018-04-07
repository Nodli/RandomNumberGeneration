#include <iostream>
#include <random>
#include <cassert>
#include <noise.h>
#include <common.h>
#include <vector.h>

float* noise::white_uniform(std::mt19937& generator, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);

	for(uint istep = 0u; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::white_normal(std::mt19937& generator, uint steps, float* out){
	std::normal_distribution<float> step_gen(0.f, 1.f);

	for(uint istep = 0u; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::random_walk(std::mt19937& generator, uint steps, float* out){
	std::normal_distribution<float> step_gen(0.f, 1.f);
	out[0] = 0.;

	for(uint istep = 1u; istep != steps; ++istep){
		out[istep] = out[istep - 1] + step_gen(generator);
	}

	return out;
}

float* noise::random_walk_min_max(std::mt19937& generator,
								float min, float max, uint steps,
								float* out){
	std::normal_distribution<float> step_gen(0.f, 1.f);

	float start = 0.5f * (min + max);
	for(uint istep = 0u; istep != steps; ++istep){
		float random_number;

		//Find a sample that keeps the random walk in the range
		do{
			random_number = step_gen(generator);
		} while((start + random_number) < min || (start + random_number) > max);

		//Adding the selected sample to the Brownian Noise
		start += random_number;
		out[istep] = start;
	}

	return out;
}

float* noise::brownian_bridge(uint steps, float* random_walk){
	for(uint ivalue = 0u; ivalue != steps; ++ivalue){
		random_walk[ivalue] -=  static_cast<float>(ivalue) / static_cast<float>(steps - 1) * random_walk[steps - 1];
	}

	return random_walk;
}

float* noise::brownian_bridge_between_values(float start_value, float end_value, uint steps, float* random_walk){
	assert(start_value != end_value);

	float start_brownian = random_walk[0];
	float end_brownian = random_walk[steps - 1];

	assert(start_brownian != end_brownian);

	for(uint ivalue = 0u; ivalue != steps; ++ivalue){
		random_walk[ivalue] = start_value + (end_value - start_value) * (random_walk[ivalue] - start_brownian) / (end_brownian - start_brownian);
	}

	return random_walk;
}

/**
 * \brief Knuth's hash function
 * \details Reference: https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
 */
int hash1D(int coord){
	return coord * 2654435761;
}

/**
 * \brief Hash function for 2D coordinates
 * \details Reference: https://stackoverflow.com/questions/2634690/good-hash-function-for-a-2d-index
 */
int hash2D(ivec2 coord, int prime_constant = 6761){
	#if 1
	return (prime_constant + hash1D(coord.y)) * prime_constant + hash1D(coord.x);
	#endif

	#if 0 //Original Hash function used by Ken Perlin
	int permutation[] = { 151,160,137,91,90,15,
	    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};
	return permutation[(permutation[abs(coord.x % 256)] + coord.y) % 256];
	#endif
}

fvec2 perlin_gradient(uint value_id){
	assert(value_id < 8u);
	fvec2 gradient_value;

	switch(value_id){
		case 0: gradient_value.set(-1.f,  0.f);
			break;

		case 1: gradient_value.set(-1.f,  1.f);
			break;

		case 2: gradient_value.set( 0.f,  1.f);
			break;

		case 3: gradient_value.set( 1.f,  1.f);
			break;

		case 4: gradient_value.set( 1.f,  0.f);
			break;

		case 5: gradient_value.set( 1.f, -1.f);
			break;

		case 6: gradient_value.set( 0.f, -1.f);
			break;

		case 7: gradient_value.set(-1.f, -1.f);
			break;
	}

	return gradient_value;
}

ivec2 corner_coord(uint corner_id){
	assert(corner_id < 4u);
	ivec2 corner_value;

	switch(corner_id){
		case 0u: corner_value.set(0, 0);
			break;

		case 1u: corner_value.set(1, 0);
			break;

		case 2u: corner_value.set(1, 1);
			break;

		case 3u: corner_value.set(0, 1);
			break;
	}

	return corner_value;
}

float lerp(const float& coord, const float& valueA, const float& valueB){
	return valueA + (valueB - valueA) * coord;
}

float bilerp(const fvec2& coord, const float* values){
	float top_value = lerp(coord.x, values[0], values[1]);
	float bottom_value = lerp(coord.x, values[3], values[2]);

	return lerp(coord.y, top_value, bottom_value);
}

float perlin_fade(const float value){
	return ((6 * value - 15) * value + 10) * value * value * value;
}

float noise::perlin2D(const fvec2& coord){
	ivec2 grid_coord = { static_cast<int>(coord.x), static_cast<int>(coord.y) };
	fvec2 local_coord = { coord.x - static_cast<float>(grid_coord.x),
							coord.y - static_cast<float>(grid_coord.y)};

	std::mt19937 gradient_generator;
	std::uniform_int_distribution<int> gradient_distribution(0, 7);

	float corner_noise[4u];
	for(uint icorner = 0u; icorner != 4u; ++icorner){
		//Gradient vector
		gradient_generator.seed(hash2D(grid_coord + corner_coord(icorner)));
		uint gradient_id = gradient_distribution(gradient_generator);
		fvec2 gradient = perlin_gradient(gradient_id);

		//Distance vector
		fvec2 distance = { local_coord.x - static_cast<float>(corner_coord(icorner).x),
							local_coord.y - static_cast<float>(corner_coord(icorner).y) };

		//Corner value
		corner_noise[icorner] = dot(gradient, distance);
	}
	fvec2 interp_coord = { perlin_fade(local_coord.x), perlin_fade(local_coord.y) };
	return bilerp(interp_coord, corner_noise);
}