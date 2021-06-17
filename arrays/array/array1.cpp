#include "array1.h"

namespace arr{

	template<>
	array1<double,3> array1<double,3>::vec_prdct( const array1<double,3>& v )const{
		array1<double,3> ret;
		ret[0] = (*this)[1]*v[2] - (*this)[2]*v[1];
		ret[1] = (*this)[2]*v[0] - (*this)[0]*v[2];
		ret[2] = (*this)[0]*v[1] - (*this)[1]*v[0];
		return ret;
	}

}