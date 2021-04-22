# lapres-sisop-modul-2-C02-2021
Laporan resmi berisi dokumentasi soal shift Sisop Modul 2.
---
Kelompok C-02:
- [Jason Andrew Gunawan](https://github.com/jasandgun): 05111940000085
- [Muchamad Maroqi Abdul Jalil](https://github.com/maroqijalil): 05111940000143
- [Muhammad Zhafran Musyaffa](https://github.com/franszhafran): 05111940000147
---

## Soal 1
### Penjelasan Soal.
### Solusi dan Penjelasannya
### Dokumentasi dan Kendala
## Soal 2
### Penjelasan Soal
### Solusi dan Penjelasannya
### Dokumentasi dan Kendala
## Soal 3
### Penjelasan Soal.
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.
- (a) Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
- (b) Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
- (c) Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
- (d) Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.
- (e) Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
### Solusi dan Penjelasannya.
Secara keseluruhan jawaban per poin dari soal 3 ini tertulis dalam satu file kode porgram dan secara keselurhan terangkum dalam satu kesatuan fungsi `main`.
- (a) Solusi untuk poin ini adalah sebagai berikut:
> Membuat sebuah perulangan yang di dalamnya dilakukan pemanggilan fungsi `sleep()` untuk melakukan pekerjaan dengan jeda setiap 40 detik.
```cpp
while (true) {
  ...
  sleep(40);
}
```
> Melakukan pemanggilan fungsi `fork()` untuk membuat child process yang melakukan pembuatan folder dan pekerjaan selanjutnya sesuai poin lainnya. Hal ini dilakukan untuk memastikan bahwa pembuatan folder terjadi tepat dalam interval 40 detik.
```cpp
while (true) {
  if (fork() == 0) {
    ...
  }
  
  sleep(40);
}
```
> Melakukan pembuatan folder dengan menggunakan fungsi `exec()` yang dipanggil di dalam child process. Sebelumnya juga dilakukan pendeklarasian nama folder.
```cpp
while (true) {
  if (fork() == 0) {
    char dir_name[100];
    time_t t_o = time(NULL);
    struct tm tm_s = *localtime(&t_o);
    sprintf(dir_name, "%d-%02d-%02d_%02d:%02d:%02d", 
      tm_s.tm_year + 1900, tm_s.tm_mon + 1, tm_s.tm_mday, tm_s.tm_hour,
      tm_s.tm_min, tm_s.tm_sec);

    pid_t child_mkdir = fork();
    int status_mkdir;

    if (child_mkdir == 0) {
      char *argv[] = {"mkdir", "-p", dir_name, NULL};
      execv("/bin/mkdir", argv);
    } else {
      while ((wait(&status_mkdir)) > 0);
      ...
    }
    exit(EXIT_SUCCESS);
  }
  sleep(40);
}
```
- (b) Solusi untuk poin ini melanjutkan hasil dari pembuatan parent-child process pada poin (a):
> Dari kondisi pada step terakhir poin (a), terdapat kondisi `else` yang didalamnya terdapat fungsi `wait()` yang akan mnunggu pembuatan folder berhasil dilakukan. Jika sudah dibuat maka selanjutnya akan dilakukan pengecekan folder menggunakan fungsi `stat()` apakah sudah benar terbuat
```cpp
if (child_mkdir == 0) {
  char *argv[] = {"mkdir", "-p", dir_name, NULL};
  execv("/bin/mkdir", argv);
} else {
  while ((wait(&status_mkdir)) > 0);
  
  char target_dir[255];
  sprintf(target_dir, "%s/%s", root_dir, dir_name);
  struct stat st_mark = {0};
  if (stat(target_dir, &st_mark) != -1) {

    ...
  } else {
    exit(EXIT_FAILURE);
  }
}
exit(EXIT_SUCCESS);
```
> Jika folder yang diinginkan ditemukan, maka directory dimana proses berjalan akan dipindah ke dalam nya menggunakan fungsi `chdir()`. Ketika sudah berpindah, maka akan dilakukan pengunduhan gambar sesuai dengan ketentuan, yaitu mengunduh gambar pada [https://picsum.photos](https://picsum.photos) dengan ukuran sesuai perhitungan waktu, yaitu `(seconds % 1000) + 5`. Pengunguhan ini dilakukan di dalam perulangan sebanyak 10 kali yang dijeda selama 5 detik menggunakan fungsi `sleep()`.
```cpp
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
        
      ...

      counter++;
      sleep(5);
    }

    ...
  } else {
    exit(EXIT_FAILURE);
  }
}
exit(EXIT_SUCCESS);
```
> Selanjutnya, pengunduhan dilakukan dengan menggunakan fungsi `execv()` dimana didalamnya memanggil perintah `wget`. Link file download disesuaikan dengan deklarasi yang dilakukan pada step sebelumnya.
```cpp
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

    ...
  } else {
    exit(EXIT_FAILURE);
  }
}
exit(EXIT_SUCCESS);
```
- (c) Solusi untuk poin ini adalah sebagai berikut:
> Ketika semua proses pengunduhan gambar selesai, selanjutnya membuat file status.txt yang berisi string "Download Success". String ini akan dienkripsi menggunakan algoritma Caesar Cipher. Pertama, dilakukan pembuatan file dengan menggunakan fungsi `fopen()`.
```cpp
FILE *scs_file;
scs_file = fopen("status.txt", "w");

if (scs_file == NULL) {
  exit(EXIT_FAILURE);
}

...
```
> Jika pembuatan sudah berhasil, maka string "Download Success" akan dituliskan ke dalam file tadi menggunakan enkripsi Caesar Cipher.
```cpp
FILE *scs_file;
scs_file = fopen("status.txt", "w");

if (scs_file == NULL) {
  exit(EXIT_FAILURE);
}

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

...
```
> Setelah pengisian status pada file, selanjutnya direktori proses berada akan dipindah ke parentnya untuk dialkukan pengarsipan folder kemudian penghapusan folder. Operasi ini dilakukan dengan membuat parent-child process dimana child-nya akan memanggil fungsi `execv()` untuk melakukan pengarsipan menggunakan perintah `zip`. Sedangkan parent-nya akan menunggu proses pada child selesai kemudian memanggil perintah `rm` dengan fungsi `execv()` juga.
```cpp
FILE *scs_file;
scs_file = fopen("status.txt", "w");

if (scs_file == NULL) {
  exit(EXIT_FAILURE);
}

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
```
- (d) Solusi poin ini akan digaung dengan poin (e).
- (e) Solusi untuk poin ini adalah sebagai berikut:
> Karena secara keseluruhan proses dari program ini berjalan pada latar belakang maka akan program ini akan dijalankan dalam sebuah Daemon proses.
```cpp
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

	char * root_dir =
		"/home/maroqi/Projects/OSProject/Modul_2/soal-shift-sisop-modul-2-C02-2021/soal3";
  if ((chdir(root_dir)) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  ... // program utama

  exit(EXIT_SUCCESS);
}
```
> Untuk mendapatkan opsi ketika executable file dari porgram ini maka argumen akan diambil dari varaible `argv`. yang dilakukan pertama kali adalah memeriksa apakah ada opsi argumen masuk, jika ada maka akan dilakukan pengecekan apakah argumen tersebut "-z" atau "-x".
```cpp
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

	char * root_dir =
		"/home/maroqi/Projects/OSProject/Modul_2/soal-shift-sisop-modul-2-C02-2021/soal3";
  if ((chdir(root_dir)) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  if (argc > 1) {
    if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
      
      ...
    }
  } else {

    ...
  }

  exit(EXIT_SUCCESS);
}
```
> Selanjutnya akan dilakukan pembuatan file "Killer.sh" yang akan berisi perintah untuk membunuh proses dari program ini dan menghapus file bash itu sendiri.
```cpp
if (argc > 1) {
  if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
    char * sh_name = "Killer.sh";
    FILE * sh_killer;
    sh_killer = fopen(sh_name, "w");
    
    if (sh_killer == NULL) {
      exit(EXIT_FAILURE);
    }

    ...
  }
} else {

  ...
}
```
> Ketika file bash berhasil dibuat maka dilakukan pendeklarasian perintah atau isi dari file tersebut. Untuk perintah ketika opsi "-z", diberikan perintah `"ps -C exec_file -o pid= | xargs -r kill -9`, perintah ini akan mendata PID yang memiliki nama [exec_file] kemudian data PID tersebut akan dibunuh menggunakan perintah `kill`. Untuk perintah ketika opsi "-x" diberikan perintah `ps -C exec_file -o pid= -o stat= | awk '/Ss/ {print $1}' | xargs -r kill -9`, perintah ini akan mendata PID dan status proses yang memiliki nama [exec_file] kemudian data PID tersebut akan diseleksi berdasarkan proses yang memiliki status `Ss` selanjutnya proses akan dibunuh menggunakan perintah `kill`. 
```cpp
if (argc > 1) {
  if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
    char * sh_name = "Killer.sh";
    FILE * sh_killer;
    sh_killer = fopen(sh_name, "w");
    
    if (sh_killer == NULL) {
      exit(EXIT_FAILURE);
    }

    char header[25] = "#!/bin/bash";
    char command_remove[75] = "rm -f Killer.sh";
    char command_kill[100];
    char * exec_arg = &argv[0][2];
    if (strcmp(argv[1], "-z") == 0) {
      sprintf(command_kill, "ps -C %s -o pid= | xargs -r kill -9", exec_arg);
    } else if (strcmp(argv[1], "-x") == 0) {
      sprintf(command_kill, "ps -C %s -o pid= -o stat= | awk '/Ss/ {print $1}' | xargs -r kill -9", exec_arg);
    }
    
    ...
  }
} else {

  ...
}
```
> Dari perintah yang sudah dideklarasikan akan dituliskan ke dalam file bash tadi dan kemudian dieksekusi menggunakan fungsi `popen()`. 
```cpp
if (argc > 1) {
  if (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0) {
    char * sh_name = "Killer.sh";
    FILE * sh_killer;
    sh_killer = fopen(sh_name, "w");
    
    if (sh_killer == NULL) {
      exit(EXIT_FAILURE);
    }

    char header[25] = "#!/bin/bash";
    char command_remove[75] = "rm -f Killer.sh";
    char command_kill[100];
    char * exec_arg = &argv[0][2];
    if (strcmp(argv[1], "-z") == 0) {
      sprintf(command_kill, "ps -C %s -o pid= | xargs -r kill -9", exec_arg);
    } else if (strcmp(argv[1], "-x") == 0) {
      sprintf(command_kill, "ps -C %s -o pid= -o stat= | awk '/Ss/ {print $1}' | xargs -r kill -9", exec_arg);
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

  ...
}
```
Untuk melihat kode prgram lengkapnya, [klik disini](/soal3/soal3.c):
---