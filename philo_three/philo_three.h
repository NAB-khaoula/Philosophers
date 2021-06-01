#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <signal.h>
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
	long			t_limit;
	int				index;
	sem_t			*semaphore;
	sem_t			*must_die;
	sem_t			*lock;
	sem_t			*lock_output;
	sem_t			*lock_death;
	sem_t			*lock_test;
	sem_t			*lock_mustdie;
}					t_gnrl;

long	time_now(void);
t_gnrl	*get_struct(t_gnrl *gnrl);
int		ft_atoi(const char *str);
int		parsing(t_gnrl *gnrl, int ac, char **av);
void	*my_process(void);
void	display_msg(t_gnrl *gnrl, int i, int status);
void	*must_die(void *var);
void	*must_die(void *var);
void	*checker(void *i);
void	init_sem(void);
void	check_n_eating(void);
void	dying_check(void);
int		is_num(char *c);
void	start_forking(t_gnrl *gnrl);

#endif