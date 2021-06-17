#ifndef SYM_TENSOR2
#define SYM_TENSOR2

#include "../array/array1.h"

namespace arr{
	class tensor1;
	class sym_tensor4;
	class tensor2;
	template< typename T > class vector;
}

namespace arr{

	class sym_tensor2 : public array1<double,6>{
	public:
		sym_tensor2();
		sym_tensor2( std::initializer_list<double> init );

		static sym_tensor2 delta();
		static sym_tensor2 zero();
		static sym_tensor2 constant( const double& val );

		void show_in_mat( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		sym_tensor2 operator -()const;

		double trace()const;
		double norm()const;
		double det()const;
		sym_tensor2 inverse()const;
		sym_tensor2 deviatoric()const;
		double I1()const;
		double I2()const;
		double I3()const;
		double J2()const;
		double p()const;
		sym_tensor2 s()const;
		double q()const;
		sym_tensor2 eta()const;
		double eta_star( const sym_tensor2& sig0 )const;
		double eta_rot( const sym_tensor2& eta0 )const;
		sym_tensor2 s_bar( const sym_tensor2& sig0 )const;
		sym_tensor2 n_bar( const sym_tensor2& sig0 )const;
		double q_bar( const sym_tensor2& sig0 )const;
		double epsv()const;
		sym_tensor2 epsd()const;
		double epss()const;
		array1<double,3> eigenvalue()const;
		array1<tensor1,3> eigenvector()const;

		tensor1 dot_prdct( const tensor1& v )const;
		sym_tensor2 dot_prdct( const sym_tensor2& t )const;
		sym_tensor4 tens_prdct( const sym_tensor2& t )const;
		//同じ２階テンソルでないと対称4階テンソルとならない
		//a otimes b + b otimes a は結果として対称4階テンソルになるが，別の関数が必要 -> tens_prdct_and_symmetrize = (a otimes b + b otimes a)/2 とか
		double dbdot_prdct( const sym_tensor2& t )const;
		sym_tensor2 dbdot_prdct( const sym_tensor4& t )const;

		explicit operator tensor2()const;
		template<typename T > operator array1<T,6>()const;
		template<typename T > operator vector<T>()const;

	};

	sym_tensor2 operator +( const sym_tensor2& t1, const sym_tensor2& t2 );
	sym_tensor2 operator -( const sym_tensor2& t1, const sym_tensor2& t2 );
	sym_tensor2 operator *( const double s, const sym_tensor2& t );
	sym_tensor2 operator *( const sym_tensor2& t, const double s );
	sym_tensor2 operator /( const sym_tensor2& t, const double s );

}

#endif