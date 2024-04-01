#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(int argc, char *argv[]){
    int fpid, cpid, status, p1[2], p2[2];
    char *readbuf = malloc(5); //Buffer to read from pipe
    
    pipe(p1);
    pipe(p2);

    fpid = getpid();
    if((cpid = fork()) < 0){//fork error
        fprintf(2, "fork error\n");
        exit(1);
    }

    if(cpid == 0 ){//Child process
        close(0);
        close(p1[1]);
        close(p2[0]);

        write(p2[1], "pong", 4);

        close(p2[1]);

        read(p1[0], readbuf, 4);
        close(p1[0]);
        printf("%d: received %s\n", cpid, readbuf);
        //printf("4: received %s\n", cpid, readbuf);
    }else{ //parent process
        close(0);
        close(p1[0]);
        close(p2[1]);
        write(p1[1], "ping", 4);
        close(p1[1]);

        wait(&status);//guarantee execute after the child process end
        read(p2[0], readbuf, 4);
        close(p2[0]);
        printf("%d: received %s\n", fpid, readbuf);
    }

    free(readbuf);
    exit(0);


}