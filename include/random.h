#ifndef H_RANDOM
#define H_RANDOM

#include <ctime>
#include <random>
#include <common.h>

namespace myrand{

	//Returns the time in seconds since epoch as an uint
	inline uint time_seed();

	//Randomly scrambles float values in place
	float* random_combination(std::default_random_engine& generator, float* input_combination, uint input_size);

}

//Inline definitions
inline uint myrand::time_seed(){
	return static_cast<uint>(time(NULL));
}

#endif