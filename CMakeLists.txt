cmake_minimum_required(VERSION 3.12)
project(ft_ls C)

set(CMAKE_C_STANDARD 99)
AUX_SOURCE_DIRECTORY(libft LIBA)
add_executable(ft_ls ${LIBA} main.c ft_ls.h print_fns.c create.c parce_argc.c sort.c aux_ls_fns.c print_xattr.c)
link_libraries(libft/libft.a)