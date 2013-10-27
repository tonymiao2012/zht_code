mpicc -g -o mpiput mpiput.c -Llib -lzht -Iinclude -lstdc++ -lprotobuf -lprotobuf-c
mpiexec -np 4 ./mpiput
