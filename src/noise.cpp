#include <iostream>
#include <random>
#include <common.h>
#include <noise.h>

float* noise::white(std::default_random_engine& generator, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);

	for(int istep = 0; istep != steps; ++istep){
		out[istep] = step_gen(generator);
	}

	return out;
}

float* noise::brownian(std::default_random_engine& generator, float start, uint steps, float* out){
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);
	out[0] = start;

	for(int istep = 1; istep != steps; ++istep){
		start += step_gen(generator);
		out[istep] = start;
	}

	return out;
}
/*
float* noise::brownian_min_max(std::default_random_engine& generator, float min, float max, float amplitude, uint steps, float* out){
	float start = 0.5f * (min + max);
	for(int istep = 0; istep != steps; ++istep){
		float rnumber;
		do{
			rnumber = rand::lcg_range_float(seed, - amplitude / 2.f, amplitude / 2.f);
		} while((start + rnumber) < min || (start + rnumber) > max);
		start += rnumber;
		out[istep] = start;
	}
	return out;
}

float* noise::perlin(std::default_random_engine& generator, uint steps, float* out){
	
}
*/