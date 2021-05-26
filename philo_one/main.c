#include "philo_one.h"
#include <sys/time.h>


long		time_now(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*print_thread(void	*var)
{
	int a;
	t_gnrl	*gnrl;

	gnrl = (t_gnrl *)var;
	a = gnrl->index;
	while (gnrl->time_ms < gnrl->time_todie)
	{
		if (!gnrl->chopsticks[a] && !gnrl->chopsticks[a + 1])
		{
			gnrl->time_ms = time_now() - gnrl->time;
			printf("%ld %c has taken a fork\n", gnrl->time_ms, gnrl->philosopher[a]);
			while (gnrl->time_ms < gnrl->time_toeat)
			{
				gnrl->time_ms = time_now() - gnrl->time;
				printf("%ld %c is eating\n", gnrl->time_ms, gnrl->philosopher[a]);
				gnrl->chopsticks[a] = 1;
				gnrl->chopsticks[a + 1] = 1;
			}
		}
		// gnrl->last_meal =  0;
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_gnrl gnrl;

	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (0);
	}
	else
	{
		gnrl.num_philo = ft_atoi(av[1]);
		gnrl.time_todie = ft_atoi(av[2]);
		gnrl.time_toeat = ft_atoi(av[3]) * 1000;
		gnrl.time_tosleep = ft_atoi(av[4]);
		if (ac == 6)
			gnrl.n_must_eat = ft_atoi(av[5]);
		else
			gnrl.n_must_eat = -1;
	}
	// gnrl.last_meal = 0;
	gnrl.thread = (pthread_t *)malloc(sizeof(pthread_t) * gnrl.num_philo);
	gnrl.philosopher = (char *)malloc(gnrl.num_philo + 1);
	gnrl.chopsticks = (int *)malloc(gnrl.num_philo);
	pthread_mutex_init(&gnrl.lock, NULL);
	gnrl.index = 0;
	// gnrl.i = 0;
	gnrl.time = time_now();
	gnrl.philosopher[gnrl.num_philo] = 0;
	pthread_mutex_lock(&gnrl.lock);
	while (gnrl.index < gnrl.num_philo)
	{
		gnrl.chopsticks[gnrl.index] = 0;
		gnrl.philosopher[gnrl.index] = gnrl.index + 49;
		pthread_create(&gnrl.thread[gnrl.index], NULL, print_thread, (void *)&gnrl);
		pthread_detach(gnrl.thread[gnrl.index]);
		gnrl.index++;
	}
	pthread_mutex_lock(&gnrl.lock);
	return (0);
}
