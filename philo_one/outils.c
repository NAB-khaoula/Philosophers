#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sgn;
	long	nb;

	i = 0;
	sgn = 1;
	nb = 0;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\f' \
	|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	nb = sgn * nb;
	return ((int)nb);
}

t_gnrl	*get_struct(t_gnrl *gnrl)
{
	static t_gnrl	*tmp;

	if (gnrl)
		tmp = gnrl;
	return (tmp);
}

int	is_num(char *c)
{
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		c++;
	}
	return (1);
}

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
