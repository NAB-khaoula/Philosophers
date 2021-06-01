#include "./philo_three.h"

void	*checker(void *i)
{
	t_gnrl	*gnrl;

	gnrl = (t_gnrl *)i;
	while (1)
	{
		sem_wait(gnrl->lock_death);
		if (time_now() > gnrl->t_limit)
		{
			sem_wait(gnrl->lock_output);
			display_msg(gnrl, gnrl->index, DIED);
			sem_post(gnrl->lock);
			return (NULL);
		}
		sem_post(gnrl->lock_death);
		usleep(500);
	}
}

void	*must_die(void *var)
{
	t_gnrl	*gnrl;
	int		nb_eat;
	int		i;

	nb_eat = 0;
	i = 0;
	gnrl = (t_gnrl *)var;
	while (1)
	{
		sem_wait(gnrl->must_die);
		nb_eat++;
		if (nb_eat == gnrl->num_philo)
		{
			sem_wait(gnrl->lock_output);
			sem_post(gnrl->lock);
			return (NULL);
		}
	}
	return (NULL);
}

void	dying_check(void)
{
	pthread_t	philo;
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	pthread_create(&philo, NULL, checker, gnrl);
	pthread_detach(philo);
}

void	check_n_eating(void)
{
	t_gnrl		*gnrl;
	pthread_t	philo;

	gnrl = get_struct(NULL);
	if (gnrl->n_must_eat > 0)
	{
		pthread_create(&philo, NULL, must_die, gnrl);
		pthread_detach(philo);
	}
}
