#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iomanip>
#include "vector.h"
#include "matrix.h"
#include "../array/array2.h"
#include "../arrays_common.h"
#include <math.h>

namespace arr{

	template<typename T>
	matrix<T>::matrix() : msize{0}, mrows{0}, mcols{0}, mstride{0}, msub{false}, mempty{true}, mref{false}, vals{nullptr}{}

	template<typename T>
	matrix<T>::matrix( const unsigned int r, const unsigned int c )
		:msize{r*c}, mrows{r}, mcols{c}, mstride{c}, msub{false}, mempty{false}, mref{false}{
		vals = new T[msize];
	}

	template<typename T>
	matrix<T>::matrix( const unsigned int r, const unsigned int c, const T& val )
		: matrix( r, c ){
		for( unsigned int i=0; i<msize; i++ ) vals[i] = val;
	}

	template<typename T>
	matrix<T>::matrix( const matrix<T>& m ) :matrix(){
		if( m.is_sub() ) this->shallow_copy(m);
		else this->deep_copy(m);
	}

	template<typename T>
	matrix<T>::~matrix(){
		if( !mempty ) delete[] vals;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator=( const matrix<T>& m ){
		if( m.is_sub() ) this->shallow_copy(m);
		else this->deep_copy(m);
		return *this;
	}

	template<typename T>
	T& matrix<T>::operator[]( const unsigned int i ){ return vals[i]; }

	template<typename T>
	T matrix<T>::operator[]( const unsigned int i )const{ return vals[i]; }

	template<typename T>
	T& matrix<T>::operator()( const unsigned int r, const unsigned int c ){
		unsigned int i= r*mstride+c;
		if( r >= mrows || c >= mcols ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return vals[i];
	}

	template<typename T>
	T matrix<T>::operator()( const unsigned int r, const unsigned int c )const{
		unsigned int i= r*mstride+c;
		if( r >= mrows || c >= mcols ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return vals[i];
	}

	template<typename T>
	vector<T> matrix<T>::operator()( const unsigned int i ){
		if( i >= mrows ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		vector<T> ret;
		ret.create_sub_vector( mcols, &(vals[i*mstride]) );
		return ret;
	}

	template<typename T>
	vector<T> matrix<T>::operator()( const unsigned int i )const{
		if( i >= mrows ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		vector<T> ret;
		ret.create_sub_vector( mcols, &(vals[i*mstride]) );
		return ret;
	}

	template<typename T>
	const T* matrix<T>::get()const{ return vals; }

	template<typename T>
	T* matrix<T>::get(){ return vals; }

	template<typename T>
	void matrix<T>::set( const unsigned int r, const unsigned int c, T* p ){
		if( msub ){
			printf( "\nERROR# %s(%d): %s\nsub-matrix\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		if( !mempty ) delete[] vals;
		mrows = r;
		mcols = c;
		mstride = c;
		msize = r*c;
		vals = p;
		mref = true;
		mempty = true;
	}

	template<typename T>
	unsigned int matrix<T>::size()const{ return msize; }

	template<typename T>
	unsigned int matrix<T>::rows()const{ return mrows; }

	template<typename T>
	unsigned int matrix<T>::cols()const{ return mcols; }

	template<typename T>
	unsigned int matrix<T>::stride()const{ return mstride; }

	template<typename T>
	bool matrix<T>::is_sub()const{ return msub; }

	template<typename T>
	bool matrix<T>::is_empty()const{ return mempty; }

	template<typename T>
	bool matrix<T>::is_ref()const{ return mref; }

	template<typename T>
	void matrix<T>::show( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		for( unsigned int i=0; i<mrows; i++ ){
			for( unsigned int j=0; j<mcols; j++ ){
				stream << std::setw(width) << vals[i*mstride+j];
			}
			stream << std::endl;
		}
		stream.unsetf( std::ios::scientific );
	}

	template<typename T>
	void matrix<T>::resize( const unsigned int r, const unsigned int c ){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-matrix is not allowed to resize\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		msize = r*c;
		mrows = r;
		mcols = c;
		mstride = c;
		msub = false;
		if( !mempty ) delete vals;
		vals = new T[msize];
		mempty = false;
	}

	template<typename T>
	void matrix<T>::resize( const unsigned int r, const unsigned int c, const T& val ){
		this->resize( r, c );
		for( unsigned int i=0; i<msize; i++ ) vals[i] = val;
	}

	template<typename T>
	void matrix<T>::reset(){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-matrix is not allowed to reset\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		msize = 0;
		mrows = 0;
		mcols = 0;
		mstride = 0;
		msub = false;
		if( !mempty ) delete[] vals;
		mempty = true;
	}

	template<typename T>
	void matrix<T>::fill( const T& val ){
		for( unsigned int i=0; i<msize; i++ ) vals[i]=val;
	}

	template<typename T>
	matrix<T> matrix<T>::zero( const unsigned int r, const unsigned int c ){
		matrix<T> ret(r,c);
		zero_common<T>( ret.get(), ret.msize );
		return ret;
	}

	template<typename T>
	matrix<T> matrix<T>::constant( const unsigned int r, const unsigned int c, const T& val ){
		matrix<T> ret(r,c);
		for( unsigned int i=0; i<ret.size(); i++ ) ret[i] = val;
		return ret;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator +=( const T s ){
		addition_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator +=( const matrix<T>& m ){
		bool suc = addition_assignment_2<T>( this->get(), m.vals, this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of matrices is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator -=( const T s ){
		subtraction_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
		return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator -=( const matrix<T>& m ){
		bool suc = subtraction_assignment_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of matrices is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator *=( const T s ){
		multiplication_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
	return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::operator /=( const T s ){
		division_assignment_2<T>( this->get(), s, this->mrows, this->mcols, this->mstride );
	return *this;
	}

	template<typename T>
	matrix<T>  matrix<T>::operator -()const{
		matrix<T> ret( mrows, mcols );
		unary_minus_2( this->get(), ret.get(), this->mrows, this->mcols, this->mstride );
		return ret;
	}

	template<typename T>
	bool matrix<T>::operator ==( const matrix<T>& m )const{
		return equal_to_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
	}

	template<typename T>
	bool matrix<T>::operator !=( const matrix<T>& m )const{
		return not_equal_to_2<T>( this->get(), m.get(), this->mrows, this->mcols, this->mstride, m.rows(), m.cols(), m.stride() );
	}

	template<typename T>
	matrix<T> matrix<T>::transpose()const{
		matrix<T> ret( mcols, mrows );
		unsigned int ret_stride = ret.stride();
		for( unsigned int i=0; i<mcols; i++ ){
			for( unsigned int j=0; j<mrows; j++ ){
				ret[i*ret_stride+j] = vals[j*mstride+i];
			}
		}
		return ret;
	}

	template<typename T>
	void matrix<T>::create_sub_matrix( const unsigned int r, const unsigned int c, T* pvals ){
		if( !mempty ){
			this->reset();
		}
		msub = true;
		mref = false;
		msize = r*c;
		mrows = r;
		mcols = c;
		mstride = c;
		vals = pvals;
	}

	template<typename T>
	vector<T> matrix<T>::sub( const unsigned int s, const unsigned int num )const{
		if( s+num > msize ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		vector<T> ret;
		ret.create_sub_vector( num, &(vals[s]) );
		return ret;
	}

	template<typename T>
	matrix<T> matrix<T>::sub( const unsigned int sr, const unsigned int sc, const unsigned int num_r, const unsigned int num_c )const{
		if( sr+num_r > mrows || sc+num_c > mcols ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		matrix<T> ret;
		ret.create_sub_matrix( num_r, num_c, &(vals[sr*mstride+sc]) );
		return ret;
	}

	template<typename T>
	matrix<T>& matrix<T>::shallow_copy( const matrix<T>& m ){
		msize = m.size();
		mrows = m.rows();
		mcols = m.cols();
		mstride = m.stride();
		mempty = true;
		msub = m.is_sub();
		vals = m.vals;
		return *this;
	}

	template<typename T>
	matrix<T>& matrix<T>::deep_copy( const matrix<T>& m ){
		if( msub ){
			printf( "\nWARNING# %s(%d): %s\ndeep_copy is called from sub-matrix\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		if( !mempty ) delete[] vals;
		msize = m.size();
		mrows = m.rows();
		mcols = m.cols();
		mstride = m.stride();
		mempty = m.is_empty();
		if( !m.is_empty() || ( m.is_ref() && m.size()>0 ) ){
			vals = new T[msize];
		}
		msub = false;
		for( unsigned int i=0; i<msize; i++ ) vals[i] = m.vals[i];
		return *this;
	}

	template<typename T>
	template<int Nr, int Nc>
	matrix<T>::operator array2<T,Nr,Nc>()const{
		array2<T,Nr,Nc> ret;
		if( Nr != mrows || Nc != mcols ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		unsigned int min_rows = ( Nr < mrows )? Nr : mrows;
		unsigned int min_cols = ( Nc < mcols )? Nc : mcols;
		for( unsigned int i=0; i<min_rows; i++ ){
			for( unsigned int j=0; j<min_cols; j++ ){
				ret(i,j) = vals[i*mstride+j];
			}
		}
		return ret;
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	template<typename T>
	matrix<T> operator +( const matrix<T>& m1, const matrix<T>& m2 ){
		matrix<T> ret( m1.rows(), m1.cols() );
		bool suc = addition_2<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		if( !suc ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	matrix<T> operator -( const matrix<T>& m1, const matrix<T>& m2 ){
		matrix<T> ret( m1.rows(), m1.cols() );
		bool suc = subtraction_2<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		if( !suc ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	matrix<T> operator *( const T s, const matrix<T>& m ){
		matrix<T> ret( m.rows(), m.cols() );
		multiplication_2<T>( ret.get(), s, m.get(), m.rows(), m.cols(), m.stride() );
		return ret;
	}

	template<typename T>
	matrix<T> operator *( const matrix<T>& m, const T s ){
		return s*m;
	}

	template<typename T>
	matrix<T> operator /( const matrix<T>& m, const T s ){
		matrix<T> ret( m.rows(), m.cols() );
		division_2<T>( ret.get(), s, m.get(), m.rows(), m.cols(), m.stride() );
		return ret;
	}

	template<typename T>
	matrix<T> operator *( const matrix<T>& m1, const matrix<T>& m2 ){
		matrix<T> ret( m1.rows(), m2.cols() );
		bool suc = multiplication_22<T>( ret.get(), m1.get(), m2.get(), m1.rows(), m1.cols(), m1.stride(), m2.rows(), m2.cols(), m2.stride() );
		if( !suc ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	matrix<T> operator *( const vector<T>& v1, const vector<T>& v2 ){
		matrix<T> ret( v1.size(), v2.size() );
		multiplication_11<T>( ret.get(), v1.get(), v2.get(), v1.size(), v2.size() );
		return ret;
	}

	template<typename T>
	vector<T> operator *( const vector<T>& v, const matrix<T>& m ){
		vector<T> ret( m.cols() );
		bool suc = multiplication_12<T>( ret.get(), v.get(), m.get(), v.size(), m.rows(), m.cols(), m.stride() );
		if( !suc ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	vector<T> operator *( const matrix<T>& m, const vector<T>& v ){
		vector<T> ret( m.rows() );
		bool suc = multiplication_21<T>( ret.get(), m.get(), v.get(), m.rows(), m.cols(), m.stride(), v.size() );
		if( !suc ){
			printf( "\nERROR# %s(%d): %s\nThe size does not match\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}



} //end of namespase arr

#endif