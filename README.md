# lapres-sisop-modul-2-C02-2021
Laporan resmi berisi dokumentasi soal shift Sisop Modul 2.
---
Kelompok C-02:
- [Jason Andrew Gunawan](https://github.com/jasandgun): 05111940000085
- [Muchamad Maroqi Abdul Jalil](https://github.com/maroqijalil): 05111940000143
- [Muhammad Zhafran Musyaffa](https://github.com/franszhafran): 05111940000147
---

## Soal 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. 

Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi. (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg (b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :). (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta (d) memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

(e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany). (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya mendapatkan hati Stevany. Bantu Woy!!

### Penjelasan Soal.
> Pada soal ini, akan diunduh 3 file zip dari Google Drive, kemudian file zip tersebut akan di extract lalu folder-foldernya di rename sesuai pada soal.
> Pada 6 jam sebelum Stevany ulang tahun, lakukan aksi diatas
> Tepat saat Stevany ulang tahun, zip semua folder menjadi Lopyu_Stevany.zip kemudian hapus semua folder tadi.

### Solusi dan Penjelasannya
> Pertama-tama saya membagi menjadi aksi-aksi kecil kemudian membuat fungsinya.
> - fungsi download untuk mendownload file dari link yang diberikan
![image](https://user-images.githubusercontent.com/49693862/115988477-25309700-a5e4-11eb-8f0f-19159724f15b.png)

> - fungsi zipAllFolder untuk meng-zip semua folder
![image](https://user-images.githubusercontent.com/49693862/115988500-4b563700-a5e4-11eb-9990-7a557b0834d7.png)

> - fungsi untuk merename folder dengan cara di move           
![image](https://user-images.githubusercontent.com/49693862/115988559-87899780-a5e4-11eb-99c4-149a140a7f2b.png)

> - fungsi untuk menjalankan fungsi execv di child process sehingga parent tidak ter-replace
![image](https://user-images.githubusercontent.com/49693862/115988591-aab44700-a5e4-11eb-9ba6-32876c2510b8.png)

> Kemudian karena program yang dibuat menunggu ulang tahun Stevany maka dibuat dalam bentuk daemon
> Pada 6 jam sebelum ulang tahun, lakukan download, zip dan rename folder.
![image](https://user-images.githubusercontent.com/49693862/115988659-ef3fe280-a5e4-11eb-8185-d85cf8c2332e.png)

> Tepat pada ulang tahun Stevany, zip semua folder kemudian hapus foldernya
![image](https://user-images.githubusercontent.com/49693862/115988684-07affd00-a5e5-11eb-828a-c4153f2ef622.png)

### Dokumentasi dan Kendala
> Pertama, compile program, kemudian jalankan, kemudian atur tanggal ke 6 jam sebelum Stevany ulang tahun.
![image](https://user-images.githubusercontent.com/49693862/115988870-b9e7c480-a5e5-11eb-95f8-5eb61a5132e8.png)

> Nantinya akan terunduh 3 zip dengan kontennya berada pada folder yang kita inginkan
![image](https://user-images.githubusercontent.com/49693862/115988906-dd127400-a5e5-11eb-96dc-c0e3936abd0a.png)

> Kemudian, kita set waktu menjadi satu detik sebelum ulang tahun Stevany
![image](https://user-images.githubusercontent.com/49693862/115989001-3ed2de00-a5e6-11eb-9bc8-8c483acb6144.png

> Setelah itu, folder-folder yang tadi akan menjadi zip dan folder telah dihapus
![image](https://user-images.githubusercontent.com/49693862/115989015-5611cb80-a5e6-11eb-9754-12b55c537db1.png)

> Kendala pengerjaan:
> - Awalnya tidak tahu kalau execv itu mereplace process. Setelah tahu, baru dibuat fungsi execvCustom agar dilakukan pada child process
> - Lupa awalnya program tidak berbentuk daemon
> - Saat testing, lupa mematikan automatic date and time nya Ubuntu

## Soal 2
### Penjelasan Soal
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.
- (a) Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
- (b) Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.
- (c) Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”.
- (d) Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.
- (e) Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun

```
Loba sangat mengapresiasi bantuanmu, minggu depan ia akan mentraktir makan malam!

**Note:**
- Setiap data peliharaan disimpan sebagai nama foto dengan format [jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]. Jika terdapat lebih dari satu peliharaan, data dipisahkan menggunakan underscore(_).
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename().
- Menggunakan fork dan exec.
### Solusi dan Penjelasannya
- Variabel global yang digunakan
```c
// Global variables
char filename[100][100];
char * default_dir = "/home/jaglfr/modul2/petshop/";
// Function definition
void execute_order(char[], char[], char[], int, bool);
```

- (a) Solusi untuk poin ini adalah melakukan unzip:
> Sebelum dilakukan unzip, perlu dibuat folder “/home/[user]/modul2/petshop”. Dalam hal ini folder akan dibuat dan path disimpan di variabel default_dir.
```c
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
```
> `child2` akan melakukan proses mkdir agar hasil unzip dapat diletakkan di directory tersebut. Sementara `child1` akan melakukan proses unzip. Proses ini hanya akan meng-unzip file saja, bukan folder. Hal ini terjadi akibat adanya parameter `"-x", "*/*"` yang meng-exclude folder dari proses unzip.

- Solusi untuk poin (b), (c), (d), dan (e) diawali dengan beberapa hal berikut:
> Menunggu hingga program unzip selesai. Semua file yang sudah berada di default_dir sekarang akan dilakukan iterasi untuk menyimpan nama dari masing-masing file yang berisi info terkait peliharaan dalam masing-masing gambar. Untuk membaca dan menyimpan nama file ini, digunakan fungsi dari library `<dirent.h>`. Nama file disimpan akan dalam array `filename[100][100]` untuk tiap iterasi hingga file habis, atau bernilai `NULL`.
```c
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
```
> Kemudian dilakukan parsing dari masing-masing nama file yang ada di dalam array `filename[100][100]`. Masing-masing nama file akan dibagi sesuai persyaratan soal. Karakter `;` membagi karakteristik dalam nama file sebagai berikut `jenis;nama;umur`. Karakter `_` membagi karakteristik antara 2 atau lebih hewan peliharaan sebagai berikut `jenis1;nama1;umur1_jenis2;nama2;umur2`. Ada statement `j == strlen(filename[i]) - 4` yang menunjukkan bahwa sebuah nama file sudah mencapai akhirnya, sebelum 4 karakter terakhir `.jpg`.
```c
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
```
> Untuk prosesnya sendiri, masing-masing terdapat di dalam sebuah fungsi `execute_order()`. Fungsi ini menerima 5 parameter. Jenis hewan, nama hewan, umur hewan, indeks nama file, dan keberadaan underscore. 

- (b) Solusi untuk poin ini adalah melakukan proses membuat folder untuk masing-masing jenis hewan peliharaan:
> Fork sebuah child untuk mengeksekusi mkdir. Nama folder merupakan hasil concatenation dari `default_dir` dan jenis hewan peliharaan. 
```c
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
```

- (c) dan (d) Solusi untuk poin ini adalah memindahkan file sesuai jenis dan rename sesuai nama hewan:
> Menyediakan variabel string `newname` yang merupakan path serta nama baru dari masing-masing foto. Menyediakan juga variabel string `oldname` yang merupakan path serta nama lama dari masing-masing foto yang ada. `oldname` digunakan untuk mengetahui lokasi foto yang relevan (sesuai index pada `filename[idx]`).
```c
// New file folder
char newname[100]="";
strcpy(newname, default_dir);
strcat(newname, type); strcat(newname, "/");
// Rename
strcat(newname, name); strcat(newname, ".jpg");
// Old filename
char oldname[100]="";
strcpy(oldname, default_dir);
strcat(oldname, filename[idx]);
```
> Membuat proses untuk memindahkan file ke folder yang sesuai. Apabila terdapat underscore`_`, file akan di-copy ke folder untuk hewan pertama, lalu fungsi akan dipanggil lagi untuk hewan kedua. Apabila hanya tersisa 1 hewan peliharaan, atau tidak terdapat underscore, file akan langsung di-move ke foldernya yang sesuai. Sehingga tidak perlu adanya perintah remove.
```c
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
```
- (e) Solusi untuk poin ini adalah menuliskan karakteristik hewan peliharaan dalam sebuah file `.txt`:
> Menyediakan variabel string `textname` yang merupakan path ke sebuah folder yang sesuai dengan jenis hewan. Sediakan pointer file dengan akses append `a` yang berguna untuk menambahkan karakteristik tiap hewan yang akan ditambahkan ke dalam folder tersebut. Isi keterangan sesuai dengan permintaan soal.
```c
// File name for keterangan.txt
char textname[100]=""; strcpy(textname, newname);
strcat(textname, "keterangan.txt");
FILE *fptr;
fptr = fopen(textname, "a");
fprintf(fptr, "nama : %s\numur : %s tahun\n\n", name, age);
```
### Dokumentasi dan Kendala
**Screenshot hasil:**
- Hasil unzip

![Screenshot_from_2021-04-22_18-42-42](https://user-images.githubusercontent.com/55174646/115715511-676a9600-a3a2-11eb-9eb7-861a96a91643.png)

- Hasil mkdir

![Screenshot_from_2021-04-22_18-43-16](https://user-images.githubusercontent.com/55174646/115713681-7d775700-a3a0-11eb-848f-1eeb0354ea13.png)

![Screenshot_from_2021-04-22_18-43-34](https://user-images.githubusercontent.com/55174646/115713705-836d3800-a3a0-11eb-94dd-91da3e106a0e.png)

![Screenshot_from_2021-04-22_18-43-59](https://user-images.githubusercontent.com/55174646/115713721-8831ec00-a3a0-11eb-90a7-2773a4bc9033.png)

- Isi folder `kucing`

![Screenshot_from_2021-04-22_18-44-12](https://user-images.githubusercontent.com/55174646/115713746-8d8f3680-a3a0-11eb-8007-b4f87dc83457.png)

- Isi `keterangan.txt` di dalam folder `kucing`

![Screenshot_from_2021-04-22_18-44-53](https://user-images.githubusercontent.com/55174646/115713770-92ec8100-a3a0-11eb-9e26-6314495a8950.png)

**Kendala ketika pengerjaan:**
- Terdapat hasil yang tidak konsisten ketika menggunakan metode `strtok` untuk membagi nama dengan delimiter `;` maupun `_`. Hal ini terjadi karena masih belum menguasai cara membagi string menggunakan `strtok` dan pointer. Metode alternatif yang dipilih adalah menggunakan looping manual untuk setiap nama file.
- Terdapat beberapa masalah ketika melakukan prosedur `fork()` karena variabel untuk mengatur `wait()` belum sesuai dengan child yang ingin ditunggu. Hal ini diatasi dengan membuat variabel status untuk masing-masing child yang ketika terjadi proses `fork()`. Misal ada variabel `pid_t child1 = fork()`, ia akan memiliki variabel `int status1`. Oleh karena itu, `while ((wait(&status1)) > 0);` akan menentukan parent process untuk menunggu hingga proses child1 selesai berjalan.

Untuk melihat kode program lengkapnya, [klik disini](/soal2/soal2.c):
---
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
Untuk melihat kode program lengkapnya, [klik disini](/soal3/soal3.c):
### Dokumentasi dan Kendala
Screenshot hasil:
- Membuat folder dan download gambar
<img src="/soal3/mkdir-download.png" width="600">
- Membuat file dan mengarsip
<img src="/soal3/create-zip.png" width="600">
<img src="/soal3/inside-zip.png" width="600">

Kendala ketika pengerjaan:
Selama pengerjaan saya mendapatkan kendala ketika tidak tahu proses mana yang berjalan, sedangkan proses yang berjalan mengalamai kesalahan algoritma. Kesalahan tersebut adalah, membuat folder setiap detiknya, dan membuat child process yang membuatnya berlipat ganda. Ketika hal itu terjadi, laptop saya sempat mengalami lag ysehingga harus dimatikan secara paksa.


---
