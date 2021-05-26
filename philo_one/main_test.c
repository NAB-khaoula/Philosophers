#include "philo_one.h"

pthread_mutex_t mutex;
int j = 0;

void	*print_thread()
{
	pthread_mutex_lock(&mutex);
	printf("hello I'm thread number %d\n", j);
	j++;
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int		main(int ac, char **av)
{
	int i;
	int *arg;
	pthread_t *thread;

	pthread_mutex_init(&mutex, NULL);
	arg = (int *)malloc(sizeof(int) *  5);
	i = 0;
	if (ac == 5 || ac == 6)
	{
		while(av[++i])
		{
			if (is_num(av[i]))
				arg[i - 1] = ft_atoi(av[i]);
			else
			{
				printf("Arguments are not correct!\n");
				break;
			}
		}
		if (ac != 6)
			arg[i - 1] = -1;
	}
	else if (ac < 5)
		printf("not enough arguments\n");
	else
		printf("too many arguments\n");
	thread = (pthread_t *)malloc(sizeof(pthread_t) * arg[1]);
	// printf("%d\n", arg[0]);
	i = arg[0];
	while (i > 0)
	{
		if (pthread_create(&thread[j], NULL, print_thread, NULL) != 0)
		{
			puts("fail to creat\n");
		}
		pthread_detach(thread[j]);
		i--;
	}
	j = 0;
	i = arg[0];
	pthread_mutex_destroy(&mutex);
	return (0);
}