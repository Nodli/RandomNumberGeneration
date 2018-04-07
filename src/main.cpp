#include <iostream>
#include <ctime> //time(NULL)
#include <common.h>
#include <array.h>
#include <noise.h>
#include <random.h>
#include <vector.h>

void use_perlin2D(){
	//Sampling size ie size of the output map
	uivec2 size = {400u, 400u};

	//Coordinates of the sampling on the support map of the Perlin Noise - Should be 3 / 4 times lower than the sampling size
	fvec2 origin = {0.f, 0.f};
	fvec2 limit = {20.f, 20.f};

	uint size_export[2] = {size.x, size.y};
	float* values = new float[size.x * size.y];

	for(uint iy = 0u; iy != size.y; ++iy){
		for(uint ix = 0u; ix != size.x; ++ix){
			fvec2 world_coord = {origin.x + static_cast<float>(ix) / static_cast<float>(size.x) * (limit.x - origin.x),
									origin.y + static_cast<float>(iy) / static_cast<float>(size.y) * (limit.y - origin.y) };
			values[iy * size.x + ix] = noise::perlin2D(world_coord);
		}
	}

	array::ASCIIexport(size_export, 2, "perlin_noise.values", true);
	array::ASCIIexport(values, size.x * size.y, "perlin_noise.values", false);

	delete[] values;
}

int main(){


	return 0;
}