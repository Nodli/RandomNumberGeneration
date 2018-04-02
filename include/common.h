#ifndef H_COMMON
#define H_COMMON

#include <iostream>

typedef unsigned int uint;

#define UINT_MAX 4294967295

template<typename T>
struct vec2{
	T x;
	T y;

	inline vec2<T>& set(T x_input, T y_input){
		x = x_input;
		y = y_input;

		return *this;
	}

	vec2<T> operator=(const vec2<T>& src){
		x = src.x;
		y = src.y;

		return *this;
	}

};


template<typename T>
vec2<T> operator+(const vec2<T>& lhs, const vec2<T>& rhs){
	vec2<T> result;

	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;

	return result;
}

template<typename T>
vec2<T> operator-(const vec2<T>& lhs, const vec2<T>& rhs){
	vec2<T> result;

	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;

	return result;
}



template<typename T>
T dot(const vec2<T>& lhs, const vec2<T>& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T>
vec2<T> normalize(const vec2<T>& to_normalize){
	float norm = sqrt(to_normalize.x * to_normalize.x + to_normalize.y * to_normalize.y);
	vec2<T> normalized = {to_normalize.x / norm, to_normalize.y / norm};
	return normalized;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec2<T>& rhs){
	os << "(" << rhs.x << ", " << rhs.y << ")";
	return os;
}

template<typename OldT, typename NewT>
NewT cast(const vec2<OldT> to_cast){
	vec2<NewT> out;
	out.x = static_cast<NewT>(to_cast.x);
	out.y = static_cast<NewT>(to_cast.y);

	return out;
}


#define uivec2 vec2<unsigned int>
#define ivec2 vec2<int>
#define fvec2 vec2<float>


#endif