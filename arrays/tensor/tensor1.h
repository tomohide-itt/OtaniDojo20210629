#ifndef TENSOR1
#define TENSOR1

#include "../array/array1.h"

namespace arr{
	class tensor2;
	class sym_tensor2;
}

namespace arr{

	class tensor1 : public array1<double,3>{
	public:
		tensor1();
		tensor1( std::initializer_list<double> init );

		static tensor1 zero();
		static tensor1 constant( const double& val );

		void show_in_mat( std::ostream& stream=std::cout, const int width=15, const int dec=5 ) const;

		tensor1 operator -() const;

		tensor1 vec_prdct( const tensor1& v )const;
		double dot_prdct( const tensor1& v )const;
		tensor1 dot_prdct( const sym_tensor2& t )const;
		tensor1 dot_prdct( const tensor2& t )const;
		tensor2 tens_prdct( const tensor1& t )const;

		template<typename T > operator array1<T,3>()const;

	};

	tensor1 operator +( const tensor1& t1, const tensor1& t2 );
	tensor1 operator -( const tensor1& t1, const tensor1& t2 );
	tensor1 operator *( const double s, const tensor1& t );
	tensor1 operator *( const tensor1& t, const double s );
	tensor1 operator /( const tensor1& t, const double s );

}

#endif