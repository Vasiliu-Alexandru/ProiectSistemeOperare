//fisier text, verificare existenta, afisarea acelui fisier, obligatoriu functia read si write  . Daca nu exista fisierul il creaza
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

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

void argument_error(void)
{
   const char mesajEroare[] ="Incorrect usage of program. To use treasure manager please input the desired operation which include the following:\n   add <hunt_id>\n   list <hunt_id>\n   view <hunt_id> <id>\n   remove_treasure <hunt_id> <id>\n   remove_hunt <hunt_id>\nFor a more detailed help guide include --help\n";

   write(STDOUT_FILENO, mesajEroare,sizeof(mesajEroare));

  return;
}

void help(void)
{
  const char mesaj[] ="To use treasure manager please input the desired operation which include the following:\n   add <hunt_id>                   -Adds a new treasure to the  hunt/game session specified by \"hunt_id\"\n   list <hunt_id>                  -Lists all treasures in the specified hunt\n   view <hunt_id> <id>             -View details of a specific treasure \n   remove_treasure <hunt_id> <id>  -Removes specified treasure from hunt\n   remove_hunt <hunt_id>           -Removes entire hunt, use with caution\n";
  write(STDOUT_FILENO, mesaj,sizeof(mesaj));
  return;

}

int este_director(const char *cale)
{
  struct stat st;
  if(stat(cale,&st)==-1)
  {
    return 0; //calea nu exista
  }
  return S_ISDIR(st.st_mode); // 1 daca este director 0 daca nu este
}

void add(char *hunt_id)
{
  if(este_director(hunt_id))
    printf("Exista directorul\n");
    else
      printf("Nu exista directorul\n");

}

int main(int argc, char**argv)
{
  if(argc<2)
  {
    argument_error();
    exit(EXIT_FAILURE);
  }

  for(int i=1;i<argc;i++)
  {
    if(strcmp(argv[i],"--help")==0)
    {
      help();
      exit(EXIT_SUCCESS);
    }
  }

  if(strcmp(argv[1],"--add")==0)
  {
    if(argc!=3)
    {
      argument_error();
      exit(EXIT_FAILURE);
    }
    add(argv[2]);
    exit(EXIT_SUCCESS);
  }


  argument_error();

  return 0;
}

