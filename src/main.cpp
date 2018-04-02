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

	array::ASCIIexport(x, nsteps, "brownian_bridge.values", true);
	array::ASCIIexport(y, nsteps, "brownian_bridge.values");
	#endif

	/* 2D Perlin Noise */
	uivec2 gradientsize = {20u, 20u};
	std::cout << "gradient vector size: " << gradientsize << std::endl;
	uint total_gradient_values = gradientsize.x * gradientsize.y;
	fvec2 gradient_map[total_gradient_values];

	noise::gradient2D(generator, total_gradient_values, gradient_map);
	//array::display(gradient_map, total_gradient_values);

	uivec2 noisesize = {gradientsize.x - 1u, gradientsize.y - 1u};
	std::cout << "noise grid size: " << noisesize << std::endl;

	uint sample_per_unit = 50u;
	uint total_samples = noisesize.x * noisesize.y * sample_per_unit * sample_per_unit;
	std::cout << "total grid samples: " << total_samples << std::endl;
	float noise_values[total_samples];


	for(unsigned int icell = 0; icell != total_samples; ++icell){
		fvec2 icoord = {static_cast<float>(icell % (noisesize.x * sample_per_unit)) / static_cast<float>(sample_per_unit) + 0.5f / sample_per_unit,
						static_cast<float>(icell / (noisesize.x * sample_per_unit)) / static_cast<float>(sample_per_unit) + 0.5f / sample_per_unit};
		noise_values[icell] = noise::perlin2D(icoord, gradient_map, gradientsize);
		//std::cout << "icell: " << icell << " icoord: " << icoord << " value: " << noise_values[icell] << std::endl;
	}

	std::string file_path = "perlin_noise.values";
	std::ofstream ofile(file_path, std::ofstream::out);
	ofile << "#size: " << noisesize.x * sample_per_unit << " " << noisesize.y * sample_per_unit << std::endl;
	ofile.close();

	array::ASCIIexport(noise_values, total_samples, file_path);
	return 0;
}