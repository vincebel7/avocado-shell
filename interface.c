/********************************************************************
  
USAGE AGREEMENT: The Avocado Shell (avo) is a free and open-source 
shell written by Vince Belanger for fun and experience. Do whatever
you want with it.
 
VERSION: 0.0.4

********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<wait.h>

#define SPACE " "
#define SPACE_N " \n"
#define TAB " \t"
#define TAB_N " \t\n"

#define ANSI_COLOR_LG	"\x1b[36m"
#define ANSI_NO_COLOR	"\x1b[0m"

char * get_cwd(){
   char cwd[1024];
   char* dir = malloc(3 * sizeof(char)); 
   dir = getcwd(cwd, sizeof(cwd));
   return dir;
}

void shell_line(){
   //char usr[1024];
   char cwd[1024];
   char* dir = malloc(3 * sizeof(char));
   dir = get_cwd();
   printf(ANSI_COLOR_LG "[avo: %s]>", dir);
   //printf(ANSI_COLOR_LG "[avo: %s]>", getcwd(cwd, sizeof(cwd)));
   printf(ANSI_NO_COLOR " "); 
   //TODO: tokenize by forward slashes
}

int main(){
   char* input = NULL;
   size_t n = 100;
   char** string = malloc(sizeof(*string) * n);
   pid_t child = 0;
   char** argv = NULL;
   int argc;
   char* file = malloc(sizeof(*file) * n);
   int i;
   char** newargv = malloc(sizeof(*newargv) * n);

   shell_line();

   //TODO: put tokenization in method
   while(getline(&input, &n, stdin) != EOF){
      argv = malloc(sizeof(*argv) * n);

      if(strcmp(input, TAB)) //tab delimited in input
         *string = strtok(input, TAB_N);

      else if(strcmp(input, SPACE_N)) //space delimited in input
         *string = strtok(input, SPACE_N);

      argc = 0;
      while(*string){
         argv[argc] = *string;
         if(!argc) file = argv[0];

         if(strcmp(input, TAB))
            *string = strtok('\0', TAB_N);

         else if(strcmp(input, SPACE_N))
            *string = strtok('\0', SPACE_N);
        
         argc++;
      }

      if((child = fork()) == -1){
         fprintf(stderr, "Error 1000\n");
         exit(1);
      }

      for(i = 0; i < argc; i++)
         newargv[i] = argv[i];

      if(child == 0){
         execvp(file, &newargv[0]);
         fprintf(stderr, "./avo: %s: No such file or directory\n", file);
         exit(1);
      }

      else wait(NULL); 
      free(argv);
      
      //ensures blank spaces aren't read as args for next command
      for(i = 0; i < argc; i++)
         newargv[i] = '\0';

      shell_line();
   }
   exit(0);
}

