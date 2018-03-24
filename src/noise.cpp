#include <iostream>
#include <random>
#include <common.h>
#include <noise.h>

float* noise::white(std::default_random_engine& generator, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);

	for(uint istep = 0u; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::brownian(std::default_random_engine& generator, float start, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);
	out[0] = start;

	for(uint istep = 1u; istep != steps; ++istep){
		start += step_gen(generator);
		out[istep] = start;
	}

	return out;
}

float* noise::brownian_min_max(std::default_random_engine& generator,
								float min, float max, float amplitude, uint steps,
								float* out){
	//Using rejection sampling
	std::uniform_real_distribution<float> step_gen(- amplitude / 2.f, amplitude / 2.f);

	float start = 0.5f * (min + max);
	for(uint istep = 0u; istep != steps; ++istep){
		float random_number;
		
		do{
			random_number = step_gen(generator);
		} while((start + random_number) < min || (start + random_number) > max);
		
		start += random_number;
		out[istep] = start;
	}
	return out;
}

float* noise::perlin(std::default_random_engine& generator, uint steps, float* out){
	
}