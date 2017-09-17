cmake_minimum_required(VERSION 3.7)
project(Corewar)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c corewar.h)
set(ASM_FILES asm/main.c asm/asm.h asm/parser.c asm/reader.c)

add_executable(Corewar ${SOURCE_FILES})
add_executable(Asm ${ASM_FILES})
target_link_libraries(Corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)
target_link_libraries(Asm ${CMAKE_SOURCE_DIR}/libft/libft.a)
