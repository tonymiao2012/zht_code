mpicxx spock2.cpp ipc_plus.cpp -o spock2
echo "spock2 compiled"

mpicxx mpi_server.cpp -o mpi_server
echo "mpi_servercompiled"

#./spock2

mpiexec -np 4 ./mpi_server : ./spock2

