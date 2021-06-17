#ifndef ARRAYS_COMMON_HPP
#define ARRAYS_COMMON_HPP

namespace arr{

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