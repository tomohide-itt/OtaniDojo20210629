#include <iostream>
#include <assert.h>
#include "arrays.h"

void check_operator_square_brackets_const( const arr::array2<int,2,2>& arr ){
	assert( arr[0] == 1 );
	assert( arr[1] == 2 );
	assert( arr[2] == 3 );
	assert( arr[3] == 4 );
}

int main( int argc, char* argv[] ){
	
	//@Host array2のインスタンスを作成する
	{
		arr::array2<int,2,2> arr;
		assert( &arr != nullptr );
	}
	//@Host array2<int,2,2>を作り，そのsize()が正しい
	{
		arr::array2<int,2,2> arr;
		assert( arr.size() == 4 );
	}
	//@Host array2<int,2,2>を作り，そのrows()が正しい
	{
		arr::array2<int,2,2> arr;
		assert( arr.rows() == 2 );
	}
	//@Host array2<int,2,2>を作り，そのcols()が正しい
	{
		arr::array2<int,2,2> arr;
		assert( arr.cols() == 2 );
	}
	//@Host array2<int,2,2>を作り，そのstride()が正しい
	{
		arr::array2<int,2,2> arr;
		assert( arr.stride() == 2 );
	}
	//@Host array2のメンバへ[]演算子を使って代入できる
	{
		arr::array2<int,2,2> arr;
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
		assert( arr[2] == 3 );
		assert( arr[3] == 4 );
	}
	//@Host array2のメンバを[]演算子を使って参照できる
	{
		arr::array2<int,2,2> arr;
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		check_operator_square_brackets_const( arr );
	}
	//@Host メンバイニシャライザ
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
		assert( arr[2] == 3 );
		assert( arr[3] == 4 );
	}
	//@Host メンバへ(r,c)でアクセスできる
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		assert( arr(0,0)==1 && arr(0,1)==2 && arr(1,0)==3 && arr(1,1)==4 );
	}
	//@Host (r)で行を取り出せる
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		arr::array1<int,2> r0 = {1,2};
		arr::array1<int,2> r1 = {3,4};
		assert( arr(0)==r0 && arr(1)==r1 );
	}
	//@Host show関数(double)
	{
		arr::array2<double,2,2> arr = {1.1, 2.2 ,3.3 ,4.4};
		printf( "test show @Host: array2{1.1, 2.2 ,3.3 ,4.4}\n" );
		arr.show();
	}
	//@Host show関数(int)
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		printf( "test show @Host: array2{1, 2, 3, 4}\n" );
		arr.show();
	}
	//@Host =演算子はdeep copyか?
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2;
		arr2 = arr1;
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
		assert( arr1[2] == arr2[2] );
		assert( arr1[3] == arr2[3] );
	}
	//@Host コピーコンストラクタはdeep copyか?
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2(arr1);
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
		assert( arr1[2] == arr2[2] );
		assert( arr1[3] == arr2[3] );
	}
	//@Host fillで全ての成分に値を代入
	{
		arr::array2<int,3,3> arr;
		arr.fill( 4 );
		for( int i=0; i<arr.size(); i++ ){
			assert( arr[i] == 4 );
		}
	}
	//@Host zero関数
	{
		arr::array2<int,3,3> zero_arr = arr::array2<int,3,3>::zero();
		for( int i=0; i<zero_arr.size(); i++ ){
			assert( zero_arr[i] == 0 );
		}
	}
	//@Host constant関数
	{
		arr::array2<int,3,3> arr = arr::array2<int,3,3>::constant( 5 );
		for( int i=0; i<arr.size(); i++ ){
			assert( arr[i] == 5 );
		}
	}
	//@Host += scalar
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		arr += 5;
		assert( arr[0] == 6 );
		assert( arr[1] == 7 );
		assert( arr[2] == 8 );
		assert( arr[3] == 9 );
	}
	//@Host += array2
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = {3,4,5,6};
		arr1 += arr2;
		assert( arr1[0] == 4 );
		assert( arr1[1] == 6 );
		assert( arr1[2] == 8 );
		assert( arr1[3] == 10 );
	}
	//@Host -= scalar
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		int s = 4;
		arr -= s;
		assert( arr[0] == -3 );
		assert( arr[1] == -2 );
		assert( arr[2] == -1 );
		assert( arr[3] == 0 );
	}
	//@Host -= array2
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = {3,4,5,6};
		arr1 -= arr2;
		assert( arr1[0] == -2 );
		assert( arr1[1] == -2 );
		assert( arr1[2] == -2 );
		assert( arr1[3] == -2 );
	}
	//@Host *= s
	{
		arr::array2<int,2,2> arr = {1,2,3,4};
		int s = 10;
		arr *= s;
		assert( arr[0] == 10 );
		assert( arr[1] == 20 );
		assert( arr[2] == 30 );
		assert( arr[3] == 40 );
	}
	//@Host /= s
	{
		arr::array2<int,2,2> arr = {11,22,33,44};
		int s = 11;
		arr /= s;
		assert( arr[0] == 1 );
		assert( arr[1] == 2 );
		assert( arr[2] == 3 );
		assert( arr[3] == 4 );
	}
	//@Host 単項マイナス
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = -arr1;
		assert( arr2[0] == -1 );
		assert( arr2[1] == -2 );
		assert( arr2[2] == -3 );
		assert( arr2[3] == -4 );
	}
	//@Host 比較演算子 ==
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = {1,2,3,4};
		assert( arr1 == arr2 );
	}
	//@Host 比較演算子 !=
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = {3,2,3,4};
		assert( arr1 != arr2 );
	}
	//@Host 転置
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = arr1.transpose();
		assert( arr2[0] == 1 );
		assert( arr2[1] == 3 );
		assert( arr2[2] == 2 );
		assert( arr2[3] == 4 );
	}
	//@Host + array2 
	{
		arr::array2<int,2,2> arr1 = { 1, 2, 3, 4 };
		arr::array2<int,2,2> arr2 = { 3, 4, 5, 6 };
		arr::array2<int,2,2> ret = arr1 + arr2;
		assert( ret[0] == 4 && ret[1] == 6 && ret[2] == 8 && ret[3] == 10);
	}
	//@Host - array2 
	{
		arr::array2<int,2,2> arr1 = { 1, 2, 3, 4 };
		arr::array2<int,2,2> arr2 = { 3, 4, 5, 6 };
		arr::array2<int,2,2> ret = arr1 - arr2;
		assert( ret[0] == -2 && ret[1] == -2 && ret[2] == -2 && ret[3] == -2);
	}
	//@Host * array2 
	{
		arr::array2<int,2,2> arr = { 1, 2, 3, 4 };
		arr::array2<int,2,2> ret = 10*arr;
		assert( ret[0] == 10 && ret[1] == 20 && ret[2] == 30 && ret[3] == 40);
	}
	//@Host / array2 
	{
		arr::array2<int,2,2> arr = { 11, 22, 33, 44 };
		arr::array2<int,2,2> ret = arr/10;
		assert( ret[0] == 1 && ret[1] == 2 && ret[2] == 3 && ret[3] == 4);
	}
	//@Host array2*array2 
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array2<int,2,2> arr2 = {3,4,5,6};
		arr::array2<int,2,2> ret = arr1 * arr2;
		assert( ret[0] == 13 && ret[1] == 16 && ret[2] == 29 && ret[3] == 36);
	}
	//@Host array1*array1
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array1<int,2> arr2 = {3,4};
		arr::array2<int,2,2> ret = arr1 * arr2;
		assert( ret[0] == 3 && ret[1] == 4 && ret[2] == 6 && ret[3] == 8);
	}
	//@Host array1*array2
	{
		arr::array1<int,2> arr1 = {1,2};
		arr::array2<int,2,2> arr2 = {3,4,5,6};
		arr::array1<int,2> ret = arr1 * arr2;
		assert( ret[0] == 13 && ret[1] == 16 );
	}
	//@Host array2*array1
	{
		arr::array2<int,2,2> arr1 = {1,2,3,4};
		arr::array1<int,2> arr2 = {3,4};
		arr::array1<int,2> ret = arr1 * arr2;
		assert( ret[0] == 11 && ret[1] == 25 );
	}
	//@Host setでポインタの付け替えができ，[],()でアクセスできる(ポインタ管理版)
	{
		arr::array2<int,2,2> arr;
		int* p = new int[4];
		p[0] = 1; p[1] = 2;
		p[2] = 3; p[3] = 4;
		arr.set( p );
		assert( arr[0] == 1 && arr[1] == 2 && arr[2] == 3 && arr[3] == 4 );
		assert( arr(0,0) == 1 && arr(0,1) == 2 && arr(1,0) == 3 && arr(1,1) == 4 );
		arr[0] = 5;
		assert( arr[0] == 5 );
		arr(0,1) = 6;
		assert( arr[1] == 6 );
		delete[] p;
	}
	//@Host show関数(int)(ポインタ管理版)
	{
		arr::array2<int,2,2> arr;
		int* p = new int[4];
		p[0] = 1; p[1] = 2;
		p[2] = 3; p[3] = 4;
		arr.set( p );
		printf( "test show @Host: array2{1, 2, 3, 4} (pointer)\n" );
		arr.show();
		delete[] p;
	}
	//@Host =演算子はdeep copyか?(ポインタ管理版)
	{
		arr::array2<int,2,2> arr1;
		int* p = new int[4];
		p[0] = 1; p[1] = 2;
		p[2] = 3; p[3] = 4;
		arr1.set( p ); //arr1 = {1,2,3,4}
		//
		arr::array2<int,2,2> arr2;
		arr2 = arr1;
		assert( arr1.get() != arr2.get() );
		arr2[1] = 3;
		assert( arr1[0] == arr2[0] );
		assert( arr1[1] != arr2[1] );
		delete[] p;
	}
	//@Host cast to matrix
	{
		arr::matrix<double> mat1;
		double* p = new double[9];
		mat1.set( 3, 3, p );
		arr::array2<double,2,2> arr1={3.0,5.0,7.0,9.0};
		mat1.replace( static_cast<arr::matrix<double>>( arr1 ) );
		assert( mat1(0,0)==3.0 && mat1(0,1)==5.0 && mat1(1,0)==7.0 && mat1(1,1)==9.0 );
		assert( mat1.rows()==3 && mat1.cols()==3 );
		assert( mat1.is_empty()==true && mat1.is_sub()==false && mat1.is_ref()==true );
		delete[] p;
	}

	std::cout << "END OF TEST (array2)" << std::endl;
	return 0;
}
