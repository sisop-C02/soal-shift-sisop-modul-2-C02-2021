#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <dirent.h>

int main(){

  // Soal A
  pid_t child1, child2;

  char * default_dir = "/home/jaglfr/modul2/petshop/";
  char * pets_dir = "/home/jaglfr/Documents/Source Codes/SisOp/Modul2/pets.zip";

  child1 = fork();
  int status1;
  if(child1 == 0) {
    child2 = fork();
    if (child2 < 0) exit(0);
    int status2;
    if(child2 == 0) {
        char *argv[] = {"mkdir", "-p", default_dir, NULL};
        execv("/bin/mkdir", argv);
    } else {
        while ((wait(&status2)) > 0);
        char *argv[] = {"unzip", pets_dir, "-d", default_dir, "-x", "*/*", NULL};
        execv("/usr/bin/unzip", argv);
    }
  }


  // Soal B
  else { 
    while ((wait(&status1)) > 0);
    
    DIR *dir_path;
    struct dirent *ent_path;
    dir_path = opendir(default_dir);

    char type[100][20];
    char name[100][20];
    char age[100][20];
    char filename[100][100];

    int iter = 0;
    if(dir_path != NULL) {
      while((ent_path = readdir(dir_path)) != NULL) {
        if(strcmp(ent_path->d_name, ".") != 0 && strcmp(ent_path->d_name, "..") != 0) {
          // printf("%s\n", ent_path->d_name);
          strcpy(filename[iter], ent_path->d_name);
          iter++;
        }
      }
    }

    int counter = 0;
    for(int i = 0; i < iter; i++) {
      int uniq = 1; 
      char *temp = strtok(filename[i], ";");
      for(int j = 0; j < iter; j++) {
        if (strcmp(temp, type[j]) != 0) {
          continue;
        } else {
          uniq = 0;
          break;
        }
      }
      if(uniq) { 
        strcpy(type[counter], temp);
        counter++;
      }
    }

    // for(int i = 0; i < counter; i++) {
    //   printf("%s\n", type[i]);
    // }

    pid_t pid[counter];
    for(int i = 0; i < counter; i++) {
      char testdir[200];
      strcpy(testdir, default_dir);
      strcat(testdir, type[i]);
      pid[i] = fork();
      if(pid[i] == 0) {
        char *argv[] = {"mkdir", "-p", testdir, NULL};
        execv("/bin/mkdir", argv);
        exit(0);
      }
    }

  }


  return 0;
}