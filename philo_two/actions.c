#include "philo_two.h"

void	init_sem(t_gnrl *gnrl)
{
	sem_unlink("semaphore");
	sem_unlink("lock");
	sem_unlink("lock_output");
	sem_unlink("lock_death");
	sem_unlink("lock_mustdie");
	gnrl->thread = (pthread_t *)malloc(sizeof(pthread_t) * gnrl->num_philo);
	gnrl->semaphore = sem_open("semaphore", O_CREAT, 777, gnrl->num_philo);
	gnrl->lock = sem_open("lock", O_CREAT, 777, 1);
	gnrl->lock_output = sem_open("lock_output", O_CREAT, 777, 1);
	gnrl->lock_death = sem_open("lock_death", O_CREAT, 777, 1);
	gnrl->lock_mustdie = sem_open("lock_mustdie", O_CREAT, 777, 1);
}

void	eating(t_gnrl *gnrl, t_threads *philo)
{
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, philo, FORK_LEFT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, philo, FORK_RIGHT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, philo, EAT);
	sem_post(gnrl->lock_output);
	philo->t_limit = time_now() + gnrl->time_todie;
	if (gnrl->n_must_eat > 0)
		gnrl->n_must_eat--;
	usleep(gnrl->time_toeat * 1000);
}
