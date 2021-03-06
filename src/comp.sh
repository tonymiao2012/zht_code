echo "compiling zht-mpibroker"
mpicxx mpi_broker.cpp proxy_stub.cpp mq_proxy_stub.cpp ipc_plus.cpp mpi_proxy_stub.cpp ConfHandler.cpp ConfEntry.cpp StrTokenizer.cpp Util.cpp HTWorker.cpp Const.cpp novoht.cpp meta.pb.cc zpack.pb.cc -DMPI_INET -lprotobuf -lpthread -o zht-mpibroker
echo "generating zht-mpibroker"

echo "compiling zht-mpiserver"
mpicxx ZHTServer.cpp mpi_server.cpp ProxyStubFactory.cpp proxy_stub.cpp mpi_proxy_stub.cpp Util.cpp mq_proxy_stub.cpp ipc_plus.cpp ConfHandler.cpp ConfEntry.cpp StrTokenizer.cpp HTWorker.cpp Const.cpp novoht.cpp meta.pb.cc zpack.pb.cc -DMPI_INET -lprotobuf -lpthread -o zht-mpiserver
echo "generating zht-mpibroker"

