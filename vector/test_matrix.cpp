#include <iostream>
#include <assert.h>
#include "vector.h"
#include "matrix.h"
#include "../array/array2.h"

#define cudaAssert(condition) \
if (!(condition)) printf( "Assertion faild: %s, file %s, line %d\n", #condition, __FILE__, __LINE__ )

//global functions (kernels)
namespace {
	#ifdef GPU

	__global__
	void g_create_instance(){
		arr::matrix<double> m;
		cudaAssert( &m != nullptr );
	}

	__global__
	void g_create_instance_with_size(){
		arr::matrix<double> m1(3,2);
		cudaAssert( m1.size() == 6 );
		cudaAssert( m1.rows() == 3 );
		cudaAssert( m1.cols() == 2 );
		cudaAssert( m1.stride() == 2 );
		cudaAssert( m1.is_sub() == false );
		cudaAssert( m1.is_empty() == false );
		arr::matrix<double> m2( 3, 2, 2.0 );
		for( unsigned int i=0; i<m2.size(); i++ ){
			cudaAssert( m2[i] == 2.0 );
		}
	}

	__global__
	void g_square_bracket(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		cudaAssert( m[0]==1.0 && m[1]==2.0 && m[2]==3.0 && m[3]==4.0 && m[4]==5.0 && m[5]==6.0 );
	}

	__global__
	void g_round_bracket1(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		cudaAssert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
	}

	__global__
	void g_round_bracket2(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::vector<double> m0 = m(0);
		cudaAssert( m0.size() == 2 );
		cudaAssert( m0[0]==1.0 && m0[1]==2.0 );
		m0[0] = 7.0;
		cudaAssert( m(0,0)==7.0 );
	}

	__global__
	void g_copy_constructor(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m( m1 );
		cudaAssert( m1.get() != m.get() );
		cudaAssert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
		m(0,0) = 3.0;
		cudaAssert( m(0.0)!=m1(0,0) );
	}

	__global__
	void g_substitution_copy(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m;
		m = m1;
		cudaAssert( m1.get() != m.get() );
		cudaAssert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
		m(0,0) = 3.0;
		cudaAssert( m(0.0)!=m1(0,0) );
	}

	__global__
	void g_show(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		printf( "show @Device matrix<double>{1.0,2.0 | 3.0,4.0 | 5.0,6.0 }\n" );
		m.device_show();
	}

	__global__
	void g_resize(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m.resize(4,3);
		cudaAssert( m.size() == 12 && m.rows()==4 && m.cols()==3 );
		m.resize(4,3, 5.0);
		for( unsigned int i=0; i<m.size(); i++ ){
			cudaAssert( m[i] == 5.0 );
		}
	}

	__global__
	void g_reset(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m.reset();
		cudaAssert( m.is_empty() == true );
		cudaAssert( m.size() == 0 );
	}

	__global__
	void g_fill(){
		arr::matrix<double> m(3,2);
		m.fill( 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			cudaAssert( m[i]==5.0 );
		}
	}

	__global__
	void g_zero(){
		arr::matrix<double> m = arr::matrix<double>::zero( 3, 2 );
		for( unsigned int i=0; i<m.size(); i++ ){
			cudaAssert( m[i]==0.0 );
		}
	}

	__global__
	void g_constant(){
		arr::matrix<double> m = arr::matrix<double>::constant( 3, 2, 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			cudaAssert( m[i]==5.0 );
		}
	}

	__global__
	void g_addition_assignment_scalar(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m += 5.0;
		cudaAssert( m(0,0)==6.0 && m(0,1)==7.0 && m(1,0)==8.0 && m(1,1)==9.0 && m(2,0)==10.0 && m(2,1)==11.0 );
	}

	__global__
	void g_addition_assignment_matrix(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		m += m1;
		cudaAssert( m(0,0)==2.0 && m(0,1)==4.0 && m(1,0)==6.0 && m(1,1)==8.0 && m(2,0)==10.0 && m(2,1)==12.0 );
	}

	__global__
	void g_subtraction_assignment_scalar(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m -= 5.0;
		cudaAssert( m(0,0)==-4.0 && m(0,1)==-3.0 && m(1,0)==-2.0 && m(1,1)==-1.0 && m(2,0)==0.0 && m(2,1)==1.0 );
	}

	__global__
	void g_subtraction_assignment_matrix(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		m -= m1;
		cudaAssert( m(0,0)==0.0 && m(0,1)==0.0 && m(1,0)==0.0 && m(1,1)==0.0 && m(2,0)==0.0 && m(2,1)==0.0 );
	}

	__global__
	void g_multiplication_assignment_scalar(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m *= 5.0;
		cudaAssert( m(0,0)==5.0 && m(0,1)==10.0 && m(1,0)==15.0 && m(1,1)==20.0 && m(2,0)==25.0 && m(2,1)==30.0 );
	}

	__global__
	void g_division_assignment_scalar(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		m /= 10.0;
		cudaAssert( m(0,0)==0.1 && m(0,1)==0.2 && m(1,0)==0.3 && m(1,1)==0.4 && m(2,0)==0.5 && m(2,1)==0.6 );
	}

	__global__
	void g_unary_minus(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = -m1;
		cudaAssert( m(0,0)==-1.0 && m(0,1)==-2.0 && m(1,0)==-3.0 && m(1,1)==-4.0 && m(2,0)==-5.0 && m(2,1)==-6.0 );
	}

	__global__
	void g_equal_to(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		cudaAssert( m1 == m2 );
	}

	__global__
	void g_not_equal_to(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 9.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		cudaAssert( m1 != m2 );
	}

	__global__
	void g_transpose(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1.transpose();
		cudaAssert( m(0,0)==1.0 && m(0,1)==3.0 && m(0,2)==5.0 && m(1,0)==2.0 && m(1,1)==4.0 && m(1,2)==6.0 );
	}

	__global__
	void g_sub_vector(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::vector<double> v = m1.sub( 2, 3 );
		cudaAssert( v.size()==3 );
		cudaAssert( v[0]==3.0 && v[1]==4.0 && v[2]==5.0 );
		v[1]=7.0;
		cudaAssert( m1(1,1)==7.0 );
	}

	__global__
	void g_sub_matrix(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1.sub( 1, 0, 2, 2 );
		// m :
		// 3.0 4.0
		// 5.0 6.0
		cudaAssert( m.rows()==2 && m.cols()==2 );
		cudaAssert( m(0,0)==3.0 && m(0,1)==4.0 && m(1,0)==5.0 && m(1,1)==6.0 );
		m(0,1)=7.0;
		cudaAssert( m1(1,1)==7.0 );
	}

	__global__
	void g_matrix_plus_matrix(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		arr::matrix<double> m = m1 + m2;
		cudaAssert( m(0,0)==2.0 && m(0,1)==4.0 && m(1,0)==6.0 && m(1,1)==8.0 && m(2,0)==10.0 && m(2,1)==12.0 );
	}

	__global__
	void g_matrix_minus_matrix(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m2(3,2);
		m2[0] = 1.0; m2[1] = 2.0;
		m2[2] = 3.0; m2[3] = 4.0;
		m2[4] = 5.0; m2[5] = 6.0;
		arr::matrix<double> m = m1 - m2;
		cudaAssert( m(0,0)==0.0 && m(0,1)==0.0 && m(1,0)==0.0 && m(1,1)==0.0 && m(2,0)==0.0 && m(2,1)==0.0 );
	}

	__global__
	void g_matrix_multiply_scalar(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = 5.0*m1;
		cudaAssert( m(0,0)==5.0 && m(0,1)==10.0 && m(1,0)==15.0 && m(1,1)==20.0 && m(2,0)==25.0 && m(2,1)==30.0 );
	}

	__global__
	void g_matrix_devide_scalar(){
		arr::matrix<double> m1(3,2);
		m1[0] = 1.0; m1[1] = 2.0;
		m1[2] = 3.0; m1[3] = 4.0;
		m1[4] = 5.0; m1[5] = 6.0;
		arr::matrix<double> m = m1/10.0;
		cudaAssert( m(0,0)==0.1 && m(0,1)==0.2 && m(1,0)==0.3 && m(1,1)==0.4 && m(2,0)==0.5 && m(2,1)==0.6 );
	}
	__global__
	void g_matrix_multiply_matrix(){
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::matrix<double> m2(3,2);
		m2(0,0)=3.0; m2(0,1)=2.0;
		m2(1,0)=1.0; m2(1,1)=2.0;
		m2(2,0)=3.0; m2(2,1)=1.0;
		arr::matrix<double> m = m1*m2;
		cudaAssert( m(0,0)==14.0 && m(0,1)==9.0 && m(1,0)==14.0 && m(1,1)==11.0 );
	}

	__global__
	void g_vector_multiply_vector(){
		arr::vector<double> v1 = {1.0,2.0,3.0};
		arr::vector<double> v2 = {2.0,1.0};
		arr::matrix<double> m = v1*v2;
		cudaAssert( m(0,0)==2.0 && m(0,1)==1.0 && m(1,0)==4.0 && m(1,1)==2.0 && m(2,0)==6.0 && m(2,1)==3.0 );
	}

	__global__
	void g_vector_multiply_matrix(){
		arr::vector<double> v1 = {2.0,1.0};
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::vector<double> v = v1*m1;
		cudaAssert( v[0]==5.0 && v[1]==6.0 && v[2]==7.0 );
	}

	__global__
	void g_matrix_multiply_vector(){
		arr::vector<double> v1 = {1.0,2.0,3.0};
		arr::matrix<double> m1(2,3);
		m1(0,0)=1.0; m1(0,1)=2.0; m1(0,2)=3.0;
		m1(1,0)=3.0; m1(1,1)=2.0; m1(1,2)=1.0;
		arr::vector<double> v = m1*v1;
		cudaAssert( v[0]==14.0 && v[1]==10.0 );
	}

	__global__
	void g_cast_to_array2(){
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		arr::array2<double,3,2> a = static_cast< arr::array2<double,3,2> >( m );
		cudaAssert( a(0,0)==1.0 && a(0,1)==2.0 && a(1,0)==3.0 && a(1,1)==4.0 && a(2,0)==5.0 && a(2,1)==6.0 );
	}

	#endif
}

int main( int argc, char* argv[] ){

	#ifdef GPU
	double* dA;
	cudaMalloc( (void**)&dA, sizeof(double) );
	#endif

	//@Host インスタンスを作成する
	{
		arr::matrix<double> m;
		assert( &m != nullptr );
	}
	//@Device インスタンスを作成する
	{
		#ifdef GPU
			g_create_instance<<<1,1>>>();
		#endif
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
	//@Device サイズつきでインスタンスを作成する, get, size, rows, cols, stride, is_sub, is_emptyなどのgetterのテスト
	{
		#ifdef GPU
			g_create_instance_with_size<<<1,1>>>();
		#endif
	}
	//@Host []で要素にアクセスできる
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		assert( m[0]==1.0 && m[1]==2.0 && m[2]==3.0 && m[3]==4.0 && m[4]==5.0 && m[5]==6.0 );
	}
	//@Deivce []で要素にアクセスできる
	{
		#ifdef GPU
			g_square_bracket<<<1,1>>>();
		#endif
	}
	//@Host (r,c)で要素にアクセス
	{
		arr::matrix<double> m(3,2);
		m[0] = 1.0; m[1] = 2.0;
		m[2] = 3.0; m[3] = 4.0;
		m[4] = 5.0; m[5] = 6.0;
		assert( m(0,0)==1.0 && m(0,1)==2.0 && m(1,0)==3.0 && m(1,1)==4.0 && m(2,0)==5.0 && m(2,1)==6.0 );
	}
	//@Deivce (r,c)で要素にアクセス
	{
		#ifdef GPU
			g_round_bracket1<<<1,1>>>();
		#endif
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
	//@Deivce (i)で行のサブベクトルにアクセス
	{
		#ifdef GPU
			g_round_bracket2<<<1,1>>>();
		#endif
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
	//@Deivce Copy constractor
	{
		#ifdef GPU
			g_copy_constructor<<<1,1>>>();
		#endif
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
	//@Deivce Substitution copy
	{
		#ifdef GPU
			g_substitution_copy<<<1,1>>>();
		#endif
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
	//@Device show
	{
		#ifdef GPU
			g_show<<<1,1>>>();
		#endif
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
	//@Device resize
	{
		#ifdef GPU
			g_resize<<<1,1>>>();
		#endif
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
	//@Device reset
	{
		#ifdef GPU
			g_reset<<<1,1>>>();
		#endif
	}
	//@Host fill
	{
		arr::matrix<double> m(3,2);
		m.fill( 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==5.0 );
		}
	}
	//@Device fill
	{
		#ifdef GPU
			g_fill<<<1,1>>>();
		#endif
	}
	//@Host zero
	{
		arr::matrix<double> m = arr::matrix<double>::zero( 3, 2 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==0.0 );
		}
	}
	//@Device zero
	{
		#ifdef GPU
			g_zero<<<1,1>>>();
		#endif
	}
	//@Host constant
	{
		arr::matrix<double> m = arr::matrix<double>::constant( 3, 2, 5.0 );
		for( unsigned int i=0; i<m.size(); i++ ){
			assert( m[i]==5.0 );
		}
	}
	//@Device constant
	{
		#ifdef GPU
			g_constant<<<1,1>>>();
		#endif
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
	//@Device += scalar
	{
		#ifdef GPU
			g_addition_assignment_scalar<<<1,1>>>();
		#endif
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
	//@Device += matrix
	{
		#ifdef GPU
			g_addition_assignment_matrix<<<1,1>>>();
		#endif
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
	//@Device -= scalar
	{
		#ifdef GPU
			g_subtraction_assignment_scalar<<<1,1>>>();
		#endif
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
	//@Device -= matrix
	{
		#ifdef GPU
			g_subtraction_assignment_matrix<<<1,1>>>();
		#endif
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
	//@Device *= scalar
	{
		#ifdef GPU
			g_multiplication_assignment_scalar<<<1,1>>>();
		#endif
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
	//@Device /= scalar
	{
		#ifdef GPU
			g_division_assignment_scalar<<<1,1>>>();
		#endif
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
	//@Device unary minus
	{
		#ifdef GPU
			g_unary_minus<<<1,1>>>();
		#endif
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
	//@Device ==
	{
		#ifdef GPU
			g_equal_to<<<1,1>>>();
		#endif
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
	//@Device !=
	{
		#ifdef GPU
			g_not_equal_to<<<1,1>>>();
		#endif
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
	//@Device transpose
	{
		#ifdef GPU
			g_transpose<<<1,1>>>();
		#endif
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
	//@Device
	{
		#ifdef GPU
			g_sub_vector<<<1,1>>>();
		#endif
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
	//@Device
	{
		#ifdef GPU
			g_sub_matrix<<<1,1>>>();
		#endif
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
	//@Device matrix + matrix
	{
		#ifdef GPU
			g_matrix_plus_matrix<<<1,1>>>();
		#endif
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
	//@Device matrix - matrix
	{
		#ifdef GPU
			g_matrix_minus_matrix<<<1,1>>>();
		#endif
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
	//@Device matrix *s
	{
		#ifdef GPU
			g_matrix_multiply_scalar<<<1,1>>>();
		#endif
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
	//@Device matrix / s
	{
		#ifdef GPU
			g_matrix_devide_scalar<<<1,1>>>();
		#endif
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
	//@Device matrix * matrix
	{
		#ifdef GPU
			g_matrix_multiply_matrix<<<1,1>>>();
		#endif
	}
	//@Host vector * vector
	{
		arr::vector<double> v1 = {1.0,2.0,3.0};
		arr::vector<double> v2 = {2.0,1.0};
		arr::matrix<double> m = v1*v2;
		assert( m(0,0)==2.0 && m(0,1)==1.0 && m(1,0)==4.0 && m(1,1)==2.0 && m(2,0)==6.0 && m(2,1)==3.0 );
	}
	//@Device vector * vector
	{
		#ifdef GPU
			g_vector_multiply_vector<<<1,1>>>();
		#endif
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
	//@Device vector * matrix
	{
		#ifdef GPU
			g_vector_multiply_matrix<<<1,1>>>();
		#endif
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
	//@Device matrix * vector
	{
		#ifdef GPU
			g_matrix_multiply_vector<<<1,1>>>();
		#endif
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
	//@Device cast to array2
	{
		#ifdef GPU
			g_cast_to_array2<<<1,1>>>();
		#endif
	}

	#ifdef GPU
	cudaFree( dA );
	#endif

	std::cout << "END OF TEST (matrix)" << std::endl;
	return 0;
}