#include "philo_one.h"

void	*checker(void *philo)
{
	t_gnrl		*gnrl;
	t_threads	*philosopher;

	gnrl = get_struct(NULL);
	philosopher = (t_threads *)philo;
	while (1)
	{
		pthread_mutex_lock(&gnrl->lock_death);
		if (time_now() > philosopher->t_limit)
		{
			pthread_mutex_lock(&gnrl->lock_output);
			printf("%ld\t%d\tdied\n", time_now() - gnrl->time, \
			philosopher->index + 1);
			pthread_mutex_unlock(&gnrl->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&gnrl->lock_death);
		usleep(500);
	}
}

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
			pthread_mutex_unlock(&gnrl->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&gnrl->lock_mustdie);
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

void	lock_fork(t_gnrl *gnrl, t_threads *philo)
{
	pthread_mutex_lock(&gnrl->chopsticks_lock[philo->index]);
	lock_msg(gnrl->lock_output, gnrl, philo, FORK_RIGHT);
	pthread_mutex_lock(&gnrl->chopsticks_lock[(philo->index + 1) \
	% gnrl->num_philo]);
	lock_msg(gnrl->lock_output, gnrl, philo, FORK_RIGHT);
}

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
		lock_fork(gnrl, philo);
		lock_msg(gnrl->lock_output, gnrl, philo, EAT);
		philo->t_limit = time_now() + gnrl->time_todie;
		if (gnrl->n_must_eat > 0)
			gnrl->n_must_eat--;
		usleep(gnrl->time_toeat * 1000);
		pthread_mutex_unlock(&gnrl->chopsticks_lock[philo->index]);
		pthread_mutex_unlock(&gnrl->chopsticks_lock[(philo->index + 1) \
		% gnrl->num_philo]);
		lock_msg(gnrl->lock_output, gnrl, philo, SLEEP);
		usleep(gnrl->time_tosleep * 1000);
		lock_msg(gnrl->lock_output, gnrl, philo, THINK);
	}
	return (NULL);
}
