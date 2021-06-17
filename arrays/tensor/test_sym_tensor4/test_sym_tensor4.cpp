#include <iostream>
#include <assert.h>
#include "arrays.h"

void check_operator_square_brackets_const( const arr::sym_tensor4& t ){
	for( unsigned int i=0; i<21; i++ ){
		assert( t[i] == static_cast<double>(i+1.0) );
	}
}

int main( int argc, char* argv[] ){

	//@Host インスタンスを作成する
	{
		arr::sym_tensor4 t;
		assert( &t != nullptr );
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == 0.0 );
		}
	}
	//@Host sym_tensor4のサイズが21である　size関数が使える
	{
		arr::sym_tensor4 t;
		assert( t.size() == 21 );
	}
	//@Host sym_tensor4のメンバへ[]演算子を使って代入できる
	{
		arr::sym_tensor4 t;
		for( unsigned int i=0; i<21; i++ ){
			t[i] = static_cast<double>(i+1.0);
		}
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>(i+1.0) );
		}
	}
	//@Host sym_tensor4のメンバを[]演算子を使って参照できる
	{
		arr::sym_tensor4 t;
		for( unsigned int i=0; i<21; i++ ){
			t[i] = static_cast<double>(i+1.0);
		}
		check_operator_square_brackets_const( t );
	}
	//@Host メンバイニシャライザ
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>(i+1.0) );
		}
	}
	//@Host =演算子はdeep copyか?
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2;
		t2 = t1;
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2( t1 );
		assert( t1.get() != t2.get() );
		t2[1] = 3.0;
		assert( t1[0] == t2[0] );
		assert( t1[1] != t2[1] );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::sym_tensor4 t;
		t.fill( 4.0 );
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 4.0 );
		}
	}
	//@Host zero関数
	{
		arr::sym_tensor4 t = arr::sym_tensor4::zero();
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 0.0 );
		}
	}
	//@Host constant関数
	{
		arr::sym_tensor4 t = arr::sym_tensor4::constant( 5.0 );
		for( unsigned int i=0; i<t.size(); i++ ){
			assert( t[i] == 5.0 );
		}
	}
	//@Host ind関数
	{
		arr::sym_tensor4 t = arr::sym_tensor4::idn();
		for( unsigned int i=0; i<t.size(); i++ ){
			if( i==0 || i==6 || i==11 ){
				assert( t[i] == 1.0 );
			}else if( i==15 || i==18 || i==20 ){
				assert( t[i] == 0.5 );
			}else{
				assert( t[i] == 0.0 );
			}
		}
	}
	//@Host show_in_mat関数
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		std::cout << "test show_in_mat @Host: sym_tensor4{1.0,2.0,3.0,...,21.0}" << std::endl;
		t.show_in_mat();
	}
	//@Host += scalar
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		t += 5.0;
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>(i+1.0+5.0) );
		}
	}
	//@Host += sym_tensor4
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		t1 += t2;
		for( unsigned int i=0; i<21; i++ ){
			assert( t1[i] == static_cast<double>((i+1.0)*2.0) );
		}
	}
	//@Host -= scalar
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		t -= 5.0;
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>(i+1.0-5.0) );
		}
	}
	//@Host -= sym_tensor4
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		t1 -= t2;
		for( unsigned int i=0; i<21; i++ ){
			assert( t1[i] == 0.0 );
		}
	}
	//@Host *= s
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		double s = 10.0;
		t *= s;
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>((i+1.0)*10.0) );
		}
	}
	//@Host /= s
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		double s = 10.0;
		t /= s;
		for( unsigned int i=0; i<21; i++ ){
			assert( t[i] == static_cast<double>((i+1.0)/10.0) );
		}
	}
	//@Host 単項マイナス
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = -t1;
		for( unsigned int i=0; i<21; i++ ){
			assert( t2[i] == static_cast<double>( -(i+1.0) ) );
		}
	}
	//@Host 比較演算子 ==
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		assert( t1 == t2 );
	}
	//@Host 比較演算子 !=
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 7.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		assert( t1 != t2 );
	}
	//@Host dbdot_prdct sym_tensor4
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 check = {168, 344, 479, 575, 633, 669,
		                          721, 1002, 1199, 1318, 1395,
		                          1397, 1672, 1837, 1944,
		                          2004, 2202, 2330,
		                          2421, 2562,
		                          2712};
		assert( t1.dbdot_prdct(t2) == check );
	}
	//@Host dbdot_prdct sym_tensor2
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       8.0, 9.0,10.0,11.0,12.0,
		                       15.0,16.0,17.0,18.0,
		                       22.0,23.0,24.0,
		                       29.0,30.0,
		                       36.0 };
		arr::sym_tensor2 t2 = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::sym_tensor2 t = t1.dbdot_prdct( t2 );
		assert( t[ 0] == 168.0 && t[ 1] == 379.0 && t[ 2] == 580.0 && t[ 3] == 766.0 && t[ 4] == 912.0 && t[ 5] ==1008.0 );
	}
	//@Host sym_tensor4 + sym_tensor4
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 check = {2.0, 4.0, 6.0, 8.0,10.0,12.0,
		                         14.0,16.0,18.0,20.0,22.0,
		                         24.0,26.0,28.0,30.0,
		                         32.0,34.0,36.0,
		                         38.0,40.0,
		                         42.0 };
		assert( t1+t2 == check );
	}
	//@Host sym_tensor4 - sym_tensor4
	{
		arr::sym_tensor4 t1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 t2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		assert( t1-t2 == arr::sym_tensor4::zero() );
	}
	//@Host sym_tensor4 * s
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 check = { 10.0, 20.0, 30.0, 40.0, 50.0, 60.0,
		                           70.0, 80.0, 90.0,100.0,110.0,
		                          120.0,130.0,140.0,150.0,
		                          160.0,170.0,180.0,
		                          190.0,200.0,
		                          210.0 };
		assert( 10*t == check );
	}
	//@Host sym_tensor4 / s
	{
		arr::sym_tensor4 t = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
		                       7.0, 8.0, 9.0,10.0,11.0,
		                      12.0,13.0,14.0,15.0,
		                      16.0,17.0,18.0,
		                      19.0,20.0,
		                      21.0 };
		arr::sym_tensor4 check = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6,
		                           0.7, 0.8, 0.9, 1.0, 1.1,
		                           1.2, 1.3, 1.4, 1.5,
		                           1.6, 1.7, 1.8,
		                           1.9, 2.0,
		                           2.1 };
		assert( t/10.0 == check );
	}

	std::cout << "END OF TEST (sym_tensor4)" << std::endl;
	return 0;
}