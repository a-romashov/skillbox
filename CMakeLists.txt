cmake_minimum_required(VERSION 3.29)
project(skillbox C)

set(CMAKE_C_STANDARD 99)

add_executable(skillbox       c55/c55.c)
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
add_executable(
        skillbox116

        c116/c116.c
        c116/student.c
        c116/student.h
        c116/employee.c
        c116/employee.h
        c116/library.c
        c116/library.h
)
add_executable(
        skillbox125

        c125/c125.c
        lib/SafeInput/SafeInput.c
        lib/SafeInput/SafeInput.h
)
add_executable(
        skillbox134

        c134/c134.c
        c134/signal.c
        c134/signal.h
        lib/SafeInput/SafeInput.c
        lib/SafeInput/SafeInput.h
)
add_executable(
        skillbox144
        c144/c144.c

        c134/signal.c
        c134/signal.h
)
add_executable(
        skillbox154
        c154/c154.c
        c154/scissorsPaperStone.c
        c154/scissorsPaperStone.h
        lib/SafeInput/SafeInput.c
        lib/SafeInput/SafeInput.h
)
