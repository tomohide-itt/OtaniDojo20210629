#include <iostream>
#include <assert.h>
#include "tensor1.h"
#include "sym_tensor2.h"
#include "tensor2.h"

void check_operator_square_brackets_const( const arr::tensor1& v ){
	assert( v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0 );
}

int main( int argc, char* argv[] ){

	//@Host tensor1のインスタンスを作成する
	{
		arr::tensor1 v;
		assert( &v != nullptr );
		assert( v[0] == 0.0 && v[1] == 0.0 && v[2] == 0.0 );
	}
	//@Host tensor1のサイズが3である　size関数が使える
	{
		arr::tensor1 v;
		assert( v.size() == 3 );
	}
	//@Host tensor1のメンバへ[]演算子を使って代入できる
	{
		arr::tensor1 v;
		v[0] = 1.0;
		v[1] = 2.0;
		v[2] = 3.0;
		assert( v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0 );
	}
	//@Host tensor1のメンバを[]演算子を使って参照できる
	{
		arr::tensor1 v;
		v[0] = 1.0;
		v[1] = 2.0;
		v[2] = 3.0;
		check_operator_square_brackets_const( v );
	}
	//@Host メンバイニシャライザ
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		assert( v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0 );
	}
	//@Host =演算子はdeep copyか?
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2;
		v2 = v1;
		assert( v1.get() != v2.get() );
		v2[1] = 3.0;
		assert( v1[0] == v2[0] );
		assert( v1[1] != v2[1] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2( v1 );
		assert( v1.get() != v2.get() );
		v2[1] = 3.0;
		assert( v1[0] == v2[0] );
		assert( v1[1] != v2[1] );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::tensor1 v;
		v.fill( 4.0 );
		for( unsigned int i=0; i<v.size(); i++ ){
			assert( v[i] == 4.0 );
		}
	}
	//@Host zero関数
	{
		arr::tensor1 v = arr::tensor1::zero();
		assert( v[0] == 0.0 && v[1] == 0.0 && v[2] == 0.0 );
	}
	//@Host constant関数
	{
		arr::tensor1 v = arr::tensor1::constant( 5.0 );
		assert( v[0] == 5.0 && v[1] == 5.0 && v[2] == 5.0 );
	}
	//@Host show_in_mat関数
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		std::cout << "test show_in_mat @Host: tensor1{1.0,2.0,3.0}" << std::endl;
		v.show_in_mat();
	}
	//@Host += scalar
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		v += 5.0;
		assert( v[0] == 6.0 && v[1] == 7.0 && v[2] == 8.0 );
	}
	//@Host += tensor1
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = {4.0,5.0,6.0};
		v1 += v2;
		assert( v1[0] == 5.0 && v1[1] == 7.0 && v1[2] == 9.0 );
	}
	//@Host -= scalar
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		v -= 5.0;
		assert( v[0] == -4.0 && v[1] == -3.0 && v[2] == -2.0 );
	}
	//@Host -= tensor1
	{
		arr::tensor1 v1 = {4.0,5.0,6.0};
		arr::tensor1 v2 = {3.0,2.0,1.0};
		v1 -= v2;
		assert( v1[0] == 1.0 && v1[1] == 3.0 && v1[2] == 5.0 );
	}
	//@Host *= s
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		double s = 10.0;
		v *= s;
		assert( v[0] == 10.0 && v[1] == 20.0 && v[2] == 30.0 );
	}
	//@Host /= s
	{
		arr::tensor1 v = {11.0,22.0,33.0};
		double s = 11.0;
		v /= s;
		assert( v[0] == 1.0 && v[1] == 2.0 && v[2] == 3.0 );
	}
	//@Host 単項マイナス
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = -v1;
		assert( v2[0] == -1.0 && v2[1] == -2.0 && v2[2] == -3.0 );
	}
	//@Host 比較演算子 ==
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = {1.0,2.0,3.0};
		assert( v1 == v2 );
	}
	//@Host 比較演算子 !=
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = {3.0,2.0,1.0};
		assert( v1 != v2 );
	}
	//@Host norm
	{
		arr::tensor1 v = {2.0,3.0,4.0};
		double norm_v = v.norm();
		double check_norm = sqrt( 2.0*2.0 + 3.0*3.0 + 4.0*4.0 );
		assert( norm_v == check_norm );
	}
	//@Host vec_prdct
	{
		arr::tensor1 v1 = {2.0,1.0,3.0};
		arr::tensor1 v2 = {1.0,-1.0,2.0};
		arr::tensor1 ret = v1.vec_prdct( v2 );
		assert( ret[0] == 5.0 && ret[1] == -1.0 && ret[2] == -3.0 );
	}
	//@Host dot_prdct
	{
		arr::tensor1 v1 = {2.0,1.0,3.0};
		arr::tensor1 v2 = {1.0,-1.0,2.0};
		double prdct = v1.dot_prdct(v2);
		assert( prdct == 7.0 );
	}
	//@Host dot_prdct sym_tensor2
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::sym_tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0};
		arr::tensor1 v = v1.dot_prdct( t );
		arr::tensor1 v_chk = {27.0,23.0,25.0};
		assert( v == v_chk );
	}
	//@Host dot_prdct tensor2
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor2 t = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
		arr::tensor1 v = v1.dot_prdct( t );
		arr::tensor1 v_chk = {30.0,36.0,42.0};
		assert( v == v_chk );
	}
	//@Host tens_prdct tensor1
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = {1.0,2.0,3.0};
		arr::tensor2 t = v1.tens_prdct( v2 );
		arr::tensor2 t_chk = {1.0,2.0,3.0,2.0,4.0,6.0,3.0,6.0,9.0};
		assert( t == t_chk );
	}
	//@Host cast to array1
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		arr::array1<double,3> a = static_cast<arr::array1<double,3>>( v );
		assert( a[0] == 1.0 && a[1] == 2.0 && a[2] == 3.0 );
	}
	//@Host tensor1 + tensor1
	{
		arr::tensor1 v1 = {1.0,2.0,3.0};
		arr::tensor1 v2 = {4.0,5.0,6.0};
		arr::tensor1 ret = v1 + v2;
		assert( ret[0] == 5.0 && ret[1] == 7.0 && ret[2] == 9.0 );
	}
	//@Host tensor1 - tensor1
	{
		arr::tensor1 v1 = {4.0,5.0,6.0};
		arr::tensor1 v2 = {3.0,2.0,1.0};
		arr::tensor1 ret = v1 - v2;
		assert( ret[0] == 1.0 && ret[1] == 3.0 && ret[2] == 5.0 );
	}
	//@Host tensor1 * s
	{
		arr::tensor1 v = {1.0,2.0,3.0};
		arr::tensor1 ret = 10.0*v;
		assert( ret[0] == 10.0 && ret[1] == 20.0 && ret[2] == 30.0 );
	}
	//@Host tensor1 / s
	{
		arr::tensor1 v = {11.0,22.0,33.0};
		arr::tensor1 ret = v/11.0;
		assert( ret[0] == 1.0 && ret[1] == 2.0 && ret[2] == 3.0 );
	}

	std::cout << "END OF TEST (tensor1)" << std::endl;
	return 0;
}