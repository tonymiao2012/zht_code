#include <stdlib.h>
#include <stdio.h>
//zht header file
#include "c_zhtclient.h"
#include <mpi.h>
#include <string.h>

/*************************************
Author: Tony_m	Date:Oct 26th,2013.
Description:
Get data from ZHT server. By using MPI
After finishing them, check the time 
usage. 
1. Key management.
2. Result space management.
3. Show time.
*************************************/
//const int req_size = 64*1024;
//const int range=32*1024*1024;
const int req_size=32;
const int range=10*32;
void mpizhtget(int rank){
	printf("Beginning.\n");
	//initialization.
	int offset=0;
	char* key=(char*)malloc(32);
	char* result=(char*)calloc(req_size,sizeof(char));
	while(offset<range){
		//key management.
		memset(key,0,32);
		sprintf(key,"%d_%d",rank,offset);
		int lrc=c_zht_lookup(key,result);
		if(lrc==0){
			printf("Lookup success.Rank: %d, Return code: %d\n",rank,lrc);

		}else{
			printf("Rank: %d cannot lookup data. Return code:%d.\n",rank,lrc);
		}
		//write result to file if possible.
		offset+=req_size;
	}
	free(key);
	free(result);

}

int main(int argc, char* argv[]){
	char* zhtConf=NULL;
	char* neighborConf=NULL;
	//int c;
	zhtConf="src/zht.conf";
	neighborConf="src/neighbor.mpi.conf";
	if(zhtConf != NULL && neighborConf != NULL){
		int myrank;
		MPI_Init(&argc,&argv);
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
		c_zht_init(zhtConf,neighborConf);
		if(myrank==0){
			struct timeval beginTime, endTime;
			MPI_Barrier(MPI_COMM_WORLD);
			gettimeofday(&beginTime,NULL);

			mpizhtget(myrank);

			MPI_Barrier(MPI_COMM_WORLD);
			gettimeofday(&endTime,NULL);
			printf("Get req_size: %d, time: %lu\n",req_size,(endTime.tv_sec-beginTime.tv_sec)*1000000+endTime.tv_usec-beginTime.tv_usec);
			c_zht_teardown();
			
		}else{
			MPI_Barrier(MPI_COMM_WORLD);
			mpizhtget(myrank);
			MPI_Barrier(MPI_COMM_WORLD);
		}
		MPI_Finalize();
	}

	return 0;
}


