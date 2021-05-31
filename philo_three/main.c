#include "philo_three.h"

void	init_sem(t_gnrl *gnrl)
{
	sem_unlink("semaphore");
	sem_unlink("lock");
	sem_unlink("lock_output");
	sem_unlink("lock_death");
	sem_unlink("lock_mustdie");
	gnrl->semaphore = sem_open("semaphore", O_CREAT, 777, gnrl->num_philo);
	gnrl->lock = sem_open("lock", O_CREAT, 777, 1);
	gnrl->lock_output = sem_open("lock_output", O_CREAT, 777, 1);
	gnrl->lock_death = sem_open("lock_death", O_CREAT, 777, 1);
	gnrl->lock_mustdie = sem_open("lock_mustdie", O_CREAT, 777, 1);
}

void	*checker(void *i)
{
	t_gnrl	*gnrl;
	t_process	*process;

	gnrl = get_struct(NULL);
	process = (t_process *)i;
	while (1)
	{
		sem_wait(gnrl->lock_death);
		if (time_now() > process->t_limit)
		{
			sem_wait(gnrl->lock_output);
			display_msg(gnrl, process->process, DIED);
			sem_post(gnrl->lock);
			return (NULL);
		}
		sem_post(gnrl->lock_death);
	}
}

void	*must_die(void *var)
{
	t_process	*process;
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	process = (t_process *)var;
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

void	dying_check(t_gnrl *gnrl, t_process *process)
{
	pthread_t	philo;
	gnrl = get_struct(NULL);

	pthread_create(&philo, NULL, checker, process);
	pthread_detach(philo);
	if (gnrl->n_must_eat > 0)
	{
		pthread_create(&philo, NULL, must_die, process);
		pthread_detach(philo);
	}
}

void	eating(t_gnrl *gnrl, t_process *process)
{
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, process->process, FORK_LEFT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->semaphore);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, process->process, FORK_RIGHT);
	sem_post(gnrl->lock_output);
	sem_wait(gnrl->lock_output);
	display_msg(gnrl, process->process, EAT);
	sem_post(gnrl->lock_output);
	process->t_limit = time_now() + gnrl->time_todie;
	if (gnrl->n_must_eat > 0)
		gnrl->n_must_eat--;
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

void	*my_process(t_process *process)
{
	t_gnrl		*gnrl;

	gnrl = get_struct(NULL);
	process->t_limit = gnrl->time + gnrl->time_todie;
	dying_check(gnrl, process);
	while (1)
	{
		eating(gnrl, process);
		sem_post(gnrl->semaphore);
		sem_post(gnrl->semaphore);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, process->process, SLEEP);
		sem_post(gnrl->lock_output);
		usleep(gnrl->time_tosleep * 1000);
		sem_wait(gnrl->lock_output);
		display_msg(gnrl, process->process, THINK);
		sem_post(gnrl->lock_output);
	}
	return (NULL);
}

void	start_forking(t_gnrl *gnrl)
{
	int i;
	int *pid;
	t_process	*process;

	pid = (int *)malloc(sizeof(int) * gnrl->num_philo);
	process = (t_process *)malloc(sizeof(t_process) * gnrl->num_philo);
	i = -1;
	gnrl->time = time_now();
	sem_wait(gnrl->lock);
	while (++i < gnrl->num_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			process[i].process = i;
			my_process(&process[i]);
			exit(0);
		}
		usleep(100);
	}
	sem_wait(gnrl->lock);
}
int main(int ac, char **av)
{
	t_gnrl  *gnrl;

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
	init_sem(gnrl);
	start_forking(gnrl);
}
