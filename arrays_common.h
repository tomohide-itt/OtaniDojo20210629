#ifndef ARRAYS_COMMON
#define ARRAYS_COMMON

namespace arr{
// zero -------------------------------------------------------------------------------------------
template< typename T >
void zero_common( T* v, const unsigned int sz );

// arrange ----------------------------------------------------------------------------------------
template< typename T >
void arrange_common( T* v, const T start, const T intvl, const unsigned int sz );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for one-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator += ------------------------------------------------------------------------------------
// vector += vector
template< typename T >
bool addition_assignment_1( T* vs, const T* vo, const unsigned int szs, const unsigned int szo );

// operator += ------------------------------------------------------------------------------------
// vector += scalar
template< typename T >
void addition_assignment_1( T* vs, const T so, const unsigned int szs );

// operator -= ------------------------------------------------------------------------------------
// vector -= vector
template< typename T >
bool subtraction_assignment_1( T* vs, const T* vo, const unsigned int szs, const unsigned int szo );

// operator -= ------------------------------------------------------------------------------------
// vector -= scalar
template< typename T >
void subtraction_assignment_1( T* vs, const T so, const unsigned int szs ){
	addition_assignment_1( vs, -so, szs );
}

// operator *= ------------------------------------------------------------------------------------
// vector *= scalar
template< typename T >
void multiplication_assignment_1( T* vs, const T so, const unsigned int szs );

// operator /= ------------------------------------------------------------------------------------
// vector /= scalar
template< typename T >
void division_assignment_1( T* vs, const T so, const unsigned int szs );

// operator - -------------------------------------------------------------------------------------
// - vector
template< typename T >
void unary_minus_1( const T* vs, T* vo, const unsigned int szs );

// operator == -------------------------------------------------------------------------------------
// vector == vector
template< typename T >
bool equal_to_1( const T* vs, const T* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) return false;
	for( unsigned int i=0; i<szs; i++ ){
		if( vs[i] != vo[i] ) ret = false;
	}
	return ret;
}

// operator != -------------------------------------------------------------------------------------
// vector != vector
template< typename T >
bool not_equal_to_1( const T* vs, const T* vo, const unsigned int szs, const unsigned int szo ){
	return !(equal_to_1(vs, vo, szs, szo));
}

// dot -------------------------------------------------------------------------------------------
template< typename T >
bool dot_1( T& ret, const T* vs, const T* vo, const unsigned int szs, const unsigned int szo );

// operator + ------------------------------------------------------------------------------------
// vector + vector
template< typename T >
bool addition_1( T* vout, const T* v1, const T* v2, const unsigned int sz1, const unsigned int sz2 );

// operator - ------------------------------------------------------------------------------------
// vector - vector
template< typename T >
bool subtraction_1( T* vout, const T* v1, const T* v2, const unsigned int sz1, const unsigned int sz2 );

// operator * ------------------------------------------------------------------------------------
// scalar * vector
template< typename T>
void multiplication_1( T* vout, const T s, const T* v, const unsigned int sz );

// operator * ------------------------------------------------------------------------------------
// vector / scalar
template< typename T >
void division_1( T* vout, const T s, const T* v, const unsigned int sz );


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for two-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator += ------------------------------------------------------------------------------------
// matrix += matrix
template< typename T >
bool addition_assignment_2( T* ms, const T* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo );


// operator += ------------------------------------------------------------------------------------
// matrix += scalar
template< typename T >
void addition_assignment_2( T* m, const T s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride );

// operator -= ------------------------------------------------------------------------------------
// matrix -= matrix
template< typename T >
bool subtraction_assignment_2( T* ms, const T* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo );


// operator -= ------------------------------------------------------------------------------------
// matrix -= scalar
template< typename T >
void subtraction_assignment_2( T* m, const T s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	addition_assignment_2( m, -s, nrow, ncol, stride );
}

// operator *= ------------------------------------------------------------------------------------
// matrix *= scalar
template< typename T >
void multiplication_assignment_2( T* m, const T s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride );

// operator /= ------------------------------------------------------------------------------------
// matrix /= scalar
template< typename T >
void division_assignment_2( T* m, const T s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride );

// operator - -------------------------------------------------------------------------------------
// - matrix
template< typename T >
void unary_minus_2( const T* ms, T* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides );

// operator == -------------------------------------------------------------------------------------
// matrix == matrix
template< typename T >
bool equal_to_2( const T* ms, const T* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) return false;
	for( int i=0; i<nrows; i++ ){
		for( int j=0; j<ncols; j++ ){
			if( ms[i*strides+j] != mo[i*strideo+j] ) ret = false;
		}
	}
	return ret;
}

// operator != -------------------------------------------------------------------------------------
// matrix != matrix
template< typename T >
bool not_equal_to_2( const T* ms, const T* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	return !(equal_to_2(ms, mo, nrows, ncols, strides, nrowo, ncolo, strideo ));
}

// operator + ------------------------------------------------------------------------------------
// matrix + matrix
template< typename T >
bool addition_2( T* mout, const T* m1, const T* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 );


// operator - ------------------------------------------------------------------------------------
// matrix - matrix
template< typename T >
bool subtraction_2( T* mout, const T* m1, const T* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 );

// operator * ------------------------------------------------------------------------------------
// scalar * matrix
template< typename T>
void multiplication_2( T* mout, const T s, const T* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride );


// operator / ------------------------------------------------------------------------------------
// matrix / scalar
template< typename T>
void division_2( T* mout, const T s, const T* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride );


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for combination of one- and two-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator * ------------------------------------------------------------------------------------
// matrix * matrix
template< typename T >
bool multiplication_22( T* mout, const T* m1, const T* m2, const unsigned int nrow1, const unsigned int ncol1, const unsigned int stride1,
	const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 );

// operator * ------------------------------------------------------------------------------------
// vector * vector
template<typename T>
void multiplication_11( T* mout, const T* v1, const T* v2, const unsigned int sz1, const unsigned int sz2 );


// operator * ------------------------------------------------------------------------------------
// vector * matrix
template<typename T>
bool multiplication_12( T* vout, const T* v, const T* m, const unsigned int sz, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride );


// operator * ------------------------------------------------------------------------------------
// matrix * vector
template<typename T>
bool multiplication_21( T* vout, const T* m, const T* v, const unsigned int nrow, const unsigned int ncol, const unsigned int stride,
	const unsigned int sz );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for sorting
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template<typename T>
int select_pivot( const T* tagv, const int start, const int end );

template<typename T>
int partition( T* tagv, const int start, const int end, const int pivotno, int* original_pos=nullptr, const int shift=0 );

template<typename T>
void quicksort_recursive( T* tagv, const int start, const int end, int* original_pos=nullptr, const int shift=0 );

template<typename T>
void quicksort( T* tagv, const int start, const int end, int* original_pos=nullptr );

template< typename T >
int sequential_search( const T* tagv, const int start, const int end, const T target );

template< typename T >
int binary_search( const T* tagv, const int start, const int end, const T target );


}// end of namespace arr

#include "arrays_common.hpp"

#endif