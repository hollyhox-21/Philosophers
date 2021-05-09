#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "ft_atoi.c"
#define SUCCESS 0
//#define MS 1000

typedef struct	s_table {
	int				count_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int 			count_eat;
	pthread_mutex_t	*forks;
	int				who_is_die;
}				t_table;

typedef struct	s_philo {
	int				numb;
	int				when_eat;
	int				when_sleep;
	int 			when_thinking;
	int				when_get_forks;
	int				when_died;
	int 			*flag_die;
	struct s_table	*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	
}				t_philo;

void	ft_print_table_struct(t_table *table)
{
	printf("addr table\t\t%p\n", table);
	printf("count_philos\t%d\n", table->count_philos);
	printf("time_to_sleep\t%d\n", table->time_to_sleep);
	printf("time_to_eat\t\t%d\n", table->time_to_eat);
	printf("time_to_die\t\t%d\n", table->time_to_die);
	printf("count_eat\t\t%d\n", table->count_eat);
	printf("forks\t\t\t[ ");
	for (int i = 0; i < table->count_philos; ++i) {
		printf("%d--->%p ", i + 1, &table->forks[i]);
	}
	printf("]\nwho_is_die\t\t%d\n", table->who_is_die);
}

void	ft_print_philo_struct(t_philo *philo)
{
	printf("-----\n");
	printf("numb\t\t\t%d\n", philo->numb);
//	printf("when_eat\t\t%d\n", philo->when_eat);
//	printf("when_sleep\t\t%d\n", philo->when_sleep);
//	printf("when_thinking\t%d\n", philo->when_thinking);
//	printf("when_get_forks\t%d\n", philo->when_get_forks);
//	printf("when_died\t\t%d\n", philo->when_died);
//	printf("flag_die\t\t%d\n", *philo->flag_die);
//	printf("addr table\t\t%p\n", philo->table);
	printf("addr LEFT_fork\t%p\n", philo->left_fork);
	printf("addr RIGHT_fork\t%p\n", philo->right_fork);
}

void	ft_culc_time(int count_time)
{

	struct timeval	begin_era;
	struct timeval	current_time;
	static long int		time_stamp = 0;
	
	gettimeofday(&begin_era, NULL);
	gettimeofday(&current_time, NULL);
	while (((current_time.tv_sec * 1000000 + current_time.tv_usec) - (begin_era.tv_sec * 1000000 + begin_era.tv_usec)) < count_time * 1000)
		gettimeofday(&current_time, NULL);
	time_stamp += count_time;
	printf("%ld ", time_stamp);
}

void 	ft_start_sleep(t_philo *philo)
{
	ft_culc_time(philo->table->time_to_sleep);
	printf("ms %d is sleeping\n", philo->numb);
}

void	ft_start_eat(t_philo *philo)
{
	if (philo->numb % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	ft_culc_time(philo->table->time_to_eat);
	printf("ms %d is eating\n", philo->numb);
	if (philo->numb % 2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*start_routin(void *atr)
{
	t_philo *thread_philo;
	
	thread_philo = (t_philo *)atr;
	while(!thread_philo->table->who_is_die)
	{
		
		ft_start_eat(thread_philo);
		ft_start_sleep(thread_philo);
		printf("%d ms %d is thinking\n", thread_philo->numb);
	}
	return (SUCCESS);
}

void 	ft_give_forks(t_table *table, t_philo *philos)
{
	int	i;
	
	i = 0;
	while(i < table->count_philos)
	{
		if (philos[i].numb != table->count_philos)
		{
			philos[i].left_fork = &table->forks[i];
			philos[i].right_fork = &table->forks[i + 1];
		}
		else
		{
			philos[i].left_fork = &table->forks[i];
			philos[i].right_fork = &table->forks[0];
		}
		i++;
	}
}

t_philo	*ft_creat_philo(t_table *table)
{
	t_philo	*philos;
	int		i;
	
	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * table->count_philos);
	while (i < table->count_philos)
	{
		philos[i].numb = i + 1;
		philos[i].when_eat = 0;
		philos[i].when_sleep = 0;
		philos[i].when_thinking = 0;
		philos[i].when_get_forks = 0;
		philos[i].when_died = 0;
		philos[i].flag_die = &table->who_is_die;
		philos[i].table = table;
		ft_give_forks(table, philos);
		i++;
	}
	return (philos);
}

t_table	*ft_create_table(char **av)
{
	t_table	*table;
	
	table = (t_table *) malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->count_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->count_eat = ft_atoi(av[5]);
	else
		table->count_eat = 0;
	table->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * table->count_philos);
	if (!table->forks)
		return (NULL);
	table->who_is_die = 0;
	return (table);
}

int 	ft_create_threads(t_table *table, t_philo *philos)
{
	pthread_t	thread_philo[table->count_philos];
	int			i;
	int			thread_status;
	i = 0;
	while (i < table->count_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_create(&thread_philo[i], NULL, start_routin, &philos[i]);
		i++;
	}
	i = 0;
	while (i < table->count_philos)
	{
		pthread_join(thread_philo[i], (void **)&thread_status);
		printf("%d\n", thread_status);
		i++;
	}
	return (0);
}

int		ft_start_simul(char **av)
{
	t_table	*table;
	t_philo	*philos;

	table = ft_create_table(av);
	philos = ft_creat_philo(table);
	if (ft_create_threads(table, philos))
		return (1);
	
//	PRINT STUCT
//	ft_print_table_struct(table);
//	for (int i = 0; i < table->count_philos; ++i)
//		ft_print_philo_struct(&philos[i]);
//	-----------
	return (0);
}

int main(int ac, char **av) {
	if (ac == 5 || ac == 6)
	{
		if (ft_start_simul(av))
			return (0);
	}
	else
		printf("Incorrect count args\n");
	return 0;
}
