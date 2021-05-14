/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:05:42 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 19:25:51 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int	ft_calc_ts(t_table *table)
{
	struct timeval	current_time;
	long int		time;

	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec * 1000 + \
		current_time.tv_usec / 1000) - table->begin_era);
	return ((int)time);
}

void	ft_wait_time(const int *count_time)
{
	struct timeval	begin_time;
	struct timeval	current_time;
	long int		begin;
	long int		current;

	gettimeofday(&begin_time, NULL);
	begin = (begin_time.tv_sec * 1000 + begin_time.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
		if (current - begin < (long int)(*count_time))
		{
			usleep(20);
			continue ;
		}
		break ;
	}
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_res;
	char	*res;

	tmp_1 = ft_itoa(ft_calc_ts(philo->table));
	tmp_2 = " ms ";
	res = ft_strjoin(tmp_1, tmp_2);
	tmp_res = res;
	free(tmp_1);
	tmp_1 = ft_itoa(philo->numb);
	res = ft_strjoin(res, tmp_1);
	free(tmp_1);
	free(tmp_res);
	tmp_res = res;
	res = ft_strjoin(res, msg);
	free(tmp_res);
	pthread_mutex_lock(&philo->table->print);
	if (!*philo->flag_die)
		write(1, res, ft_strlen(res));
	free(res);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_free(t_philo *philos, t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->wait);
	pthread_mutex_destroy(&table->death);
	while (++i < table->count_philos)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
	free(table);
	free(philos);
}
