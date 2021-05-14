/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:05:10 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:39 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

void	ft_start_think(t_philo *p)
{
	if (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		ft_print_msg(p, " \x1B[94mis thinking\033[0m\n");
	}
}

void	ft_start_sleep(t_philo *p)
{
	if (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		ft_print_msg(p, " \x1B[93mis sleeping\033[0m\n");
		ft_wait_time(&p->table->time_to_sleep);
	}
}

void	ft_start_eat(t_philo *phil)
{
	if (phil->numb % 2)
	{
		pthread_mutex_lock(phil->left_fork);
		ft_print_msg(phil, " \x1B[95mhas taken a fork LEFT\033[0m\n");
		pthread_mutex_lock(phil->right_fork);
		ft_print_msg(phil, " \x1B[95mhas taken a fork RIGHT\033[0m\n");
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		ft_print_msg(phil, " \x1B[95mhas taken a fork RIGHT\033[0m\n");
		pthread_mutex_lock(phil->left_fork);
		ft_print_msg(phil, " \x1B[95mhas taken a fork LEFT\033[0m\n");
	}
	if (!phil->table->who_is_die && phil->count_eat != phil->table->count_eat)
	{
		phil->when_eat = ft_calc_ts(phil->table);
		phil->count_eat++;
		ft_print_msg(phil, " \x1B[92mis eating\033[0m\n");
		ft_wait_time(&phil->table->time_to_eat);
	}
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}
