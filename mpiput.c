#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
//include zht header file.
#include "c_zhtclient.h"
//getopt function header.
#include <unistd.h>
#include <string.h>

/*************************************
Date: 2013/10/24 Author: Tony_M
Function: Insert using MPI. 
1. Get operation from user.
2. MPI input data
3. Test time cost.
*************************************/
//const int req_size=64*1024;
//each process insert such amount of data. Each data is 64K.
//const int range=8*1024*1024;

const int req_size= 512;
const int range=10 * 512;

void printUsage(char* argv_0);
void mpizhtput(int rank){
	printf("Beginning.\n");
	//printf("myrank: %d.\n", rank);
	int offset=0;
	char* key=(char*)malloc(32);
	char* value=(char*)calloc(req_size,sizeof(char));
	while(offset<range){
		//key management. we use offset as key.
		memset(key,0,32);
		sprintf(key,"%d_%d",rank,offset);

		if(rank == 1){
			printf("key is: %s_",key);
		}

		//data management.
		if(offset%2==0){
			memset(value,'z',req_size-1);
		}else{
			memset(value,'x',req_size-1);
		}
		//insert data.
		int irc=c_zht_insert(key,value);
		if(irc == 0){
			printf("Insert success.Rank: %d, Return code: %d\n",irc,rank);
		}else{
			printf("Rank: %d cannot insert data. Return code:%d.\n",rank,irc);
		}
		//modify offset.
		offset+=req_size;
	}
	//recycle.
	free(value);
	free(key);
	
}
int main(int argc, char* argv[]){
	//getopt()shall return -1 when all command line options are parsed.
	char* zhtConf=NULL;
	char* neighborConf=NULL;
	int c;
	int printHelp = 0;
	/*
	while((c=getopt(argc,argv,"z:n:f:h"))!=-1){
		switch(c){
			case 'z':
				zhtConf=optarg;
				break;
			case 'n':
				neighborConf=optarg;
				break;
			case 'h':
				printHelp=1;
				break;
			default:
				fprintf(stderr, "Illegal argument \"%c\"\n",c);
				printUsage(argv[0]);
				exit(1);
		}
	}
	int helpPrinted=0;
	if(printHelp){
		printUsage(argv[0]);
		helpPrinted=1;
	}
	*/
	zhtConf="src/zht.conf";
	neighborConf="src/neighbor.mpi.conf";
	if(zhtConf != NULL && neighborConf != NULL){
		int myrank;
		MPI_Init(&argc,&argv);
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
		

/*
		if(argc < 2){
			MPI_Finalize();
			return;
		}
*/		
		c_zht_init(zhtConf,neighborConf);
		//test function.
		if(myrank==0){
			struct timeval beginTime, endTime;
			MPI_Barrier(MPI_COMM_WORLD);
			gettimeofday(&beginTime,NULL);
			//start I/O
			mpizhtput(myrank);
			//mpizhtget();
			MPI_Barrier(MPI_COMM_WORLD);
			gettimeofday(&endTime,NULL);
			printf("Put req_size: %d, time: %lu\n", req_size,(endTime.tv_sec-beginTime.tv_sec)*1000000+endTime.tv_usec-beginTime.tv_usec);
			c_zht_teardown();
		}else{
			MPI_Barrier(MPI_COMM_WORLD);
			mpizhtput(myrank);
			MPI_Barrier(MPI_COMM_WORLD);
		}
		MPI_Finalize();

	}
/*
	else{
		if(!helpPrinted){
			fprintf(stderr, "zhtConf or neighborConf is NULL\n");
			printUsage(argv[0]);

		}
	}
*/
	return 0;

}

void printUsage(char* argv_0){
	fprintf(stdout, "Usage:\n%s %s\n",argv_0, 
			"-z zht.conf -n neighbor.conf [-h]");
}
