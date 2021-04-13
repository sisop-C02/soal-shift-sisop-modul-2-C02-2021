#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

void main()
{
  char * link = "https://picsum.photos";

  char file_name[65];
	time_t t_o = time(NULL);
	struct tm tm_s = *localtime(&t_o);
	sprintf(file_name, "%d-%02d-%02d_%02d:%02d:%02d.jpg", 
		tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
		tm_s.tm_min, tm_s.tm_sec);
  
  int seconds = time(NULL);
  char download_link[255];
  sprintf(download_link, "%s/%d", link, (seconds % 1000) + 5);

  CURL * curl_util;
  FILE * image;

  printf("Download gambar dengan nama %s dari link %s.\n", file_name, download_link);

  curl_util = curl_easy_init(); 
  if (curl_util) {
    image = fopen(file_name, "wb"); 
    if (image == NULL) {
      printf("Tidak dapat membuka file!\n"); 
    } else {
      curl_easy_setopt(curl_util, CURLOPT_URL, download_link);
      curl_easy_setopt(curl_util, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(curl_util, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl_util, CURLOPT_WRITEDATA, image);

      if (curl_easy_perform(curl_util)) {
        printf("Gagal menyelesaikan pengambilan gambar!\n");
      }
      
      curl_easy_cleanup(curl_util);
      fclose(image); 
    }
  }

  exit(EXIT_SUCCESS);
}