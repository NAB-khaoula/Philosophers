#include "philo_one.h"

void	*must_die(void *var)
{
	t_threads	*philo;
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	philo = (t_threads *)var;
	while (1)
	{
		pthread_mutex_lock(&gnrl->lock_mustdie);
		if (gnrl->n_must_eat == 0)
		{
			pthread_mutex_lock(&gnrl->lock_output);
			printf("DONE");
			pthread_mutex_unlock(&gnrl->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&gnrl->lock_mustdie);
	}
}

void    *my_thread(void *var)
{
    //some code;
	t_gnrl		*gnrl;
	t_threads	*philo;

	gnrl = get_struct(NULL);
	philo = (t_threads *)var;
	philo->t_limit = gnrl->time + gnrl->time_todie;
	pthread_create(&philo->th, NULL, checker, philo);
	pthread_detach(philo->th);
	if (gnrl->n_must_eat > 0)
	{
		pthread_create(&philo->must_die, NULL, must_die, philo);
		pthread_detach(philo->must_die);
	}
	while (1)
	{
		pthread_mutex_lock(&gnrl->chopsticks_lock[philo->index]);

		pthread_mutex_lock(&gnrl->lock_output);
		printf("%ld\t%d\thas taken a fork\n", time_now() - gnrl->time, philo->index + 1);
		pthread_mutex_unlock(&gnrl->lock_output);

		pthread_mutex_lock(&gnrl->chopsticks_lock[(philo->index + 1) % gnrl->num_philo]);

		pthread_mutex_lock(&gnrl->lock_output);
		printf("%ld\t%d\thas taken a fork\n", time_now() - gnrl->time, philo->index + 1);
		pthread_mutex_unlock(&gnrl->lock_output);

		pthread_mutex_lock(&gnrl->lock_output);
		philo->t_limit = time_now() + gnrl->time_todie;
		printf("%ld\t%d\tis eating\n", time_now() - gnrl->time, philo->index + 1);
		if (gnrl->n_must_eat > 0)
			gnrl->n_must_eat--;
		pthread_mutex_unlock(&gnrl->lock_output);
		
		usleep(gnrl->time_toeat * 1000);

		pthread_mutex_unlock(&gnrl->chopsticks_lock[philo->index]);
		pthread_mutex_unlock(&gnrl->chopsticks_lock[(philo->index + 1) % gnrl->num_philo]);

		pthread_mutex_lock(&gnrl->lock_output);
		printf("%ld\t%d\tis sleeping\n", time_now() - gnrl->time, philo->index + 1);
		pthread_mutex_unlock(&gnrl->lock_output);
	
		usleep(gnrl->time_tosleep * 1000);

		pthread_mutex_lock(&gnrl->lock_output);
		printf("%ld\t%d\tis thinking\n", time_now() - gnrl->time, philo->index + 1);
		pthread_mutex_unlock(&gnrl->lock_output);
	}
	return (NULL);
}

int main(int ac, char **av)
{
    t_gnrl		*gnrl;
	t_threads	*philo;

	gnrl = (t_gnrl *)malloc(sizeof(t_gnrl));
	get_struct(gnrl);
	gnrl->time = time_now();
	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (-1);
	}
	else
	{
		gnrl->num_philo = ft_atoi(av[1]);
		if (gnrl->num_philo > 200)
		{
			printf("Philosopher number must be less than 200\n");
			return (-1);
		}
		gnrl->time_todie = ft_atoi(av[2]);
		gnrl->time_toeat = ft_atoi(av[3]);
		gnrl->time_tosleep = ft_atoi(av[4]);
		if (gnrl->time_todie < 60 || gnrl->time_toeat < 60 || gnrl->time_tosleep < 60)
		{
			printf("time to die, to sleep and to eat must be more than 60ms\n");
			return (-1);
		}
		if (ac == 6)
			gnrl->n_must_eat = ft_atoi(av[5]) * gnrl->num_philo;
		else
			gnrl->n_must_eat = -1;
	}
	gnrl->thread = (pthread_t *)malloc(sizeof(pthread_t) * gnrl->num_philo);
    philo = (t_threads *)malloc(sizeof(t_threads) * gnrl->num_philo);
    gnrl->chopsticks_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * gnrl->num_philo);
    pthread_mutex_init(&gnrl->lock, NULL);
    pthread_mutex_init(&gnrl->lock_death, NULL);
    pthread_mutex_init(&gnrl->lock_mustdie, NULL);
    pthread_mutex_init(&gnrl->lock_output, NULL);
	int i = -1;
	while (++i< gnrl->num_philo)
	{
		pthread_mutex_init(&gnrl->chopsticks_lock[i], NULL);
		philo[i].index = i;
	}
    i = -1;
	pthread_mutex_lock(&gnrl->lock);
    while (++i < gnrl->num_philo)
	{
		pthread_create(&gnrl->thread[i], NULL, my_thread, &philo[i]);
		pthread_detach(gnrl->thread[i]);
		usleep(100);
	}
	pthread_mutex_lock(&gnrl->lock);
	return (0);
}