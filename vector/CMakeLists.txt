#CMakeLists.txt "test for vector"
cmake_minimum_required( VERSION 3.16 )
#
option(TVEC "test vector" [OFF] )
option(TMAT "test matrix" [OFF] )
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
if( TVEC )
	message( STATUS "--- TEST VECTOR = ON -------" )
	#
	set( PRG_NAME "test_vector" )
	project( ${PRG_NAME} )
	#
	message( STATUS "--- GPU  = OFF -----" )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
#
if( TMAT )
	message( STATUS "--- TEST MATRIX = ON -------" )
	#
	set( PRG_NAME "test_matrix" )
	project( ${PRG_NAME} )
	#
	message( STATUS "--- GPU  = OFF -----" )
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()

