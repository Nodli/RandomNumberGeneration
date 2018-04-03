#ifndef H_ARRAY
#define H_ARRAY

#include <iostream>
#include <string>
#include <fstream>
#include <common.h>

namespace array
{

	template<typename T>
	void display(T* src, uint length);

	/**
	 * \brief Exports the content of an array to a file
	 * \details The array is exported as a line of the file separated by whitespaces
	 * \param[in] overwrite true: overwrites the file with the array content
	 *						false: appends the array content to the file
	 */
	template<typename T>
	bool ASCIIexport(T* src, uint length,
						std::string filepath, bool overwrite = true);

	template<typename T>
	T* setall(T* src, uint length, const T& value);

	template<typename T>
	T* copy(T* src, T* dest);

	template<typename T>
	T* add(T* src, T* dest, uint length);

	template<typename T>
	T* add(T* src, uint length, const T& increment);

	template<typename T>
	T* mult(T* src, uint length, const T& mult);

	template<typename T>
	T* div(T* src, uint length, const T& div);

}

/* -------------------------------------------------------------------------- */

template<typename T>
void array::display(T* src, uint length){
	for(uint ivalue = 0u; ivalue != length; ++ivalue){
		std::cout << src[ivalue] << " ";
	}
}

template<typename T>
bool array::ASCIIexport(T* src, uint length,
						std::string filepath, bool overwrite){
	std::ofstream ofile;
	if(overwrite){
		ofile.open(filepath, std::ofstream::out);
	}else{
		ofile.open(filepath, std::ofstream::out | std::ofstream::app);
	}

	if(!ofile.is_open()){
		std::cout << "WARNING: The file could not be opened" << std::endl;
		return false;
	}

	for(uint ivalue = 0u; ivalue != length - 1; ++ivalue){
		ofile << src[ivalue] << " ";
	}
	ofile << src[length - 1] << std::endl;

	ofile.close();

	return true;
}

template<typename T>
T* array::setall(T* src, uint length, const T& value){
	for(uint i = 0u; i != length; ++i){
		src[i] = value;
	}
	return src;
}

template<typename T>
T* array::copy(T* src, T* dest, uint length){
	for(uint i = 0u; i != length; ++i){
		dest[i] = src[i];
	}
	return dest;
}

template<typename T>
T* array::add(T* src, T* dest, uint length){
	for(uint ivalue = 0u; ivalue != length; ++ivalue){
		dest[ivalue] += src[ivalue];
	}
	return dest;
}

template<typename T>
T* array::add(T* src, uint length, const T& increment){
	for(uint i = 0u; i != length; ++i){
		src[i] += increment;
	}
	return src;
}

template<typename T>
T* array::mult(T* src, uint length, const T& mult){
	for(uint i = 0u; i != length; ++i){
		src[i] *= mult;
	}
	return src;
}

template<typename T>
T* div(T* src, uint length, const T& div){
	for(uint ivalue = 0u; ivalue != length; ++ivalue){
		src[ivalue] /= div;
	}

	return src;
}

#endif