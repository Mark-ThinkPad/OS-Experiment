#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SHMKEY 75

int shmid=0, i=0;
int *addr;

void client()
{
    int i = 0;
    shmid = shmget(SHMKEY, 1024, 0777);
    addr = shmat(shmid, 0, 0);
    for (i = 9; i >= 0; i--)
    {
        while (*addr != -1);
        printf("(client) sent\n");
        *addr = i;
    }
    exit(0);
}

void server() {
    shmid = shmget(SHMKEY, 1024, 0777 | IPC_CREAT);
    addr = shmat(shmid, 0, 0);
    do
    {
        *addr = -1;
        while (*addr == -1);
        printf("(server) received\n");
    } while (*addr);
    shmctl(shmid, IPC_RMID, 0);
    exit(0);
}

int main(int argc, char const *argv[])
{
    while ((i=fork()) == -1);
    if (!i) server();
    system("ipcs -m");
    while ((i=fork()) == -1);
    if (!i) client();
    wait(0);
    wait(0);

    return 0;
}
