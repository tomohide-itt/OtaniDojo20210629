#ifndef ARRAY1
#define ARRAY1

#include <iostream>

namespace arr{

	template< typename T, int N >
	class array1{
	protected:
		unsigned int msize;	///< 配列のサイズ
		T* pvals;			///< 成分へのポインタ
		T vals[N];
	public:
		array1();
		array1( const T& v );
		array1( std::initializer_list<T> init );
		array1( const array1<T,N>& v );
		array1<T,N>& operator=( const array1<T,N>& v );

		T& operator[]( const unsigned int i );
		T  operator[]( const unsigned int i )const;

		unsigned int size()const;
		const T* get()const;
		T* get();
		void set( T* p );
		T* begin(){ return vals; }
		T* end(){ return &(vals[N-1]); }

		void show( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		void fill( const T& val );
		static array1<T,N> zero();
		static array1<T,N> constant( const T& val );

		array1<T,N>& operator +=( const T s );
		array1<T,N>& operator +=( const array1<T,N>& v );
		array1<T,N>& operator -=( const T s );
		array1<T,N>& operator -=( const array1<T,N>& v );
		array1<T,N>& operator *=( const T s );
		array1<T,N>& operator /=( const T s );
		array1<T,N>  operator -() const;
		bool operator == ( const array1<T,N>& v ) const;
		bool operator != ( const array1<T,N>& v ) const;
		T dot( const array1<T,N>& ) const;
		T norm() const;
		array1<double,3> vec_prdct( const array1<double,3>& v ) const;

		array1<T,N>& deep_copy( const array1<T,N>& v );
	};

	//-------------------------------------------------------------------------------------------
	template<typename T, int N>
	array1<T,N> operator +( const array1<T,N>& v1, const array1<T,N>& v2 );

	template<typename T, int N>
	array1<T,N> operator -( const array1<T,N>& v1, const array1<T,N>& v2 );

	template<typename T, int N>
	array1<T,N> operator *( const T s, const array1<T,N>& v );

	template<typename T, int N>
	array1<T,N> operator *( const array1<T,N>& v, const T s );

	template<typename T, int N>
	array1<T,N> operator /( const array1<T,N>& v, const T s );

}

#include "array1.hpp"

#endif