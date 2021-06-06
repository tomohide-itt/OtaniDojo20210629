#ifndef TENSOR2
#define TENSOR2

#include "../array/array1.h"

namespace arr{
	class tensor1;
	class sym_tensor2;
}

namespace arr{

	class tensor2 : public array1<double,9>{
	public:
		tensor2();
		tensor2( std::initializer_list<double> init );

		static tensor2 delta();
		static tensor2 zero();
		static tensor2 constant( const double& val );

		void show_in_mat( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		tensor2 operator -()const;

		double trace()const;
		double norm()const;
		double det()const;
		tensor2 inverse()const;
		tensor2 transpose()const;
		double I1()const;
		double I2()const;
		double I3()const;
		array1<double,3> eigenvalue()const;
		array1<tensor1,3> eigenvector()const; 

		tensor1 dot_prdct( const tensor1& v )const;
		tensor2 dot_prdct( const tensor2& t )const;
		double dbdot_prdct( const tensor2& t )const;

		explicit operator sym_tensor2()const;

	private:
		tensor1 cal_eigenv();

	};

	tensor2 operator +( const tensor2& t1, const tensor2& t2 );
	tensor2 operator -( const tensor2& t1, const tensor2& t2 );
	tensor2 operator *( const double s, const tensor2& t );
	tensor2 operator *( const tensor2& t, const double s );
	tensor2 operator /( const tensor2& t, const double s );

}

#include "tensor2.hpp"

#endif