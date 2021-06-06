#ifndef ARRAYS_COMMON_HPP
#define ARRAYS_COMMON_HPP

namespace arr{

// zero -------------------------------------------------------------------------------------------
template<>
void zero_common( int* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = 0;
}
template<>
void zero_common( float* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = 0.0;
}
template<>
void zero_common( double* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = 0.0;
}

// arrange ----------------------------------------------------------------------------------------
template<>
void arrange_common( int* v, const int start, const int intvl, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = start + i*intvl;
}
template<>
void arrange_common( float* v, const float start, const float intvl, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = start + i*intvl;
}
template<>
void arrange_common( double* v, const double start, const double intvl, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) v[i] = start + i*intvl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for one-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator += ------------------------------------------------------------------------------------
// vector += vector
template<>
bool addition_assignment_1( int* vs, const int* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] += vo[i];
	}
	return ret;
}
template<>
bool addition_assignment_1( float* vs, const float* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] += vo[i];
	}
	return ret;
}
template<>
bool addition_assignment_1( double* vs, const double* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] += vo[i];
	}
	return ret;
}

// operator += ------------------------------------------------------------------------------------
// vector += scalar
template<>
void addition_assignment_1( int* vs, const int so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] += so;
}
template<>
void addition_assignment_1( float* vs, const float so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] += so;
}
template<>
void addition_assignment_1( double* vs, const double so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] += so;
}

// operator -= ------------------------------------------------------------------------------------
// vector -= vector
template<>
bool subtraction_assignment_1( int* vs, const int* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] -= vo[i];
	}
	return ret;
}
template<>
bool subtraction_assignment_1( float* vs, const float* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] -= vo[i];
	}
	return ret;
}
template<>
bool subtraction_assignment_1( double* vs, const double* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	for( unsigned int i=0; i<min_sz; i++ ){
		vs[i] -= vo[i];
	}
	return ret;
}

// operator *= ------------------------------------------------------------------------------------
// vector *= scalar
template<>
void multiplication_assignment_1( int* vs, const int so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] *= so;
}
template<>
void multiplication_assignment_1( float* vs, const float so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] *= so;
}
template<>
void multiplication_assignment_1( double* vs, const double so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] *= so;
}

// operator /= ------------------------------------------------------------------------------------
// vector /= scalar
template<>
void division_assignment_1( int* vs, const int so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] /= so;
}
template<>
void division_assignment_1( float* vs, const float so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] /= so;
}
template<>
void division_assignment_1( double* vs, const double so, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vs[i] /= so;
}

// operator - -------------------------------------------------------------------------------------
// - vector
template<>
void unary_minus_1( const int* vs, int* vo, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vo[i] = -vs[i];
}
template<>
void unary_minus_1( const float* vs, float* vo, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vo[i] = -vs[i];
}
template<>
void unary_minus_1( const double* vs, double* vo, const unsigned int szs ){
	for( unsigned int i=0; i<szs; i++ ) vo[i] = -vs[i];
}

// dot -------------------------------------------------------------------------------------------
template<>
bool dot_1( int& dot, const int* vs, const int* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	dot = 0;
	for( unsigned int i=0; i<min_sz; i++ ){
		dot += vs[i]*vo[i];
	}
	return ret;
}
template<>
bool dot_1( float& dot, const float* vs, const float* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	dot = 0.0;
	for( unsigned int i=0; i<min_sz; i++ ){
		dot += vs[i]*vo[i];
	}
	return ret;
}
template<>
bool dot_1( double& dot, const double* vs, const double* vo, const unsigned int szs, const unsigned int szo ){
	bool ret = true;
	if( szs != szo ) ret = false;
	unsigned int min_sz = ( szs > szo )? szo : szs;
	dot = 0.0;
	for( unsigned int i=0; i<min_sz; i++ ){
		dot += vs[i]*vo[i];
	}
	return ret;
}

