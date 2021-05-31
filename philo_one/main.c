#include "philo_one.h"

void	init_mutex(t_gnrl *gnrl)
{
	gnrl->thread = (pthread_t *)malloc(sizeof(pthread_t) * gnrl->num_philo);
	gnrl->chopsticks_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* gnrl->num_philo);
	pthread_mutex_init(&gnrl->lock, NULL);
	pthread_mutex_init(&gnrl->lock_death, NULL);
	pthread_mutex_init(&gnrl->lock_mustdie, NULL);
	pthread_mutex_init(&gnrl->lock_output, NULL);
}

void	start_threading(t_gnrl *gnrl, t_threads *philo)
{
	int	i;

	i = -1;
	gnrl->time = time_now();
	pthread_mutex_lock(&gnrl->lock);
	philo = (t_threads *)malloc(sizeof(t_threads) * gnrl->num_philo);
	i = -1;
	while (++i < gnrl->num_philo)
	{
		pthread_mutex_init(&gnrl->chopsticks_lock[i], NULL);
		philo[i].index = i;
	}
	i = -1;
	while (++i < gnrl->num_philo)
	{
		pthread_create(&gnrl->thread[i], NULL, my_thread, &philo[i]);
		pthread_detach(gnrl->thread[i]);
		usleep(100);
	}
	pthread_mutex_lock(&gnrl->lock);
}

int	main(int ac, char **av)
{
	t_gnrl		*gnrl;
	t_threads	*philo;

	gnrl = (t_gnrl *)malloc(sizeof(t_gnrl));
	get_struct(gnrl);
	philo = NULL;
	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (-1);
	}
	else
		if (parsing(gnrl, ac, av))
			return (-1);
	init_mutex(gnrl);
	start_threading(gnrl, philo);
	free(philo);
	free(gnrl->chopsticks_lock);
	free(gnrl->thread);
	return (0);
}
