#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"
#define MAX_LENGTH 100

// handles input/output redirection
void in_out_redirection(char *args[], char *input_file, char * output_file, int append){
   pid_t pid;
   int status;
   pid = fork();
   if(pid == 0){
   // child process
      if(input_file != NULL){
      //redirect inout from file
         FILE *file_in = fopen(input_file, "r");
         if(file_in == NULL){
            perror("Couldn't open input file");
         	   exit(EXIT_FAILURE);
         }
         dup2(fileno(file_in), STDIN_FILENO);
         fclose(file_in);
      }
      if(output_file != NULL){
      // redirect output to a file
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
      // execute the command
      execvp(args[0], args);
      perror("Error executing");
      }
      else if(pid > 0){
      // parent process, waits for child to finish
         waitpid(pid, &status, 0);
      }
      else{
      // error handling for fork failure
         perror("Fork failed");
      }
}
// handles the batchfile
void read_batchfile(const char *filename){
   FILE * fptr = fopen(filename, "r");
   if(fptr == NULL){
      perror("Error opening file");
      return;
   }
   char command_to_string[100];
   while(fgets(command_to_string, sizeof(command_to_string), fptr) != NULL){
      // execute each command from file
      system(command_to_string);
   }
   fclose(fptr);
}
//handles internal commands
void internal_command(char ** args){
   int background = 0;
   int i = 0;
   // find the number of arguments
   while(args[i] != NULL){
      i++;
   }
  // check if the background execution is requested
   if(i < 0 && strcmp(args[i - 1], "&") == 0){
      args[i - 1] = NULL;
      background -= 1;
   }
   // execute internal commands
   if(!strcmp(args[0], "clr")){
      system("clear");
   }
   else if(!strcmp(args[0], "quit")){
      exit(0);
   }
   else if (!strcmp(args[0], "cd")) {
      chdir("..");
   }
   else if (!strcmp(args[0], "pwd")){
      char s[MAX_LENGTH];
      printf("%s\n", getcwd(s, MAX_LENGTH));
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
   // if not an internal command, execute as an external command
   else{
      while(*args){
         fprintf(stdout, "%s", *args++);
      }
      fputs("\n", stdout);
   }
}
//tokenizes the input
void tokenize(char * buf, char ** args){
   char ** arg = args;
   *arg++ = strtok(buf , SEPARATORS);
    while ((*arg++ = strtok(NULL,SEPARATORS)));
            // last entry will be NULL
}
int main (int argc, char * argv[]){
   char buf[MAX_BUFFER];                      // line buffer
   char * args[MAX_ARGS];                     // pointers to arg strings
 //  char ** arg;                               // working pointer thru args
   char prompt[MAX_LENGTH];
   char input_file[MAX_LENGTH], output_file[MAX_LENGTH];
   int append = 0;
   // check if a batchfile has been provided as an argument
   if(argc == 2){
      read_batchfile(argv[1]);
   }
   // get the current working directory for the prompt
      if(getcwd(prompt, sizeof(prompt)) == NULL) {
      	 perror("error");
      	 exit(EXIT_FAILURE);
      }
      // check for input/ output redirection
    if(argc == 7){
       in_out_redirection(args, input_file[0] != '\0' ? input_file: NULL, output_file[0] != '\0' ? output_file : NULL, append);
   }
   strcat(prompt, ">");
   while (!feof(stdin)) {
 /* get command line from input */
      fputs(prompt, stdout); // write prompt

      if (fgets (buf, MAX_BUFFER, stdin )) {
         tokenize(buf, args);
      }
       // read a line
         if (args[0]) {
            internal_command(args);                   // if there's anything there
    /* check for internal/external command */
         }
   }
   return 0;
}
