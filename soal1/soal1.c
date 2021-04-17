#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void download(char link[], char output[]);
void childProcess(int i);
void childProcessOne();
void childProcessTwo();
void childProcessThree();
void execvCustom(char path[], char *argv[]);
void removeFolder(char folderName[]);

void download(char link[], char output[]) {
    char *argv[] = {"wget", "--no-check-certificate", link, "-O", output, "-q", NULL};
    execvCustom("/usr/bin/wget", argv);
}

/**
 * Run exec without terminating program synchronously
 * 
 **/
void execvCustom(char path[], char *argv[]) {
    pid_t child_id;
    int status;


    child_id = fork();

    if (child_id < 0) {
        while(child_id < 0)
            child_id = fork();
        exit(EXIT_FAILURE);
    }
    
    if (child_id == 0) {
        // this is child
        execv(path, argv);
        exit(0);
    } else {
        // this is parent
        while ((wait(&status)) > 0);
    }
}

void childProcess(int i) {
    if(i == 0) childProcessOne();
    if(i == 1) childProcessTwo();
    if(i == 2) childProcessThree();
}
void unzip(char filename[]) {
    char *argv[] = {"unzip", "-q", filename, NULL};
    execvCustom("/usr/bin/unzip", argv);
}

void renameFolder(char from[], char to[]) {
    char *argv[] = {"mv", from, to, NULL};
    execvCustom("/usr/bin/mv", argv);
}

void moveAllFolder() {
    renameFolder("FILM", "Fylm");
    renameFolder("FOTO", "Pyoto");
    renameFolder("MUSIK", "Myusik");
}

void removeZip(char filename[]) {
    char *argv[] = {"rm", filename, NULL};
    execvCustom("/usr/bin/rm", argv);
}

void removeAllFolder() {
    removeFolder("Fylm/");
    removeFolder("Myusik/");
    removeFolder("Pyoto/");
}

void removeFolder(char folderName[]) {
    char *argv[] = {"rm", "-rf", folderName, NULL};
    execvCustom("/usr/bin/rm", argv);
}

void removeAllZip() {
    removeZip("Foto.zip");
    removeZip("Film.zip");
    removeZip("Music.zip");
}

void zipAllFolder() {
    char *argv[] = {"zip", "-rq", "Lopyu_Stevany.zip", "Fylm/", "Pyoto/", "Myusik/", NULL};
    execvCustom("/usr/bin/zip", argv);
}

void childProcessOne() {
    download("https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "Film.zip");
    unzip("Film.zip");
}

void childProcessTwo() {
    download("https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "Music.zip");   
    unzip("Music.zip");
}

void childProcessThree() {
    download("https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "Foto.zip");
    unzip("Foto.zip");
}

int main() {
    // pid_t pid, sid;        // Variabel untuk menyimpan PID

    // pid = fork();     // Menyimpan PID dari Child Process

    // /* Keluar saat fork gagal
    // * (nilai variabel pid < 0) */
    // if (pid < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // /* Keluar saat fork berhasil
    // * (nilai variabel pid adalah PID dari child process) */
    // if (pid > 0) {
    //     exit(EXIT_SUCCESS);
    // }

    // umask(0);

    // sid = setsid();
    // if (sid < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // if ((chdir("/")) < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);

    while (1) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        if(tm.tm_mon + 1 == 4 && tm.tm_mday == 9 && tm.tm_hour == 16 && tm.tm_min == 21 && tm.tm_sec == 59) {
            printf("Ulang taun\n");
            for(int i=0;i<3;i++) // loop will run n times (n=5)
            {
                if(fork() == 0)
                {
                    childProcess(i);
                    exit(0);
                }
            }

            printf("This is parent\n");

            for(int i=0;i<3;i++) // loop will run n times (n=5)
            wait(NULL);

            printf("Parent is done waiting\n");
            removeZip("Foto.zip");
            removeZip("Film.zip");
            removeZip("Music.zip");
            moveAllFolder();
            zipAllFolder();
            removeAllFolder();
            printf("Parent finished\n");
        }

        sleep(1);
    }
    
    exit(0);
}