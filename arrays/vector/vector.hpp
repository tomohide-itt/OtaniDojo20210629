#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iomanip>
#include "vector.h"
#include "../arrays_common.h"
#include <math.h>

namespace arr{

	template<typename T>
	vector<T>::vector() :msize{0}, msub{false}, mempty{true}, mref{false}, vals{nullptr}{}

	template<typename T>
	vector<T>::vector( const unsigned int size ) :msize{size}, msub{false}, mref{false}, mempty{false}{
		vals = new T[msize];
	}

	template<typename T>
	vector<T>::vector( const unsigned int size, const T& val ) :vector(size){
		for( unsigned int i=0; i<msize; i++ ){
			vals[i] = val;
		}
	}

	template<typename T>
	vector<T>::vector( std::initializer_list<T> init ){
		msize = init.size();
		msub = false;
		mempty = false;
		mref = false;
		vals = new T[msize];
		for( unsigned int i=0; i<msize; i++ ){
			vals[i] = *( init.begin() + i );
		}
	}

	template<typename T>
	vector<T>::vector( const vector<T>& v ) :vector(){
		if( v.is_sub() ) this->shallow_copy(v);
		else this->deep_copy(v);
	}

	template<typename T>
	vector<T>::~vector(){
		if( !mempty ) delete[] vals;
	}

	template<typename T>
	vector<T>& vector<T>::operator=( const vector<T>& v ){
		if( v.is_sub() ) this->shallow_copy(v);
		this->deep_copy(v);
		return *this;
	}

	template<typename T>
	T& vector<T>::operator[]( const unsigned int i ){
		return vals[i];
	}

	template<typename T>
	T vector<T>::operator[]( const unsigned int i )const{
		return vals[i];
	}

	template<typename T>
	const T* vector<T>::get()const{
		return vals;
	}

	template<typename T>
	T* vector<T>::get(){
		return vals;
	}

	template<typename T>
	T* vector<T>::begin()const{
		return vals;
	}

	template<typename T>
	T* vector<T>::end()const{
		return &(vals[msize-1])+1;
	}

	template<typename T>
	void vector<T>::set( const unsigned int size, T* p ){
		if( !mempty ) delete[] vals;
		msize = size;
		vals = p;
		mref = true;
		mempty = true;
	}

	template<typename T>
	unsigned int vector<T>::size()const{
		return msize;
	}

	template<typename T>
	bool vector<T>::is_sub()const{
		return msub;
	}

	template<typename T>
	bool vector<T>::is_empty()const{
		return mempty;
	}

	template<typename T>
	bool vector<T>::is_ref()const{
		return mref;
	}

	template<typename T>
	void vector<T>::show( std::ostream& stream, const int width, const int dec )const{
		stream << std::scientific << std::setprecision( dec );
		for( unsigned int i=0; i<msize; i++ ){
			 stream << std::setw(width) << vals[i];
		}
		stream << std::endl;
		stream.unsetf( std::ios::scientific );
	}

	template<typename T>
	void vector<T>::resize( const unsigned int size ){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-vector is not allowed to resize\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		this->msize = size;
		if( !mempty ) delete[] vals;
		vals = new T[msize];
		mempty = false;
	}

	template<typename T>
	void vector<T>::resize( const unsigned int size, const T& val ){
		this->resize( size );
		for( unsigned int i=0; i<msize; i++ ) vals[i] = val;
	}

	template<typename T>
	void vector<T>::reset(){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-vector is not allowed to reset\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		msize = 0;
		if( !mempty ) delete[] vals;
		mempty = true;
	}

	template<typename T>
	void vector<T>::push_back( const T& val ){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-vector is not allowed to push_back\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		if( !mempty ){
			vector<T> tmp_vec( *this );
			this->resize( tmp_vec.size() + 1 );
			for( unsigned int i=0; i<tmp_vec.size(); i++ ){
				this->vals[i] = tmp_vec[i];
			}
			this->vals[tmp_vec.size()] = val;
		}else{
			this->resize( 1 );
			this->vals[0] = val;
		}
	}

