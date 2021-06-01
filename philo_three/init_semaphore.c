#include "./philo_three.h"

void	init_sem(void)
{
	t_gnrl	*gnrl;

	gnrl = get_struct(NULL);
	sem_unlink("semaphore");
	sem_unlink("lock");
	sem_unlink("lock_output");
	sem_unlink("lock_death");
	sem_unlink("lock_mustdie");
	sem_unlink("must_die");
	sem_unlink("lock_test");
	gnrl->semaphore = sem_open("semaphore", O_CREAT, 777, gnrl->num_philo);
	gnrl->lock = sem_open("lock", O_CREAT, 777, 1);
	gnrl->lock_output = sem_open("lock_output", O_CREAT, 777, 1);
	gnrl->lock_death = sem_open("lock_death", O_CREAT, 777, 1);
	gnrl->lock_mustdie = sem_open("lock_mustdie", O_CREAT, 777, 1);
	gnrl->must_die = sem_open("must_die", O_CREAT, 777, 0);
	gnrl->lock_test = sem_open("lock_test", O_CREAT, 777, 0);
}
