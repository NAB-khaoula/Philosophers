#include "philo_two.h"

void	*my_thread(void *var)
{
	t_gnrl		*gnrl;
	t_threads	*philo;

	gnrl = get_struct(NULL);
	philo = (t_threads *)var;
	philo->t_limit = gnrl->time + gnrl->time_todie;
	dying_check(gnrl, philo);
	while (1)
	{
		eating(gnrl, philo);
		sem_post(gnrl->semaphore);
		sem_post(gnrl->semaphore);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, philo, SLEEP);
		sem_post(gnrl->lock_output);
		usleep(gnrl->time_tosleep * 1000);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, philo, THINK);
		sem_post(gnrl->lock_output);
	}
	return (NULL);
}

void	*must_die(void *var)
{
	t_threads	*philo;
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	philo = (t_threads *)var;
	while (1)
	{
		sem_wait(gnrl->lock_mustdie);
		if (gnrl->n_must_eat == 0)
		{
			sem_wait(gnrl->lock_output);
			printf("DONE\n");
			sem_post(gnrl->lock);
			return (NULL);
		}
		sem_post(gnrl->lock_mustdie);
	}
}

void	dying_check(t_gnrl *gnrl, t_threads *philo)
{
	pthread_create(&philo->th, NULL, checker, philo);
	pthread_detach(philo->th);
	if (gnrl->n_must_eat > 0)
	{
		pthread_create(&philo->must_die, NULL, must_die, philo);
		pthread_detach(philo->must_die);
	}
}

void	start_threading(t_gnrl *gnrl, t_threads *philo)
{
	int	i;

	gnrl->time = time_now();
	sem_wait(gnrl->lock);
	philo = (t_threads *)malloc(sizeof(t_threads) * gnrl->num_philo);
	i = -1;
	while (++i < gnrl->num_philo)
		philo[i].index = i;
	i = -1;
	while (++i < gnrl->num_philo)
	{
		pthread_create(&gnrl->thread[i], NULL, my_thread, &philo[i]);
		pthread_detach(gnrl->thread[i]);
		usleep(100);
	}
	sem_wait(gnrl->lock);
}

int	main(int ac, char **av)
{
	t_gnrl		*gnrl;
	t_threads	*philo;

	gnrl = (t_gnrl *)malloc(sizeof(t_gnrl));
	philo = NULL;
	get_struct(gnrl);
	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (-1);
	}
	else
		if (parsing(gnrl, ac, av))
			return (-1);
	init_sem(gnrl);
	start_threading(gnrl, philo);
}
