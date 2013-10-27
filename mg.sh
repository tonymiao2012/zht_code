mpicc -g -o mpiget mpiget.c -Llib -lzht -Iinclude -lstdc++ -lprotobuf -lprotobuf-c
mpiexec -np 4 ./mpiget
