#ifndef ARRAY2_HPP
#define ARRAY2_HPP

#include <iomanip>
#include "../arrays_common.h"
#include "../vector/matrix.h"
#include <math.h>

namespace arr{

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>::array2() : msize{Nr*Nc}, mrows{Nr}, mcols{Nc}, mstride{Nc}, pvals{nullptr}{};

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>::array2( std::initializer_list<T> init )
		: msize{Nr*Nc}, mrows{Nr}, mcols{Nc}, mstride{Nc}, pvals{nullptr}{
		int min_sz = ( static_cast<int>(init.size()) > Nr*Nc )? Nr*Nc : static_cast<int>(init.size());
		for( int i=0; i<min_sz; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>::array2( const array2<T,Nr,Nc>& m ) :array2(){
		this->deep_copy( m );
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator=( const array2<T,Nr,Nc>& m ){
		this->deep_copy( m );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	T& array2<T,Nr,Nc>::operator[]( const unsigned int i ){
		if( pvals != nullptr ) return *(pvals+i);
		return vals[i];
	}

	template< typename T, int Nr, int Nc >
	T array2<T,Nr,Nc>::operator[]( const unsigned int i )const{
		if( pvals != nullptr ) return *(pvals+i);
		return vals[i];
	}

	template< typename T, int Nr, int Nc>
	T& array2<T,Nr,Nc>::operator()( const unsigned int i, const unsigned int j ){
		unsigned int no = i*mstride+j;
		if( no >= msize ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		if( pvals != nullptr ) return *(pvals+no);
		return vals[no];
	}

	template< typename T, int Nr, int Nc>
	T array2<T,Nr,Nc>::operator()( const unsigned int i, const unsigned int j )const{
		unsigned int no = i*mstride+j;
		if( no >= msize ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		if( pvals != nullptr ) return *(pvals+no);
		return vals[no];
	}

	template< typename T, int Nr, int Nc >
	array1<T,Nc> array2<T,Nr,Nc>::operator()( const unsigned int r )const{
		array1<T,Nc> ret = array1<T,Nc>::zero();
		if( r > Nr ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
			return ret;
		}
		for( unsigned int c=0; c<Nc; c++ ){
			ret[c] = (*this)(r,c);
		}
		return ret;
	}

	template< typename T, int Nr, int Nc >
	const T* array2<T,Nr,Nc>::get()const{
		if( pvals != nullptr ) return pvals;
		return &(vals[0]);
	}

	template< typename T, int Nr, int Nc >
	T* array2<T,Nr,Nc>::get(){
		if( pvals != nullptr ) return pvals;
		return &(vals[0]);
	}

	template< typename T, int Nr, int Nc >
	void array2<T,Nr,Nc>::set( T* p ){
		pvals = p;
	}

	template< typename T, int Nr, int Nc >
	unsigned int array2<T,Nr,Nc>::size()const{
		return msize;
	}

	template< typename T, int Nr, int Nc >
	unsigned int array2<T,Nr,Nc>::rows()const{
		return mrows;
	}

	template< typename T, int Nr, int Nc >
	unsigned int array2<T,Nr,Nc>::cols()const{
		return mcols;
	}

	template< typename T, int Nr, int Nc >
	unsigned int array2<T,Nr,Nc>::stride()const{
		return mstride;
	}

	template< typename T, int Nr, int Nc >
	void array2<T,Nr,Nc>::show( std::ostream& stream, const int width, const int dec ) const{
		stream << std::scientific << std::setprecision( dec );
		for( int i=0; i<mrows; i++ ){
			for( int j=0; j<mcols; j++ ){
				stream << std::setw(width) << (*this)(i,j);
			}
			stream << std::endl;
		}
		stream.unsetf( std::ios::scientific );
	}

	template< typename T, int Nr, int Nc >
	void array2<T,Nr,Nc>::fill( const T& val ){
		for( int i=0; i<msize; i++ ) vals[i] = val;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc> array2<T,Nr,Nc>::zero(){
		array2<T,Nr,Nc> ret;
		zero_common<T>( ret.get(), ret.size() );
		return ret;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc> array2<T,Nr,Nc>::constant( const T& val ){
		array2<T,Nr,Nc> ret;
		for( int i=0; i<ret.size(); i++ ) ret[i] = val;
		return ret;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator +=( const T s ){
		addition_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator +=( const array2<T,Nr,Nc>& m ){
		addition_assignment_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator -=( const T s ){
		subtraction_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator -=( const array2<T,Nr,Nc>& m ){
		subtraction_assignment_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator *=( const T s ){
		multiplication_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::operator /=( const T s ){
		division_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc> array2<T,Nr,Nc>::operator -() const{
		array2<T,Nr,Nc> ret;
		unary_minus_2<T>( this->get(), ret.get(), this->mrows, this->mcols, this->mstride );
		return ret;
	}

	template< typename T, int Nr, int Nc >
	bool array2<T,Nr,Nc>::operator == ( const array2<T,Nr,Nc>& m ) const{
		return equal_to_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
	}

	template< typename T, int Nr, int Nc >
	bool array2<T,Nr,Nc>::operator != ( const array2<T,Nr,Nc>& m ) const{
		return not_equal_to_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nc,Nr> array2<T,Nr,Nc>::transpose() const{
		array2<T,Nc,Nr> ret;
		for( int i=0; i<mcols; i++ ){
			for( int j=0; j<mrows; j++ ){
				ret(i,j) = (*this)(j,i);
			}
		}
		return ret;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>& array2<T,Nr,Nc>::deep_copy( const array2<T,Nr,Nc>& m ){
		this->msize = m.size();
		this->mrows = m.rows();
		this->mcols = m.cols();
		this->mstride = m.stride();
		//this->pvals = nullptr;
		for( unsigned int i=0; i<this->size(); i++ ){
			(*this)[i] = m[i];
		}
		return *this;
	}

	template< typename T, int Nr, int Nc >
	array2<T,Nr,Nc>::operator matrix<T>()const{
		matrix<T> ret( Nr, Nc );
		for( unsigned int i=0; i<Nr; i++ ){
			for( unsigned int j=0; j<Nc; j++ ){
				ret(i,j) = (*this)(i,j);
			}
		}
		return ret;
	}

	
	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator +( const array2<T,Nr,Nc>& m1, const array2<T,Nr,Nc>& m2 ){
		array2<T,Nr,Nc> ret;
		addition_2<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		return ret;
	}

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator -( const array2<T,Nr,Nc>& m1, const array2<T,Nr,Nc>& m2 ){
		array2<T,Nr,Nc> ret;
		subtraction_2<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		return ret;
	}

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const T s, const array2<T,Nr,Nc>& m ){
		array2<T,Nr,Nc> ret;
		multiplication_2<T>( ret.get(), s, m.get(), m.rows(), m.cols(), m.stride() );
		return ret;
	}

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const array2<T,Nr,Nc>& m, const T s ){
		return s*m;
	}

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator /( const array2<T,Nr,Nc>& m, const T s ){
		array2<T,Nr,Nc> ret;
		division_2<T>( ret.get(), s, m.get(), m.rows(), m.cols(), m.stride() );
		return ret;
	}

	template<typename T, int Nr1, int Nc1, int Nc2 >
	array2<T,Nr1,Nc2> operator *( const array2<T,Nr1,Nc1>& m1, const array2<T,Nc1,Nc2>& m2 ){
		array2<T,Nr1,Nc2> ret;
		multiplication_22<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		return ret;
	}

	template<typename T, int Nr, int Nc >
	array2<T,Nr,Nc> operator *( const array1<T,Nr>& v1, const array1<T,Nc>& v2 ){
		array2<T,Nr,Nc> ret;
		multiplication_11<T>( ret.get(), v1.get(), v2.get(), v1.size(), v2.size() );
		return ret;
	}

	template<typename T, int Nv, int Nc >
	array1<T,Nc> operator *( const array1<T,Nv>& v, const array2<T,Nv,Nc>& m ){
		array1<T,Nc> ret;
		multiplication_12<T>( ret.get(), v.get(), m.get(), v.size(), m.rows(), m.cols(), m.stride() );
		return ret;
	}

	template<typename T, int Nr, int Nv >
	array1<T,Nr> operator *( const array2<T,Nr,Nv>& m, const array1<T,Nv>& v ){
		array1<T,Nr> ret;
		multiplication_21<T>( ret.get(), m.get(), v.get(), m.rows(), m.cols(), m.stride(), v.size() );
		return ret;
	}

	



} //end of namespace arr



#endif