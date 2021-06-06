#ifndef VECTOR
#define VECTOR

namespace arr{

	template< typename T >
	class vector{
	private:
		unsigned int msize;
		bool msub;
		bool mempty;
		bool mref;
		T* vals;
	public:
		vector();
		vector( const unsigned int size );
		vector( const unsigned int size, const T& val );
		vector( std::initializer_list<T> init );
		vector( const vector<T>& v );
		~vector();
		vector<T>& operator=( const vector<T>& v );

		T& operator[]( const unsigned int i );
		T  operator[]( const unsigned int i )const;

		const T* get()const;
		T* get();
		void set( const unsigned int size, T* p );
		unsigned int size()const;
		bool is_sub()const;
		bool is_empty()const;
		bool is_ref()const;

		void show( std::ostream& stream=std::cout, const int width=15, const int dec=5 )const;

		void resize( const unsigned int size );
		void resize( const unsigned int size, const T& val );
		void reset();
		void push_back( const T& val );
		void erase( const unsigned int no );
		void fill( const T& val, const int start=0, const int end=-1 );
		int  find( const T& val, const int start=0, const int end=-1 );
		vector<int> sort( const int start=0, const int end=-1 );

		static vector<T> zero( const unsigned int size );
		static vector<T> constant( const unsigned int size, const T& val );
		static vector<T> arrange( const T start, const T end, const T intvl );

		vector<T>& operator +=( const T s );
		vector<T>& operator +=( const vector<T>& v );
		vector<T>& operator -=( const T s );
		vector<T>& operator -=( const vector<T>& v );
		vector<T>& operator *=( const T s );
		vector<T>& operator /=( const T s );
		vector<T>  operator -()const;
		bool operator ==( const vector<T>& v )const;
		bool operator !=( const vector<T>& v )const;
		T dot( const vector<T>& v )const;

		void create_sub_vector( unsigned int size, T* pvals );
		vector<T> sub( const unsigned int s, const unsigned int num )const;

		vector<T>& shallow_copy( const vector<T>& v );
		vector<T>& deep_copy( const vector<T>& v );
		
	};

	template<typename T>
	vector<T> operator +( const vector<T>& v1, const vector<T>& v2 );

	template<typename T>
	vector<T> operator -( const vector<T>& v1, const vector<T>& v2 );

	template<typename T>
	vector<T> operator *( const vector<T>& v, const T s );

	template<typename T>
	vector<T> operator *( const T s, const vector<T>& v );

	template<typename T>
	vector<T> operator *( const vector<T>& v, const T s );

}

#include "vector.hpp"

#endif