#include "philo_three.h"

void	eating(t_gnrl *gnrl)
{
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, gnrl->index, FORK_LEFT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, gnrl->index, FORK_RIGHT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, gnrl->index, EAT);
	sem_post(gnrl->lock_output);
	if (gnrl->n_must_eat > 0)
		gnrl->n_must_eat--;
	gnrl->t_limit = time_now() + gnrl->time_todie;
	usleep(gnrl->time_toeat * 1000);
}

void	display_msg(t_gnrl *gnrl, int i, int status)
{
	if (status == FORK_LEFT)
		printf("%ld\t%d\thas taken a fork\n", \
		time_now() - gnrl->time, i + 1);
	if (status == FORK_RIGHT)
		printf("%ld\t%d\thas taken a fork\n", \
		time_now() - gnrl->time, i + 1);
	if (status == EAT)
		printf("%ld\t%d\tis eating\n", \
		time_now() - gnrl->time, i + 1);
	if (status == SLEEP)
		printf("%ld\t%d\tis sleeping\n", \
		time_now() - gnrl->time, i + 1);
	if (status == THINK)
		printf("%ld\t%d\tis thinking\n", \
		time_now() - gnrl->time, i + 1);
	if (status == DIED)
		printf("%ld\t%d\tdied\n", \
		time_now() - gnrl->time, i + 1);
}

void	*my_process(void)
{
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	gnrl->t_limit = gnrl->time + gnrl->time_todie;
	dying_check();
	while (1)
	{
		eating(gnrl);
		if (gnrl->n_must_eat == 0)
			sem_post(gnrl->must_die);
		sem_post(gnrl->semaphore);
		sem_post(gnrl->semaphore);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, gnrl->index, SLEEP);
		sem_post(gnrl->lock_output);
		usleep(gnrl->time_tosleep * 1000);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, gnrl->index, THINK);
		sem_post(gnrl->lock_output);
	}
	return (NULL);
}

void	start_forking(void)
{
	int			i;
	int			*pid;
	t_gnrl		*gnrl;

	i = -1;
	gnrl = get_struct(NULL);
	pid = (int *)malloc(sizeof(int) * gnrl->num_philo);
	gnrl->time = time_now();
	sem_wait(gnrl->lock);
	check_n_eating();
	while (++i < gnrl->num_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			gnrl->index = i;
			my_process();
			exit(0);
		}
		usleep(100);
	}
	i = -1;
	sem_wait(gnrl->lock);
	while (++i < gnrl->num_philo)
		kill(pid[i], SIGKILL);
}

int	main(int ac, char **av)
{
	t_gnrl	*gnrl;

	gnrl = (t_gnrl *)malloc(sizeof(t_gnrl));
	get_struct(gnrl);
	if (ac != 5 && ac != 6)
	{
		printf("Arguments are not correct\n");
		return (-1);
	}
	else
		if (parsing(gnrl, ac, av))
			return (-1);
	init_sem();
	start_forking();
	return (0);
}
