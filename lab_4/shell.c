#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_BUFFER 1024  // max line buffer
#define MAX_ARGS 64      // max # args
#define SEPARATORS " \t\n"
#define MAX_LENGTH 100



void in_out_redirection(char *args[], char *input_file, char * output_file, int append){
   pid_t pid;
   int status;
   pid = fork();
   if(pid == 0){
      if(input_file != NULL){
         FILE *file_in = fopen(input_file, "r");
         if(file_in == NULL){
			perror("Couldn't open input file");
			exit(EXIT_FAILURE);

         }
         dup2(fileno(file_in), STDIN_FILENO);
         fclose(file_in);
      }
   if(output_file != NULL){
      FILE * file_out;
      if(append){
         file_out = fopen(output_file, "a");
      }
      else{
         file_out = fopen(output_file, "w");


      }
      if(file_out == NULL){
         perror("Could'nt open ouput file");
         exit(EXIT_FAILURE);
      }
      dup2(fileno(file_out), STDIN_FILENO);
      fclose(file_out);
   }
   execvp(args[0], args);
   perror("Error executing");
   }
   else if(pid > 0){
      waitpid(pid, &status, 0);
   }
   else{
      perror("Fork failed");
   }
}
void internal_command(char ** args){

   if(!strcmp(args[0], "clr")){
      system("clear");
   }
   else if(!strcmp(args[0], "quit")){
      exit(0);
   }
   else if (!strcmp(args[0], "cd")){
      chdir("..");
   }
   else if (!strcmp(args[0], "pwd")){
      char s[100];
      printf("%s\n", getcwd(s, 100));
   }
   else if(!strcmp(args[0], "dir")){
	  system("ls -l");
   }

   else if(!strcmp(args[0], "environ")){
	  system("env");
   }

   else if(!strcmp(args[0], "echo")){
      printf("%s\n", args[1]);
   }

   else if(!strcmp(args[0], "help")){
      system("man bash");
   }
   else if(!strcmp(args[0], "pause")){
      printf("Press Enter to continue");
      while(getchar() != '\n');

   }
   else{
      while(*args){
         fprintf(stdout, "%s", *args++);
      }
      fputs("\n", stdout);
   }
}

void tokenize(char * buf, char ** args){
   char ** arg = args;
   *arg++ = strtok(buf , SEPARATORS);
   while ((*arg++ = strtok(NULL,SEPARATORS)));
   // last entry will be NULL
}

//void in_out_redirection(char ** args){

//}

int main(int argc, char * argv[]){
   while(1){
      char dir[100];

      if (argc == 2){
         FILE * fptr;
         fptr  = fopen(argv[1], "rb");
         for(int i = 0; i < sizeof(fptr); ++i){
            char command_to_string[100];
            fgets(command_to_string, 100, fptr);
            system(command_to_string);
         }
         fclose(fptr);
      }
      char buf[MAX_BUFFER];  // line buffer
      char * args[MAX_ARGS];
      char input_file[MAX_LENGTH], output_file[MAX_LENGTH];
      int append = 0;
      int args_num;
      char working_dir[100];
      if(argc == 7){
         in_out_redirection(args, input_file[0] != '\0' ? input_file: NULL, output_file[0] != '\0' ? output_file : NULL, append);
      }
      char prompt[100];
      if(getcwd(prompt, sizeof(prompt)) == NULL) {
	     perror("error");
	     exit(EXIT_FAILURE);
      }
      strcat(prompt, ">");
      while(!feof(stdin)){
         fputs(prompt, stdout);
         if(fgets(buf, MAX_BUFFER, stdin)){
        //tokenize the input
            tokenize(buf, args);
         }
      }
      //check for commands and execute
            if(args[0]){
               internal_command(args);
            }
      }
      return 0;
}
