#include <iostream>
#include <ctime>
#include <common.h>
#include <array.h>
#include <noise.h>
#include <random.h>

int main(){
	
	//uint seed = myrand::time_seed();
	uint seed = 22u;
	
	std::default_random_engine generator{seed};
	
	uint alt_length = 10u;
	float alt[alt_length];

	noise::white(generator, alt_length, alt);
	array::display(alt, alt_length);

	noise::brownian(generator, 0., alt_length, alt);
	array::display(alt, alt_length);

	for(uint ialt = 0; ialt != alt_length; ++ialt){
		alt[ialt] = static_cast<float>(ialt);
	}

	myrand::random_combination(generator, alt, alt_length);
	array::display(alt, alt_length);

	return 0;
}
