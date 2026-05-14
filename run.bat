@echo off
del a.exe
gcc main.c -lfreeglut -lopengl32 -lglu32 -O3
a
@echo on