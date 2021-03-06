#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

sem_t semafor;

struct task_t {
    int id;
    int counter;
} infos[] = {{1},{2},{3},{4}};

void* routine(void*arg) {
    struct task_t* pinfo = (struct task_t*)arg;
    
    while(pinfo->counter < 5) {
        sem_wait(&semafor);
        printf("ID=%d; counter=%d START\n", pinfo->id, pinfo->counter);
        usleep(5 * 1000000); // jakieś zadanie
        printf("ID=%d; counter=%d STOP\n", pinfo->id, pinfo->counter);
        pinfo->counter++;
    }
    printf("ID=%d; counter=%d (KONIEC)\n", pinfo->id, pinfo->counter);
    return NULL;
}

int main(int argc, char **argv)
{
    int hsem = sem_init(&semafor, 0 /*false*/, 3);
    assert(hsem == 0);

    pthread_t th[4];
    for (int i = 0; i < 4; i++)
        pthread_create(th + i, NULL, routine, infos + i);

    
    
    for (int value = -1; value != 0; ) {
        printf("Wpisz liczbę do zasygnalizowania semafora: ");
        fflush(stdout);
        scanf("%d", &value);
        for (int i = 0; i < value; i++)
            sem_post(&semafor);
    }


    for (int i = 0; i < 4; i++)
        pthread_join(th[i], NULL);


    sem_destroy(&semafor);
	return 0;
}
