#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
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
	sem_t			*semaphore;
	sem_t			*lock;
	sem_t			*lock_output;
	sem_t			*lock_death;
	sem_t			*lock_mustdie;
}					t_gnrl;

typedef struct s_process
{
	long	t_limit;
	int		process;
}			t_process;

long	time_now(void);
t_gnrl	*get_struct(t_gnrl *gnrl);
int		ft_atoi(const char *str);
int		parsing(t_gnrl *gnrl, int ac, char **av);
void	*my_process(t_process *process);
void	display_msg(t_gnrl *gnrl, int i, int status);
void	*must_die(void *var);

#endif