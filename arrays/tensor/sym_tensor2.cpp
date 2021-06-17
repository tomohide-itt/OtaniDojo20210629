#include "sym_tensor2.h"
#include "tensor1.h"
#include "sym_tensor4.h"
#include "tensor2.h"
#include "../vector/vector.h"
#include <math.h>

namespace arr{
	sym_tensor2::sym_tensor2() :array1<double,6>(){
		//for( unsigned int i=0; i<sz; i++ ) vals[i] = 0.0;
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0; vals[3] = 0.0; vals[4] = 0.0; vals[5] = 0.0;
	}

	sym_tensor2::sym_tensor2( std::initializer_list<double> init ){
		vals[0] = 0.0; vals[1] = 0.0; vals[2] = 0.0; vals[3] = 0.0; vals[4] = 0.0; vals[5] = 0.0;
		unsigned int min_sz = ( static_cast<unsigned int>(init.size()) > this->size())? this->size() : static_cast<unsigned int>(init.size());
		for( unsigned int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	sym_tensor2 sym_tensor2::delta(){
		sym_tensor2 ret;
		ret.vals[0] = 1.0; ret.vals[1] = 1.0; ret.vals[2] = 1.0; ret.vals[3] = 0.0; ret.vals[4] = 0.0; ret.vals[5] = 0.0;
		return ret;
	}

	sym_tensor2 sym_tensor2::zero(){
		sym_tensor2 ret;
		ret.vals[0] = 0.0; ret.vals[1] = 0.0; ret.vals[2] = 0.0; ret.vals[3] = 0.0; ret.vals[4] = 0.0; ret.vals[5] = 0.0;
		return ret;
	}

	sym_tensor2 sym_tensor2::constant( const double& val ){
		sym_tensor2 ret;
		ret.vals[0] = val; ret.vals[1] = val; ret.vals[2] = val; ret.vals[3] = val; ret.vals[4] = val; ret.vals[5] = val;
		return ret;
	}

	void sym_tensor2::show_in_mat( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		stream << std::setw(width) << (*this)[0];
		stream << std::setw(width) << (*this)[3];
		stream << std::setw(width) << (*this)[5] << std::endl;
		stream << std::setw(width) << (*this)[3];
		stream << std::setw(width) << (*this)[1];
		stream << std::setw(width) << (*this)[4] << std::endl;
		stream << std::setw(width) << (*this)[5];
		stream << std::setw(width) << (*this)[4];
		stream << std::setw(width) << (*this)[2] << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	sym_tensor2 sym_tensor2::operator -() const{
		sym_tensor2 ret;
		unary_minus_1<double>( this->get(), ret.get(), 6 );
		return ret;
	}

	double sym_tensor2::trace()const{
		return (*this)[0] + (*this)[1] + (*this)[2];
	}

	double sym_tensor2::norm()const{
		double ret = dbdot_prdct( *this );
		return sqrt( ret );
	}

	double sym_tensor2::det()const{
		return (*this)[0]*(*this)[1]*(*this)[2]
		     + (*this)[3]*(*this)[4]*(*this)[5]
		     + (*this)[3]*(*this)[4]*(*this)[5]
		     - (*this)[5]*(*this)[1]*(*this)[5]
		     - (*this)[0]*(*this)[4]*(*this)[4]
		     - (*this)[3]*(*this)[3]*(*this)[2];
	}

	sym_tensor2 sym_tensor2::inverse()const{
		sym_tensor2 ret;
		double dett = this->det();
		ret[0] = ( (*this)[1]*(*this)[2] - (*this)[4]*(*this)[4] )/dett;
		ret[1] = ( (*this)[0]*(*this)[2] - (*this)[5]*(*this)[5] )/dett;
		ret[2] = ( (*this)[0]*(*this)[1] - (*this)[3]*(*this)[3] )/dett;
		ret[3] = ( (*this)[5]*(*this)[4] - (*this)[3]*(*this)[2] )/dett;
		ret[4] = ( (*this)[5]*(*this)[3] - (*this)[0]*(*this)[4] )/dett;
		ret[5] = ( (*this)[3]*(*this)[4] - (*this)[5]*(*this)[1] )/dett;
		return ret;
	}

	sym_tensor2 sym_tensor2::deviatoric()const{
		sym_tensor2 del = sym_tensor2::delta();
		return *this - (this->trace()/3.0)*del;
	}

	double sym_tensor2::I1()const{
		return (*this)[0] + (*this)[1] + (*this)[2];
	}

	double sym_tensor2::I2()const{
		double tr = this->trace();
		sym_tensor2 t2 = this->dot_prdct( *this );
		double tr2 = t2.trace();
		return 0.5*(tr*tr-tr2);
	}

	double sym_tensor2::I3()const{
		return this->det();
	}

	double sym_tensor2::J2()const{
		sym_tensor2 d = this->deviatoric();
		return 0.5* d.dbdot_prdct( d );
	}

	double sym_tensor2::p()const{
		return this->trace()/3.0;
	}

	sym_tensor2 sym_tensor2::s()const{
		return this->deviatoric();
	}

	double sym_tensor2::q()const{
		return sqrt(1.5)*this->s().norm();
	}

	sym_tensor2 sym_tensor2::eta()const{
		return this->s()/this->p();
	}

	double sym_tensor2::eta_star( const sym_tensor2& sig0 )const{
		sym_tensor2 deta;
		deta = this->eta() - sig0.eta();
		return sqrt( 1.5 )*deta.norm();
	}

	double sym_tensor2::eta_rot( const sym_tensor2& etae )const{
		if( this->p() == 0.0 ) return 0.0;
		sym_tensor2 deta = this->eta() - etae;
		return sqrt( 1.5 )*deta.norm();
	}

	sym_tensor2 sym_tensor2::s_bar( const sym_tensor2& sig0 )const{
		sym_tensor2 del = sym_tensor2::delta();
		return *this - this->p()*( del + sig0.eta() );
	}

	sym_tensor2 sym_tensor2::n_bar( const sym_tensor2& sig0 )const{
		sym_tensor2 s_bar = this->s_bar( sig0 );
		return s_bar/s_bar.norm();
	}

	double sym_tensor2::q_bar( const sym_tensor2& sig0 )const{
		double norm_s_bar = this->s_bar(sig0).norm();
		return sqrt( 1.5 )*norm_s_bar;
	}

	double sym_tensor2::epsv()const{
		return (*this)[0] + (*this)[1] + (*this)[2];
	}

	sym_tensor2 sym_tensor2::epsd()const{
		return this->deviatoric();
	}

	double sym_tensor2::epss()const{
		double  norm_epsd = this->epsd().norm();
		return sqrt(2.0/3.0)*norm_epsd;
	}

	array1<double,3> sym_tensor2::eigenvalue()const{
		tensor2 t = static_cast<tensor2>(*this);
		return t.eigenvalue();
	}

	array1<tensor1,3> sym_tensor2::eigenvector()const{
		tensor2 t = static_cast<tensor2>(*this);
		return t.eigenvector();
	}

	tensor1 sym_tensor2::dot_prdct( const tensor1& v )const{
		tensor1 ret;
		ret[0] = (*this)[0]*v[0] + (*this)[3]*v[1] + (*this)[5]*v[2];
		ret[1] = (*this)[3]*v[0] + (*this)[1]*v[1] + (*this)[4]*v[2];
		ret[2] = (*this)[5]*v[0] + (*this)[4]*v[1] + (*this)[2]*v[2];
		return ret;
	}

	sym_tensor2 sym_tensor2::dot_prdct( const sym_tensor2& t )const{
		sym_tensor2 ret;
		ret[0] = (*this)[0]*t[0] + (*this)[3]*t[3] + (*this)[5]*t[5];
		ret[1] = (*this)[3]*t[3] + (*this)[1]*t[1] + (*this)[4]*t[4];
		ret[2] = (*this)[5]*t[5] + (*this)[4]*t[4] + (*this)[2]*t[2];
		ret[3] = (*this)[0]*t[3] + (*this)[3]*t[1] + (*this)[5]*t[4];
		ret[4] = (*this)[3]*t[5] + (*this)[1]*t[4] + (*this)[4]*t[2];
		ret[5] = (*this)[0]*t[5] + (*this)[3]*t[4] + (*this)[5]*t[2];
		return ret;
	}

	sym_tensor4 sym_tensor2::tens_prdct( const sym_tensor2& t )const{
		if( *this != t ){
			printf( "\nERROR# %s(%d): %s\nresult is not sym_tensor4\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		sym_tensor4 ret;
		ret[ 0] = (*this)[0] * t[0]; //1111
		ret[ 1] = (*this)[0] * t[1]; //1122
		ret[ 2] = (*this)[0] * t[2]; //1133
		ret[ 3] = (*this)[0] * t[3]; //1112
		ret[ 4] = (*this)[0] * t[4]; //1123
		ret[ 5] = (*this)[0] * t[5]; //1131
		ret[ 6] = (*this)[1] * t[1]; //2222
		ret[ 7] = (*this)[1] * t[2]; //2233
		ret[ 8] = (*this)[1] * t[3]; //2212
		ret[ 9] = (*this)[1] * t[4]; //2223
		ret[10] = (*this)[1] * t[5]; //2231
		ret[11] = (*this)[2] * t[2]; //3333
		ret[12] = (*this)[2] * t[3]; //3312
		ret[13] = (*this)[2] * t[4]; //3323
		ret[14] = (*this)[2] * t[5]; //3331
		ret[15] = (*this)[3] * t[3]; //1212
		ret[16] = (*this)[3] * t[4]; //1223
		ret[17] = (*this)[3] * t[5]; //1231
		ret[18] = (*this)[4] * t[4]; //2323
		ret[19] = (*this)[4] * t[5]; //2331
		ret[20] = (*this)[5] * t[5]; //3131
		return ret;
	}

	double sym_tensor2::dbdot_prdct( const sym_tensor2& t )const{
		double ret;
		ret = (*this)[0]*t[0]
		    + (*this)[1]*t[1]
		    + (*this)[2]*t[2]
		    + (*this)[3]*t[3]*2.0
		    + (*this)[4]*t[4]*2.0
		    + (*this)[5]*t[5]*2.0;
		return ret;
	}

	sym_tensor2 sym_tensor2::dbdot_prdct( const sym_tensor4& t )const{
		sym_tensor2 ret;
		//11 = 1111*11 + 1122*22 + 1133*33 + 2*( 1112*12 + 1123*23 + 1131*31 )
		//22 = 2211*11 + 2222*22 + 2233*33 + 2*( 2212*12 + 2223*23 + 2231*31 )
		//33 = 3311*11 + 3322*22 + 3333*33 + 2*( 3312*12 + 3323*23 + 3331*31 )
		//12 = 1211*11 + 1222*22 + 1233*33 + 2*( 1212*12 + 1223*23 + 1231*31 )
		//23 = 2311*11 + 2322*22 + 2333*33 + 2*( 2312*12 + 2323*23 + 2331*31 )
		//31 = 3111*11 + 3122*22 + 3133*33 + 2*( 3112*12 + 3123*23 + 3131*31 )
		ret[0] = t[ 0]*(*this)[0] + t[ 1]*(*this)[1] + t[ 2]*(*this)[2] + 2.0*( t[ 3]*(*this)[3] + t[ 4]*(*this)[4] + t[ 5]*(*this)[5] );
		ret[1] = t[ 1]*(*this)[0] + t[ 6]*(*this)[1] + t[ 7]*(*this)[2] + 2.0*( t[ 8]*(*this)[3] + t[ 9]*(*this)[4] + t[10]*(*this)[5] );
		ret[2] = t[ 2]*(*this)[0] + t[ 7]*(*this)[1] + t[11]*(*this)[2] + 2.0*( t[12]*(*this)[3] + t[13]*(*this)[4] + t[14]*(*this)[5] );
		ret[3] = t[ 3]*(*this)[0] + t[ 8]*(*this)[1] + t[12]*(*this)[2] + 2.0*( t[15]*(*this)[3] + t[16]*(*this)[4] + t[17]*(*this)[5] );
		ret[4] = t[ 4]*(*this)[0] + t[ 9]*(*this)[1] + t[13]*(*this)[2] + 2.0*( t[16]*(*this)[3] + t[18]*(*this)[4] + t[19]*(*this)[5] );
		ret[5] = t[ 5]*(*this)[0] + t[10]*(*this)[1] + t[14]*(*this)[2] + 2.0*( t[17]*(*this)[3] + t[19]*(*this)[4] + t[20]*(*this)[5] );
		return ret;
	}

	sym_tensor2::operator tensor2()const{
		tensor2 ret;
		ret[0] = (*this)[0];
		ret[1] = (*this)[3];
		ret[2] = (*this)[5];
		ret[3] = (*this)[3];
		ret[4] = (*this)[1];
		ret[5] = (*this)[4];
		ret[6] = (*this)[5];
		ret[7] = (*this)[4];
		ret[8] = (*this)[2];
		return ret;
	}

	template<>
	sym_tensor2::operator array1<double,6>()const{
		array1<double,6> ret;
		ret[0] = (*this)[0];
		ret[1] = (*this)[1];
		ret[2] = (*this)[2];
		ret[3] = (*this)[3];
		ret[4] = (*this)[4];
		ret[5] = (*this)[5];
		return ret;
	}

	template<>
	sym_tensor2::operator vector<double>()const{
		vector<double> ret(6);
		ret[0] = (*this)[0];
		ret[1] = (*this)[1];
		ret[2] = (*this)[2];
		ret[3] = (*this)[3];
		ret[4] = (*this)[4];
		ret[5] = (*this)[5];
		return ret;
	}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	sym_tensor2 operator +( const sym_tensor2& t1, const sym_tensor2& t2 ){
		sym_tensor2 ret;
		addition_1<double>( ret.get(), t1.get(), t2.get(), 6, 6 );
		return ret;
	}

	sym_tensor2 operator -( const sym_tensor2& t1, const sym_tensor2& t2 ){
		sym_tensor2 ret;
		subtraction_1<double>( ret.get(), t1.get(), t2.get(), 6, 6 );
		return ret;
	}

	sym_tensor2 operator *( const double s, const sym_tensor2& t ){
		sym_tensor2 ret;
		multiplication_1<double>( ret.get(), s, t.get(), 6 );
		return ret;
	}

	sym_tensor2 operator *( const sym_tensor2& t, const double s ){
		return s*t;
	}

	sym_tensor2 operator /( const sym_tensor2& t, const double s ){
		sym_tensor2 ret;
		division_1<double>( ret.get(), s, t.get(), 6 );
		return ret;
	}


}//end of namespace arr