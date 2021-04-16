#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wait.h>
#include <dirent.h>

char filename[100][100];
char * default_dir = "/home/jaglfr/modul2/petshop/";
void execute_order(char[], char[], char[], int, bool);

int main(){

  pid_t child1, child2;

  char * pets_dir = "/home/jaglfr/Documents/Source Codes/SisOp/Modul2/pets.zip";

  child1 = fork();
  int status1;
  if(child1 == 0) {
    child2 = fork();
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


  else {
     
    while ((wait(&status1)) > 0);
    
    // Variabel yang diperlukan
    DIR *dir_path;
    struct dirent *ent_path;
    dir_path = opendir(default_dir);
    // Menyimpan nama file
    int iter = 0;
    if(dir_path != NULL) {
      while((ent_path = readdir(dir_path)) != NULL) {
        if(strcmp(ent_path->d_name, ".") != 0 && strcmp(ent_path->d_name, "..") != 0) {
          strcpy(filename[iter], ent_path->d_name);
          iter++;
        }
      }
    }


    char type[60], name[60], age[60];
    for(int i = 0; i < iter; i++) {
      int semicol_count = 0, counter = 0; 
      char temp[50];
      bool isunderscore = false;

      for (int j = 0; j < strlen(filename[i]); j++) {
        if(filename[i][j] == ';') {
          temp[counter] = '\0';
          counter = 0; semicol_count++;
          switch(semicol_count) {
            case 1:
              strcpy(type, temp);
              // printf("type:%s ", type);
              break;
            case 2:
              strcpy(name, temp);
              // printf("name:%s ", name);
              break;
          }
          strcpy(temp, "");
        } else if (j == strlen(filename[i]) - 4 || filename[i][j] == '_') {
            bool isunderscore = false;
            if(filename[i][j] == '_') isunderscore = true;
            temp[counter] = '\0'; counter = 0;
            strcpy(age, temp);
            if(isunderscore) {
                execute_order(type, name, age, i, isunderscore);
                strcpy(temp, "");
                counter = 0; semicol_count = 0;
                continue;
            } else {
                execute_order(type, name, age, i, isunderscore);
                break;
            }
        } else {
            temp[counter] = filename[i][j];
            counter++;
        }
      }
    }
  }
  return 0;
}


void execute_order(char type[], char name[], char age[], int idx, bool isunderscore) {
  // Create a directory for each type
  pid_t pid1 = fork();
  int status1;
  char testdir[200];
  strcpy(testdir, default_dir);strcat(testdir, type);
  if(pid1==0) {
    char *argv[] = {"mkdir", "-p", testdir, NULL};
    execv("/bin/mkdir", argv);
    exit(0);
  } else {
      while ((wait(&status1)) > 0);

      char newname[100]="";
      strcpy(newname, default_dir);
      strcat(newname, type); strcat(newname, "/");
      
      char textname[100]=""; strcpy(textname, newname);
      strcat(textname, "keterangan.txt");
      FILE *fptr;
      fptr = fopen(textname, "a");
      fprintf(fptr, "nama : %s\numur : %s tahun\n\n", name, age);

      strcat(newname, name); strcat(newname, ".jpg");

      char oldname[100]="";
      strcpy(oldname, default_dir);
      strcat(oldname, filename[idx]);

      pid_t pid2 = fork();
      int status2;
      if(pid2 == 0) {
        if(isunderscore) {
          char *argv[] = {"cp", oldname, newname, NULL};
          execv("/bin/cp", argv);
          exit(0);
        } else {
          char *argv[] = {"mv", oldname, newname, NULL};
          execv("/bin/mv", argv);
          exit(0);
        }
      } else  {
          return;
      }
  }
}