// operator + ------------------------------------------------------------------------------------
// vector + vector
template<>
bool addition_1( int* vout, const int* v1, const int* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] + v2[i];
	return true;
}
template<>
bool addition_1( float* vout, const float* v1, const float* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] + v2[i];
	return true;
}
template<>
bool addition_1( double* vout, const double* v1, const double* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] + v2[i];
	return true;
}

// operator - ------------------------------------------------------------------------------------
// vector - vector
template<>
bool subtraction_1( int* vout, const int* v1, const int* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] - v2[i];
	return true;
}
template<>
bool subtraction_1( float* vout, const float* v1, const float* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] - v2[i];
	return true;
}
template<>
bool subtraction_1( double* vout, const double* v1, const double* v2, const unsigned int sz1, const unsigned int sz2 ){
	if( sz1 != sz2 ) return false;
	for( unsigned int i=0; i<sz1; i++ ) vout[i] = v1[i] - v2[i];
	return true;
}

// operator * ------------------------------------------------------------------------------------
// scalar * vector
template<>
void multiplication_1( int* vout, const int s, const int* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = s*v[i];
}
template<>
void multiplication_1( float* vout, const float s, const float* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = s*v[i];
}
template<>
void multiplication_1( double* vout, const double s, const double* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = s*v[i];
}

// operator / ------------------------------------------------------------------------------------
// vector / scalar
template<>
void division_1( int* vout, const int s, const int* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = v[i]/s;
}
template<>
void division_1( float* vout, const float s, const float* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = v[i]/s;
}
template<>
void division_1( double* vout, const double s, const double* v, const unsigned int sz ){
	for( unsigned int i=0; i<sz; i++ ) vout[i] = v[i]/s;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for two-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator += ------------------------------------------------------------------------------------
// matrix += matrix
template<>
bool addition_assignment_2( int* ms, const int* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] += mo[i*strideo+j];
		}
	}
	return ret;
}
template<>
bool addition_assignment_2( float* ms, const float* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] += mo[i*strideo+j];
		}
	}
	return ret;
}
template<>
bool addition_assignment_2( double* ms, const double* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] += mo[i*strideo+j];
		}
	}
	return ret;
}

// operator += ------------------------------------------------------------------------------------
// matrix += scalar
template<>
void addition_assignment_2( int* m, const int s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] += s;
		}
	}
}
template<>
void addition_assignment_2( float* m, const float s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] += s;
		}
	}
}
template<>
void addition_assignment_2( double* m, const double s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] += s;
		}
	}
}

// operator -= ------------------------------------------------------------------------------------
// matrix -= matrix
template<>
bool subtraction_assignment_2( int* ms, const int* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] -= mo[i*strideo+j];
		}
	}
	return ret;
}
template<>
bool subtraction_assignment_2( float* ms, const float* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] -= mo[i*strideo+j];
		}
	}
	return ret;
}
template<>
bool subtraction_assignment_2( double* ms, const double* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides, const unsigned int nrowo, const unsigned int ncolo, const unsigned int strideo ){
	bool ret = true;
	if( nrows != nrowo || ncols != ncolo ) ret = false;
	unsigned int min_row = ( nrows > nrowo )? nrowo : nrows;
	unsigned int min_col = ( ncols > ncolo )? ncolo : ncols;
	for( unsigned int i=0; i<min_row; i++ ){
		for( unsigned int j=0; j<min_col; j++ ){
			ms[i*strides+j] -= mo[i*strideo+j];
		}
	}
	return ret;
}


// operator *= ------------------------------------------------------------------------------------
// matrix *= scalar
template<>
void multiplication_assignment_2( int* m, const int s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] *= s;
		}
	}
}
template<>
void multiplication_assignment_2( float* m, const float s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] *= s;
		}
	}
}
template<>
void multiplication_assignment_2( double* m, const double s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] *= s;
		}
	}
}

// operator /= ------------------------------------------------------------------------------------
// vector /= scalar
template<>
void division_assignment_2( int* m, const int s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] /= s;
		}
	}
}
template<>
void division_assignment_2( float* m, const float s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] /= s;
		}
	}
}
template<>
void division_assignment_2( double* m, const double s, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			m[i*stride+j] /= s;
		}
	}
}

