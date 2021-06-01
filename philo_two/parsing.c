#include "philo_two.h"

t_gnrl	*token(char **av)
{
	int		i;
	t_gnrl	*gnrl;

	i = 0;
	gnrl = get_struct(NULL);
	while (av[++i])
	{
		if (!(is_num(av[i])))
		{
			printf("the argument must be a positive number!\n");
			exit(0);
		}
	}
	gnrl->time_todie = ft_atoi(av[2]);
	gnrl->time_toeat = ft_atoi(av[3]);
	gnrl->time_tosleep = ft_atoi(av[4]);
	return (gnrl);
}

int	parsing(t_gnrl *gnrl, int ac, char **av)
{
	gnrl->num_philo = ft_atoi(av[1]);
	if (gnrl->num_philo > 200 || gnrl->num_philo < 2)
	{
		printf("Philosopher number must be greater than 2 and less than 200\n");
		return (1);
	}
	gnrl = token(av);
	if (gnrl->time_todie < 60 || \
	gnrl->time_toeat < 60 || gnrl->time_tosleep < 60)
	{
		printf("time to die, to sleep and to eat must be more than 60ms\n");
		return (1);
	}
	if (ac == 6)
	{
		if (!is_num(av[5]))
		{
			printf("last argument must be a positive number!\n");
			return (1);
		}
		gnrl->n_must_eat = ft_atoi(av[5]) * gnrl->num_philo;
	}
	else
		gnrl->n_must_eat = -1;
	return (0);
}
