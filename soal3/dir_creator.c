#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
  
void main()
{
	char * root_dir =
		"/home/maroqi/Projects/OSProject/Modul_2/soal-shift-sisop-modul-2-C02-2021/soal3";

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
		if (!mkdir(target_dir, 0700))
			printf("Folder %s berhasil dibuat\n", folder_name);
		else {
			printf("Gagal membuat folder %s\n", folder_name);
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Folder %s telah ada\n", folder_name);
	}

	exit(EXIT_SUCCESS);
}