// operator - -------------------------------------------------------------------------------------
// - matrix
template<>
void unary_minus_2( const int* ms, int* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides ){
	for( unsigned int i=0; i<nrows; i++ ){
		for( unsigned int j=0; j<ncols; j++ ){
			mo[i*strides+j] = -ms[i*strides+j];
		}
	}
}
template<>
void unary_minus_2( const float* ms, float* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides ){
	for( unsigned int i=0; i<nrows; i++ ){
		for( unsigned int j=0; j<ncols; j++ ){
			mo[i*strides+j] = -ms[i*strides+j];
		}
	}
}
template<>
void unary_minus_2( const double* ms, double* mo, const unsigned int nrows, const unsigned int ncols,
	const unsigned int strides ){
	for( unsigned int i=0; i<nrows; i++ ){
		for( unsigned int j=0; j<ncols; j++ ){
			mo[i*strides+j] = -ms[i*strides+j];
		}
	}
}


// operator + ------------------------------------------------------------------------------------
// matrix + matrix
template<>
bool addition_2( int* mout, const int* m1, const int* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] + m2[i*stride2+j];
		}
	}
	return true;
}
template<>
bool addition_2( float* mout, const float* m1, const float* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] + m2[i*stride2+j];
		}
	}
	return true;
}
template<>
bool addition_2( double* mout, const double* m1, const double* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] + m2[i*stride2+j];
		}
	}
	return true;
}

// operator - ------------------------------------------------------------------------------------
// matrix - matrix
template<>
bool subtraction_2( int* mout, const int* m1, const int* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] - m2[i*stride2+j];
		}
	}
	return true;
}
template<>
bool subtraction_2( float* mout, const float* m1, const float* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] - m2[i*stride2+j];
		}
	}
	return true;
}
template<>
bool subtraction_2( double* mout, const double* m1, const double* m2, const unsigned int nrow1, const unsigned int ncol1,
	const unsigned int stride1, const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	if( nrow1 != nrow2 || ncol1 != ncol2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol1; j++ ){
			mout[i*stride1+j] = m1[i*stride1+j] - m2[i*stride2+j];
		}
	}
	return true;
}

// operator * ------------------------------------------------------------------------------------
// scalar * matrix
template<>
void multiplication_2( int* mout, const int s, const int* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = s*m[i*stride+j];
		}
	}
}
template<>
void multiplication_2( float* mout, const float s, const float* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = s*m[i*stride+j];
		}
	}
}
template<>
void multiplication_2( double* mout, const double s, const double* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = s*m[i*stride+j];
		}
	}
}

//*
// operator / ------------------------------------------------------------------------------------
// matrix / scalar
template<>
void division_2( int* mout, const int s, const int* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = m[i*stride+j]/s;
		}
	}
}
template<>
void division_2( float* mout, const float s, const float* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = m[i*stride+j]/s;
		}
	}
}
template<>
void division_2( double* mout, const double s, const double* m, const unsigned int nrow, const unsigned int ncol, const unsigned int stride ){
	for( unsigned int i=0; i<nrow; i++ ){
		for( unsigned int j=0; j<ncol; j++ ){
			mout[i*stride+j] = m[i*stride+j]/s;
		}
	}
}
//*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for combination of one- and two-dimensional array
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// operator * ------------------------------------------------------------------------------------
// matrix * matrix
template<>
bool multiplication_22( int* mout, const int* m1, const int* m2, const unsigned int nrow1, const unsigned int ncol1, const unsigned int stride1,
	const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	bool ret = true;
	if( ncol1 != nrow2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol2; j++ ){
			mout[i*stride2+j] = 0;
			for( unsigned int k=0; k<ncol1; k++ ){
				mout[i*stride2+j] += m1[i*stride1+k]*m2[k*stride2+j];
			}
		}
	}
	return ret;
}
template<>
bool multiplication_22( float* mout, const float* m1, const float* m2, const unsigned int nrow1, const unsigned int ncol1, const unsigned int stride1,
	const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	bool ret = true;
	if( ncol1 != nrow2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol2; j++ ){
			mout[i*stride2+j] = 0.0;
			for( unsigned int k=0; k<ncol1; k++ ){
				mout[i*stride2+j] += m1[i*stride1+k]*m2[k*stride2+j];
			}
		}
	}
	return ret;
}
template<>
bool multiplication_22( double* mout, const double* m1, const double* m2, const unsigned int nrow1, const unsigned int ncol1, const unsigned int stride1,
	const unsigned int nrow2, const unsigned int ncol2, const unsigned int stride2 ){
	bool ret = true;
	if( ncol1 != nrow2 ) return false;
	for( unsigned int i=0; i<nrow1; i++ ){
		for( unsigned int j=0; j<ncol2; j++ ){
			mout[i*stride2+j] = 0.0;
			for( unsigned int k=0; k<ncol1; k++ ){
				mout[i*stride2+j] += m1[i*stride1+k]*m2[k*stride2+j];
			}
		}
	}
	return ret;
}

