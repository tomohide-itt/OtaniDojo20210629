#include "sym_tensor2.h"
#include "tensor1.h"
#include "tensor2.h"
#include <math.h>

namespace arr{
	tensor2::tensor2() :array1<double,9>(){
		//for( unsigned int i=0; i<sz; i++ ) vals[i] = 0.0;
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0; vals[3] = 0.0; vals[4] = 0.0; vals[5] = 0.0; vals[6] = 0.0; vals[7] = 0.0; vals[8] = 0.0;
	}

	tensor2::tensor2( std::initializer_list<double> init ){
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0; vals[3] = 0.0; vals[4] = 0.0; vals[5] = 0.0; vals[6] = 0.0; vals[7] = 0.0; vals[8] = 0.0;
		unsigned int min_sz = ( static_cast<unsigned int>(init.size()) > this->size())? this->size() : static_cast<unsigned int>(init.size());
		for( unsigned int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	tensor2 tensor2::delta(){
		tensor2 ret;
		ret.vals[0] = 1.0; ret.vals[1] = 0.0; ret.vals[2] = 0.0; ret.vals[3] = 0.0; ret.vals[4] = 1.0; ret.vals[5] = 0.0; ret.vals[6] = 0.0; ret.vals[7] = 0.0; ret.vals[8] = 1.0;
		return ret;
	}

	tensor2 tensor2::zero(){
		tensor2 ret;
		ret.vals[0] = 0.0; ret.vals[1] = 0.0; ret.vals[2] = 0.0; ret.vals[3] = 0.0; ret.vals[4] = 0.0; ret.vals[5] = 0.0; ret.vals[6] = 0.0; ret.vals[7] = 0.0; ret.vals[8] = 0.0;
		return ret;
	}

	tensor2 tensor2::constant( const double& val ){
		tensor2 ret;
		ret.vals[0] = val; ret.vals[1] = val; ret.vals[2] = val; ret.vals[3] = val; ret.vals[4] = val; ret.vals[5] = val; ret.vals[6] = val; ret.vals[7] = val; ret.vals[8] = val;
		return ret;
	}

	void tensor2::show_in_mat( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		stream << std::setw(width) << (*this)[0];
		stream << std::setw(width) << (*this)[1];
		stream << std::setw(width) << (*this)[2] << std::endl;
		stream << std::setw(width) << (*this)[3];
		stream << std::setw(width) << (*this)[4];
		stream << std::setw(width) << (*this)[5] << std::endl;
		stream << std::setw(width) << (*this)[6];
		stream << std::setw(width) << (*this)[7];
		stream << std::setw(width) << (*this)[8] << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	tensor2 tensor2::operator -() const{
		tensor2 ret;
		unary_minus_1<double>( this->get(), ret.get(), 9 );
		return ret;
	}

	double tensor2::trace()const{
		return (*this)[0] + (*this)[4] + (*this)[8];
	}

	double tensor2::norm()const{
		double ret = dbdot_prdct( *this );
		return sqrt( ret );
	}

	double tensor2::det()const{
		return (*this)[0]*(*this)[4]*(*this)[8]
		 	 + (*this)[1]*(*this)[5]*(*this)[6]
		 	 + (*this)[2]*(*this)[3]*(*this)[7]
		 	 - (*this)[2]*(*this)[4]*(*this)[6]
		 	 - (*this)[0]*(*this)[5]*(*this)[7]
		 	 - (*this)[1]*(*this)[3]*(*this)[8];
	}

	tensor2 tensor2::inverse()const{
		tensor2 ret;
		double dett = this->det();
		ret[0] = ( (*this)[4]*(*this)[8] - (*this)[5]*(*this)[7] )/dett;
		ret[1] = ( (*this)[2]*(*this)[7] - (*this)[1]*(*this)[8] )/dett;
		ret[2] = ( (*this)[1]*(*this)[5] - (*this)[2]*(*this)[4] )/dett;
		ret[3] = ( (*this)[5]*(*this)[6] - (*this)[3]*(*this)[8] )/dett;
		ret[4] = ( (*this)[0]*(*this)[8] - (*this)[2]*(*this)[6] )/dett;
		ret[5] = ( (*this)[2]*(*this)[3] - (*this)[0]*(*this)[5] )/dett;
		ret[6] = ( (*this)[3]*(*this)[7] - (*this)[4]*(*this)[6] )/dett;
		ret[7] = ( (*this)[1]*(*this)[6] - (*this)[0]*(*this)[7] )/dett;
		ret[8] = ( (*this)[0]*(*this)[4] - (*this)[1]*(*this)[3] )/dett;
		return ret;
	}

	tensor2 tensor2::transpose()const{
		tensor2 ret;
		ret[0] = (*this)[0];
		ret[1] = (*this)[3];
		ret[2] = (*this)[6];
		ret[3] = (*this)[1];
		ret[4] = (*this)[4];
		ret[5] = (*this)[7];
		ret[6] = (*this)[2];
		ret[7] = (*this)[5];
		ret[8] = (*this)[8];
		return ret;
	}

	double tensor2::I1()const{
		return (*this)[0] + (*this)[4] + (*this)[8];
	}

	double tensor2::I2()const{
		double tr = this->trace();
		tensor2 t2 = this->dot_prdct( *this );
		double tr2 = t2.trace();
		return 0.5*(tr*tr-tr2);
	}

	double tensor2::I3()const{
		return this->det();
	}

	array1<double,3> tensor2::eigenvalue()const{
		array1<double,3> eigenval;
		const double PI = 3.141592;

		double I1 = this->I1();
		double I2 = this->I2();
		double I3 = this->I3();

		double Q = -(I1*I1-3.0*I2)/9.0;
		double R = ( 2.0*I1*I1*I1 - 9.0*I1*I2 + 27.0*I3 )/54.0;
		double cs = 0.0;
		if( Q < 0.0 ) cs = R/( pow( -Q, double(1.5) ) );
		if( cs >  1.0 ) cs =  1.0;
		if( cs < -1.0 ) cs = -1.0;
		double theta = acos( cs );

		eigenval[0] = I1/3.0 + 2.0*sqrt( -Q ) * cos( theta/3.0 );
		eigenval[1] = I1/3.0 + 2.0*sqrt( -Q ) * cos( theta/3.0 - 2.0/3.0*PI );
		eigenval[2] = I1/3.0 + 2.0*sqrt( -Q ) * cos( theta/3.0 + 2.0/3.0*PI );
		return eigenval;
	}

	array1<tensor1,3> tensor2::eigenvector()const{
		array1<double,3> eval = this->eigenvalue();
		array1<tensor2,3> tns, nn;
		for( unsigned int i=0; i<3; i++ ){
			tns[i] = *this - eval[i]*tensor2::delta();
		}

		if( eval[0] != eval[1] && eval[1] != eval[2] ){
			nn[0] = tns[1].dot_prdct(tns[2])/( eval[0] - eval[1] )/( eval[0] - eval[2] );
			nn[1] = tns[2].dot_prdct(tns[0])/( eval[1] - eval[2] )/( eval[1] - eval[0] );
			nn[2] = tns[0].dot_prdct(tns[1])/( eval[2] - eval[0] )/( eval[2] - eval[1] );
		}else if( eval[0] == eval[1] && eval[1] != eval[2] ){
			nn[0] = tns[2]/( eval[0] - eval[2] );
			nn[1] = tensor2::zero();
			nn[2] = tns[0]/( eval[2] - eval[0] );
		}else if( eval[0] != eval[1] && eval[1] == eval[2] ){
			nn[0] = tns[1]/( eval[0] - eval[1] );
			nn[1] = tns[0]/( eval[1] - eval[0] );
			nn[2] = tensor2::zero();
		}else{
			nn[0] = tensor2::delta();
			nn[1] = tensor2::zero();
			nn[2] = tensor2::zero();
		}

		array1<tensor1,3> evec;
		for( unsigned int i=0; i<3; i++ ){
			evec[i] = nn[i].cal_eigenv();
		}
		return evec;
	}

	tensor1 tensor2::cal_eigenv(){
		tensor1 ret = tensor1::zero();
		unsigned int idx = 0;
		if( fabs( (*this)[0] ) <= fabs( (*this)[4] ) && fabs( (*this)[4] ) >= fabs( (*this)[8] ) ){
			idx = 1;
		}else if( fabs( (*this)[0] ) <= fabs( (*this)[8] ) && fabs( (*this)[4] ) <= fabs( (*this)[8] ) ){
			idx = 2;
		}
		if( fabs( (*this)[idx*3+idx] ) == 0.0 ) return ret;
		if( idx == 0 ){
			ret[0] = sqrt( (*this)[0] );
			ret[1] = (*this)[3]/ret[0];
			ret[2] = (*this)[6]/ret[0];
		}else if( idx == 1 ){
			ret[1] = sqrt( (*this)[4] );
			ret[0] = (*this)[1]/ret[1];
			ret[2] = (*this)[7]/ret[1];
		}else{
			ret[2] = sqrt( (*this)[8] );
			ret[0] = (*this)[2]/ret[2];
			ret[1] = (*this)[5]/ret[2];
		}
		return ret;
	}

	tensor1 tensor2::dot_prdct( const tensor1& v )const{
		tensor1 ret;
		ret[0] = (*this)[0]*v[0] + (*this)[1]*v[1] + (*this)[2]*v[2];
		ret[1] = (*this)[3]*v[0] + (*this)[4]*v[1] + (*this)[5]*v[2];
		ret[2] = (*this)[6]*v[0] + (*this)[7]*v[1] + (*this)[8]*v[2];
		return ret;
	}


	tensor2 tensor2::dot_prdct( const tensor2& t )const{
		tensor2 ret;
		ret[0] = (*this)[0]*t[0] + (*this)[1]*t[3] + (*this)[2]*t[6];
		ret[1] = (*this)[0]*t[1] + (*this)[1]*t[4] + (*this)[2]*t[7];
		ret[2] = (*this)[0]*t[2] + (*this)[1]*t[5] + (*this)[2]*t[8];
		ret[3] = (*this)[3]*t[0] + (*this)[4]*t[3] + (*this)[5]*t[6];
		ret[4] = (*this)[3]*t[1] + (*this)[4]*t[4] + (*this)[5]*t[7];
		ret[5] = (*this)[3]*t[2] + (*this)[4]*t[5] + (*this)[5]*t[8];
		ret[6] = (*this)[6]*t[0] + (*this)[7]*t[3] + (*this)[8]*t[6];
		ret[7] = (*this)[6]*t[1] + (*this)[7]*t[4] + (*this)[8]*t[7];
		ret[8] = (*this)[6]*t[2] + (*this)[7]*t[5] + (*this)[8]*t[8];
		return ret;
	}

	double tensor2::dbdot_prdct( const tensor2& t )const{
		double ret;
		ret = (*this)[0]*t[0]
		    + (*this)[1]*t[1]
		    + (*this)[2]*t[2]
		    + (*this)[3]*t[3]
		    + (*this)[4]*t[4]
		    + (*this)[5]*t[5]
		    + (*this)[6]*t[6]
		    + (*this)[7]*t[7]
		    + (*this)[8]*t[8];
		return ret;
	}

	tensor2::operator sym_tensor2()const{
		sym_tensor2 ret;
		ret[0] = (*this)[0];
		ret[1] = (*this)[4];
		ret[2] = (*this)[8];
		ret[3] = 0.5*( (*this)[1] + (*this)[3] );
		ret[4] = 0.5*( (*this)[5] + (*this)[7] );
		ret[5] = 0.5*( (*this)[2] + (*this)[6] );
		return ret;
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	tensor2 operator +( const tensor2& t1, const tensor2& t2 ){
		tensor2 ret;
		addition_1<double>( ret.get(), t1.get(), t2.get(), 9, 9 );
		return ret;
	}

	tensor2 operator -( const tensor2& t1, const tensor2& t2 ){
		tensor2 ret;
		subtraction_1<double>( ret.get(), t1.get(), t2.get(), 9, 9 );
		return ret;
	}

	tensor2 operator *( const double s, const tensor2& t ){
		tensor2 ret;
		multiplication_1<double>( ret.get(), s, t.get(), 9 );
		return ret;
	}

	tensor2 operator *( const tensor2& t, const double s ){
		return s*t;
	}

	tensor2 operator /( const tensor2& t, const double s ){
		tensor2 ret;
		division_1<double>( ret.get(), s, t.get(), 9 );
		return ret;
	}


}//end of namespace arr
