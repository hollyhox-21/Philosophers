/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:01:38 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/17 18:02:33 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# define SUCCESS 0

typedef struct s_table {
	long int		begin_era;
	struct timeval	start_t;
	int				count_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				count_eat;
	sem_t			*print;
	sem_t			*waiter;
	sem_t			*locker;
	sem_t			*death;
	sem_t			*forks;
	int				who_is_die;
}					t_table;

typedef struct s_philo {
	int				numb;
	int				when_eat;
	int				count_eat;
	int				*flag_die;
	struct s_table	*table;
}					t_philo;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c);

void	ft_start_think(t_philo *p);
void	ft_start_sleep(t_philo *p);
void	ft_start_eat(t_philo *phil);

void	ft_print_msg(t_philo *philo, char *msg);
int		ft_calc_ts(t_table *table);
void	ft_wait_time(const int count_time);
void	ft_free(t_philo *philos, t_table *table);

t_philo	*ft_creat_philo(t_table *table);
int		ft_init_sem(t_table *t);
t_table	*ft_create_table(char **av);

void	ft_worker_death(t_philo *philo);
void	*ft_counter_die(void *arg);
void	*ft_check_kill(void *arg);
void	start_routin(void *atr);
int		ft_create_processes(t_table *table, t_philo *philos);

int		ft_validation(char **av);

#endif