// operator * ------------------------------------------------------------------------------------
// vector * vector
template<>
void multiplication_11( int* mout, const int* v1, const int* v2, const unsigned int sz1, const unsigned int sz2 ){
	for( unsigned int i=0; i<sz1; i++ ){
		for( unsigned int j=0; j<sz2; j++ ){
			mout[i*sz2+j] = v1[i]*v2[j];
		}
	}
}
template<>
void multiplication_11( float* mout, const float* v1, const float* v2, const unsigned int sz1, const unsigned int sz2 ){
	for( unsigned int i=0; i<sz1; i++ ){
		for( unsigned int j=0; j<sz2; j++ ){
			mout[i*sz2+j] = v1[i]*v2[j];
		}
	}
}
template<>
void multiplication_11( double* mout, const double* v1, const double* v2, const unsigned int sz1, const unsigned int sz2 ){
	for( unsigned int i=0; i<sz1; i++ ){
		for( unsigned int j=0; j<sz2; j++ ){
			mout[i*sz2+j] = v1[i]*v2[j];
		}
	}
}

// operator * ------------------------------------------------------------------------------------
// vector * matrix
template<>
bool multiplication_12( int* vout, const int* v, const int* m, const unsigned int sz, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	if( sz != nrow ) return false;
	for( unsigned int i=0; i<ncol; i++ ){
		vout[i] = 0;
		for( unsigned int j=0; j<nrow; j++ ){
			vout[i] += v[j]*m[j*stride+i];
		}
	}
	return true;
}
template<>
bool multiplication_12( float* vout, const float* v, const float* m, const unsigned int sz, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	if( sz != nrow ) return false;
	for( unsigned int i=0; i<ncol; i++ ){
		vout[i] = 0.0;
		for( unsigned int j=0; j<nrow; j++ ){
			vout[i] += v[j]*m[j*stride+i];
		}
	}
	return true;
}
template<>
bool multiplication_12( double* vout, const double* v, const double* m, const unsigned int sz, const unsigned int nrow, const unsigned int ncol,
	const unsigned int stride ){
	if( sz != nrow ) return false;
	for( unsigned int i=0; i<ncol; i++ ){
		vout[i] = 0.0;
		for( unsigned int j=0; j<nrow; j++ ){
			vout[i] += v[j]*m[j*stride+i];
		}
	}
	return true;
}

