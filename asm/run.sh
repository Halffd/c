mkdir -p ../bin
as -o ../bin/hello-linux.o hello-linux.s
ld -o ../bin/hello-linux ../bin/hello-linux.o
../bin/hello-linux
echo $?