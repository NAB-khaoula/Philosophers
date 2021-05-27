#include "philo_one.h"

void	display_msg(t_gnrl *gnrl, t_threads *philo, int status)
{
	if (status == FORK_LEFT)
		printf("%ld\t%d\thas taken a fork\n", \
		time_now() - gnrl->time, philo->index + 1);
	if (status == FORK_RIGHT)
		printf("%ld\t%d\thas taken a fork\n", \
		time_now() - gnrl->time, philo->index + 1);
	if (status == EAT)
		printf("%ld\t%d\tis eating\n", \
		time_now() - gnrl->time, philo->index + 1);
	if (status == SLEEP)
		printf("%ld\t%d\tis sleeping\n", \
		time_now() - gnrl->time, philo->index + 1);
	if (status == THINK)
		printf("%ld\t%d\tis thinking\n", \
		time_now() - gnrl->time, philo->index + 1);
	if (status == DIED)
		printf("%ld\t%d\tdied\n", \
		time_now() - gnrl->time, philo->index + 1);
}
