#include <iostream>
#include <assert.h>
#include "vector.h"
#include "matrix.h"
#include "../array/array2.h"


int main( int argc, char* argv[] ){


	//@Host インスタンスを作成する
	{
		arr::matrix<double> m;
		assert( &m != nullptr );
	}
	//@Host サイズつきでインスタンスを作成する, get, size, rows, cols, stride, is_sub, is_emptyなどのgetterのテスト
	{
		arr::matrix<double> m1(3,2);
		assert( m1.size() == 6 );
		assert( m1.rows() == 3 );
		assert( m1.cols() == 2 );
		assert( m1.stride() == 2 );
		assert( m1.is_sub() == false );
		assert( m1.is_empty() == false );
		arr::matrix<double> m2( 3, 2, 2.0 );
		for( unsigned int i=0; i<m2.size(); i++ ){
			assert( m2[i] == 2.0 );
		}
	}
	//@Host []で要素にアクセスできる
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		assert( m[0]==1.0 && m[1]==2.0 && m[2]==3.0 && m[3]==4.0 && m[4]==5.0 && m[5]==6.0 );
	}
	//@Host (r,c)で要素にアクセス
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		assert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
	}
	//@Host (i)で行のサブベクトルにアクセス
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::vector<double> m0 = m(0);
		assert( m0.size() == 2 );
		assert( m0[0]==1.0 && m0[1]==2.0 );
		m0[0] = 7.0;
		assert( m(0,0)==7.0 );
	}
	//@Host Copy constractor
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m( m1 );
		assert( m1.get() != m.get() );
		assert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
		m(0,0) = 3.0;
		assert( m(0.0)!=m1(0,0) );
	}
	//@Host Substitution copy
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m;
		m = m1;
		assert( m1.get() != m.get() );
		assert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
		m(0,0) = 3.0;
		assert( m(0.0)!=m1(0,0) );
	}
	//@Host show
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		std::cout << "show @Host matrix<double>{1.0,2.0 | 3.0,4.0 | 5.0,6.0 }" << std::endl;
		m.show();
	}
	//@Host resize
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m.resize(4,3);
		assert( m.size() == 12 && m.rows()==4 && m.cols()==3 );
		m.resize(4,3, 5.0);
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i] == 5.0 );
		}
	}
	//@Host reset
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m.reset();
		assert( m.is_empty() == true );
		assert( m.size() == 0 );
	}
	//@Host fill
	{
		arr::matrix<double> m(3,2);
		m.fill( 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==5.0 );
		}
	}
	//@Host zero
	{
		arr::matrix<double> m = arr::matrix<double>::zero( 3, 2 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==0.0 );
		}
	}
	//@Host constant
	{
		arr::matrix<double> m = arr::matrix<double>::constant( 3, 2, 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==5.0 );
		}
	}
	//@Host += scalar
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m += 5.0;
		assert( m(0,0)==6.0 && m(0,1)==7.0 && m(1,0)==8.0 && m(1,1)==9.0 && m(2,0)==10.0 && m(2,1)==11.0 );
	}
	//@Host += matrix
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		m += m1;
		assert( m(0,0)==2.0 && m(0,1)==4.0 && m(1,0)==6.0 && m(1,1)==8.0 && m(2,0)==10.0 && m(2,1)==12.0 );
	}
	//@Host -= scalar
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m -= 5.0;
		assert( m(0,0)==-4.0 && m(0,1)==-3.0 && m(1,0)==-2.0 && m(1,1)==-1.0 && m(2,0)==0.0 && m(2,1)==1.0 );
	}
	//@Host -= matrix
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		m -= m1;
		assert( m(0,0)==0.0 && m(0,1)==0.0 && m(1,0)==0.0 && m(1,1)==0.0 && m(2,0)==0.0 && m(2,1)==0.0 );
	}
	//@Host *= scalar
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m *= 5.0;
		assert( m(0,0)==5.0 && m(0,1)==10.0 && m(1,0)==15.0 && m(1,1)==20.0 && m(2,0)==25.0 && m(2,1)==30.0 );
	}
	//@Host /= scalar
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m /= 10.0;
		assert( m(0,0)==0.1 && m(0,1)==0.2 && m(1,0)==0.3 && m(1,1)==0.4 && m(2,0)==0.5 && m(2,1)==0.6 );
	}
	//@Host unary minus
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = -m1;
		assert( m(0,0)==-1.0 && m(0,1)==-2.0 && m(1,0)==-3.0 && m(1,1)==-4.0 && m(2,0)==-5.0 && m(2,1)==-6.0 );
	}
	//@Host ==
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		assert( m1 == m2 );
	}
	//@Host !=
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 9.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		assert( m1 != m2 );
	}
	//@Host transpose
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1.transpose();
		assert( m(0,0)==1.0 && m(0,1)==3.0 && m(0,2)==5.0 && m(1,0)==2.0 && m(1,1)==4.0 && m(1,2)==6.0 );
	}
	//@Host sub_vector
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::vector<double> v = m1.sub( 2, 3 );
		assert( v.size()==3 );
		assert( v[0]==3.0 && v[1]==4.0 && v[2]==5.0 );
		v[1]=7.0;
		assert( m1(1,1)==7.0 );
	}

	//@Host sub_matrix
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1.sub( 1, 0, 2, 2 );
		// m :
		// 3.0 4.0
		// 5.0 6.0
		assert( m.rows()==2 && m.cols()==2 );
		assert( m(0,0)==3.0 && m(0,1)==4.0 && m(1,0)==5.0 && m(1,1)==6.0 );
		m(0,1)=7.0;
		assert( m1(1,1)==7.0 );
	}
	//@Host matrix + matrix
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		arr::matrix<double> m = m1 + m2;
		assert( m(0,0)==2.0 && m(0,1)==4.0 && m(1,0)==6.0 && m(1,1)==8.0 && m(2,0)==10.0 && m(2,1)==12.0 );
	}
	//@Host matrix - matrix
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		arr::matrix<double> m = m1 - m2;
		assert( m(0,0)==0.0 && m(0,1)==0.0 && m(1,0)==0.0 && m(1,1)==0.0 && m(2,0)==0.0 && m(2,1)==0.0 );
	}
	//@Host matrix * s
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = 5.0*m1;
		assert( m(0,0)==5.0 && m(0,1)==10.0 && m(1,0)==15.0 && m(1,1)==20.0 && m(2,0)==25.0 && m(2,1)==30.0 );
	}
	//@Host matrix / s
	{
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1/10.0;
		assert( m(0,0)==0.1 && m(0,1)==0.2 && m(1,0)==0.3 && m(1,1)==0.4 && m(2,0)==0.5 && m(2,1)==0.6 );
	}
	//@Host matrix * matrix
	{
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::matrix<double> m2(3,2);
		m2(0,0)=3.0; m2(0,1)=2.0;
		m2(1,0)=1.0; m2(1,1)=2.0;
		m2(2,0)=3.0; m2(2,1)=1.0;
		arr::matrix<double> m = m1*m2;
		assert( m(0,0)==14.0 && m(0,1)==9.0 && m(1,0)==14.0 && m(1,1)==11.0 );
	}
	//@Host vector * vector
	{
		arr::vector<double> v1 = {1.0,2.0,3.0};
		arr::vector<double> v2 = {2.0,1.0};
		arr::matrix<double> m = v1*v2;
		assert( m(0,0)==2.0 && m(0,1)==1.0 && m(1,0)==4.0 && m(1,1)==2.0 && m(2,0)==6.0 && m(2,1)==3.0 );
	}
	//@Host vector * matrix
	{
		arr::vector<double> v1 = {2.0,1.0};
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::vector<double> v = v1*m1;
		assert( v[0]==5.0 && v[1]==6.0 && v[2]==7.0 );
	}
	//@Host matrix * vector
	{
		arr::vector<double> v1 = {1.0,2.0,3.0};
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::vector<double> v = m1*v1;
		assert( v[0]==14.0 && v[1]==10.0 );
	}
	//@Host cast to array2
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::array2<double,3,2> a = static_cast< arr::array2<double,3,2> >( m );
		assert( a(0,0)==1.0 && a(0,1)==2.0 && a(1,0)==3.0 && a(1,1)==4.0 && a(2,0)==5.0 && a(2,1)==6.0 );
	}

	std::cout << "END OF TEST (matrix)" << std::endl;
	return 0;
}