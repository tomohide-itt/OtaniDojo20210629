cmake_minimum_required( VERSION 3.16 )
set( PRG_NAME "test_tensor2" )
project( ${PRG_NAME} LANGUAGES CXX )
#
#--------------- TEST ----------------------
#サブディレクトリの追加
add_subdirectory( ../../../arrays arrays )
#
#実行ファイルの作成
add_executable( ${PRG_NAME} ${PRG_NAME}.cpp )
#最適化・警告等のオプション
if( MSVC )
	target_compile_options( ${PRG_NAME} PUBLIC /wd4819 )
endif()
#C++11/14/17
target_compile_features( ${PRG_NAME} PUBLIC cxx_std_17 )
#ライブラリのリンク
target_link_libraries( ${PRG_NAME} PRIVATE arrays )
