/********************************************************************
  
USAGE AGREEMENT: The Avocado Shell (avo) is a free and open-source 
shell written by Vince Belanger for fun and experience. Do whatever
you want with it.
 
VERSION: 0.0.3

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

void shell_line(){
   //char usr[1024];
   char cwd[1024];
   printf("[avo: %s]> ", getcwd(cwd, sizeof(cwd))); 
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
         fprintf(stderr, "Child failed to fork\n");
         exit(1);
      }

      for(i = 0; i < argc; i++)
         newargv[i] = argv[i];

      if(child == 0){
         execvp(file, &newargv[0]);
         fprintf(stderr, "./avosh: %s: No such file or directory\n", file);
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

