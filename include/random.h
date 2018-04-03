#ifndef H_RANDOM
#define H_RANDOM

#include <random>
#include <common.h>

namespace myrand{

	//Randomly scrambles float values in place
	float* random_combination(std::default_random_engine& generator, float* input_combination, uint input_size);

}

#endif