// operator * ------------------------------------------------------------------------------------
// matrix * vector
template<>
bool multiplication_21( int* vout, const int* m, const int* v, const unsigned int nrow, const unsigned int ncol, const unsigned int stride,
	const unsigned int sz ){
	if( sz != ncol ) return false;
	for( unsigned int i=0; i<nrow; i++ ){
		vout[i] = 0;
		for( unsigned int j=0; j<ncol; j++ ){
			vout[i] += m[i*stride+j]*v[j];
		}
	}
	return true;
}
template<>
bool multiplication_21( float* vout, const float* m, const float* v, const unsigned int nrow, const unsigned int ncol, const unsigned int stride,
	const unsigned int sz ){
	if( sz != ncol ) return false;
	for( unsigned int i=0; i<nrow; i++ ){
		vout[i] = 0.0;
		for( unsigned int j=0; j<ncol; j++ ){
			vout[i] += m[i*stride+j]*v[j];
		}
	}
	return true;
}
template<>
bool multiplication_21( double* vout, const double* m, const double* v, const unsigned int nrow, const unsigned int ncol, const unsigned int stride,
	const unsigned int sz ){
	if( sz != ncol ) return false;
	for( unsigned int i=0; i<nrow; i++ ){
		double sum = 0.0;
		for( unsigned int j=0; j<ncol; j++ ){
			sum += m[i*stride+j]*v[j];
		}
		vout[i] = sum;
	}
	return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// common function templates & their specializations for sorting
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<typename T>
int select_pivot( const T* tagv, const int start, const int end ){
	int k = start+1;
	while( k<=end && tagv[start]==tagv[k] ) k++;
	if( k > end ) return -1;
	if( tagv[start]>=tagv[k] ) return start;
	else return k;
}

template<typename T>
int partition( T* tagv, const int start, const int end, const int pivotno, int* original_pos, const int shift ){
	T pivot = tagv[pivotno];
	int l=start, r=end;
	while( l<=r ){
		while( l<=end && tagv[l]<pivot ) l++;
		while( r>=start && tagv[r]>=pivot ) r--;
		if( l>r ) break;
		T tmp = tagv[l];
		tagv[l] = tagv[r];
		tagv[r] = tmp;
		if( original_pos ){
			int tempno = original_pos[l-shift];
			original_pos[l-shift] = original_pos[r-shift];
			original_pos[r-shift] = tempno;
		}
		l++; r--;
	}
	return l;
}

template<typename T>
void quicksort_recursive( T* tagv, const int start, const int end, int* original_pos, const int shift ){
	if( start == end ) return;
	int pivotno = select_pivot( tagv, start, end );
	if( pivotno != -1 ){
		int k = partition( tagv, start, end, pivotno, original_pos, shift );
		quicksort_recursive( tagv, start, k-1, original_pos, shift );
		quicksort_recursive( tagv,     k, end, original_pos, shift );
	}
}

template<typename T>
void quicksort( T* tagv, const int start, const int end, int* original_pos ){
	if( original_pos ){
		for( int i=0; i<=end-start; i++ ){
			original_pos[i] = i+start;
		}
	}
	quicksort_recursive( tagv, start, end, original_pos, start );
}

/**
 * @brief 値の検索を行い，その位置を返す
 * @details 特にソートされていないデータが対象
 * @param[in] tagv 検索を行うベクトルデータへのポインタ
 * @param[in] start 検索開始位置
 * @param[in] end 検索終了位置
 * @param[in] target 検索値
 * @return 見つかれば，その位置，見つからなければ-1
*/
template< typename T >
int sequential_search( const T* tagv, const int start, const int end, const T target ){
	int ret = -1;
	for( unsigned int k=start; k<=end; k++ ){
		if( tagv[k] == target ){
			ret = k;
			break;
		}
	}
	return ret;
}
/**
 * @brief 値の検索を行い，その位置を返す
 * @details ソートされているデータが対象
 * @param[in] tagv 検索を行うベクトルデータへのポインタ
 * @param[in] start 検索開始位置
 * @param[in] end 検索終了位置
 * @param[in] target 検索値
 * @return 見つかれば，その位置，見つからなければ-1
*/
template< typename T >
int binary_search( const T* tagv, const int start, const int end, const T target ){
	int l=start;
	int r=end;
	if( target < tagv[l] || target > tagv[r] ){
		return -1;
	}else{
		int m;
		while( l <= r ){
			m = (l+r)/2;
			if( tagv[m] == target ){
				return m;
			}else if( tagv[m] < target ){
				l = m+1;
			}else{
				r = m-1;
			}
		}
	}
	return -1;
}


}// end of namespace arr

#endif