# Project: [Volume of water contained in Chess Board]

Brief: The program calculates the volume of water held by a given MxN board.
where M is number of rows
      N is number of columns

Source file: calcVolume.cpp

Following assumptions are considered for the program:
1) The program considers, side of each square to be 1
2) The program doesn't consider negative heights

Compiling instructions:
-----------------------
1) mkdir build
2) cd build/
3) cmake ../
4) make

raju@dev:chessBoard$ mkdir build

raju@dev:build$ cmake ../
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/balaram/projects/bitbucket/raju/test/chessBoard/build

raju@dev:build$ make
Scanning dependencies of target calcVolume
[ 50%] Building CXX object CMakeFiles/calcVolume.dir/calcVolume.cpp.o
[100%] Linking CXX executable calcVolume
[100%] Built target calcVolume

raju@dev:build$ ls
calcVolume  CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile

Testing:
----------
$ ./calcVolume 8 8 board_8x8.txt
i.e., 
argument1: number of rows
argument2: number of columns
argument3: input file name with contents as row-major array of board

- Provided are three files with board dimenstions 3x3, 3x4 and 8x8 as board_3x3.txt, board_3x4.txt and board_8x8.txt

Example:
$ cat board_8x8.txt
3, 3, 1, 3, 3, 3, 1, 3,
3, 3, 1, 3, 3, 3, 1, 3,
3, 3, 2, 0, 2, 0, 1, 3,
3, 3, 0, 3, 3, 0, 1, 3,
3, 3, 0, 3, 3, 0, 1, 3,
3, 3, 0, 3, 3, 0, 1, 3,
3, 1, 0, 2, 0, 0, 3, 3,
1, 3, 1, 1, 1, 3, 1, 1,

raju@dev:build$ ./calcVolume 8 8 ../board_8x8.txt
Total Volume of Board = 12
