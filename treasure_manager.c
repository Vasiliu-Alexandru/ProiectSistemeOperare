//fisier text, verificare existenta, afisarea acelui fisier, obligatoriu functia read si write  . Daca nu exista fisierul il creaza
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MAX_USERNAME 64 // lungime maxima username (63 caractere + terminator null)
#define MAX_CLUE 256    // lungime maxima username (255 caractere + terminator null)

typedef struct {
    int   treasure_id;
    char  username[MAX_USERNAME];
    float latitude;
    float longitude;
    char  clue[MAX_CLUE];
    int   value;
}Treasure;



int main(int argc, char **argv)
{
  char *buffer=malloc(4096*sizeof(char *));
  char *mesaj="Please include file name as an argument\n";
  if(argc!=2)
    {
      write(1,mesaj,strlen(mesaj));
      free(buffer);
      return -1;
    }

  struct stat st;
  if(stat(argv[1],&st)!=0)
    {
      char *mesaj_eroare="Fisierul nu exista, dar s-a creat\n";
      write(1,mesaj_eroare,strlen(mesaj_eroare));
      int f;
      f=open(argv[1], O_CREAT| O_RDWR| O_APPEND, S_IRUSR| S_IWUSR);
      int bytes;
       while((bytes=read(0,buffer, sizeof(buffer)))>0)
	  {
	      write(f,buffer,bytes);
	  }

       close(f);
      
    }
  else
    {
        int fd;
	fd=open(argv[1], O_RDONLY, 0777);

	int bytesread;
	while((bytesread=read(fd,buffer, sizeof(buffer)))>0)
	    {
	      write(1,buffer,bytesread);
	    }

	 close(fd);
    }
  free(buffer);
  return 0;
}

