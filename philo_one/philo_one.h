#ifndef PHILO_ONE_H
# define	PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
 #include <sys/time.h>
# include <pthread.h>

typedef struct		s_gnrl
{
	int				num_philo;
	int				time_todie;
	int				time_toeat;
	int				time_tosleep;
	int				n_must_eat;
	pthread_mutex_t	*chopsticks_lock;
    int				index;
	int				i;
	long			time;
	char			*philosopher;
    pthread_mutex_t	lock;
    pthread_mutex_t	lock_output;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_mustdie;
	pthread_t		*thread;
	long			time_ms;
}					t_gnrl;

typedef struct		s_threads
{
	
	int				index;
	pthread_t		th;
	pthread_t		must_die;
	long			t_limit;
}					t_threads;

int		ft_atoi(const char *str);
int		is_num(char *c);
t_gnrl	*get_struct(t_gnrl *gnrl);

#endif