#include <iostream>
#include <assert.h>
#include "arrays.h"

void check_operator_square_brackets_const( const arr::sym_tensor2& t ){
	assert( t[0] == 1.0 && t[1] == 2.0 && t[2] == 3.0 &&
		    t[3] == 4.0 && t[4] == 5.0 && t[5] == 6.0 );
}

int main( int argc, char* argv[] ){

	//@Host インスタンスを作成する
	{
		arr::sym_tensor2 t;
		assert( &t != nullptr );
		assert( t[0] == 0.0 && t[1] == 0.0 && t[2] == 0.0 &&
			    t[3] == 0.0 && t[4] == 0.0 && t[5] == 0.0 );
	}
	//@Host sym_tensor2のサイズが6である　size関数が使える
	{
		arr::sym_tensor2 t;
		assert( t.size() == 6 );
	}
	//@Host sym_tensor2のメンバへ[]演算子を使って代入できる
	{
		arr::sym_tensor2 t;
		t[0] = 1.0;
		t[1] = 2.0;
		t[2] = 3.0;
		t[3] = 4.0;
		t[4] = 5.0;
		t[5] = 6.0;
		assert( t[0] == 1.0 && t[1] == 2.0 && t[2] == 3.0 &&
		        t[3] == 4.0 && t[4] == 5.0 && t[5] == 6.0 );
	}
	//@Host sym_tensor2のメンバを[]演算子を使って参照できる
	{
		arr::sym_tensor2 t;
		t[0] = 1.0;
		t[1] = 2.0;
		t[2] = 3.0;
		t[3] = 4.0;
		t[4] = 5.0;
		t[5] = 6.0;
		check_operator_square_brackets_const( t );
	}
	//@Host メンバイニシャライザ
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		assert( t[0] == 1.0 && t[1] == 2.0 && t[2] == 3.0 &&
		        t[3] == 4.0 && t[4] == 5.0 && t[5] == 6.0 );
	}
	//@Host =演算子はdeep copyか?
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2;
		t2 = t1;
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2( t1 );
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::sym_tensor2 t;
		t.fill( 4.0 );
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 4.0 );
		}
	}
	//@Host zero関数
	{
		arr::sym_tensor2 t = arr::sym_tensor2::zero();
		assert( t[0] == 0.0 && t[1] == 0.0 && t[2] == 0.0 &&
		        t[3] == 0.0 && t[4] == 0.0 && t[5] == 0.0 );
	}
	//@Host constant関数
	{
		arr::sym_tensor2 t = arr::sym_tensor2::constant( 5.0 );
		assert( t[0] == 5.0 && t[1] == 5.0 && t[2] == 5.0 &&
		        t[3] == 5.0 && t[4] == 5.0 && t[5] == 5.0 );
	}
	//@Host delta関数
	{
		arr::sym_tensor2 t = arr::sym_tensor2::delta();
		assert( t[0] == 1.0 && t[1] == 1.0 && t[2] == 1.0 &&
		        t[3] == 0.0 && t[4] == 0.0 && t[5] == 0.0 );
	}
	//@Host show_in_mat関数
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		std::cout << "test show_in_mat @Host: sym_tensor2{1.0,2.0,3.0,4.0,5.0,6.0}" << std::endl;
		t.show_in_mat();
	}
	//@Host += scalar
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		t += 5.0;
		assert( t[0] == 6.0 && t[1] == 7.0 && t[2] == 8.0 &&
		        t[3] == 9.0 && t[4] == 10.0 && t[5] == 11.0 );
	}
	//@Host += sym_tensor2
	{
		arr::sym_tensor2 t1 = {9.0,7.0,5.0,3.0,1.0,2.0};
		arr::sym_tensor2 t2 = {1.0,2.0,3.0,4.0,5.0,6.0};
		t1 += t2;
		assert( t1[0] == 10.0 && t1[1] == 9.0 && t1[2] == 8.0 &&
		        t1[3] == 7.0  && t1[4] == 6.0 && t1[5] == 8.0 );
	}
	//@Host -= scalar
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		t -= 5.0;
		assert( t[0] == -4.0 && t[1] == -3.0 && t[2] == -2.0 &&
		        t[3] == -1.0 && t[4] ==  0.0 && t[5] ==  1.0 );
	}
	//@Host -= sym_tensor2
	{
		arr::sym_tensor2 t1 = {9.0,7.0,5.0,3.0,1.0,2.0};
		arr::sym_tensor2 t2 = {1.0,2.0,3.0,4.0,5.0,6.0};
		t1 -= t2;
		assert( t1[0] ==  8.0 && t1[1] ==  5.0 && t1[2] ==  2.0 &&
		        t1[3] == -1.0 && t1[4] == -4.0 && t1[5] == -4.0 );
	}
	//@Host *= s
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double s = 10.0;
		t *= s;
		assert( t[0] == 10.0 && t[1] == 20.0 && t[2] == 30.0 &&
		        t[3] == 40.0 && t[4] == 50.0 && t[5] == 60.0 );
	}
	//@Host /= s
	{
		arr::sym_tensor2 t = {11.0,22.0,33.0,44.0,55.0,66.0};
		double s = 11.0;
		t /= s;
		assert( t[0] == 1.0 && t[1] == 2.0 && t[2] == 3.0 &&
		        t[3] == 4.0 && t[4] == 5.0 && t[5] == 6.0 );
	}
	//@Host 単項マイナス
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = -t1;
		assert( t2[0] == -1.0 && t2[1] == -2.0 && t2[2] == -3.0 &&
		        t2[3] == -4.0 && t2[4] == -5.0 && t2[5] == -6.0 );
	}
	//@Host 比較演算子 ==
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {1.0,2.0,3.0,4.0,5.0,6.0};
		assert( t1 == t2 );
	}
	//@Host 比較演算子 !=
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {1.0,2.0,7.0,4.0,5.0,6.0};
		assert( t1 != t2 );
	}
	//@Host trace
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double trace = t.trace();
		assert( trace == 6.0 );
	}
	//@Host norm
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double norm = t.norm();
		double check_norm = sqrt( 1.0 + 4.0 + 9.0 + 32.0 + 50.0 + 72.0 );
		assert( norm == check_norm );
	}
	//@Host det
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double det = t.det();
		assert( det == 101.0 );
	}
	//@Host inverse
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t_inv = t.inverse();
		assert( t_inv[0] == -19.0/101.0 );
		assert( t_inv[1] == -33.0/101.0 );
		assert( t_inv[2] == -14.0/101.0 ); 
		assert( t_inv[3] ==  18.0/101.0 );
		assert( t_inv[4] ==  19.0/101.0 );
		assert( t_inv[5] ==   8.0/101.0 );
	}
	//@Host deviatoric
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t = t1.deviatoric();
		assert( t[0] == -1.0 && t[1] ==  0.0 && t[2] ==  1.0 &&
		        t[3] ==  4.0 && t[4] ==  5.0 && t[5] ==  6.0 );
	}
	//@Host I1
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double I1 = t.I1();
		assert( I1 == 6.0 );
	}
	//@Host I2
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double I2 = t.I2();
		assert( I2 == -66.0 );
	}
	//@Host I3
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double I3 = t.I3();
		assert( I3 == 101.0 );
	}
	//@Host J2
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		double J2 = t.J2();
		assert( J2 == 78.0 );
	}
	//@Host p
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		double p = sig.p();
		assert( p == 2.0 );
	}
	//@Host s
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 s = sig.s();
		assert( s[0] == -1.0 && s[1] == 0.0 && s[2] == 1.0 && s[3] == 4.0 && s[4] == 5.0 && s[5] == 6.0 );
	}
	//@Host q
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		double q = sig.q();
		assert( q == 3.0*sqrt(26.0) );
	}
	//@Host eta
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 eta = sig.eta();
		assert( eta[0] == -0.5 && eta[1] == 0.0 && eta[2] == 0.5 && eta[3] == 2.0 && eta[4] == 2.5 && eta[5] == 3.0 );
	}
	//@Host eta_star
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 sig0 = {3.0,6.0,3.0,0.0,0.0,0.0};
		double eta_star = sig.eta_star(sig0);
		double eta_star_check = 3.0*sqrt(105.0)/4.0;
		assert( (eta_star - eta_star_check) < 1.0e-5 );
	}
	//@Host eta_rot
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 eta0 = {-0.25,0.5,-0.25,0.0,0.0,0.0};
		double eta_star = sig.eta_rot(eta0);
		double eta_star_check = 3.0*sqrt(105.0)/4.0;
		assert( (eta_star - eta_star_check) < 1.0e-5 );
	}
	//@Host s_bar
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 sig0 = {3.0,6.0,3.0,0.0,0.0,0.0};
		arr::sym_tensor2 s_bar = sig.s_bar( sig0 );
		assert( s_bar[0] == -0.5 && s_bar[1] == -1.0 && s_bar[2] == 1.5 && s_bar[3] == 4.0 && s_bar[4] == 5.0 && s_bar[5] == 6.0 );
	}
	//@Host n_bar
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 sig0 = {3.0,6.0,3.0,0.0,0.0,0.0};
		arr::sym_tensor2 n_bar = sig.n_bar( sig0 );
		assert( (n_bar[0]+0.039841) < 1.0e-5
			 && (n_bar[1]+0.079682) < 1.0e-5
			 && (n_bar[2]-0.119523) < 1.0e-5
			 && (n_bar[3]-0.318728) < 1.0e-5
			 && (n_bar[4]-0.398410) < 1.0e-5
			 && (n_bar[5]-0.478091) < 1.0e-5 );
	}
	//@Host q_bar
	{
		arr::sym_tensor2 sig = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 sig0 = {3.0,6.0,3.0,0.0,0.0,0.0};
		double q_bar = sig.q_bar( sig0 );
		assert( (q_bar-15.37042615) < 1.0e-5 );
	}
	//@Host epsv
	{
		arr::sym_tensor2 eps = {1.0,2.0,3.0,4.0,5.0,6.0};
		double epsv = eps.epsv();
		assert( epsv == 6.0 );
	}
	//@Host epsd
	{
		arr::sym_tensor2 eps = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 epsd = eps.epsd();
		assert( epsd[0] == -1.0 && epsd[1] == 0.0 && epsd[2] == 1.0 && epsd[3] == 4.0 && epsd[4] == 5.0 && epsd[5] == 6.0 );
	}
	//@Host epss
	{
		arr::sym_tensor2 eps = {1.0,2.0,3.0,4.0,5.0,6.0};
		double epss = eps.epss();
		assert( (epss-10.19803903) < 1.0e-5 );
	}
	//@Host eigenvalue
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::array1<double,3> eigenval = t.eigenvalue();
		assert( (eigenval[0]-12.128393)<1.0e-5 && (eigenval[1]+2.033791)<1.0e-5 && (eigenval[2]+4.094602)<1.0e-5 );
	}
	//@Host eigenvector
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::array1<arr::tensor1,3> eigenvec = t.eigenvector();
		assert( (eigenvec[0][0]-0.541851)<1.0e-5 && (eigenvec[0][1]-0.534281)<1.0e-5 && (eigenvec[0][2]-0.648801)<1.0e-5 );
		assert( (eigenvec[1][0]+0.401071)<1.0e-5 && (eigenvec[1][1]-0.842752)<1.0e-5 && (eigenvec[1][2]+0.359041)<1.0e-5 );
		assert( (eigenvec[2][0]-0.738607)<1.0e-5 && (eigenvec[2][1]-0.065669)<1.0e-5 && (eigenvec[2][2]+0.670930)<1.0e-5 );
	}
	//@Host dot_prdct tensor1
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::tensor1 v = t.dot_prdct( v1 );
		assert( v[0] == 27.0 && v[1] == 23.0 && v[2] == 25.0 );
	}
	//@Host dot_prdct sym_tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,1.0,0.0,3.0,1.0};
		arr::sym_tensor2 t = t1.dot_prdct( t1 );
		assert( t[0] ==  2.0 && t[1] == 13.0 && t[2] == 11.0 &&
		        t[3] ==  3.0 && t[4] ==  9.0 && t[5] ==  2.0 );
	}

	//@Host dbdot_prdct sym_tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {1.0,2.0,1.0,0.0,3.0,1.0};
		double ret = t1.dbdot_prdct( t2 );
		assert( ret == 50.0 );
	}
	//@Host tns_prdct sym_tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor4 t = t1.tens_prdct( t2 );
		arr::sym_tensor4 t_chk = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                          4.0, 6.0, 8.0,10.0,12.0,
		                          9.0,12.0,15.0,18.0,
		                          16.0,20.0,24.0,
		                          25.0,30.0,
		                          36.0 };
		assert( t == t_chk );
	}
	//@Host dbdot_prdct sym_tensor4
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       4.0, 6.0, 8.0,10.0,12.0,
		                       9.0,12.0,15.0,18.0,
		                       16.0,20.0,24.0,
		                       25.0,30.0,
		                       36.0 };
		arr::sym_tensor2 t = t1.dbdot_prdct( t2 );
		arr::sym_tensor2 t_chk = { 168.0, 336.0, 504.0, 672.0, 840.0, 1008.0 };
		assert( t == t_chk );
	}

	//@Host cast to tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::tensor2 t = static_cast<arr::tensor2>( t1 );
		arr::tensor2 t_chk = {1.0,4.0,6.0,4.0,2.0,5.0,6.0,5.0,3.0};
		assert( t == t_chk );
	}
	//@Host cast to array1<double,6>
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::array1<double,6> a = static_cast<arr::array1<double,6>>( t );
		assert( a[0] == 1.0 && a[1] == 2.0 && a[2] == 3.0 && a[3] == 4.0 && a[4] == 5.0 && a[5] == 6.0 );
	}
	//@Host cast to vector<double>
	{
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::vector<double> v = static_cast<arr::vector<double>>( t );
		assert( v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0 && v[3] == 4.0 && v[4] == 5.0 && v[5] == 6.0 );
	}

