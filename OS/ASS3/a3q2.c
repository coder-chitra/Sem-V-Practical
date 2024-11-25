#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void *allThreadFun(void *varmt) {
	long *fid =(long *)varmt;
	printf("Executing thread......Thread ID :%ld,\n",*fid);
}

int main() {
    int i;
	pthread_t thread_id;
    for(i=0;i<3;i++){
	    pthread_create(&thread_id,NULL,allThreadFun,(void *)&thread_id);
	    printf("Created new thread :%d...,Thread ID=(%lu)...\n",i,thread_id);
	   sleep(2);
    }
    pthread_exit(NULL);
    return 0;
}
