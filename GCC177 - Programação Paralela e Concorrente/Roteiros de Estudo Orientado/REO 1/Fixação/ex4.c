#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   
   sleep(14);
   
   int pid1 = fork();

   if (pid1 < 0) {
      fprintf(stderr, "Erro ao criar processo\n");
   } else if (pid1 == 0) {
         sleep(12);
         int pid3 = fork();
         
         if (pid3 < 0) {
            fprintf(stderr, "Erro ao criar processo\n");
         } else if (pid3 == 0) {
            sleep(12);
            exit(0);
         }

         sleep(18);
         exit(0);
   }
   
   sleep(2);
   int pid2 = fork();
   
   if (pid2 < 0) {
      fprintf(stderr, "Erro ao criar processo\n");
   } else if (pid2 == 0) {
      sleep(14);
      int pid4 = fork();

      if (pid4 < 0) {
            fprintf(stderr, "Erro ao criar processo\n");
      }

      sleep(14);
      exit(0);
   }
   
   sleep(44);
   
   return 0;
}
