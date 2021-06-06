#CMakeLists.txt "test for tensor"
cmake_minimum_required( VERSION 3.16 )
#
option(T1  "test tensor1" [OFF] )
option(ST2 "test sym_tensor2" [OFF] )
option(ST4 "test sym_tensor4" [OFF] )
option(T2  "test tensor2" [OFF] )
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
if( T1 )
	message( STATUS "--- TEST TENSOR1 = ON -------" )
	#
	set( PRG_NAME "test_tensor1" )
	#
	message( STATUS "--- GPU  = OFF -----" )
	project( ${PRG_NAME} )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
#
if( ST2 )
	message( STATUS "--- TEST SYM_TENSOR2 = ON -------" )
	#
	set( PRG_NAME "test_sym_tensor2" )
	#
	message( STATUS "--- GPU  = OFF -----" )
	project( ${PRG_NAME} )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
#
if( ST4 )
	message( STATUS "--- TEST SYM_TENSOR4 = ON -------" )
	#
	set( PRG_NAME "test_sym_tensor4" )
	#
	message( STATUS "--- GPU  = OFF -----" )
	project( ${PRG_NAME} )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
#
if( T2 )
	message( STATUS "--- TEST TENSOR2 = ON -------" )
	#
	set( PRG_NAME "test_tensor2" )
	#
	message( STATUS "--- GPU  = OFF -----" )
	project( ${PRG_NAME} )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
