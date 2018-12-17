cmake_minimum_required(VERSION 3.10)
project(ft_ssl C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ft_ssl
		main.c
		ss_ssl.h md5.c)
