#include <iostream>
#include <assert.h>
#include "vector.h"

#define cudaAssert(condition) \
if (!(condition)) printf( "Assertion faild: %s, file %s, line %d\n", #condition, __FILE__, __LINE__ )

//global functions (kernels)
namespace {
	#ifdef GPU

	__global__
	void g_create_instance(){
		arr::vector<double> v;
		cudaAssert( &v != nullptr );
	}

	__global__
	void g_create_instance_with_size(){
		arr::vector<double> v1(3);
		cudaAssert( v1.size() == 3 );
		cudaAssert( v1.is_sub() == false );
		cudaAssert( v1.is_empty() == false );
		arr::vector<double> v2(3,2.0);
		for( unsigned int i=0; i<v2.size(); i++ ){
			cudaAssert( v2[i] == 2.0 );
		}
	}

	__global__
	void g_square_brackets(){
		arr::vector<double> v(4);
		v[0] = 1.0; v[1] = 2.0; v[2] = 3.0; v[3] = 4.0;
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}

	__global__
	void g_initializer(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		cudaAssert( v.size() == 4 );
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}

	__global__
	void g_deep_copy(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v;
		v.deep_copy( v1 );
		cudaAssert( v1.get() != v.get() );
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}

	__global__
	void g_copy_constructor(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v( v1 );
		cudaAssert( v1.get() != v.get() );
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}

	__global__
	void g_copy_substitution(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1;
		cudaAssert( v1.get() != v.get() );
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}

	__global__
	void g_show(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		printf( "show @Device vector<double>{1.0,2.0,3.0,4.0}\n" );
		v1.device_show();
	}

	__global__
	void g_resize(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.resize(3);
		cudaAssert( v.size() == 3 );
		v.resize(4,5.0);
		for( unsigned int i=0; i<v.size(); i++ ){
			cudaAssert( v[i] == 5.0 );
		}
	}

	__global__
	void g_reset(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.reset();
		cudaAssert( v.is_empty() == true );
		cudaAssert( v.size() == 0 );
	}

	__global__
	void g_push_back(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.push_back( 5.0 );
		cudaAssert( v.size() == 5 );
		cudaAssert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 && v[4]==5.0 );
	}

	__global__
	void g_erase(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.erase(1);
		cudaAssert( v.size() == 3 );
		cudaAssert( v[0]==1.0  && v[1]==3.0 && v[2]==4.0 );
	}

	__global__
	void g_fill(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.fill( 5.0, 1, 2 );
		cudaAssert( v[0]==1.0 && v[1]==5.0 && v[2]==5.0 && v[3]==4.0 );
	}

	__global__
	void g_find(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		int n1 = v.find( 3.0 );
		int n2 = v.find( 5.0 );
		cudaAssert( n1==2 && n2==-1 );
	}

	__global__
	void g_zero(){
		arr::vector<double> v = arr::vector<double>::zero( 3 );
		cudaAssert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 );
	}

	__global__
	void g_constant(){
		arr::vector<double> v = arr::vector<double>::constant( 3, 5.0 );
		cudaAssert( v[0]==5.0 && v[1]==5.0 && v[2]==5.0 );
	}

	__global__
	void g_addition_assignment_scalar(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v += 5.0;
		cudaAssert( v[0]==6.0 && v[1]==7.0 && v[2]==8.0 && v[3]==9.0 );
	}

	__global__
	void g_addition_assignment_vector(){
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v += v1;
		cudaAssert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}

	__global__
	void g_subtraction_assignment_scalar(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v -= 5.0;
		cudaAssert( v[0]==-4.0 && v[1]==-3.0 && v[2]==-2.0 && v[3]==-1.0 );
	}

	__global__
	void g_subtraction_assignment_vector(){
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v -= v1;
		cudaAssert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}

	__global__
	void g_multiplication_assignment_scalar(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v *= 5.0;
		cudaAssert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}

	__global__
	void g_division_assignment_scalar(){
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v /= 10.0;
		cudaAssert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}

	__global__
	void g_unary_minus(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = -v1;
		cudaAssert( v[0]==-1.0 && v[1]==-2.0 && v[2]==-3.0 && v[3]==-4.0 );
	}

	__global__
	void g_equal_to(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		cudaAssert( v1 == v2 );
	}

	__global__
	void g_not_equal_to(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {6.0, 2.0, 3.0, 4.0};
		cudaAssert( v1 != v2 );
	}

	__global__
	void g_dot(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		double d = v1.dot( v2 );
		cudaAssert( d == 30.0 );
	}

	__global__
	void g_vector_plus_vector(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 + v2;
		cudaAssert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}

	__global__
	void g_vector_minus_vector(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 - v2;
		cudaAssert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}

	__global__
	void g_vector_multiply_scalar(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = 5.0*v1;
		cudaAssert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}

	__global__
	void g_vector_divide_scalar(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1/10.0;
		cudaAssert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}

	__global__
	void g_sub(){
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
		arr::vector<double> v = v1.sub( 3, 2 );
		cudaAssert( v.size() == 2 );
		cudaAssert( v[0]==4.0 && v[1]==5.0 );
		v[1] = 10.0;
		cudaAssert( v1[4] == 10.0 );
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
		arr::vector<double> v;
		assert( &v != nullptr );
	}
	//@Device インスタンスを作成する
	{
		#ifdef GPU
			g_create_instance<<<1,1>>>();
		#endif
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
	//@Device サイズつきでインスタンスを作成する, get, size, is_sub, is_emptyなどのgetterのテスト
	{
		#ifdef GPU
			g_create_instance_with_size<<<1,1>>>();
		#endif
	}
	//@Host []で要素にアクセスできる
	{
		arr::vector<double> v(4);
		v[0] = 1.0; v[1] = 2.0; v[2] = 3.0; v[3] = 4.0;
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Device []で要素にアクセスできる
	{
		#ifdef GPU
			g_square_brackets<<<1,1>>>();
		#endif
	}
	//@Host メンバイニシャライザ
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		assert( v.size() == 4 );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Device メンバイニシャライザ
	{
		#ifdef GPU
			g_initializer<<<1,1>>>();
		#endif
	}
	//@Host deep_copy
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v;
		v.deep_copy( v1 );
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Device deep_copy
	{
		#ifdef GPU
			g_deep_copy<<<1,1>>>();
		#endif
	}
	//@Host Copy constractor
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v( v1 );
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Device Copy constractor
	{
		#ifdef GPU
			g_copy_constructor<<<1,1>>>();
		#endif
	}
	//@Host substitution copy
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1;
		assert( v1.get() != v.get() );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 );
	}
	//@Device substitution copy
	{
		#ifdef GPU
			g_copy_substitution<<<1,1>>>();
		#endif
	}
	//@Host show
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		std::cout << "show @Host vector<double>{1.0,2.0,3.0,4.0}" << std::endl;
		v1.show();
	}
	//@Device show
	{
		#ifdef GPU
			g_show<<<1,1>>>();
		#endif
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
	//@Device resize
	{
		#ifdef GPU
			g_resize<<<1,1>>>();
		#endif
	}
	//@Host reset
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.reset();
		assert( v.is_empty() == true );
		assert( v.size() == 0 );
	}
	//@Device reset
	{
		#ifdef GPU
			g_reset<<<1,1>>>();
		#endif
	}
	//@Host push_back
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.push_back( 5.0 );
		assert( v.size() == 5 );
		assert( v[0]==1.0 && v[1]==2.0 && v[2]==3.0 && v[3]==4.0 && v[4]==5.0 );
	}
	//@Device push_back
	{
		#ifdef GPU
			g_push_back<<<1,1>>>();
		#endif
	}
	//@Host erase
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.erase(1);
		assert( v.size() == 3 );
		assert( v[0]==1.0  && v[1]==3.0 && v[2]==4.0 );
	}
	//@Device erase
	{
		#ifdef GPU
			g_erase<<<1,1>>>();
		#endif
	}
	//@Host fill
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v.fill( 5.0, 1, 2 );
		assert( v[0]==1.0 && v[1]==5.0 && v[2]==5.0 && v[3]==4.0 );
	}
	//@Device fill
	{
		#ifdef GPU
			g_fill<<<1,1>>>();
		#endif
	}
	//@Host find
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		int n1 = v.find( 3.0 );
		int n2 = v.find( 5.0 );
		assert( n1==2 && n2==-1 );
	}
	//@Device find
	{
		#ifdef GPU
			g_find<<<1,1>>>();
		#endif
	}
	//@Host zero
	{
		arr::vector<double> v = arr::vector<double>::zero( 3 );
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 );
	}
	//@Device zero
	{
		#ifdef GPU
			g_zero<<<1,1>>>();
		#endif
	}
	//@Host constant
	{
		arr::vector<double> v = arr::vector<double>::constant( 3, 5.0 );
		assert( v[0]==5.0 && v[1]==5.0 && v[2]==5.0 );
	}
	//@Device constant
	{
		#ifdef GPU
			g_constant<<<1,1>>>();
		#endif
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
	//@Device += scalar
	{
		#ifdef GPU
			g_addition_assignment_scalar<<<1,1>>>();
		#endif
	}
	//@Host += vector
	{
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v += v1;
		assert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}
	//@Device += vector
	{
		#ifdef GPU
			g_addition_assignment_vector<<<1,1>>>();
		#endif
	}
	//@Host -= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v -= 5.0;
		assert( v[0]==-4.0 && v[1]==-3.0 && v[2]==-2.0 && v[3]==-1.0 );
	}
	//@Device -= scalar
	{
		#ifdef GPU
			g_subtraction_assignment_scalar<<<1,1>>>();
		#endif
	}
	//@Host -= vector
	{
		arr::vector<double> v  = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		v -= v1;
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}
	//@Device -= vector
	{
		#ifdef GPU
			g_subtraction_assignment_vector<<<1,1>>>();
		#endif
	}
	//@Host *= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v *= 5.0;
		assert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}
	//@Device *= scalar
	{
		#ifdef GPU
			g_multiplication_assignment_scalar<<<1,1>>>();
		#endif
	}
	//@Host /= scalar
	{
		arr::vector<double> v = {1.0, 2.0, 3.0, 4.0};
		v /= 10.0;
		assert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}
	//@Device /= scalar
	{
		#ifdef GPU
			g_division_assignment_scalar<<<1,1>>>();
		#endif
	}
	//@Host unary minus
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = -v1;
		assert( v[0]==-1.0 && v[1]==-2.0 && v[2]==-3.0 && v[3]==-4.0 );
	}
	//@Device unary minus
	{
		#ifdef GPU
			g_unary_minus<<<1,1>>>();
		#endif
	}
	//@Host ==
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		assert( v1 == v2 );
	}
	//@Device ==
	{
		#ifdef GPU
			g_equal_to<<<1,1>>>();
		#endif
	}
	//@Host !=
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {6.0, 2.0, 3.0, 4.0};
		assert( v1 != v2 );
	}
	//@Device !=
	{
		#ifdef GPU
			g_not_equal_to<<<1,1>>>();
		#endif
	}
	//@Host dot
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		double d = v1.dot( v2 );
		assert( d == 30.0 );
	}
	//@Device dot
	{
		#ifdef GPU
			g_dot<<<1,1>>>();
		#endif
	}
	//@Host vector + vector
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 + v2;
		assert( v[0]==2.0 && v[1]==4.0 && v[2]==6.0 && v[3]==8.0 );
	}
	//@Device vector + vector
	{
		#ifdef GPU
			g_vector_plus_vector<<<1,1>>>();
		#endif
	}
	//@Host vector - vector
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v2 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1 - v2;
		assert( v[0]==0.0 && v[1]==0.0 && v[2]==0.0 && v[3]==0.0 );
	}
	//@Device vector - vector
	{
		#ifdef GPU
			g_vector_minus_vector<<<1,1>>>();
		#endif
	}
	//@Host vector * s
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = 5.0*v1;
		assert( v[0]==5.0 && v[1]==10.0 && v[2]==15.0 && v[3]==20.0 );
	}
	//@Device vector *s
	{
		#ifdef GPU
			g_vector_multiply_scalar<<<1,1>>>();
		#endif
	}
	//@Host vector / s
	{
		arr::vector<double> v1 = {1.0, 2.0, 3.0, 4.0};
		arr::vector<double> v = v1/10.0;
		assert( v[0]==0.1 && v[1]==0.2 && v[2]==0.3 && v[3]==0.4 );
	}
	//@Device vector /s
	{
		#ifdef GPU
			g_vector_divide_scalar<<<1,1>>>();
		#endif
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
	//@Device sub
	{
		#ifdef GPU
			g_sub<<<1,1>>>();
		#endif
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

	#ifdef GPU
	cudaFree( dA );
	#endif

	std::cout << "END OF TEST (vector)" << std::endl;
	return 0;
}