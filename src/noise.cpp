#include <iostream>
#include <random>
#include <cassert>
#include <common.h>
#include <noise.h>

float* noise::white(std::default_random_engine& generator, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);

	for(uint istep = 0u; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::white_normal(std::default_random_engine& generator, uint steps, float* out){
	std::normal_distribution<float> step_gen(0.f, 1.f);

	for(uint istep = 0u; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::random_walk(std::default_random_engine& generator, uint steps, float* out){
	std::normal_distribution<float> step_gen(0.f, 1.f);
	out[0] = 0.;

	for(uint istep = 1u; istep != steps; ++istep){
		out[istep] = out[istep - 1] + step_gen(generator);
	}

	return out;
}

float* noise::random_walk_min_max(std::default_random_engine& generator,
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


float* noise::perlin(std::default_random_engine& generator, uint steps, float* out){
	
}