#include <iostream>
#include <random.h>

float* myrand::random_combination(std::default_random_engine& generator, float* input_combination, uint input_size){
	for(unsigned int step = 0; step != input_size - 1; ++step){
		std::uniform_int_distribution<unsigned int> step_gen(0, input_size - 1 - step);
		unsigned int random_index = step_gen(generator);

		float picked_value = input_combination[random_index];
		input_combination[random_index] = input_combination[input_size - 1 - step];
		input_combination[input_size - 1 - step] = picked_value;
	}
	return input_combination;
}