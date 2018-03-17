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
	T* add(T* array, uint length, T increment);

	template<typename T>
	T* multiply(T* array, uint length, T multiplicator);

}

namespace array{

	template<typename T>
	void display(T* array, uint length){
		for(int i = 0; i != length; ++i){
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	T* add(T* array, uint length, T increment){
		for(int i = 0; i != length; ++i){
			array[i] += increment;
		}
		return array;
	}

	template<typename T>
	T* multiply(T* array, uint length, T multiplicator){
		for(int i = 0; i != length; ++i){
			array[i] *= multiplicator;
		}
		return array;
	}

}

#endif