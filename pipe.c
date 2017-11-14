#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
 
int main( int argc, char* argv[] ) {
    int fd[2];
    pid_t pid;
 
    char readBuff[50];
    char writeBuff[50];
    int readCounter;
 
    pipe(fd);
 
    int fileOpen = open( argv[1], 0 );
    int targetFile = open( argv[2], 0666 );
     
    if (fileOpen ==-1 || targetFile ==-1) {
        printf( "Opening file failed " );
        exit(1);
    }
    pid=fork();
 
    if(pid==0) {
        // inside the child prcocess
        close( fd[1] );
 
        read(fd[0], readBuff, sizeof(readBuff));
        printf("The recived message is : %s",readBuff);
 
        //Writing to the target fileOpen
        write(targetFile,readBuff,strlen(readBuff)+1);
    } else {
        // inside the parent process
        close( fd[0] );
        // code to read from a text file
 
        while((readCounter=read(fileOpen,readBuff,sizeof(readBuff))>0))  {
        write(fd[1],readBuff,sizeof( readBuff ) );
        }
        close(fd[1]);
    }
}
