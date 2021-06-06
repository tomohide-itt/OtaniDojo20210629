#ifndef ARRAY1_HPP
#define ARRAY1_HPP

#include <iomanip>
#include "../arrays_common.h"
#include <math.h>

namespace arr{

	template< typename T, int N >
	array1<T,N>::array1() : msize(N), pvals(nullptr){
	}

	template< typename T, int N >
	array1<T,N>::array1( const T& v ) :array1(){
		//msize = N;
		for( int i=0; i<N; i++ ) vals[i] = v;
	}

	template< typename T, int N >
	array1<T,N>::array1( std::initializer_list<T> init ) :array1(){
		//msize = N;
		int min_sz = init.size();
		if( msize < init.size() ) min_sz = msize;
		for( int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	template< typename T, int N >
	array1<T,N>::array1( const array1<T,N>& v ) :array1(){
		this->deep_copy( v );
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator=( const array1<T,N>& v ){
		this->deep_copy( v );
		return *this;
	}

	template< typename T, int N >
	T& array1<T,N>::operator[]( const unsigned int i ){
		if( pvals != nullptr ) return *(pvals+i);
		return vals[i];
	}

	template< typename T, int N >
	T array1<T,N>::operator[]( const unsigned int i )const{
		if( pvals != nullptr ) return *(pvals+i);
		return vals[i];
	}

	template< typename T, int N >
	unsigned int array1<T,N>::size()const{
		return msize;
	}

	template< typename T, int N >
	const T* array1<T,N>::get()const{
		if( pvals != nullptr ) return pvals;
		return vals;
	}

	template< typename T, int N >
	T* array1<T,N>::get(){
		if( pvals != nullptr ) return pvals;
		return vals;
	}

	template< typename T, int N >
	void array1<T,N>::set( T* p ){
		pvals = p;
	}

	template< typename T, int N >
	void array1<T,N>::show( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		for( unsigned int i=0; i<msize; i++ ){
			stream << std::setw(width) << (*this)[i];
		}
		stream << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	template< typename T, int N >
	void array1<T,N>::fill( const T& val ){
		for( unsigned int i=0; i<msize; i++ ){
			(*this)[i] = val;
		}
	}

	template< typename T, int N >
	array1<T,N> array1<T,N>::zero(){
		array1<T,N> ret;
		zero_common<T>( ret.get(), N );
		return ret;
	}

	template< typename T, int N >
	array1<T,N> array1<T,N>::constant( const T& val ){
		array1<T,N> ret;
		for( int i=0; i<N; i++ ) ret[i] = val;
		return ret;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator +=( const T s ){
		addition_assignment_1<T>( this->get(), s, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator +=( const array1<T,N>& v ){
		addition_assignment_1<T>( this->get(), v.get(), N, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator -=( const T s ){
		subtraction_assignment_1<T>( this->get(), s, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator -=( const array1<T,N>& v ){
		subtraction_assignment_1<T>( this->get(), v.get(), N, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator *=( const T s ){
		multiplication_assignment_1<T>( this->get(), s, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::operator /=( const T s ){
		division_assignment_1<T>( this->get(), s, N );
		return *this;
	}

	template< typename T, int N >
	array1<T,N> array1<T,N>::operator -() const{
		array1<T,N> ret;
		unary_minus_1<T>( this->get(), ret.get(), N );
		return ret;
	}

	template< typename T, int N >
	bool array1<T,N>::operator ==( const array1<T,N>& v )const{
		return equal_to_1<T>( this->get(), v.get(), N, N );
	}

	template< typename T, int N >
	bool array1<T,N>::operator !=( const array1<T,N>& v )const{
		return not_equal_to_1<T>( this->get(), v.get(), N, N );
	}

	template< typename T, int N >
	T array1<T,N>::dot( const array1<T,N>& v )const{
		T ret = 0.0;
		dot_1( ret, this->get(), v.get(), N, N );
		return ret;
	}

	template< typename T, int N >
	T array1<T,N>::norm()const{
		T ret = 0.0;
		for( unsigned int i=0; i<N; i++ ) ret += (*this)[i]*(*this)[i];
		return sqrt( ret );
	}

	template<>
	array1<double,3> array1<double,3>::vec_prdct( const array1<double,3>& v )const{
		array1<double,3> ret;
		ret[0] = (*this)[1]*v[2] - (*this)[2]*v[1];
		ret[1] = (*this)[2]*v[0] - (*this)[0]*v[2];
		ret[2] = (*this)[0]*v[1] - (*this)[1]*v[0];
		return ret;
	}

	template< typename T, int N >
	array1<T,N>& array1<T,N>::deep_copy( const array1<T,N>& v ){
		this->msize = v.size();
		//this->pvals = nullptr;
		for( unsigned int i=0; i<N; i++ ){
			(*this)[i] = v[i];
		}
		return *this;
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	template<typename T, int N>
	array1<T,N> operator +( const array1<T,N>& v1, const array1<T,N>& v2 ){
		array1<T,N> ret;
		addition_1<T>( ret.get(), v1.get(), v2.get(), N, N );
		return ret;
	}

	template<typename T, int N>
	array1<T,N> operator -( const array1<T,N>& v1, const array1<T,N>& v2 ){
		array1<T,N> ret;
		subtraction_1<T>( ret.get(), v1.get(), v2.get(), N, N );
		return ret;
	}

	template<typename T, int N>
	array1<T,N> operator *( const T s, const array1<T,N>& v ){
		array1<T,N> ret;
		multiplication_1<T>( ret.get(), s, v.get(), N );
		return ret;
	}

	template<typename T, int N>
	array1<T,N> operator *( const array1<T,N>& v, const T s ){
		return s*v;
	}

	template<typename T, int N>
	array1<T,N> operator /( const array1<T,N>& v, const T s ){
		array1<T,N> ret;
		division_1<T>( ret.get(), s, v.get(), N );
		return ret;
	}


}

#endif