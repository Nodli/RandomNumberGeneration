#ifndef H_ARRAY
#define H_ARRAY

#include <iostream>
#include <string>
#include <fstream>
#include <common.h>

namespace array
{

	template<typename T>
	void display(T* array, uint length);

	template<typename T>
	bool ASCIIexport(T* array, uint length, std::string filepath, bool clear = false);

	template<typename T>
	T* add(T* array, uint length, T& increment);

	template<typename T>
	T* add(T* arrayA, T* arrayB, uint length);

	template<typename T>
	T* multiply(T* array, uint length, T& multiplicator);

	template<typename T>
	T* set(T* array, uint length, T& value);

	template<typename T>
	T* copy(T* source, T* destination);

}

namespace array{

	template<typename T>
	void display(T* array, uint length){
		for(uint i = 0u; i != length; ++i){
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	bool ASCIIexport(T* array, uint length, std::string filepath, bool clear){
		std::ofstream ofile;
		if(clear){
			ofile.open(filepath, std::ofstream::out);
		}else{
			ofile.open(filepath, std::ofstream::out | std::ofstream::app);
		}
		
		if(!ofile.is_open()){ //Checking that the file has been opened
			return false;
		}
		
		for(uint ivalue = 0u; ivalue != length - 1; ++ivalue){
			ofile << array[ivalue] << " ";
		}
		ofile << array[length - 1] <<  std::endl;

		ofile.close();
		return true;
	}

	template<typename T>
	T* add(T* array, uint length, T& increment){
		for(uint i = 0u; i != length; ++i){
			array[i] += increment;
		}
		return array;
	}

	template<typename T>
	T* add(T* arrayA, T* arrayB, uint length){
		for(uint i = 0u; i != length; ++i){
			arrayA[i] += arrayB[i];
		}
		return arrayA;
	}

	template<typename T>
	T* multiply(T* array, uint length, T& multiplicator){
		for(uint i = 0u; i != length; ++i){
			array[i] *= multiplicator;
		}
		return array;
	}

	template<typename T>
	T* set(T* array, uint length, T& value){
		for(uint i = 0u; i != length; ++i){
			array[i] = value;
		}
		return array;
	}

	template<typename T>
	T* copy(T* source, T* destination, uint length){
		for(uint i = 0u; i != length; ++i){
			destination[i] = source[i];
		}
		return destination;
	}
}

#endif