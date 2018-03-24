#ifndef H_ARRAY
#define H_ARRAY

#include <iostream>
#include <common.h>

//TODO: increment & numtiplicator should be references.
//      float and int types should be specialized templates to use copy.

namespace array
{

	template<typename T>
	void display(T* array, uint length);

	template<typename T>
	T* add(T* array, uint length, T& increment);

	template<typename T>
	T* multiply(T* array, uint length, T& multiplicator);

	template<typename T>
	T* set(T* array, uint length, T& value);

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
	T* add(T* array, uint length, T& increment){
		for(uint i = 0u; i != length; ++i){
			array[i] += increment;
		}
		return array;
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

}

#endif