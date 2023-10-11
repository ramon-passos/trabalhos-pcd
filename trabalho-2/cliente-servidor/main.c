#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FOREVER 1

int SOMA = 0;
int respond = 0;
int request = 0;
int execucoes = 0;

void servidor()
{
    while (SOMA < 30)
    {
        // pre protocolo
        while (request == 0);
        respond = request;
        // regiao critica
        while (respond != 0);
        request = 0;
    }
}

void cliente(int numThread)
{
    while (SOMA < 30)
    {
        //  pre protocolo
        while (respond != numThread)
        {
            request = numThread;
        }
        // regiao critica
        int local = SOMA;
        sleep(rand() % 2);
        SOMA = local + 1;
        printf("Thread %d - Soma = %d\n", numThread, SOMA);
        respond = 0;
    }
}

int main(int argc, char **argv)
{
    int th_id;
    omp_set_num_threads(5);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if (th_id == 0)
            servidor();
        else
            cliente(th_id);
    }
    return 0;
}