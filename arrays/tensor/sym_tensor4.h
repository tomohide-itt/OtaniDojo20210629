#ifndef SYM_TENSOR4
#define SYM_TENSOR4

#include "../array/array1.h"

namespace arr{
	class sym_tensor2;
	template< typename T, int Nr, int Nc > class array2;
	template< typename T > class matrix;
}

namespace arr{

	class sym_tensor4 : public array1<double,21>{
	public:
		sym_tensor4();
		sym_tensor4( std::initializer_list<double> init );

		static sym_tensor4 idn();
		static sym_tensor4 zero();
		static sym_tensor4 constant( const double& val );

		void show_in_mat( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		sym_tensor4 operator -()const;

		//__host__ __device__ sym_tensor4 dot_prdct( const sym_tensor2& t )const;
		sym_tensor4 dbdot_prdct( const sym_tensor4& t )const;
		sym_tensor2 dbdot_prdct( const sym_tensor2& t )const;

		template<typename T > operator array2<T,6,6>()const;
		template<typename T > operator matrix<T>()const;

	};

	sym_tensor4 operator +( const sym_tensor4& t1, const sym_tensor4& t2 );
	sym_tensor4 operator -( const sym_tensor4& t1, const sym_tensor4& t2 );
	sym_tensor4 operator *( const double s, const sym_tensor4& t );
	sym_tensor4 operator *( const sym_tensor4& t, const double s );
	sym_tensor4 operator /( const sym_tensor4& t, const double s );

}

#endif