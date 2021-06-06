#CMakeLists.txt "test for array"
cmake_minimum_required( VERSION 3.16 )
#
option(TARR1 "test array1" [OFF] )
option(TARR2 "test array2" [OFF] )
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
if( TARR1 )
	message( STATUS "--- TEST ARRAY1 = ON -------" )
	#
	set( PRG_NAME "test_array1" )
	project( ${PRG_NAME} )
	#
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
#
elseif( TARR2 )
	message( STATUS "--- TEST2 = ON -------" )
	#
	set( PRG_NAME "test_array2" )
	project( ${PRG_NAME} )
	#
	if( MSVC )
		add_compile_options(/wd4819)
	endif()
	#
	add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
endif()
