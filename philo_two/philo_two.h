#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# define FORK_LEFT 1
# define FORK_RIGHT 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIED 6

typedef struct s_gnrl
{
	int				num_philo;
	int				time_todie;
	int				time_toeat;
	int				time_tosleep;
	int				n_must_eat;
	long			time;
	pthread_t		*thread;
	sem_t			*semaphore;
	sem_t			*lock;
	sem_t			*lock_output;
	sem_t			*lock_death;
	sem_t			*lock_mustdie;
}					t_gnrl;

typedef struct s_threads
{
	int				index;
	pthread_t		th;
	pthread_t		must_die;
	long			t_limit;
}					t_threads;

int		ft_atoi(const char *str);
t_gnrl	*get_struct(t_gnrl *gnrl);
int		is_num(char *c);
long	time_now(void);
int		parsing(t_gnrl *gnrl, int ac, char **av);
void	display_msg(t_gnrl *gnrl, t_threads *philo, int status);
void	*checker(void *philo);
void	*my_thread(void *var);
void	dying_check(t_gnrl *gnrl, t_threads *philo);
void	start_threading(t_gnrl *gnrl, t_threads *philo);
void	*must_die(void *var);
void	init_sem(t_gnrl *gnrl);
void	eating(t_gnrl *gnrl, t_threads *philo);

#endif