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
  // create a child process
  pid_t pid = fork();

  // check the process creation status
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  // change the permissions
  umask(0);

  // set sid
  pid_t sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  // change the root dir
	char * root_dir =
		"/home/maroqi/Projects/OSProject/Modul_2/soal-shift-sisop-modul-2-C02-2021/soal3";
  if ((chdir(root_dir)) < 0) {
    exit(EXIT_FAILURE);
  }

  // change the io permission
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // check the arguments
  if (argc > 1) {
    if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
      // declare the bash file
      char * sh_name = "Killer.sh";
      FILE * sh_killer;
      sh_killer = fopen(sh_name, "w");
      
      // check the opening file status
      if (sh_killer == NULL) {
        exit(EXIT_FAILURE);
      }

      // declare the commands
      char header[25] = "#!/bin/bash";
      char command_remove[75] = "rm -f Killer.sh";
      char command_kill[100];
      // get the executable file
      char * exec_arg = &argv[0][2];
      if (strcmp(argv[1], "-z") == 0) {
        sprintf(command_kill, "ps -C %s -o pid= | xargs -r kill -9", exec_arg);
      } else if (strcmp(argv[1], "-x") == 0) {
        sprintf(command_kill, "ps -C %s -o pid= -o stat= | awk '/Ss/ {print $1}' | xargs -r kill -9", exec_arg);
      }

      // put the command into the file
      fputs(header, sh_killer);
      fputs("\n\n", sh_killer);
      fputs(command_kill, sh_killer);
      fputs("\n\n", sh_killer);
      fputs(command_remove, sh_killer);
      fclose(sh_killer);

      // execute the file
      char command_sh[35];
      sprintf(command_sh, "chmod u+x %s && ./%s", sh_name, sh_name);
      FILE * run_sh = popen(command_sh, "w");
      pclose(run_sh);
    }
  } else {
    // iterate infinitely
    while (true) {
      // create a child process
      if (fork() == 0) {
        // declare the dir name
        char dir_name[100];
        time_t t_o = time(NULL);
        struct tm tm_s = *localtime(&t_o);
        sprintf(dir_name, "%d-%02d-%02d_%02d:%02d:%02d", 
          tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
          tm_s.tm_min, tm_s.tm_sec);

        // create a child process
        pid_t child_mkdir = fork();
        int status_mkdir;

        // execute mkdir and create a dir
        if (child_mkdir == 0) {
          char *argv[] = {"mkdir", "-p", dir_name, NULL};
          execv("/bin/mkdir", argv);
        } else {
          // wait the child process until terminated
          while ((wait(&status_mkdir)) > 0);
          
          // move to the created dir and run the next process
          char target_dir[255];
          sprintf(target_dir, "%s/%s", root_dir, dir_name);
          struct stat st_mark = {0};
          if (stat(target_dir, &st_mark) != -1) {
            chdir(target_dir);

            // iterate until 10 times
            int counter = 1;
            while (counter <= 10) {
              // declare the download link
              char * link = "https://picsum.photos";
              int seconds = time(NULL);
              char download_link[255];
              sprintf(download_link, "%s/%d", link, (seconds % 1000) + 5);

              // declare the file name
              char file_name[65];
              time_t t_o = time(NULL);
              struct tm tm_s = *localtime(&t_o);
              sprintf(file_name, "%d-%02d-%02d_%02d:%02d:%02d.jpg", 
                tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
                tm_s.tm_min, tm_s.tm_sec);
              
              // create a child process and execute the wget command
              if (fork() == 0) {
                char *argv[] = {"wget", "-qO", file_name, download_link, NULL};
                execv("/bin/wget", argv);
              }

              // make a 5 seconds delay
              counter++;
              sleep(5);
            }

            // create the file which is required when the process complete
            FILE *scs_file;
            scs_file = fopen("status.txt", "w");

            // check the file opening status
            if (scs_file == NULL) {
              exit(EXIT_FAILURE);
            }

            // caesar cipher algorith to make encrypted message
            char string[25] = "Download Success";
            for(int i = 0; string[i] != '\0'; ++i) {
              char ch_str = string[i];
              if (ch_str >= 'a' && ch_str <= 'z') {
                ch_str = ch_str + 5;
                if(ch_str > 'z'){
                  ch_str = ch_str - 'z' + 'a' - 1;
                }
              } else if (ch_str >= 'A' && ch_str <= 'Z') {
                ch_str = ch_str + 5;
                if(ch_str > 'Z'){
                  ch_str = ch_str - 'Z' + 'A' - 1;
                }
              }
              fputc(ch_str, scs_file);
            }
            fclose(scs_file);

            // change the current dir to root
            chdir(root_dir);

            // create a child prcess
            pid_t child_zip = fork();
            int status_zip;

            // archive the folder
            if (child_zip == 0) {
              // declare the zip name
              char archive_name[25];
              strcpy(archive_name, dir_name);
              strcat(archive_name, ".zip");

              char *argv[] = {"zip", "-r", archive_name, dir_name, NULL};
              execv("/bin/zip", argv);
            } else {
              // wait the child process
              while ((wait(&status_zip)) > 0);

              // remove the folder
              char *argv[] = {"rm", "-rf", dir_name, NULL};
              execv("/bin/rm", argv);
            }
          } else {
            exit(EXIT_FAILURE);
          }
        }
        exit(EXIT_SUCCESS);
      }
      // delay the process with 40 seconds sleep
      sleep(40);
    }
  }
  exit(EXIT_SUCCESS);
}