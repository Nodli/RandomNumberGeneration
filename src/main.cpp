#include <iostream>
#include <ctime>
#include <common.h>
#include <array.h>
#include <noise.h>
#include <random.h>

float* linear_sampling(float valueA, float valueB, uint array_size, float* array){
	for(uint i = 0u; i != array_size; ++i){
		float linear_interp_coeff = static_cast<float>(i) / static_cast<float>(array_size - 1);
		array[i] = valueA * (1.f - linear_interp_coeff) + valueB * linear_interp_coeff;
	}
}

int main(){
	
	uint seed = 0u;
	std::default_random_engine generator{seed};
	
	#if 0
	uint a_length = 10u;
	float a[a_length];
	float ida[a_length];
	for(uint i = 0u; i != a_length; ++i){
		ida[i] = static_cast<float>(i);
	}

	//noise::white(generator, a_length, a);
	//array::display(a, a_length);

	//noise::white_normal(generator, a_length, a);
	//array::display(a, a_length);

	//noise::random_walk(generator, a_length, a);
	//array::display(a, a_length);

	//noise::random_walk_min_max(generator, 0.f, 2.f, a_length, a);
	//array::display(a, a_length);

	//noise::brownian_bridge(a_length, a);
	//array::display(a, a_length);

	//noise::brownian_bridge_between_values(-1.f, 1.f, a_length, a);
	//array::display(a, a_length);

	//array::ASCIIexport(ida, a_length, "brownian_bridge.txt", true);
	//array::ASCIIexport(a, a_length, "brownian_bridge.txt");

	//myrand::random_combination(generator, ida, a_length);
	//array::display(ida, a_length);
	#endif

	/**/
	uint nsteps = 100;
	float y[nsteps];
	float x[nsteps];
	for(uint i = 0u; i != nsteps; ++i){
		x[i] = static_cast<float>(i);
	}

	noise::random_walk_min_max(generator, 0, nsteps, nsteps, y);
	noise::brownian_bridge_between_values(0., 10., nsteps, y);
	array::ASCIIexport(x, nsteps, "brownian_bridge.txt", true);
	array::ASCIIexport(y, nsteps, "brownian_bridge.txt");


	/* 2D Random Path between two points */
	#if 0
	float startx = 0.;
	float starty = 0.;

	float endx = 1.;
	float endy = 1.;

	uint nsteps = 100;
	float x[nsteps];
	float y[nsteps];

	noise::random_walk(generator, nsteps, x);
	noise::brownian_bridge_between_values(startx, endx, nsteps, x);
	array::display(x, nsteps);

	noise::random_walk(generator, nsteps, y);
	noise::brownian_bridge_between_values(starty, endy, nsteps, y);
	array::display(y, nsteps);

	array::ASCIIexport(x, nsteps, "brownian_bridge.txt", true);
	array::ASCIIexport(y, nsteps, "brownian_bridge.txt");
	#endif

	return 0;
}
