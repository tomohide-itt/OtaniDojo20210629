#ifndef ARRAY2
#define ARRAY2

#include "array1.h"

namespace arr{
	template< typename T> class matrix;
}

namespace arr{

	template< typename T, int Nr, int Nc >
	class array2{
	protected:
		unsigned int msize;	///<配列のサイズ
		unsigned int mrows;	///<行数
		unsigned int mcols;	///<列数
		unsigned int mstride;	///<ストライド：実際の列数
		T vals[Nr*Nc];		///<マトリクスの各要素を格納するための静的配列
		T* pvals;
	public:
		array2();
		array2( std::initializer_list<T> init );
		array2( const array2<T,Nr,Nc>& m );
		array2<T,Nr,Nc>& operator=( const array2<T,Nr,Nc>& m );

		T& operator[]( const unsigned int i );
		T  operator[]( const unsigned int i )const;
		T& operator()( const unsigned int i, const unsigned int j );
		T  operator()( const unsigned int i, const unsigned int j )const;
		array1<T,Nc> operator()( const unsigned int r )const;

		const T* get()const;
		T* get();
		void set( T* p );
		unsigned int size()const;
		unsigned int rows()const;
		unsigned int cols()const;
		unsigned int stride()const;

		void show( std::ostream& stream=std::cout, const int width=15, const int dec=5 ) const;

		void fill( const T& val );
		static array2<T,Nr,Nc> zero();
		static array2<T,Nr,Nc> constant( const T& val );

		array2<T,Nr,Nc>& operator +=( const T s );
		array2<T,Nr,Nc>& operator +=( const array2<T,Nr,Nc>& m );
		array2<T,Nr,Nc>& operator -=( const T s );
		array2<T,Nr,Nc>& operator -=( const array2<T,Nr,Nc>& m );
		array2<T,Nr,Nc>& operator *=( const T s );
		array2<T,Nr,Nc>& operator /=( const T s );
		array2<T,Nr,Nc>  operator -() const;
		bool operator == ( const array2<T,Nr,Nc>& m ) const;
		bool operator != ( const array2<T,Nr,Nc>& m ) const;
		
		array2<T,Nc,Nr> transpose() const;

		array2<T,Nr,Nc>& deep_copy( const array2<T,Nr,Nc>& m );

		operator matrix<T>()const;
	};

	
	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator +( const array2<T,Nr,Nc>& m1, const array2<T,Nr,Nc>& m2 );

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator -( const array2<T,Nr,Nc>& m1, const array2<T,Nr,Nc>& m2 );

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const T s, const array2<T,Nr,Nc>& m );

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const array2<T,Nr,Nc>& m, const T s );

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator /( const array2<T,Nr,Nc>& m, const T s );

	template<typename T, int Nr1, int Nc1, int Nc2 >
	array2<T,Nr1,Nc2> operator *( const array2<T,Nr1,Nc1>& m1, const array2<T,Nc1,Nc2>& m2 );

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const array1<T,Nr>& v1, const array1<T,Nc>& v2 );

	template<typename T, int Nv, int Nc >
	array1<T,Nc> operator *( const array1<T,Nv>& v, const array2<T,Nv,Nc>& m );

	template<typename T, int Nr, int Nv >
	array1<T,Nr> operator *( const array2<T,Nr,Nv>& m, const array1<T,Nv>& v );
	

} //end of namespace arr

#include "array2.hpp"

#endif