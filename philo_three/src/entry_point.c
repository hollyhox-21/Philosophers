/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:38:52 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/17 17:58:52 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

void	ft_worker_death(t_philo *philo)
{
	int	i;

	i = -1;
	sem_wait(philo->table->locker);
	sem_wait(philo->table->print);
	*philo->flag_die = 1;
	if (philo->table->count_eat == -1)
		ft_print_msg(philo, " \x1B[91mdied\033[0m\n");
	sem_post(philo->table->death);
	exit(1);
}

void	*ft_counter_die(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (ft_calc_ts(p->table) - p->when_eat > p->table->time_to_die)
			break ;
		usleep(20);
	}
	ft_worker_death(p);
	return (SUCCESS);
}

void	start_routin(void *atr)
{
	t_philo		*p;
	pthread_t	thread_die;

	p = (t_philo *)atr;
	pthread_create(&thread_die, NULL, ft_counter_die, (void *)p);
	while (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		ft_start_eat(p);
		ft_start_sleep(p);
		ft_start_think(p);
	}
	pthread_join(thread_die, NULL);
	exit(0);
}

int	ft_create_processes(t_table *table, t_philo *philos)
{
	pid_t	*philo;
	int		i;
	int		status;

	philo = (pid_t *)malloc(sizeof(pid_t) * table->count_philos);
	if (!philo)
		return (0);
	i = -1;
	while (++i < table->count_philos)
	{
		philo[i] = fork();
		if (philo[i] == -1)
			return (-1);
		else if (!philo[i])
			start_routin(&philos[i]);
	}
	sem_wait(table->death);
	i = -1;
	while (++i < table->count_philos)
		kill(philo[i], SIGKILL);
	waitpid(0, &status, WUNTRACED);
	return (0);
}
