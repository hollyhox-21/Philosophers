/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:05:31 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:35:16 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# define SUCCESS 0

typedef struct s_table {
	long int		begin_era;
	struct timeval	start_t;
	int				count_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				count_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	wait;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	int				who_is_die;
}					t_table;

typedef struct s_philo {
	int				numb;
	int				when_eat;
	int				count_eat;
	int				*flag_die;
	struct s_table	*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);

int		ft_calc_ts(t_table *table);
void	ft_wait_time(const int *count_time);
void	ft_free(t_philo *philos, t_table *table);
void	ft_print_msg(t_philo *philo, char *msg);

void	ft_start_think(t_philo *philo);
void	ft_start_sleep(t_philo *philo);
void	ft_start_eat(t_philo *philo);

void	*ft_counter_die(void *arg);
void	*start_routin(void *atr);

void	ft_give_forks(t_table *table, t_philo *philos);
t_philo	*ft_creat_philo(t_table *table);
t_table	*ft_create_table(char **av, int i);

int		ft_create_threads(t_table *table, t_philo *philos);
#endif
