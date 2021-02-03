/* Programa cria duas threads tid1 e tid2. tid1 executa a funcao runner que realiza a soma dos numeros */
/* de 1 até o valor passado como argumento. tid2 imprime o identificador da thread */
#include "pthread.h"
#include <stdlib.h>
#include <stdio.h>

int sum;
void *runner(void *param);
void *print_message_function();

int main(int argc, char **argv)
{
        pthread_t tid1, tid2, tid3;
        pthread_attr_t attr;


        pthread_attr_init(&attr);
        if (argc<2){
                 printf("Passar como argumento a quantidade de numeros a serem somados\n");
                exit(0);
        }
        /*Cria thread tid1*/
        pthread_create(&tid1,&attr,runner,argv[1]);
        /*Cria thread tid2*/
        pthread_create(&tid2,&attr,print_message_function,NULL);
        /*Thread principal espera até thread tid1 terminar execução*/
        pthread_join(tid1,NULL);
        /*Thread principal espera até thread tid2 terminar execução*/
        pthread_join(tid2,NULL);
        printf("Soma = %d\n",sum);
        exit(0);
}

void *print_message_function( )
{
       /*pthread_self retorna id da thread*/
   printf("Thread filha\n");
}

void *runner(void *param)
{
        int upper = atoi(param);
        int i;

        sum = 0;
        if (upper > 0) {
                /* Soma os valores de 1 até o valor upper inclusive*/
                for (i = 1; i <= upper; i++)
                sum += i;
        }
        pthread_exit(0);
}