//

	//@Host sym_tensor2 + sym_tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {3.0,2.0,1.0,1.0,2.0,3.0};
		arr::sym_tensor2 t = t1 + t2;
		assert( t[0] ==  4.0 && t[1] ==  4.0 && t[2] ==  4.0 &&
		        t[3] ==  5.0 && t[4] ==  7.0 && t[5] ==  9.0 );
	}
	//@Host sym_tensor2 - sym_tensor2
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t2 = {3.0,2.0,1.0,1.0,2.0,3.0};
		arr::sym_tensor2 t = t1 - t2;
		assert( t[0] == -2.0 && t[1] ==  0.0 && t[2] ==  2.0 &&
		        t[3] ==  3.0 && t[4] ==  3.0 && t[5] ==  3.0 );
	}
	//@Host sym_tensor2 * s
	{
		arr::sym_tensor2 t1 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t = 10.0*t1;
		assert( t[0] == 10.0 && t[1] == 20.0 && t[2] == 30.0 &&
		        t[3] == 40.0 && t[4] == 50.0 && t[5] == 60.0 );
	}
	//@Host sym_tensor2 / s
	{
		arr::sym_tensor2 t1 = {11.0,22.0,33.0,44.0,55.0,66.0};
		arr::sym_tensor2 t = t1/11.0;
		assert( t[0] == 1.0 && t[1] == 2.0 && t[2] == 3.0 &&
		        t[3] == 4.0 && t[4] == 5.0 && t[5] == 6.0 );
	}

	std::cout << "END OF TEST (sym_tensor2)" << std::endl;
	return 0;
}