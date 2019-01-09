cmake_minimum_required(VERSION 3.10)
project(ft_ssl C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ft_ssl
		main.c
        ft_ssl.h md5.c help_md5.c sha256.c help_sha256.c sha512.c)
