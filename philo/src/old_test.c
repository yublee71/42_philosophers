#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long start_timestamp;

int time_to_eat = 500000;
int time_to_sleep = 500000;

pthread_mutex_t f1;
pthread_mutex_t f2;
pthread_mutex_t f3;

unsigned long   get_timestamp(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    *routine(void *arg)
{
    int p_number;

    p_number = (int)arg;
    while (1)
    {
        if (p_number == 1)
        {
            pthread_mutex_lock(&f1);
            pthread_mutex_lock(&f2);
        }
        else if (p_number == 2)
        {
            pthread_mutex_lock(&f3);
            pthread_mutex_lock(&f2);
        }
        else
        {
            pthread_mutex_lock(&f3);
            pthread_mutex_lock(&f1);
        }
        printf("%lu %d is eating\n",
            get_timestamp() - start_timestamp,
            p_number);
        usleep(time_to_eat);
        if (p_number == 1)
        {
            pthread_mutex_unlock(&f1);
            pthread_mutex_unlock(&f2);
        }
        else if (p_number == 2)
        {
            pthread_mutex_unlock(&f3);
            pthread_mutex_unlock(&f2);
        }
        else
        {
            pthread_mutex_unlock(&f3);
            pthread_mutex_unlock(&f1);
        }
        printf("%lu %d is sleeping\n",
            get_timestamp() - start_timestamp,
            p_number);
        usleep(time_to_sleep);
        printf("%lu %d is thinking\n",
            get_timestamp() - start_timestamp,
            p_number);
    }
    return (NULL);
}

int main(void)
{
    pthread_t       p1;
    pthread_t       p2;
    pthread_t       p3;

    pthread_mutex_init(&f1, NULL);
    pthread_mutex_init(&f2, NULL);
    pthread_mutex_init(&f3, NULL);

    start_timestamp = get_timestamp();

    pthread_create(&p1, NULL, &routine, 1);
    pthread_create(&p2, NULL, &routine, 2);
    pthread_create(&p3, NULL, &routine, 3);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

    pthread_mutex_destroy(&f1);
    pthread_mutex_destroy(&f2);
    pthread_mutex_destroy(&f3);

    return (0);
}