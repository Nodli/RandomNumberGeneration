#include <iostream>
#include <ctime>
#include <common.h>
#include <array.h>
#include <noise.h>

int main(){
	
	uint seed = time(NULL);
	
	std::default_random_engine generator{seed};
	
	float alt[10];
	noise::white(generator, 10, alt);
	array::display(alt, 10);

	noise::brownian(generator, 0., 10, alt);
	array::display(alt, 10);


	
/*
	noise::brownian_min_max(0.f, 20.f, 5, seed, 1000u, alt)[10];
	array::add(alt, 1000u, -10.f);
	array::display(alt, 1000u);
*/
	

	return 0;
}
