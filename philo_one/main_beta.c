
#include "philo_one.h"


long		time_now(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    *my_thread(void *var)
{
	t_gnrl		*gnrl;
	// t_threads	*philo;
	// int			sleep_time;
	int			time;
	int				philosopher;

	gnrl = get_struct(NULL);
	philosopher = (int)var;
	// printf ("Philosopher %d is done thinking and now ready to eat.\n", philosopher);
	while (1)
	{
		gnrl->time_ms = time_now() - gnrl->time;
		time = gnrl->time_ms + gnrl->time_toeat;
		printf("%ld %c has taken a fork\n", gnrl->time_ms, gnrl->philosopher[philosopher]);
		pthread_mutex_lock(&gnrl->chopsticks_lock[philosopher]);
		pthread_mutex_lock(&gnrl->chopsticks_lock[(philosopher + 1) % gnrl->num_philo]);
		printf("%ld %c is eating\n", gnrl->time_ms, gnrl->philosopher[philosopher]);
		// usleep(gnrl->time_toeat);
		pthread_mutex_unlock(&gnrl->chopsticks_lock[philosopher]);
		pthread_mutex_unlock(&gnrl->chopsticks_lock[(philosopher + 1) % gnrl->num_philo]);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_gnrl		gnrl;
	t_threads	*philo;

	get_struct(&gnrl);
	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (-1);
	}
	else
	{
		gnrl.num_philo = ft_atoi(av[1]);
		gnrl.time_todie = ft_atoi(av[2]) * 1000;
		gnrl.time_toeat = ft_atoi(av[3]) * 1000;
		gnrl.time_tosleep = ft_atoi(av[4]) * 1000;
		if (ac == 6)
			gnrl.n_must_eat = ft_atoi(av[5]) * 1000;
		else
			gnrl.n_must_eat = -1;
	}
	gnrl.thread = (pthread_t *)malloc(sizeof(pthread_t) * gnrl.num_philo);
	gnrl.philosopher = (char *)malloc(gnrl.num_philo);
	// philo = (t_threads *)malloc(sizeof(t_threads) * gnrl.num_philo);
	gnrl.chopsticks_lock = (pthread_mutex_t *)malloc(gnrl.num_philo);
	pthread_mutex_init(&gnrl.lock, NULL);
	gnrl.index = -1;
	while (++gnrl.index < gnrl.num_philo)
	{
		pthread_mutex_init(&gnrl.chopsticks_lock[gnrl.index], NULL);
		gnrl.philosopher[gnrl.index] = gnrl.index + 49;
	}
	gnrl.index = 0;
	gnrl.time = time_now();
	gnrl.time_ms = time_now() - gnrl.time;
	gnrl.philosopher[gnrl.num_philo] = 0;
	pthread_mutex_lock(&gnrl.lock);
	while (gnrl.index < gnrl.num_philo)
	{
		pthread_create(&gnrl.thread[gnrl.index], NULL, my_thread, (void *)gnrl.index);
		pthread_detach(gnrl.thread[gnrl.index]);
		gnrl.index++;
	}
	// gnrl.index = 0;
	// while (gnrl.index < gnrl.num_philo)
	// {
	// 	pthread_join(gnrl.thread[gnrl.index], NULL);
	// 	gnrl.index++;
	// }
	pthread_mutex_lock(&gnrl.lock);
	return (0);
}