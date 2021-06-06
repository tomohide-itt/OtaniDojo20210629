#include <iostream>
#include <assert.h>
#include "array1.h"

void check_operator_square_brackets_const( const arr::array1<int,2>& arr ){
	assert( arr[0] == 1 );
	assert( arr[1] == 2 );
}


int main( int argc, char* argv[] ){

	//@Host array1のインスタンスを作成する
	{
		arr::array1<int,2> arr;
		assert( &arr != nullptr );
	}
	//@Host array1<int,2>を作り，そのsize()が正しい
	{
		arr::array1<int,2> arr;
		assert( arr.size() == 2 );
	}
	//@Host array1のメンバへ[]演算子を使って代入できる
	{
		arr::array1<int,2> arr;
		arr[0] = 1;
		arr[1] = 2;
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
	}
	//@Host array1のメンバを[]演算子を使って参照できる
	{
		arr::array1<int,2> arr;
		arr[0] = 1;
		arr[1] = 2;
		check_operator_square_brackets_const( arr );
	}
	//@Host メンバイニシャライザ
	{
		arr::array1<int,2> arr = {1,2};
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
	}
	//@Host 全ての要素に値を代入するコンストラクタ
	{
		arr::array1<int,2> arr( 3 );
		assert( arr[0] == 3 );
		assert( arr[1] == 3 );
	}
	//@Host show関数(double)
	{
		arr::array1<double,2> arr = {1.1, 2.2};
		printf( "test show @Host: array1{1.1,2.2}\n" );
		arr.show();
	}
	//@Host show関数(int)
	{
		arr::array1<int,2> arr = {1,2};
		printf( "test show @Host: array1{1,2}\n" );
		arr.show();
	}
	//@Host =演算子はdeep copyか?
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2;
		arr2 = arr1;
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2(arr1);
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
	}
	//@Host getで配列へのconstポインタを得る
	{
		arr::array1<int,2> arr1 = {1,2};
		assert( (arr1.get())[0] == 1 && (arr1.get())[1] == 2 );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::array1<int,3> arr;
		arr.fill( 4 );
		for( int i=0; i<arr.size(); i++ ){
			assert( arr[i] == 4 );
		}
	}
	//@Host zero関数
	{
		arr::array1<int,3> zero_arr = arr::array1<int,3>::zero();
		for( int i=0; i<zero_arr.size(); i++ ){
			assert( zero_arr[i] == 0 );
		}
	}
	//@Host constant関数
	{
		arr::array1<int,3> arr = arr::array1<int,3>::constant( 5 );
		for( int i=0; i<arr.size(); i++ ){
			assert( arr[i] == 5 );
		}
	}
	//@Host += scalar
	{
		arr::array1<int,2> arr = {1,2};
		arr += 5;
		assert( arr[0] == 6 );
		assert( arr[1] == 7 );
	}
	//@Host += array1
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {3,4};
		arr1 += arr2;
		assert( arr1[0] == 4 );
		assert( arr1[1] == 6 );
	}
	//@Host -= scalar
	{
		arr::array1<int,2> arr = {1,2};
		int s = 4;
		arr -= s;
		assert( arr[0] == -3 );
		assert( arr[1] == -2 );
	}
	//@Host -= array1
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {3,4};
		arr1 -= arr2;
		assert( arr1[0] == -2 );
		assert( arr1[1] == -2 );
	}
	//@Host *= s
	{
		arr::array1<int,2> arr = {1,2};
		int s = 10;
		arr *= s;
		assert( arr[0] == 10 );
		assert( arr[1] == 20 );
	}
	//@Host /= s
	{
		arr::array1<int,2> arr = {11,22};
		int s = 11;
		arr /= s;
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
	}
	//@Host 単項マイナス
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = -arr1;
		assert( arr2[0] == -1 );
		assert( arr2[1] == -2 );
	}
	//@Host 比較演算子 ==
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {1,2};
		assert( arr1 == arr2 );
	}
	//@Host 比較演算子 !=
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {3,2};
		assert( arr1 != arr2 );
	}
	//@Host dot
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {3,1};
		int prdct = arr1.dot(arr2);
		assert( prdct == 5 );
	}
	//@Host norm
	{
		arr::array1<double,3> arr = {2.0,3.0,4.0};
		double norm_arr = arr.norm();
		double check_norm = sqrt( 2.0*2.0 + 3.0*3.0 + 4.0*4.0 );
		assert( norm_arr == check_norm );
	}
	//@Host vec_prdct
	{
		arr::array1<double,3> arr1 = {2.0,1.0,3.0};
		arr::array1<double,3> arr2 = {1.0,-1.0,2.0};
		arr::array1<double,3> ret = arr1.vec_prdct( arr2 );
		assert( ret[0] == 5.0 && ret[1] == -1.0 && ret[2] == -3.0 );
	}
	//@Host array1 + array1
	{
		arr::array1<int,2> arr1 = { 1, 2 };
		arr::array1<int,2> arr2 = { 3, 4 };
		arr::array1<int,2> ret = arr1 + arr2;
		assert( ret[0] == 4 && ret[1] == 6 );
	}
	//@Host array1 - array1
	{
		arr::array1<int,2> arr1 = { 1, 2 };
		arr::array1<int,2> arr2 = { 3, 4 };
		arr::array1<int,2> ret = arr1 - arr2;
		assert( ret[0] == -2 && ret[1] == -2 );
	}
	//@Host array1 * s
	{
		arr::array1<int,2> arr = { 1, 2 };
		arr::array1<int,2> ret = 10*arr;
		assert( ret[0] == 10 && ret[1] == 20 );
	}
	//@Host array1 / s
	{
		arr::array1<int,2> arr = { 11, 22 };
		arr::array1<int,2> ret = arr/10;
		assert( ret[0] == 1 && ret[1] == 2 );
	}
	//@Host setでポインタの付け替えができ，[]でアクセスできる(ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr.set( p );
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
		arr[0] = 3;
		assert( arr[0] == 3 );
		delete[] p;
	}
	//@Host show関数(int)(ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr.set( p );
		printf( "test show @Host: array1{1,2} (pointer)\n" );
		arr.show();
		delete[] p;
	}
	//@Host =演算子はdeep copyか?(ポインタ管理版)
	{
		arr::array1<int,2> arr1;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr1.set( p );
		arr::array1<int,2> arr2;
		arr2 = arr1;
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
		delete[] p;
	}
	//@Host += (ポインタ管理版)
	{
		arr::array1<int,2> arrp1;
		int* p1 = new int[2];
		p1[0] = 1;
		p1[1] = 2;
		arrp1.set( p1 ); //arrp1 = {1,2}
		//
		arrp1 += 5; //arrp1 = {6,7}
		assert( arrp1[0] == 6 && arrp1[1] == 7 );
		//
		arr::array1<int,2> arr1 = {1,3};
		arrp1 += arr1; //arrp1 = {7,10}
		assert( arrp1[0] == 7 && arrp1[1] == 10 );
		//
		arr1 += arrp1; //arr1 = {8,13}
		assert( arr1[0] == 8 && arr1[1] == 13 );
		delete[] p1;
	}
	//@Host -= (ポインタ管理版)
	{
		arr::array1<int,2> arrp1;
		int* p1 = new int[2];
		p1[0] = 1;
		p1[1] = 2;
		arrp1.set( p1 ); //arrp1 = {1,2}
		//
		arrp1 -= 5; //arrp1 = {-4,-3}
		assert( arrp1[0] == -4 && arrp1[1] == -3 );
		//
		arr::array1<int,2> arr1 = {1,3};
		arrp1 -= arr1; //arrp1 = {-5,-6}
		assert( arrp1[0] == -5 && arrp1[1] == -6 );
		//
		arr1 -= arrp1; //arr1 = {6,9}
		assert( arr1[0] == 6 && arr1[1] == 9 );
		delete[] p1;
	}
	//@Host *= s (ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr.set( p );
		int s = 10;
		arr *= s;
		assert( arr[0] == 10 && arr[1] == 20 );
		delete[] p;
	}
	//@Host /= s (ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 11;
		p[1] = 22;
		arr.set( p );
		int s = 11;
		arr /= s;
		assert( arr[0] == 1 && arr[1] == 2 );
		delete[] p;
	}
	//@Host 単項マイナス (ポインタ管理版)
	{
		arr::array1<int,2> arr1;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr1.set( p );
		arr::array1<int,2> arr2 = -arr1;
		assert( arr2[0] == -1 && arr2[1] == -2 );
		delete[] p;
	}
	//@Host 比較演算子 == (ポインタ管理版)
	{
		arr::array1<int,2> arr1;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr1.set( p );
		arr::array1<int,2> arr2 = {1,2};
		assert( arr1 == arr2 );
		delete[] p;
	}
	//@Host 比較演算子 != (ポインタ管理版)
	{
		arr::array1<int,2> arr1;
		int* p = new int[2];
		p[0] = 1;
		p[1] = 2;
		arr1.set( p );
		arr::array1<int,2> arr2 = {3,2};
		assert( arr1 != arr2 );
		delete[] p;
	}
	//@Host dot (ポインタ管理版)
	{
		arr::array1<int,2> arrp1;
		int* p1 = new int[2];
		p1[0] = 1;
		p1[1] = 2;
		arrp1.set( p1 ); //arrp1 = {1,2}
		//
		arr::array1<int,2> arrp2;
		int* p2 = new int[2];
		p2[0] = 3;
		p2[1] = 1;
		arrp2.set( p2 ); //arrp2 = {3,1}
		//
		arr::array1<int,2> arr2 = {3,1};
		//
		assert( arrp1.dot(arrp2) == 5 );
		assert( arrp1.dot(arr2)  == 5 );
		delete[] p1;
		delete[] p2;
	}
	//@Host norm (ポインタ管理版)
	{
		arr::array1<double,3> arr = {2.0,3.0,4.0};
		double* p = new double[3];
		p[0] = 2.0; p[1] = 3.0; p[2] = 4.0;
		arr.set( p );
		double check_norm = sqrt( 2.0*2.0 + 3.0*3.0 + 4.0*4.0 );
		assert( arr.norm() == check_norm );
		delete[] p;
	}
	//@Host vec_prdct (ポインタ管理版)
	{
		arr::array1<double,3> arrp1;
		double* p1 = new double[3];
		p1[0] = 2.0; p1[1] = 1.0; p1[2] = 3.0;
		arrp1.set( p1 ); //arrp1 = {2.0,1.0,3.0}
		//
		arr::array1<double,3> arrp2;
		double* p2 = new double[3];
		p2[0] = 1.0; p2[1] = -1.0; p2[2] = 2.0;
		arrp2.set( p2 ); //arrp2 = {2.0,1.0,3.0}
		//
		arr::array1<double,3> arr2 = {1.0,-1.0,2.0};
		//
		arr::array1<double,3> check = {5.0,-1.0,-3.0};
		//
		assert( arrp1.vec_prdct(arrp2) == check );
		assert( arrp1.vec_prdct(arr2)  == check );
		delete[] p1;
		delete[] p2;
	}
	//@Host array1 + array1 (ポインタ管理版)
	{
		arr::array1<int,2> arrp1;
		int* p1 = new int[2];
		p1[0] = 1;
		p1[1] = 2;
		arrp1.set( p1 ); //arrp1 = {1,2}
		//
		arr::array1<int,2> arrp2;
		int* p2 = new int[2];
		p2[0] = 3;
		p2[1] = 4;
		arrp2.set( p2 ); //arrp2 = {3,4}
		//
		arr::array1<int,2> arr2 = {3,4};
		//
		arr::array1<int,2> check = {4,6};
		//
		assert( arrp1 + arrp2 == check );
		assert( arrp1 + arr2  == check );
		delete[] p1;
		delete[] p2;
	}
	//@Host array1 - array1 (ポインタ管理版)
	{
		arr::array1<int,2> arrp1;
		int* p1 = new int[2];
		p1[0] = 1;
		p1[1] = 2;
		arrp1.set( p1 ); //arrp1 = {1,2}
		//
		arr::array1<int,2> arrp2;
		int* p2 = new int[2];
		p2[0] = 3;
		p2[1] = 4;
		arrp2.set( p2 ); //arrp2 = {3,4}
		//
		arr::array1<int,2> arr2 = {3,4};
		//
		arr::array1<int,2> check = {-2,-2};
		//
		assert( arrp1 - arrp2 == check );
		assert( arrp1 - arr2  == check );
		delete[] p1;
		delete[] p2;
	}
	//@Host array1 * s (ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 1; p[1] = 2;
		arr.set( p ); //arr = {1,2}
		//
		arr::array1<int,2> check = {10,20};
		assert( 10*arr == check );
		delete[] p;
	}
	//@Host array1 / s (ポインタ管理版)
	{
		arr::array1<int,2> arr;
		int* p = new int[2];
		p[0] = 11; p[1] = 22;
		arr.set( p ); //arr = {1,2}
		//
		arr::array1<int,2> check = {1,2};
		assert( arr/10 == check );
		delete[] p;
	}

	std::cout << "END OF TEST (array1)" << std::endl;
	return 0;
}