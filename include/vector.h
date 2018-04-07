#ifndef H_VECTOR
#define H_VECTOR

template<typename T>
struct vec2{
	T x;
	T y;

	//TODO: Make these outside functions - this does not allow the initialization through braced enclosed list
	//vec2();
	//vec2(const vec2<T>& src);

	vec2<T>& operator=(const vec2<T>& src);
	vec2<T>& operator+=(const vec2<T>& other);
	vec2<T>& operator-=(const vec2<T>& other);
	vec2<T>& operator*=(const T& mult);
	vec2<T>& operator/=(const T& div);

	inline vec2<T>& set(const T& setx, const T& sety);
	/**
	 * \brief Normalizes the vec2 in place and returns a reference to the instance
	 */
	vec2<T>& normalize();
};

template<typename T>
vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs);

template<typename T>
vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs);

template<typename T>
vec2<T> operator*(vec2<T> lhs, const vec2<T>& rhs);

template<typename T>
vec2<T> operator/(vec2<T> lhs, const vec2<T>& rhs);

template<typename T>
inline bool operator==(const vec2<T>& lhs, const vec2<T>& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec2<T>& src);

/**
 * \brief Normalizes and returns a copy /src/
 */
template<typename T>
vec2<T> normalize(vec2<T> src);

/**
 * \brief Returns the dot product of two vec2
 */
template<typename T>
T dot(const vec2<T>& lhs, const vec2<T>& rhs);

/* -------------------------------------------------------------------------- */

/* Methods */
/*
template<typename T>
vec2<T>::vec2(){
};

template<typename T>
vec2<T>::vec2(const vec2<T>& src): x(src.x), y(src.y){
};
*/
template<typename T>
vec2<T>& vec2<T>::operator=(const vec2<T>& src){
		if(this != &src){
			x = src.x;
			y = src.y;
		}

		return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator+=(const vec2<T>& other){
	x += other.x;
	y += other.y;

	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator-=(const vec2<T>& other){
	x -= other.x;
	y -= other.y;

	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator*=(const T& mult){
	x *= mult;
	y *= mult;

	return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator/=(const T& div){
	x /= div;
	y /= div;

	return *this;
}

template<typename T>
inline vec2<T>& vec2<T>::set(const T& setx, const T& sety){
		x = setx;
		y = sety;

		return *this;
}

template<typename T>
vec2<T>& vec2<T>::normalize(){
	T norm = sqrt(x * x + y * y);
	x = x / norm;
	y = y / norm;

	return *this;
}

/* Functions */
template<typename T>
vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs){
	lhs += rhs;
	return lhs;
}

template<typename T>
vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs){
	lhs -= rhs;
	return lhs;
}

template<typename T>
vec2<T> operator*(vec2<T> src, const T& mult){
	src *= mult;
	return src;
}

template<typename T>
vec2<T> operator/(vec2<T> src, const T& div){
	src /= div;
	return src;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec2<T>& src){
	os << "(" << src.x << ", " << src.y << ")";
	return os;
}

template<typename T>
vec2<T> normalize(vec2<T> src){
	T norm = sqrt(src.x * src.x + src.y * src.y);
	src.x = src.x / norm;
	src.y = src.y / norm;
	return src;
}

template<typename T>
T dot(const vec2<T>& lhs, const vec2<T>& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

/* -------------------------------------------------------------------------- */

#define uivec2 vec2<unsigned int>
#define ivec2 vec2<int>
#define fvec2 vec2<float>
#define dvec2 vec2<double>

#endif