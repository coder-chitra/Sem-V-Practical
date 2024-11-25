#include<unistd.h>
#include<pthread.h>
#include <stdio.h>

void *allThreadFun(void *varmt){
    sleep(3);
    printf("*Printing from thread.\n\n");
    return NULL;
}

int main(){
    pthread_t thread_id;
    printf("Within main .....Before thread.\n\n");
    pthread_create(&thread_id,NULL,allThreadFun,NULL);
    pthread_join(thread_id,NULL);
    printf("Within main .....After thread.\n\n");
}
