#include "philo_two.h"

void	*checker(void *philo)
{
	t_gnrl		*gnrl;
	t_threads	*philosopher;

	gnrl = get_struct(NULL);
	philosopher = (t_threads *)philo;
	while (1)
	{
		sem_wait(gnrl->lock_death);
		if (time_now() > philosopher->t_limit)
		{
			sem_wait(gnrl->lock_output);
			display_msg(gnrl, philo, DIED);
			sem_post(gnrl->lock);
			return (NULL);
		}
		sem_post(gnrl->lock_death);
		usleep(500);
	}
}
