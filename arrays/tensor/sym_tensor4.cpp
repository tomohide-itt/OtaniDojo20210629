#include "sym_tensor2.h"
#include "sym_tensor4.h"
#include "../array/array2.h"
#include "../vector/matrix.h"
#include <math.h>

namespace arr{
	sym_tensor4::sym_tensor4() :array1<double,21>(){
		//for( unsigned int i=0; i<sz; i++ ) vals[i] = 0.0;
		vals[ 0] = 0.0; vals[ 1] = 0.0; vals[ 2] = 0.0; vals[ 3] = 0.0; vals[ 4] = 0.0; vals[ 5] = 0.0;
		vals[ 6] = 0.0; vals[ 7] = 0.0; vals[ 8] = 0.0; vals[ 9] = 0.0; vals[10] = 0.0;
		vals[11] = 0.0; vals[12] = 0.0; vals[13] = 0.0; vals[14] = 0.0;
		vals[15] = 0.0; vals[16] = 0.0; vals[17] = 0.0;
		vals[18] = 0.0; vals[19] = 0.0;
		vals[20] = 0.0;
	}

	sym_tensor4::sym_tensor4( std::initializer_list<double> init ){
		for( unsigned int i=0; i<msize; i++ ) vals[i] = 0.0;
		unsigned int min_sz = ( static_cast<unsigned int>(init.size()) > this->size())? this->size() : static_cast<unsigned int>(init.size());
		for( unsigned int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	sym_tensor4 sym_tensor4::idn(){
		sym_tensor4 ret;
		ret.vals[ 0] = 1.0; ret.vals[ 1] = 0.0; ret.vals[ 2] = 0.0; ret.vals[ 3] = 0.0; ret.vals[ 4] = 0.0; ret.vals[ 5] = 0.0;
		ret.vals[ 6] = 1.0; ret.vals[ 7] = 0.0; ret.vals[ 8] = 0.0; ret.vals[ 9] = 0.0; ret.vals[10] = 0.0;
		ret.vals[11] = 1.0; ret.vals[12] = 0.0; ret.vals[13] = 0.0; ret.vals[14] = 0.0;
		ret.vals[15] = 0.5; ret.vals[16] = 0.0; ret.vals[17] = 0.0;
		ret.vals[18] = 0.5; ret.vals[19] = 0.0;
		ret.vals[20] = 0.5;
		return ret;
	}

	sym_tensor4 sym_tensor4::zero(){
		sym_tensor4 ret;
		ret.vals[ 0] = 0.0; ret.vals[ 1] = 0.0; ret.vals[ 2] = 0.0; ret.vals[ 3] = 0.0; ret.vals[ 4] = 0.0; ret.vals[ 5] = 0.0;
		ret.vals[ 6] = 0.0; ret.vals[ 7] = 0.0; ret.vals[ 8] = 0.0; ret.vals[ 9] = 0.0; ret.vals[10] = 0.0;
		ret.vals[11] = 0.0; ret.vals[12] = 0.0; ret.vals[13] = 0.0; ret.vals[14] = 0.0;
		ret.vals[15] = 0.0; ret.vals[16] = 0.0; ret.vals[17] = 0.0;
		ret.vals[18] = 0.0; ret.vals[19] = 0.0;
		ret.vals[20] = 0.0;
		return ret;
	}

	sym_tensor4 sym_tensor4::constant( const double& val ){
		sym_tensor4 ret;
		ret.vals[ 0] = val; ret.vals[ 1] = val; ret.vals[ 2] = val; ret.vals[ 3] = val; ret.vals[ 4] = val; ret.vals[ 5] = val;
		ret.vals[ 6] = val; ret.vals[ 7] = val; ret.vals[ 8] = val; ret.vals[ 9] = val; ret.vals[10] = val;
		ret.vals[11] = val; ret.vals[12] = val; ret.vals[13] = val; ret.vals[14] = val;
		ret.vals[15] = val; ret.vals[16] = val; ret.vals[17] = val;
		ret.vals[18] = val; ret.vals[19] = val;
		ret.vals[20] = val;
		return ret;
	}

	void sym_tensor4::show_in_mat( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		stream << std::setw(width) << (*this)[ 0];	//1111
		stream << std::setw(width) << (*this)[ 1];
		stream << std::setw(width) << (*this)[ 2];
		stream << std::setw(width) << (*this)[ 3];
		stream << std::setw(width) << (*this)[ 4];
		stream << std::setw(width) << (*this)[ 5] << std::endl;
		stream << std::setw(width) << (*this)[ 1];	//2211
		stream << std::setw(width) << (*this)[ 6];
		stream << std::setw(width) << (*this)[ 7];
		stream << std::setw(width) << (*this)[ 8];
		stream << std::setw(width) << (*this)[ 9];
		stream << std::setw(width) << (*this)[10] << std::endl;
		stream << std::setw(width) << (*this)[ 2];	//3311
		stream << std::setw(width) << (*this)[ 7];
		stream << std::setw(width) << (*this)[11];
		stream << std::setw(width) << (*this)[12];
		stream << std::setw(width) << (*this)[13];
		stream << std::setw(width) << (*this)[14] << std::endl;
		stream << std::setw(width) << (*this)[ 3];	//1211
		stream << std::setw(width) << (*this)[ 8];
		stream << std::setw(width) << (*this)[12];
		stream << std::setw(width) << (*this)[15];
		stream << std::setw(width) << (*this)[16];
		stream << std::setw(width) << (*this)[17] << std::endl;
		stream << std::setw(width) << (*this)[ 4];	//2311
		stream << std::setw(width) << (*this)[ 9];
		stream << std::setw(width) << (*this)[13];
		stream << std::setw(width) << (*this)[16];
		stream << std::setw(width) << (*this)[18];
		stream << std::setw(width) << (*this)[19] << std::endl;
		stream << std::setw(width) << (*this)[ 5];	//3111
		stream << std::setw(width) << (*this)[10];
		stream << std::setw(width) << (*this)[14];
		stream << std::setw(width) << (*this)[17];
		stream << std::setw(width) << (*this)[19];
		stream << std::setw(width) << (*this)[20] << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	sym_tensor4 sym_tensor4::operator -() const{
		sym_tensor4 ret;
		unary_minus_1<double>( this->get(), ret.get(), 21 );
		return ret;
	}


	/*
	__host__ __device__
	sym_tensor4 sym_tensor4::dot_prdct( const sym_tensor2& t )const{
		sym_tensor4 ret;
		ret[0*6+0] = (*this)[0*6+0]*t[0] + (*this)[0*6+3]*t[3] + (*this)[0*6+5]*t[5];
		ret[0*6+1] = (*this)[0*6+3]*t[3] + (*this)[0*6+1]*t[1] + (*this)[0*6+4]*t[4];
		ret[0*6+2] = (*this)[0*6+5]*t[5] + (*this)[0*6+4]*t[4] + (*this)[0*6+2]*t[2];
		ret[0*6+3] = (*this)[0*6+0]*t[3] + (*this)[0*6+3]*t[1] + (*this)[0*6+5]*t[4];
		ret[0*6+4] = (*this)[0*6+3]*t[5] + (*this)[0*6+1]*t[4] + (*this)[0*6+4]*t[2];
		ret[0*6+5] = (*this)[0*6+5]*t[0] + (*this)[0*6+4]*t[3] + (*this)[0*6+2]*t[5];
		ret[1*6+0] = (*this)[1*6+0]*t[0] + (*this)[1*6+3]*t[3] + (*this)[1*6+5]*t[5];
		ret[1*6+1] = (*this)[1*6+3]*t[3] + (*this)[1*6+1]*t[1] + (*this)[1*6+4]*t[4];
		ret[1*6+2] = (*this)[1*6+5]*t[5] + (*this)[1*6+4]*t[4] + (*this)[1*6+2]*t[2];
		ret[1*6+3] = (*this)[1*6+0]*t[3] + (*this)[1*6+3]*t[1] + (*this)[1*6+5]*t[4];
		ret[1*6+4] = (*this)[1*6+3]*t[5] + (*this)[1*6+1]*t[4] + (*this)[1*6+4]*t[2];
		ret[1*6+5] = (*this)[1*6+5]*t[0] + (*this)[1*6+4]*t[3] + (*this)[1*6+2]*t[5];
		ret[2*6+0] = (*this)[2*6+0]*t[0] + (*this)[2*6+3]*t[3] + (*this)[2*6+5]*t[5];
		ret[2*6+1] = (*this)[2*6+3]*t[3] + (*this)[2*6+1]*t[1] + (*this)[2*6+4]*t[4];
		ret[2*6+2] = (*this)[2*6+5]*t[5] + (*this)[2*6+4]*t[4] + (*this)[2*6+2]*t[2];
		ret[2*6+3] = (*this)[2*6+0]*t[3] + (*this)[2*6+3]*t[1] + (*this)[2*6+5]*t[4];
		ret[2*6+4] = (*this)[2*6+3]*t[5] + (*this)[2*6+1]*t[4] + (*this)[2*6+4]*t[2];
		ret[2*6+5] = (*this)[2*6+5]*t[0] + (*this)[2*6+4]*t[3] + (*this)[2*6+2]*t[5];
		ret[3*6+0] = (*this)[3*6+0]*t[0] + (*this)[3*6+3]*t[3] + (*this)[3*6+5]*t[5];
		ret[3*6+1] = (*this)[3*6+3]*t[3] + (*this)[3*6+1]*t[1] + (*this)[3*6+4]*t[4];
		ret[3*6+2] = (*this)[3*6+5]*t[5] + (*this)[3*6+4]*t[4] + (*this)[3*6+2]*t[2];
		ret[3*6+3] = (*this)[3*6+0]*t[3] + (*this)[3*6+3]*t[1] + (*this)[3*6+5]*t[4];
		ret[3*6+4] = (*this)[3*6+3]*t[5] + (*this)[3*6+1]*t[4] + (*this)[3*6+4]*t[2];
		ret[3*6+5] = (*this)[3*6+5]*t[0] + (*this)[3*6+4]*t[3] + (*this)[3*6+2]*t[5];
		ret[4*6+0] = (*this)[4*6+0]*t[0] + (*this)[4*6+3]*t[3] + (*this)[4*6+5]*t[5];
		ret[4*6+1] = (*this)[4*6+3]*t[3] + (*this)[4*6+1]*t[1] + (*this)[4*6+4]*t[4];
		ret[4*6+2] = (*this)[4*6+5]*t[5] + (*this)[4*6+4]*t[4] + (*this)[4*6+2]*t[2];
		ret[4*6+3] = (*this)[4*6+0]*t[3] + (*this)[4*6+3]*t[1] + (*this)[4*6+5]*t[4];
		ret[4*6+4] = (*this)[4*6+3]*t[5] + (*this)[4*6+1]*t[4] + (*this)[4*6+4]*t[2];
		ret[4*6+5] = (*this)[4*6+5]*t[0] + (*this)[4*6+4]*t[3] + (*this)[4*6+2]*t[5];
		ret[5*6+0] = (*this)[5*6+0]*t[0] + (*this)[5*6+3]*t[3] + (*this)[5*6+5]*t[5];
		ret[5*6+1] = (*this)[5*6+3]*t[3] + (*this)[5*6+1]*t[1] + (*this)[5*6+4]*t[4];
		ret[5*6+2] = (*this)[5*6+5]*t[5] + (*this)[5*6+4]*t[4] + (*this)[5*6+2]*t[2];
		ret[5*6+3] = (*this)[5*6+0]*t[3] + (*this)[5*6+3]*t[1] + (*this)[5*6+5]*t[4];
		ret[5*6+4] = (*this)[5*6+3]*t[5] + (*this)[5*6+1]*t[4] + (*this)[5*6+4]*t[2];
		ret[5*6+5] = (*this)[5*6+5]*t[0] + (*this)[5*6+4]*t[3] + (*this)[5*6+2]*t[5];
		return ret;
	}
	*/

	sym_tensor2 sym_tensor4::dbdot_prdct( const sym_tensor2& t )const{
		return t.dbdot_prdct( *this );
	}

	sym_tensor4 sym_tensor4::dbdot_prdct( const sym_tensor4& t )const{
		sym_tensor4 ret;
		//1111 = 1111*1111 + 1122*2211 + 1133*3311 + 2.0*( 1112*1211 + 1123*2311 + 1131*3111 )
		//1122 = 1111*1122 + 1122*2222 + 1133*3322 + 2.0*( 1112*1222 + 1123*2322 + 1131*3122 )
		//1133 = 1111*1133 + 1122*2233 + 1133*3333 + 2.0*( 1112*1233 + 1123*2333 + 1131*3133 )
		//1112 = 1111*1112 + 1122*2212 + 1133*3312 + 2.0*( 1112*1212 + 1123*2312 + 1131*3112 )
		//1123 = 1111*1123 + 1122*2223 + 1133*3323 + 2.0*( 1112*1223 + 1123*2323 + 1131*3123 )
		//1131 = 1111*1131 + 1122*2231 + 1133*3331 + 2.0*( 1112*1231 + 1123*2331 + 1131*3131 )
		ret[ 0] = (*this)[ 0]*t[ 0] + (*this)[ 1]*t[ 1] + (*this)[ 2]*t[ 2] + 2.0*( (*this)[ 3]*t[ 3] + (*this)[ 4]*t[ 4] + (*this)[ 5]*t[ 5] );
		ret[ 1] = (*this)[ 0]*t[ 1] + (*this)[ 1]*t[ 6] + (*this)[ 2]*t[ 7] + 2.0*( (*this)[ 3]*t[ 8] + (*this)[ 4]*t[ 9] + (*this)[ 5]*t[10] );
		ret[ 2] = (*this)[ 0]*t[ 2] + (*this)[ 1]*t[ 7] + (*this)[ 2]*t[11] + 2.0*( (*this)[ 3]*t[12] + (*this)[ 4]*t[13] + (*this)[ 5]*t[14] );
		ret[ 3] = (*this)[ 0]*t[ 3] + (*this)[ 1]*t[ 8] + (*this)[ 2]*t[12] + 2.0*( (*this)[ 3]*t[15] + (*this)[ 4]*t[16] + (*this)[ 5]*t[17] );
		ret[ 4] = (*this)[ 0]*t[ 4] + (*this)[ 1]*t[ 9] + (*this)[ 2]*t[13] + 2.0*( (*this)[ 3]*t[16] + (*this)[ 4]*t[18] + (*this)[ 5]*t[19] );
		ret[ 5] = (*this)[ 0]*t[ 5] + (*this)[ 1]*t[10] + (*this)[ 2]*t[14] + 2.0*( (*this)[ 3]*t[17] + (*this)[ 4]*t[19] + (*this)[ 5]*t[20] );
		//2222 = 2211*1122 + 2222*2222 + 2233*3322 + 2.0*( 2212*1222 + 2223*2322 + 2231*3122 )
		//2233 = 2211*1133 + 2222*2233 + 2233*3333 + 2.0*( 2212*1233 + 2223*2333 + 2231*3133 )
		//2212 = 2211*1112 + 2222*2212 + 2233*3312 + 2.0*( 2212*1212 + 2223*2312 + 2231*3112 )
		//2223 = 2211*1123 + 2222*2223 + 2233*3323 + 2.0*( 2212*1223 + 2223*2323 + 2231*3123 )
		//2231 = 2211*1131 + 2222*2231 + 2233*3331 + 2.0*( 2212*1231 + 2223*2331 + 2231*3131 )
		ret[ 6] = (*this)[ 1]*t[ 1] + (*this)[ 6]*t[ 6] + (*this)[ 7]*t[ 7] + 2.0*( (*this)[ 8]*t[ 8] + (*this)[ 9]*t[ 9] + (*this)[10]*t[10] );
		ret[ 7] = (*this)[ 1]*t[ 2] + (*this)[ 6]*t[ 7] + (*this)[ 7]*t[11] + 2.0*( (*this)[ 8]*t[12] + (*this)[ 9]*t[13] + (*this)[10]*t[14] );
		ret[ 8] = (*this)[ 1]*t[ 3] + (*this)[ 6]*t[ 8] + (*this)[ 7]*t[12] + 2.0*( (*this)[ 8]*t[15] + (*this)[ 9]*t[16] + (*this)[10]*t[17] );
		ret[ 9] = (*this)[ 1]*t[ 4] + (*this)[ 6]*t[ 9] + (*this)[ 7]*t[13] + 2.0*( (*this)[ 8]*t[16] + (*this)[ 9]*t[18] + (*this)[10]*t[19] );
		ret[10] = (*this)[ 1]*t[ 5] + (*this)[ 6]*t[10] + (*this)[ 7]*t[14] + 2.0*( (*this)[ 8]*t[17] + (*this)[ 9]*t[19] + (*this)[10]*t[20] );
		//3333 = 3311*1133 + 3322*2233 + 3333*3333 + 2.0*( 3312*1233 + 3323*2333 + 3331*3133 )
		//3312 = 3311*1112 + 3322*2212 + 3333*3312 + 2.0*( 3312*1212 + 3323*2312 + 3331*3112 )
		//3323 = 3311*1123 + 3322*2223 + 3333*3323 + 2.0*( 3312*1223 + 3323*2323 + 3331*3123 )
		//3331 = 3311*1131 + 3322*2231 + 3333*3331 + 2.0*( 3312*1231 + 3323*2331 + 3331*3131 )
		ret[11] = (*this)[ 2]*t[ 2] + (*this)[ 7]*t[ 7] + (*this)[11]*t[11] + 2.0*( (*this)[12]*t[12] + (*this)[13]*t[13] + (*this)[14]*t[14] );
		ret[12] = (*this)[ 2]*t[ 3] + (*this)[ 7]*t[ 8] + (*this)[11]*t[12] + 2.0*( (*this)[12]*t[15] + (*this)[13]*t[16] + (*this)[14]*t[17] );
		ret[13] = (*this)[ 2]*t[ 4] + (*this)[ 7]*t[ 9] + (*this)[11]*t[13] + 2.0*( (*this)[12]*t[16] + (*this)[13]*t[18] + (*this)[14]*t[19] );
		ret[14] = (*this)[ 2]*t[ 5] + (*this)[ 7]*t[10] + (*this)[11]*t[14] + 2.0*( (*this)[12]*t[17] + (*this)[13]*t[19] + (*this)[14]*t[20] );
		//1212 = 1211*1112 + 1222*2212 + 1233*3312 + 2.0*( 1212*1212 + 1223*2312 + 1231*3112 )
		//1223 = 1211*1123 + 1222*2223 + 1233*3323 + 2.0*( 1212*1223 + 1223*2323 + 1231*3123 )
		//1231 = 1211*1131 + 1222*2231 + 1233*3331 + 2.0*( 1212*1231 + 1223*2331 + 1231*3131 )
		ret[15] = (*this)[ 3]*t[ 3] + (*this)[ 8]*t[ 8] + (*this)[12]*t[12] + 2.0*( (*this)[15]*t[15] + (*this)[16]*t[16] + (*this)[17]*t[17] );
		ret[16] = (*this)[ 3]*t[ 4] + (*this)[ 8]*t[ 9] + (*this)[12]*t[13] + 2.0*( (*this)[15]*t[16] + (*this)[16]*t[18] + (*this)[17]*t[19] );
		ret[17] = (*this)[ 3]*t[ 5] + (*this)[ 8]*t[10] + (*this)[12]*t[14] + 2.0*( (*this)[15]*t[17] + (*this)[16]*t[19] + (*this)[17]*t[20] );
		//2323 = 2311*1123 + 2322*2223 + 2333*3323 + 2.0*( 2312*1223 + 2323*2323 + 2331*3123 )
		//2331 = 2311*1131 + 2322*2231 + 2333*3331 + 2.0*( 2312*1231 + 2323*2331 + 2331*3131 )
		ret[18] = (*this)[ 4]*t[ 4] + (*this)[ 9]*t[ 9] + (*this)[13]*t[13] + 2.0*( (*this)[16]*t[16] + (*this)[18]*t[18] + (*this)[19]*t[19] );
		ret[19] = (*this)[ 4]*t[ 5] + (*this)[ 9]*t[10] + (*this)[13]*t[14] + 2.0*( (*this)[16]*t[17] + (*this)[18]*t[19] + (*this)[19]*t[20] );
		//3131 = 3111*1131 + 3122*2231 + 3133*3331 + 2.0*( 3112*1231 + 3123*2331 + 3131*3131 )
		ret[20] = (*this)[ 5]*t[ 5] + (*this)[10]*t[10] + (*this)[14]*t[14] + 2.0*( (*this)[17]*t[17] + (*this)[19]*t[19] + (*this)[20]*t[20] );
		return ret;
	}

	template<>
	sym_tensor4::operator array2<double,6,6>()const{
		array2<double,6,6> ret;
		ret(0,0) = (*this)[ 0]; ret(0,1) = (*this)[ 1]; ret(0,2) = (*this)[ 2]; ret(0,3) = (*this)[ 3]; ret(0,4) = (*this)[ 4]; ret(0,5) = (*this)[ 5];
		ret(1,0) = (*this)[ 1]; ret(1,1) = (*this)[ 6]; ret(1,2) = (*this)[ 7]; ret(1,3) = (*this)[ 8]; ret(1,4) = (*this)[ 9]; ret(1,5) = (*this)[10];
		ret(2,0) = (*this)[ 2]; ret(2,1) = (*this)[ 7]; ret(2,2) = (*this)[11]; ret(2,3) = (*this)[12]; ret(2,4) = (*this)[13]; ret(2,5) = (*this)[14];
		ret(3,0) = (*this)[ 3]; ret(3,1) = (*this)[ 8]; ret(3,2) = (*this)[12]; ret(3,3) = (*this)[15]; ret(3,4) = (*this)[16]; ret(3,5) = (*this)[17];
		ret(4,0) = (*this)[ 4]; ret(4,1) = (*this)[ 9]; ret(4,2) = (*this)[13]; ret(4,3) = (*this)[16]; ret(4,4) = (*this)[18]; ret(4,5) = (*this)[19];
		ret(5,0) = (*this)[ 5]; ret(5,1) = (*this)[10]; ret(5,2) = (*this)[14]; ret(5,3) = (*this)[17]; ret(5,4) = (*this)[19]; ret(5,5) = (*this)[20];
		return ret;
	}

	template<>
	sym_tensor4::operator matrix<double>()const{
		matrix<double> ret(6,6);
		ret(0,0) = (*this)[ 0]; ret(0,1) = (*this)[ 1]; ret(0,2) = (*this)[ 2]; ret(0,3) = (*this)[ 3]; ret(0,4) = (*this)[ 4]; ret(0,5) = (*this)[ 5];
		ret(1,0) = (*this)[ 1]; ret(1,1) = (*this)[ 6]; ret(1,2) = (*this)[ 7]; ret(1,3) = (*this)[ 8]; ret(1,4) = (*this)[ 9]; ret(1,5) = (*this)[10];
		ret(2,0) = (*this)[ 2]; ret(2,1) = (*this)[ 7]; ret(2,2) = (*this)[11]; ret(2,3) = (*this)[12]; ret(2,4) = (*this)[13]; ret(2,5) = (*this)[14];
		ret(3,0) = (*this)[ 3]; ret(3,1) = (*this)[ 8]; ret(3,2) = (*this)[12]; ret(3,3) = (*this)[15]; ret(3,4) = (*this)[16]; ret(3,5) = (*this)[17];
		ret(4,0) = (*this)[ 4]; ret(4,1) = (*this)[ 9]; ret(4,2) = (*this)[13]; ret(4,3) = (*this)[16]; ret(4,4) = (*this)[18]; ret(4,5) = (*this)[19];
		ret(5,0) = (*this)[ 5]; ret(5,1) = (*this)[10]; ret(5,2) = (*this)[14]; ret(5,3) = (*this)[17]; ret(5,4) = (*this)[19]; ret(5,5) = (*this)[20];
		return ret;
	}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	sym_tensor4 operator +( const sym_tensor4& t1, const sym_tensor4& t2 ){
		sym_tensor4 ret;
		addition_1<double>( ret.get(), t1.get(), t2.get(), 21, 21 );
		return ret;
	}

	sym_tensor4 operator -( const sym_tensor4& t1, const sym_tensor4& t2 ){
		sym_tensor4 ret;
		subtraction_1<double>( ret.get(), t1.get(), t2.get(), 21, 21 );
		return ret;
	}

	sym_tensor4 operator *( const double s, const sym_tensor4& t ){
		sym_tensor4 ret;
		multiplication_1<double>( ret.get(), s, t.get(), 21 );
		return ret;
	}

	sym_tensor4 operator *( const sym_tensor4& t, const double s ){
		return s*t;
	}

	sym_tensor4 operator /( const sym_tensor4& t, const double s ){
		sym_tensor4 ret;
		division_1<double>( ret.get(), s, t.get(), 21 );
		return ret;
	}


}//end of namespace arr