	template<typename T>
	void vector<T>::erase( const unsigned int no ){
		if( mref || msub ){
			printf( "\nERROR# %s(%d): %s\nsub-/ref-vector is not allowed to erase\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		if( no > msize ){
			printf( "\nERROR# %s(%d): %s\naccess violation\n", __FILE__, __LINE__, __FUNCTION__ );
			return;
		}
		if( !mempty && msize > 1 ){
			vector<T> tmp_vec( *this );
			this->resize( tmp_vec.size() - 1 );
			unsigned int cnt=0;
			for( unsigned int i=0; i<tmp_vec.size(); i++ ){
				if( i != no ){
					this->vals[cnt++] = tmp_vec[i];
				}
			}
		}else if( !mempty && msize == 1 ){
			this->reset();
		}
	}

	template<typename T>
	void vector<T>::fill( const T& val, const int start, const int end ){
		int End = end;
		if( End == -1 ) End = this->msize-1;
		for( int i=start; i<=End; i++ ){
			unsigned int ui = static_cast<unsigned int>( i );
			vals[ui] = val;
		}
	}

	template<typename T>
	int vector<T>::find( const T& val, const int start, const int end ){
		int End = end;
		if( End == -1 ) End = this->msize-1;
		int ret = -1;
		for( int i=start; i<=End; i++ ){
			unsigned int ui = static_cast<unsigned int>( i );
			if( vals[ui] == val ){
				ret = i;
				break;
			}
		}
		return ret;
	}

	template<typename T>
	vector<int> vector<T>::sort( const int start, const int end ){
		int End = end;
		if( End == -1 ) End = this->msize-1;
		vector<int> original_pos( End-start+1, 0 );
		quicksort<T>( vals, start, End, original_pos.get() );
		return original_pos;
	}

	template<typename T>
	vector<T> vector<T>::zero( const unsigned int size ){
		vector<T> ret( size );
		zero_common<T>( ret.get(), size );
		return ret;
	}

	template<typename T>
	vector<T> vector<T>::constant( const unsigned int size, const T& val ){
		vector<T> ret( size );
		for( unsigned int i=0; i<size; i++ ){
			ret[i] = val;
		}
		return ret;
	}

	template<typename T>
	vector<T> vector<T>::arrange( const T start, const T end, const T intvl ){
		unsigned int size = static_cast<unsigned int>( (end-start)/intvl + 1 );
		vector<T> ret( size );
		arrange_common<T>( ret.get(), start, intvl, size );
		return ret;
	}

	template<typename T>
	vector<T>& vector<T>::operator +=( const T s ){
		addition_assignment_1<T>( this->get(), s, this->msize );
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator +=( const vector<T>& v ){
		bool suc = addition_assignment_1<T>( this->get(), v.get(), this->msize, v.size() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of vectors is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator -=( const T s ){
		subtraction_assignment_1<T>( this->get(), s, this->msize );
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator -=( const vector<T>& v ){
		bool suc = subtraction_assignment_1<T>( this->get(), v.get(), this->msize, v.size() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of vectors is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator *=( const T s ){
		multiplication_assignment_1<T>( this->get(), s, this->msize );
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::operator /=( const T s ){
		division_assignment_1<T>( this->get(), s, this->msize );
		return *this;
	}

	template<typename T>
	vector<T> vector<T>::operator -()const{
		vector<T> ret(msize);
		unary_minus_1<T>( this->get(), ret.get(), this->msize );
		return ret;
	}

	template<typename T>
	bool vector<T>::operator ==( const vector<T>& v )const{
		return equal_to_1<T>( this->get(), v.get(), this->msize, v.size() );
	}

	template<typename T>
	bool vector<T>::operator !=( const vector<T>& v )const{
		return not_equal_to_1<T>( this->get(), v.get(), this->msize, v.size() );
	}

	template<typename T>
	T vector<T>::dot( const vector<T>& v )const{
		T ret=0.0;
		bool suc = dot_1<T>( ret, this->get(), v.get(), this->msize, v.msize );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of vectors is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	vector<T>& vector<T>::shallow_copy( const vector<T>& v ){
		msize = v.size();
		mempty = true;
		msub = v.is_sub();
		vals = v.vals;
		return *this;
	}

	template<typename T>
	vector<T>& vector<T>::deep_copy( const vector<T>& v ){
		if( msub ){
			printf( "\nWARNING# %s(%d): %s\ndeep_copy is called from sub-vector\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		if( !mempty ) delete[] vals;
		if( v.is_empty() && !v.is_ref() ){
			msize = 0;
			mempty = true;
		}else{
			msize = v.size();
			vals = new T[msize];
			mempty = false;
		}
		msub = false;
		mref = false;
		for( unsigned int i=0; i<msize; i++ ) vals[i] = v[i];
		return *this;
	}

	template<typename T>
	void vector<T>::create_sub_vector( unsigned int size, T* pvals ){
		if( !mempty ){
			this->reset();
		}
		msub = true;
		msize = size;
		mref = false;
		vals = pvals;
	}

	template<typename T>
	vector<T> vector<T>::sub( const unsigned int s, const unsigned int num )const{
		if( s+num > msize ){
			printf( "\nERROR# %s(%d): %s\narguments are invalid\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		vector<T> ret;
		ret.create_sub_vector( num, &(vals[s]) );
		return ret;
	}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	template<typename T>
	vector<T> operator +( const vector<T>& v1, const vector<T>& v2 ){
		vector<T> ret( v1.size() );
		bool suc = addition_1<T>( ret.get(), v1.get(), v2.get(), v1.size(), v2.size() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of vectors is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	vector<T> operator -( const vector<T>& v1, const vector<T>& v2 ){
		vector<T> ret( v1.size() );
		bool suc = subtraction_1<T>( ret.get(), v1.get(), v2.get(), v1.size(), v2.size() );
		if( !suc ){
			printf( "\nWARNING# %s(%d): %s\nThe size of vectors is different\n", __FILE__, __LINE__, __FUNCTION__ );
		}
		return ret;
	}

	template<typename T>
	vector<T> operator *( const T s, const vector<T>& v ){
		vector<T> ret( v.size() );
		multiplication_1<T>( ret.get(), s, v.get(), v.size() );
		return ret;
	}

	template<typename T>
	vector<T> operator *( const vector<T>& v, const T s ){
		return s*v;
	}

	template<typename T>
	vector<T> operator /( const vector<T>& v, const T s ){
		vector<T> ret( v.size() );
		division_1<T>( ret.get(), s, v.get(), v.size() );
		return ret;
	}



} //end of namespase arr

#endif