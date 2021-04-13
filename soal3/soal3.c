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
#include <curl/curl.h>
#include <curl/easy.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
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
  char * link = "https://picsum.photos";

  while (true) {
    if (fork() == 0) {
      char folder_name[100];
      time_t t_o = time(NULL);
      struct tm tm_s = *localtime(&t_o);
      sprintf(folder_name, "/%d-%02d-%02d_%02d:%02d:%02d", 
        tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
        tm_s.tm_min, tm_s.tm_sec);

      char target_dir[255];
      strcpy(target_dir, root_dir);
      strcat(target_dir, folder_name);

      struct stat st_mark = {0};
      if (stat(target_dir, &st_mark) == -1) {
        if (!mkdir(target_dir, 0700)) {
          chdir(target_dir);

          int counter = 1;
          while (counter <= 10) {
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
              CURL * curl_util;
              FILE * image;

              curl_util = curl_easy_init(); 
              if (curl_util) {
                image = fopen(file_name, "wb"); 
                if (image != NULL) {
                  curl_easy_setopt(curl_util, CURLOPT_URL, download_link);
                  curl_easy_setopt(curl_util, CURLOPT_FOLLOWLOCATION, 1);
                  curl_easy_setopt(curl_util, CURLOPT_WRITEFUNCTION, write_data);
                  curl_easy_setopt(curl_util, CURLOPT_WRITEDATA, image);

                  curl_easy_perform(curl_util);
                  curl_easy_cleanup(curl_util);
                  fclose(image); 
                } else {
                  exit(EXIT_FAILURE);
                }
              }

              exit(EXIT_SUCCESS);
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
          for(int i = 0; string[i] != '\0'; ++i){
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
        } else {
          exit(EXIT_FAILURE);
        }
      }
      exit(EXIT_SUCCESS);
    }
    
    sleep(10);
  }
}