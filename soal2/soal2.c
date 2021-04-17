#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <sys/types.h>


// Global variables
char filename[100][100];
char * default_dir = "/home/jaglfr/modul2/petshop/";
// Function definition
void execute_order(char[], char[], char[], int, bool);


// Main function
int main()
{
    // 2 children for mkdir and unzip
    pid_t child1, child2;
    // variable to store the zip directory
    char *pets_dir = "/home/jaglfr/Documents/Source Codes/SisOp/Modul2/pets.zip";

    // Start mkdir and unzip processes
    child1 = fork(); int status1;
    if(child1 == 0) 
    {
        child2 = fork(); int status2;
        if(child2 == 0) {
            char *argv[] = {"mkdir", "-p", default_dir, NULL};
            execv("/bin/mkdir", argv);
        } else {
            while ((wait(&status2)) > 0);
            char *argv[] = {"unzip", pets_dir, "-d", default_dir, "-x", "*/*", NULL};
            execv("/usr/bin/unzip", argv);
        }
    }

    else 
    {
        // Wait before proceed
        while ((wait(&status1)) > 0);
        // Variables required for traversing files
        DIR *dir_path;
        struct dirent *ent_path;
        dir_path = opendir(default_dir);
        // Store the filenames
        int iter = 0;
        if(dir_path != NULL) {
            while((ent_path = readdir(dir_path)) != NULL) {
                if(strcmp(ent_path->d_name, ".") != 0 && strcmp(ent_path->d_name, "..") != 0) {
                    strcpy(filename[iter], ent_path->d_name);
                    iter++;
                }
            }
        }

        // Temporary variables to store animal type, name, and age
        char type[60], name[60], age[60];
        // Loop through each file
        for(int i = 0; i < iter; i++) {
            // Required variables
            int semicol_count = 0, counter = 0;
            char temp[50]; bool isunderscore = false;
            
            // Loop through each file name
            for(int j = 0; j < strlen(filename[i]); j++) {
                // Parsing type and name
                if(filename[i][j] == ';') {
                    temp[counter] = '\0';
                    counter = 0; semicol_count++;
                    switch(semicol_count) {
                        case 1:
                            strcpy(type, temp);
                            break;
                        case 2:
                            strcpy(name, temp);
                            break;
                    }
                    strcpy(temp, "");
                }
                // Parse age and decide if there's another pet.
                else if (j == strlen(filename[i]) - 4 || filename[i][j] == '_') {
                    bool isunderscore = false;
                    if(filename[i][j] == '_') isunderscore = true;
                    temp[counter] = '\0'; counter = 0;
                    strcpy(age, temp);
                    // Execute order
                    execute_order(type, name, age, i, isunderscore);
                    if(isunderscore) {
                        strcpy(temp, "");
                        counter = 0; semicol_count = 0;
                        continue;
                    } else {
                        break;
                    }
                }
                // Normal characters
                else {
                    temp[counter] = filename[i][j];
                    counter++;
                }
            }
        }
    }

    return 0;
}

void execute_order(char type[], char name[], char age[], int idx, bool isunderscore) {
    // First child to mkdir
    pid_t pid1 = fork(); int status1;
    // Create folders for each animal type
    char testdir[200];
    strcpy(testdir, default_dir);strcat(testdir, type);
    if(pid1==0) {
        char *argv[] = {"mkdir", "-p", testdir, NULL};
        execv("/bin/mkdir", argv);
        exit(0);
    }
    else {
        // Wait until mkdir is finished
        while ((wait(&status1)) > 0);
        // New file folder
        char newname[100]="";
        strcpy(newname, default_dir);
        strcat(newname, type); strcat(newname, "/");
        // File name for keterangan.txt
        char textname[100]=""; strcpy(textname, newname);
        strcat(textname, "keterangan.txt");
        FILE *fptr;
        fptr = fopen(textname, "a");
        fprintf(fptr, "nama : %s\numur : %s tahun\n\n", name, age);
        // Rename
        strcat(newname, name); strcat(newname, ".jpg");
        // Old filename
        char oldname[100]="";
        strcpy(oldname, default_dir);
        strcat(oldname, filename[idx]);
        // Decide to move or copy files
        pid_t pid2 = fork(); int status2;
        if(pid2 == 0) {
            if(isunderscore) {
                char *argv[] = {"cp", oldname, newname, NULL};
                execv("/bin/cp", argv);
                exit(0);
            } 
            else {
                char *argv[] = {"mv", oldname, newname, NULL};
                execv("/bin/mv", argv);
                exit(0);
            }
        } else {
            return;
        }
    }
}