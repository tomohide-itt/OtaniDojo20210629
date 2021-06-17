#ifndef MATRIX
#define MATRIX

#include <iostream>

namespace arr{
	template< typename T> class vector;
	template< typename T, int Nr, int Nc > class array2;
}

namespace arr{

	template< typename T >
	class matrix{
	private:
		unsigned int msize;
		unsigned int mrows;
		unsigned int mcols;
		unsigned int mstride;
		bool msub;
		bool mempty;
		bool mref;
		T* vals;
	public:
		matrix();
		matrix( const unsigned int r, const unsigned int c );
		matrix( const unsigned int r, const unsigned int c, const T& val );
		matrix( const matrix<T>& m );
		~matrix();
		matrix<T>& operator=( const matrix<T>& m );

		T& operator[]( const unsigned int i );
		T  operator[]( const unsigned int i )const;
		T& operator()( const unsigned int r, const unsigned int c );
		T  operator()( const unsigned int r, const unsigned int c )const;
		vector<T> operator()( const unsigned int i );
		vector<T> operator()( const unsigned int i )const;

		const T* get()const;
		T* get();
		void set( const unsigned int r, const unsigned int c, T* p );
		unsigned int size()const;
		unsigned int rows()const;
		unsigned int cols()const;
		unsigned int stride()const;
		bool is_sub()const;
		bool is_empty()const;
		bool is_ref()const;

		void show( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		void resize( const unsigned int r, const unsigned int c );
		void resize( const unsigned int r, const unsigned int c, const T& val );
		void reset();
		void fill( const T& val );

		static matrix<T> zero( const unsigned int r, const unsigned int c );
		static matrix<T> constant( const unsigned int r, const unsigned int c, const T& val );

		matrix<T>& operator +=( const T s );
		matrix<T>& operator +=( const matrix<T>& m );
		matrix<T>& operator -=( const T s );
		matrix<T>& operator -=( const matrix<T>& m );
		matrix<T>& operator *=( const T s );
		matrix<T>& operator /=( const T s );
		matrix<T>  operator -()const;
		bool operator ==( const matrix<T>& m )const;
		bool operator !=( const matrix<T>& m )const;
		matrix<T> transpose()const;

		void create_sub_matrix( const unsigned int r, const unsigned int c, T* pvals );
		vector<T> sub( const unsigned int s, const unsigned int num )const;
		matrix<T> sub( const unsigned int sr, const unsigned int sc, const unsigned int num_r, const unsigned int num_c )const;

		matrix<T>& shallow_copy( const matrix<T>& m );
		matrix<T>& deep_copy( const matrix<T>& m );
		matrix<T>& replace( const matrix<T>& m );
		template<int Nr, int Nc> matrix<T>& replace( const array2<T,Nr,Nc>& m );

		template<int Nr, int Nc> operator array2<T,Nr,Nc>()const;
	};

	template<typename T>
	matrix<T> operator +( const matrix<T>& m1, const matrix<T>& m2 );

	template<typename T>
	matrix<T> operator -( const matrix<T>& m1, const matrix<T>& m2 );

	template<typename T>
	matrix<T> operator *( const matrix<T>& m, const T s );

	template<typename T>
	matrix<T> operator *( const T s, const matrix<T>& m );

	template<typename T>
	matrix<T> operator *( const matrix<T>& m, const T s );

	template<typename T>
	matrix<T> operator *( const matrix<T>& m1, const matrix<T>& m2 );

	template<typename T>
	matrix<T> operator *( const vector<T>& v1, const vector<T>& v2 );

	template<typename T>
	vector<T> operator *( const vector<T>& v, const matrix<T>& m );

	template<typename T>
	vector<T> operator *( const matrix<T>& m, const vector<T>& v );



}

#include "matrix.hpp"

#endif