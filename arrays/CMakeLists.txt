add_library( arrays STATIC
	arrays_common.h arrays_common.cpp
	tensor/tensor1.h tensor/tensor1.cpp
	tensor/tensor2.h tensor/tensor2.cpp
	tensor/sym_tensor2.h tensor/sym_tensor2.cpp
	tensor/sym_tensor4.h tensor/sym_tensor4.cpp
	array/array1.h array/array1.cpp
	array/array2.h
)
#
if( MSVC )
	target_compile_options( arrays PUBLIC /wd4819 )
endif()
#
target_compile_features( arrays PUBLIC cxx_std_17 )
#
target_include_directories( arrays INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )