@echo off
gcc -save-temps -S main.c -I ../lib/lua/include -I ../lib
rem  -L ../lib/lua -lluajit-5.1