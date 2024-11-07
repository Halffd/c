nasm -f win64 hello.s -o ../bin/hello.o
gcc ..\bin\hello.o -o ../bin/hello -lkernel32 -nostdlib
..\bin\hello.exe