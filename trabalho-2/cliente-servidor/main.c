#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FOREVER 1

int SOMA = 0;
int respond = 0;
int request = 0;

void servidor()
{
    while (FOREVER)
    {
        // pre protocolo
        while (request == 0);
        respond = request;
        while (respond != 0);
        request = 0;
        // printf("Servidor\n");
    }
}

void cliente(int numThread)
{
    while (FOREVER)
    {
        if (SOMA >= 30)
            return;
        // printf("Cliente %d\n", numThread);
        //  pre protocolo
        while (respond != numThread)
        {
            request = numThread;
        }
        // regiao critica
        int local = SOMA;
        sleep(rand() % 2);
        SOMA = local + 1;
        printf("Soma = %d\n", SOMA);
        respond = 0;
        // printf("Fim cliente %d\n", numThread);
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