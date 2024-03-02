cmake_minimum_required(VERSION 3.27)
project(TicTacToe_C_Graphics)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe_C_Graphics TicTacToe.cpp
        TicTacToe.h
        TicTacToeLogic.cpp
        TicTacToeGraphics.cpp
)

target_link_libraries(TicTacToe_C_Graphics PRIVATE -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 "C:/MinGW/lib/libbgi.a")
