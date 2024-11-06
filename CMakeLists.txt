cmake_minimum_required(VERSION 3.29)
project(skillbox C)

set(CMAKE_C_STANDARD 99)

add_executable(skillbox       c55/c55.c
)
add_executable(skillbox64     c64/c64.c)
add_executable(skillbox74     c74/c74.c)
add_executable(skillbox86     c86/c86.c)
add_executable(skillbox95     c95/c95.c)
add_executable(
        skillbox104
        c104/c104.c
        c104/fibo.c
        c104/fibo.h
        c104/sapper.c
        c104/sapper.h
        lib/SafeInput/SafeInput.c
        lib/SafeInput/SafeInput.h
)
