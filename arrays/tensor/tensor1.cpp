#include "tensor1.h"
#include "sym_tensor2.h"
#include "tensor2.h"
#include <math.h>

namespace arr{
	tensor1::tensor1() :array1<double,3>(){
		//for( unsigned int i=0; i<sz; i++ ) vals[i] = 0.0;
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0;
	}

	tensor1::tensor1( std::initializer_list<double> init ){
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0;
		unsigned int min_sz = ( static_cast<unsigned int>(init.size()) > this->size())? this->size() : static_cast<unsigned int>(init.size());
		for( unsigned int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	tensor1 tensor1::zero(){
		tensor1 ret;
		ret.vals[0] = 0.0; ret.vals[1] = 0.0; ret.vals[2] = 0.0;
		return ret;
	}

	tensor1 tensor1::constant( const double& val ){
		tensor1 ret;
		ret.vals[0] = val; ret.vals[1] = val; ret.vals[2] = val;
		return ret;
	}

	void tensor1::show_in_mat( std::ostream& stream, const int width, const int dec ) const{
		stream << std::scientific << std::setprecision( dec );
		stream << std::setw(width) << (*this)[0];
		stream << std::setw(width) << (*this)[1];
		stream << std::setw(width) << (*this)[2] << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	tensor1 tensor1::operator -() const{
		tensor1 ret;
		unary_minus_1<double>( this->get(), ret.get(), 3 );
		return ret;
	}

	tensor1 tensor1::vec_prdct( const tensor1& v )const{
		tensor1 ret;
		ret[0] = (*this)[1]*v[2] - (*this)[2]*v[1];
		ret[1] = (*this)[2]*v[0] - (*this)[0]*v[2];
		ret[2] = (*this)[0]*v[1] - (*this)[1]*v[0];
		return ret;
	}

	double tensor1::dot_prdct( const tensor1& t )const{
		return t[0]*(*this)[0] + t[1]*(*this)[1] + t[2]*(*this)[2];
	}

	tensor1 tensor1::dot_prdct( const sym_tensor2& t )const{
		tensor1 ret;
		ret[0] = t[0]*(*this)[0] + t[3]*(*this)[1] + t[5]*(*this)[2];
		ret[1] = t[3]*(*this)[0] + t[1]*(*this)[1] + t[4]*(*this)[2];
		ret[2] = t[5]*(*this)[0] + t[4]*(*this)[1] + t[2]*(*this)[2];
		return ret;
	}

	tensor1 tensor1::dot_prdct( const tensor2& t )const{
		tensor1 ret;
		ret[0] = t[0]*(*this)[0] + t[3]*(*this)[1] + t[6]*(*this)[2];
		ret[1] = t[1]*(*this)[0] + t[4]*(*this)[1] + t[7]*(*this)[2];
		ret[2] = t[2]*(*this)[0] + t[5]*(*this)[1] + t[8]*(*this)[2];
		return ret;
	}

	tensor2 tensor1::tens_prdct( const tensor1& v )const{
		tensor2 ret;
		ret[0] = (*this)[0]*v[0];
		ret[1] = (*this)[0]*v[1];
		ret[2] = (*this)[0]*v[2];
		ret[3] = (*this)[1]*v[0];
		ret[4] = (*this)[1]*v[1];
		ret[5] = (*this)[1]*v[2];
		ret[6] = (*this)[2]*v[0];
		ret[7] = (*this)[2]*v[1];
		ret[8] = (*this)[2]*v[2];
		return ret;
	}

	template<>
	tensor1::operator array1<double,3>()const{
		array1<double,3> ret;
		ret[0] = (*this)[0];
		ret[1] = (*this)[1];
		ret[2] = (*this)[2];
		return ret;
	}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	tensor1 operator +( const tensor1& t1, const tensor1& t2 ){
		tensor1 ret;
		addition_1<double>( ret.get(), t1.get(), t2.get(), 3, 3 );
		return ret;
	}

	tensor1 operator -( const tensor1& t1, const tensor1& t2 ){
		tensor1 ret;
		subtraction_1<double>( ret.get(), t1.get(), t2.get(), 3, 3 );
		return ret;
	}

	tensor1 operator *( const double s, const tensor1& t ){
		tensor1 ret;
		multiplication_1<double>( ret.get(), s, t.get(), 3 );
		return ret;
	}

	tensor1 operator *( const tensor1& t, const double s ){
		return s*t;
	}

	tensor1 operator /( const tensor1& t, const double s ){
		tensor1 ret;
		division_1<double>( ret.get(), s, t.get(), 3 );
		return ret;
	}


} //end of namespase arr