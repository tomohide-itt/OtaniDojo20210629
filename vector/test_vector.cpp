#include <iostream>
#include <assert.h>
#include "vector.h"

int main( int argc, char* argv[] ){

	//@Host インスタンスを作成する
	{
		arr::vector<double> v;
		assert( &v != nullptr );
	}
	//@Host サイズつきでインスタンスを作成する, get, size, is_sub, is_emptyなどのgetterのテスト
	{
		arr::vector<double> v1(3);
		assert( v1.size() == 3 );
		assert( v1.is_sub() == false );
		assert( v1.is_empty() == false );
		arr::vector<double> v2(3,2.0);
		for( unsigned int i=0; i<v2.size(); i++ ){
			assert( v2[i] == 2.0 );
		}
	}
	//@Host []で要素にアクセスできる
	{
		arr::vector<double> v(4);
		v[0] = 1.0; v[1] = 2.0; v[2] = 3.0; v[3] = 4.0;
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Host メンバイニシャライザ
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		assert( v.size() == 4 );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Host deep_copy
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v;
		v.deep_copy( v1 );
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Host Copy constractor
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v( v1 );
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Host substitution copy
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1;
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Host show
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		std::cout << "show @Host vector<double>{1.0,2.0,3.0,4.0}" << std::endl;
		v1.show();
	}
	//@Host resize
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.resize(3);
		assert( v.size() == 3 );
		v.resize(4,5.0);
		for( unsigned int i=0; i<v.size(); i++ ){
			assert( v[i] == 5.0 );
		}
	}
	//@Host reset
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.reset();
		assert( v.is_empty() == true );
		assert( v.size() == 0 );
	}
	//@Host push_back
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.push_back( 5.0 );
		assert( v.size() == 5 );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 && v[4]==5.0 );
	}
	//@Host erase
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.erase(1);
		assert( v.size() == 3 );
		assert( v[0]==1.0  && v[1]==3.0 && v[2]==4.0 );
	}
	//@Host fill
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.fill( 5.0, 1, 2 );
		assert( v[0]==1.0 && v[1]==5.0 && v[2]==5.0 && v[3]==4.0 );
	}
	//@Host find
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		int n1 = v.find( 3.0 );
		int n2 = v.find( 5.0 );
		assert( n1==2 && n2==-1 );
	}
	//@Host zero
	{
		arr::vector<double> v = arr::vector<double>::zero( 3 );
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 );
	}
	//@Host constant
	{
		arr::vector<double> v = arr::vector<double>::constant( 3, 5.0 );
		assert( v[0]==5.0 && v[1]==5.0 && v[2]==5.0 );
	}
	//@Host arrange
	{
		arr::vector<double> v = arr::vector<double>::arrange( 1.0, 2.0, 0.1 );
		for( unsigned int i=0; i<v.size(); i++ ){
			assert( v[i]==1.0+0.1*static_cast<double>(i) );
		}
	}
	//@Host += scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v += 5.0;
		assert( v[0]==6.0 && v[1]==7.0 && v[2]==8.0 && v[3]==9.0 );
	}
	//@Host += vector
	{
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v += v1;
		assert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}
	//@Host -= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v -= 5.0;
		assert( v[0]==-4.0 && v[1]==-3.0 && v[2]==-2.0 && v[3]==-1.0 );
	}
	//@Host -= vector
	{
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v -= v1;
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}
	//@Host *= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v *= 5.0;
		assert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}
	//@Host /= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v /= 10.0;
		assert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}
	//@Host unary minus
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = -v1;
		assert( v[0]==-1.0 && v[1]==-2.0 && v[2]==-3.0 && v[3]==-4.0 );
	}
	//@Host ==
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		assert( v1 == v2 );
	}
	//@Host !=
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {6.0, 2.0, 3.0, 4.0};
		assert( v1 != v2 );
	}
	//@Host dot
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		double d = v1.dot( v2 );
		assert( d == 30.0 );
	}
	//@Host vector + vector
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 + v2;
		assert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}
	//@Host vector - vector
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 - v2;
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}
	//@Host vector * s
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = 5.0*v1;
		assert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}
	//@Host vector / s
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1/10.0;
		assert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}
	//@Host sub
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
		arr::vector<double> v = v1.sub( 3, 2 );
		assert( v.size() == 2 );
		assert( v[0]==4.0 && v[1]==5.0 );
		v[1] = 10.0;
		assert( v1[4] == 10.0 );
	}
	//@Host sort
	{
		arr::vector<double> v = {3.0, 2.0, 13.0, 4.0, 1.0, 6.0, 10.0};
		arr::vector<int> original_pos = v.sort();
		arr::vector<double> v_sorted = {1.0, 2.0, 3.0, 4.0, 6.0, 10.0, 13.0};
		arr::vector<int> opos = {4,1,0,3,5,6,2};
		assert( v == v_sorted );
		assert( original_pos == opos );
	}

	std::cout << "END OF TEST (vector)" << std::endl;
	return 0;
}