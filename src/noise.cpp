#include <iostream>
#include <random>
#include <cassert>
#include <noise.h>
#include <common.h>
#include <vector.h>

float* noise::white_uniform(std::default_random_engine& generator, uint steps, float* out){
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

fvec2* noise::gradient2D(std::default_random_engine& generator, uint size, fvec2* out){
	#if 0
	std::uniform_real_distribution<float> step_gen(-1.f, 1.f);

	for(uint igrad = 0; igrad != size; ++igrad){
		out[igrad].x = step_gen(generator);
		out[igrad].y = step_gen(generator);
		out[igrad] = normalize(out[igrad]);
	}
	#endif

	#if 1
	fvec2 possible_grad[8]; //Clockwise from top left
	possible_grad[0].set(-1, 1);
	possible_grad[1].set(0, 1);
	possible_grad[2].set(1, 1);
	possible_grad[3].set(1, 0);
	possible_grad[4].set(1, -1);
	possible_grad[5].set(0, -1);
	possible_grad[6].set(-1, -1);
	possible_grad[7].set(-1, 0);

	std::uniform_int_distribution<uint> step_gen(0u, 7u);
	for(uint igrad = 0; igrad != size; ++igrad){
		out[igrad] = possible_grad[step_gen(generator)];
	}
	#endif

	return out;
}
#include <array.h>
//TODO: Optimize implementation for serial calculations inside a given unit square
float noise::perlin2D(const fvec2& coord, const fvec2* gradient2D, const uivec2& gradientsize){
	//Reference frame origin is at the top left ie local frame origin is the top left corner

	const uivec2 noisesize = {gradientsize.x - 1u, gradientsize.y - 1u};

	uint corner_id[4]; //Global id of the corners in clockwise order starting from the top left corner
	grid::get_corner_global_id(coord, gradientsize, corner_id);

	fvec2 corner_coord[4]; //Global coordinates of the corners
	grid::get_corner_global_coord(coord, corner_coord);

	fvec2 corner_distance_vect[4]; //Distance to /coord/ vectors
	for(unsigned int icorner = 0u; icorner != 4; ++icorner){
		corner_distance_vect[icorner] = coord - corner_coord[icorner];
	}

	float corner_influences[4]; //Influences of each vector
	for(unsigned int icorner = 0u; icorner != 4; ++icorner){
		corner_influences[icorner] = dot(corner_distance_vect[icorner], gradient2D[corner_id[icorner]]);
	}
	//array::display(corner_influences, 4);

	fvec2 local_coord = coord - corner_coord[0];

	float interpolation_value = grid::bilinear_interpolation(corner_influences, local_coord); //@Debug - Return this directly

	return interpolation_value;

	//return 0.1f;
}

uint* grid::get_corner_global_id(const fvec2& coord,
								const uivec2& gradientsize,
								uint* out){
	out[0] = static_cast<unsigned int>(coord.y) * gradientsize.x
				+ static_cast<unsigned int>(coord.x);
	out[1] = out[0] + 1;
	out[2] = out[0] + gradientsize.x + 1;
	out[3] = out[0] + gradientsize.x;

	return out;
}

fvec2* grid::get_corner_global_coord(const fvec2& coord, fvec2* out){
	out[0].set(static_cast<float>(static_cast<unsigned int>(coord.x)),
				static_cast<float>(static_cast<unsigned int>(coord.y)));
	out[1].set(out[0].x + 1., out[0].y);
	out[2].set(out[0].x + 1., out[0].y + 1.);
	out[3].set(out[0].x, out[0].y + 1.);

	return out;
}

float grid::bilinear_interpolation(const float* values, const fvec2& coord){
	float interpolation_top = values[0] + (values[1] - values[0]) * evaluator_function(coord.x);
	float interpolation_bottom = values[3] + (values[2] - values[3]) * evaluator_function(coord.x);
	float interpolation_final = interpolation_top + (interpolation_bottom - interpolation_top) * evaluator_function(coord.y);

	return interpolation_final;
}

float grid::evaluator_function(float value){
	return ((6 * value - 15) * value + 10) * value * value * value;
}