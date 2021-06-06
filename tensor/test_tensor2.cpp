#include <iostream>
#include <assert.h>
#include "tensor1.h"
#include "tensor2.h"
#include "sym_tensor2.h"
#include "../array/array1.h"

void check_operator_square_brackets_const( const arr::tensor2& t ){
	for( unsigned int i=0; i<9; i++ ){
		assert( t[i] == static_cast<double>(i+1.0) );
	}
}

int main( int argc, char* argv[] ){

	//@Host インスタンスを作成する
	{
		arr::tensor2 t;
		assert( &t != nullptr );
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == 0.0 );
		}
	}
	//@Host tensor2のサイズが9である　size関数が使える
	{
		arr::tensor2 t;
		assert( t.size() == 9 );
	}
	//@Host tensor2のメンバへ[]演算子を使って代入できる
	{
		arr::tensor2 t;
		for( unsigned int i=0; i<9; i++ ){
			t[i] = static_cast<double>(i+1.0);
		}
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>(i+1.0) );
		}
	}
	//@Host tensor2のメンバを[]演算子を使って参照できる
	{
		arr::tensor2 t;
		for( unsigned int i=0; i<9; i++ ){
			t[i] = static_cast<double>(i+1.0);
		}
		check_operator_square_brackets_const( t );
	}
	//@Host メンバイニシャライザ
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>(i+1.0) );
		}
	}
	//@Host =演算子はdeep copyか?
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2;
		t2 = t1;
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2(t1);
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::tensor2 t;
		t.fill( 4.0 );
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 4.0 );
		}
	}
	//@Host zero関数
	{
		arr::tensor2 t = arr::tensor2::zero();
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 0.0 );
		}
	}
	//@Host constant関数
	{
		arr::tensor2 t = arr::tensor2::constant( 5.0 );
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 5.0 );
		}
	}
	//@Host delta関数
	{
		arr::tensor2 t = arr::tensor2::delta();
		for( unsigned int i=0; i<t.size(); i++ ){
			if( i==0 || i==4 || i==8 ){
				assert( t[i] == 1.0 );
			}else{
				assert( t[i] == 0.0 );
			}
		}
	}
	//@Host show_in_mat関数
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		std::cout << "test show_in_mat @Host: tensor2{1.0,2.0,3.0,...,9.0}" << std::endl;
		t.show_in_mat();
	}
	//@Host += scalar
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		t += 5.0;
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>(i+1.0+5.0) );
		}
	}
	//@Host += sym_tensor4
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		t1 += t2;
		for( unsigned int i=0; i<9; i++ ){
			assert( t1[i] == static_cast<double>((i+1.0)*2.0) );
		}
	}
	//@Host -= scalar
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		t -= 5.0;
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>(i+1.0-5.0) );
		}
	}
	//@Host -= sym_tensor4
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		t1 -= t2;
		for( unsigned int i=0; i<9; i++ ){
			assert( t1[i] == 0.0 );
		}
	}
	//@Host *= s
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double s = 10.0;
		t *= s;
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>((i+1.0)*10.0) );
		}
	}
	//@Host /= s
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double s = 10.0;
		t /= s;
		for( unsigned int i=0; i<9; i++ ){
			assert( t[i] == static_cast<double>((i+1.0)/10.0) );
		}
	}
	//@Host 単項マイナス
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = -t1;
		for( unsigned int i=0; i<9; i++ ){
			assert( t2[i] == static_cast<double>( -(i+1.0) ) );
		}
	}
	//@Host 比較演算子 ==
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		assert( t1 == t2 );
	}
	//@Host 比較演算子 !=
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 7.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		assert( t1 != t2 );
	}
	//@Host trace
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double trace = t.trace();
		assert( trace == 15.0 );
	}
	//@Host norm
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double norm = t.norm();
		assert( ( norm - 16.88194 ) < 1.0e-5 );
	}
	//@Host det
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 9.0, 9.0 };
		double det = t.det();
		assert( det == 6.0 );
	}
	//@Host inverse
	{
		arr::tensor2 t = { 1.0, 4.0, 6.0, 4.0, 2.0, 5.0, 6.0, 5.0, 3.0 };
		arr::tensor2 t_inv = t.inverse();
		assert( t_inv[0] == -19.0/101.0 );
		assert( t_inv[4] == -33.0/101.0 );
		assert( t_inv[8] == -14.0/101.0 ); 
		assert( t_inv[1] ==  18.0/101.0 );
		assert( t_inv[5] ==  19.0/101.0 );
		assert( t_inv[2] ==   8.0/101.0 );
	}
	//@Host transpose
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t_tns = t.transpose();
		arr::tensor2 t_tns_chk = { 1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0 };
		assert( t_tns == t_tns_chk );
	}
	//@Host I1
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double I1 = t.I1();
		assert( I1 == 15.0 );
	}
	//@Host I2
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double I2 = t.I2();
		assert( I2 == -18.0 );
	}
	//@Host I3
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 9.0, 9.0 };
		double I3 = t.I3();
		assert( I3 == 6.0 );
	}
	//@Host eigenvalue
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::array1<double,3> eigenval = t.eigenvalue();
		assert( (eigenval[0]-16.11684)<1.0e-5 && (eigenval[1]-0.0)<1.0e-5 && (eigenval[2]+1.11684)<1.0e-5 );
	}
	//@Host eigenvector
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::array1<arr::tensor1,3> eigenvec = t.eigenvector();
		assert( (eigenvec[0][0]-0.215092)<1.0e-5 && (eigenvec[0][1]-0.487097)<1.0e-5 && (eigenvec[0][2]-0.759103)<1.0e-5 );
		assert( (eigenvec[1][0]+0.408248)<1.0e-5 && (eigenvec[1][1]-0.816497)<1.0e-5 && (eigenvec[1][2]+0.408248)<1.0e-5 );
		assert( (eigenvec[2][0]-0.849295)<1.0e-5 && (eigenvec[2][1]-0.093758)<1.0e-5 && (eigenvec[2][2]+0.661780)<1.0e-5 );
	}
	//@Host dot_prdct tensor1
	{
		arr::tensor2 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v = t.dot_prdct( v1 );
		assert( v[0] == 14.0 && v[1] == 32.0 && v[2] == 50.0 );
	}
	//@Host dot_prdct tensor2
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t = t1.dot_prdct( t2 );
		arr::tensor2 t_chk = {30.0,36.0,42.0,66.0,81.0,96.0,102.0,126.0,150.0};
		assert( t == t_chk );
	}
	//@Host dbdot_prdct tensor2
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		double p = t1.dbdot_prdct( t2 );
		assert( p == 285.0 );
	}
	//@Host cast to sym_tensor2
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::sym_tensor2 t = static_cast<arr::sym_tensor2>( t1 );
		arr::sym_tensor2 t_chk = { 1.0, 5.0, 9.0, 3.0, 7.0, 5.0 };
		assert( t == t_chk );
	}
//

	//@Host tensor2 + tensor2
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t = t1 + t2;
		arr::tensor2 t_chk = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0 };
		assert( t == t_chk );
	}
	//@Host tensor2 - tensor2
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t = t1 - t2;
		arr::tensor2 t_chk = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		assert( t == t_chk );
	}
	//@Host tensor2 * s
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t = 10.0*t1;
		arr::tensor2 t_chk = { 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0 };
		assert( t == t_chk );
	}
	//@Host tensor2 / s
	{
		arr::tensor2 t1 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
		arr::tensor2 t = t1/10.0;
		arr::tensor2 t_chk = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
		assert( t == t_chk );
	}

	std::cout << "END OF TEST (tensor2)" << std::endl;
	return 0;
}