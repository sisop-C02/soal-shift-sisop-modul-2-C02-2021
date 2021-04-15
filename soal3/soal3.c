#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void main(int argc, char * argv[]) {
  pid_t pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  pid_t sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

	char * root_dir =
		"/home/maroqi/Projects/OSProject/Modul_2/soal-shift-sisop-modul-2-C02-2021/soal3";

  if (argc > 1) {
    if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
      chdir(root_dir);
      
      char * sh_name = "Killer.sh";
      FILE * sh_killer;
      sh_killer = fopen(sh_name, "w");

      if (sh_killer == NULL) {
        exit(EXIT_FAILURE);
      }

      char header[25] = "#!/bin/bash";
      char command_remove[75] = "rm -f Killer.sh";
      char command_kill[100];
      if (strcmp(argv[1], "-z") == 0) {
        strcpy(command_kill, "ps -C soal3 -o pid= | xargs -r kill -9");
      } else if (strcmp(argv[1], "-x") == 0) {
        strcpy(command_kill, "ps -C soal3 -o pid= -o stat= | awk '/Ss/ {print $1}' | xargs -r kill -9");
      }

      fputs(header, sh_killer);
      fputs("\n\n", sh_killer);
      fputs(command_kill, sh_killer);
      fputs("\n\n", sh_killer);
      fputs(command_remove, sh_killer);
      fclose(sh_killer);

      char command_sh[35];
      sprintf(command_sh, "chmod u+x %s && ./%s", sh_name, sh_name);
      FILE * run_sh = popen(command_sh, "w");
      pclose(run_sh);
    }
  } else {
    while (true) {
      if (fork() == 0) {
        chdir(root_dir);

        char dir_name[100];
        time_t t_o = time(NULL);
        struct tm tm_s = *localtime(&t_o);
        sprintf(dir_name, "%d-%02d-%02d_%02d:%02d:%02d", 
          tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
          tm_s.tm_min, tm_s.tm_sec);

        pid_t child_mkdir= fork();
        int status_mkdir;

        if (child_mkdir == 0) {
          char *argv[] = {"mkdir", "-p", dir_name, NULL};
          execv("/bin/mkdir", argv);
        } else {
          while ((wait(&status_mkdir)) > 0);
          
          char target_dir[255];
          sprintf(target_dir, "%s/%s", root_dir, dir_name);
          struct stat st_mark = {0};
          if (stat(target_dir, &st_mark) != -1) {
            chdir(target_dir);

            int counter = 1;
            while (counter <= 10) {
              char * link = "https://picsum.photos";
              int seconds = time(NULL);
              char download_link[255];
              sprintf(download_link, "%s/%d", link, (seconds % 1000) + 5);

              char file_name[65];
              time_t t_o = time(NULL);
              struct tm tm_s = *localtime(&t_o);
              sprintf(file_name, "%d-%02d-%02d_%02d:%02d:%02d.jpg", 
                tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
                tm_s.tm_min, tm_s.tm_sec);
              
              if (fork() == 0) {
                char *argv[] = {"wget", "-qO", file_name, download_link, NULL};
                execv("/bin/wget", argv);
              }

              counter++;
              sleep(5);
            }

            FILE *scs_file;
            scs_file = fopen("status.txt", "w");

            if (scs_file == NULL) {
              exit(EXIT_FAILURE);
            }

            char string[25] = "Download Success";
            for(int i = 0; string[i] != '\0'; ++i) {
              char ch = string[i];
              if (ch >= 'a' && ch <= 'z') {
                ch = ch + 5;
                if(ch > 'z'){
                  ch = ch - 'z' + 'a' - 1;
                }
                fputc(ch, scs_file);
              } else if (ch >= 'A' && ch <= 'Z') {
                ch = ch + 5;
                if(ch > 'Z'){
                  ch = ch - 'Z' + 'A' - 1;
                }
                fputc(ch, scs_file);
              } else {
                fputc(ch, scs_file);
              }
            }

            chdir(root_dir);
            pid_t child_zip = fork();
            int status_zip;

            if (child_zip == 0) {
              char archive_name[25];
              strcpy(archive_name, dir_name);
              strcat(archive_name, ".zip");

              char *argv[] = {"zip", "-r", archive_name, dir_name, NULL};
              execv("/bin/zip", argv);
            } else {
              while ((wait(&status_zip)) > 0);

              char *argv[] = {"rm", "-rf", dir_name, NULL};
              execv("/bin/rm", argv);
            }
          } else {
            exit(EXIT_FAILURE);
          }
        }
        exit(EXIT_SUCCESS);
      }
      sleep(40);
    }
  }
  exit(EXIT_SUCCESS);
}