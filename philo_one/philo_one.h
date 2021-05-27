#ifndef PHILO_ONE_H
# define	PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# define FORK_LEFT 1
# define FORK_RIGHT 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIED 6
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
long	time_now(void);
void	*checker(void *philo);
void	*must_die(void *var);
void    *my_thread(void *var);
void	display_msg(t_gnrl *gnrl, t_threads *philo, int status);

#endif