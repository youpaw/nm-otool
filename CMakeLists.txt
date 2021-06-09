cmake_minimum_required(VERSION 3.17)
project(ft_nm_otool C)

set(CMAKE_C_STANDARD 99)

set(NM_DIR "nm")
include_directories(${NM_DIR})
add_subdirectory(${NM_DIR})

set(OTOOL_DIR "otool")
include_directories(${OTOOL_DIR})
add_subdirectory(${OTOOL_DIR})

set(LIBSHARE_DIR "share")
include_directories(${LIBSHARE_DIR})
add_subdirectory(${LIBSHARE_DIR})

set(LIBFT_PRINTF_DIR "printf")
include_directories(${LIBFT_PRINTF_DIR})
add_subdirectory(${LIBFT_PRINTF_DIR})

add_custom_target(${PROJECT_NAME} DEPENDS ft_printf share nm otool)
