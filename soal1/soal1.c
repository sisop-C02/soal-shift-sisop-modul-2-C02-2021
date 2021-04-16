#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void download(char link[], char output[]);
void childProcess(int i);
void childProcessOne();
void childProcessTwo();
void childProcessThree();

void download(char link[], char output[]) {
    char *argv[] = {"wget", "--no-check-certificate", link, "-O", output, "-q", NULL};
    execv("/usr/bin/wget", argv);
}

void childProcess(int i) {
    if(i == 0) childProcessOne();
    if(i == 1) childProcessTwo();
    if(i == 2) childProcessThree();
}
void unzip(char filename[]) {
    char *argv[] = {"unzip", filename, NULL};
    execv("/usr/bin/unzip", argv);
}

void renameFolder(char from[], char to[]) {
    char *argv[] = {from, to, NULL};
    execv("/usr/bin/mv", argv);
}

void moveAllFolder() {
    renameFolder("FILM", "Fylm");
    renameFolder("FOTO", "Pyoto");
    renameFolder("MUSIK", "Myusik");
}

void childProcessOne() {
    printf("Downloading films\n");
    download("https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "Film.zip");
}

void childProcessTwo() {
    printf("Downloading music\n");
    download("https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "Music.zip");   
}

void childProcessThree() {
    printf("Downloading photo\n");
    download("https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "Foto.zip");
}

int main() {
    pid_t pids[3];
    int i;
    int n = 3;

    for(int i = 0; i < 3; i++) {
        pids[i] = fork();
    
        if(pids[i] == 0) {
            printf("Child process => PPID=%d, PID=%d\n", getppid(), getpid());
            childProcess(i);
            exit(0);
        }
    }

    printf("Parent process => PID=%d\n", getpid());
    printf("Waiting for child processes to finish...\n");
    wait(NULL);
    printf("child process finished.\n");
    unzip("*.zip");
    moveAllFolder();
}