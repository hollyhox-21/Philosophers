#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "ft_atoi.c"
#define SUCCESS 0
#define BRIGHT_BLACK ("\x1B[90m")
#define BRIGHT_RED ("\x1B[91m")
#define BRIGHT_GREEN ("\x1B[92m")
#define BRIGHT_YELLOW ("\x1B[93m")
#define BRIGHT_BLUE ("\x1B[94m")
#define BRIGHT_MAGENTA ("\x1B[95m")
#define BRIGHT_CYAN  ("\x1B[96m")
#define BRIGHT_WHITE ("\x1B[97m")
#define BG_BLUE ("\x1B[104m")
#define END ("\033[0m")
//#define MS 1000

typedef struct		s_table {
	struct timeval	begin_era;
	int				count_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int 			count_eat;
	pthread_mutex_t death;
	pthread_mutex_t	*forks;
	int				who_is_die;
}					t_table;

typedef struct		s_philo {
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
	
}					t_philo;

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

long int	difference_in_time(struct timeval begin, struct timeval current)
{
	return ((current.tv_sec * 1000000 + current.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
}

void	ft_wait_time(int count_time)
{

	struct timeval	begin_era;
	struct timeval	current_time;

	gettimeofday(&begin_era, NULL);
	gettimeofday(&current_time, NULL);
	while (difference_in_time(begin_era, current_time) < count_time * 1000)
		gettimeofday(&current_time, NULL);
}

long int		ft_calc_time_stamp(t_table *table)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (difference_in_time(table->begin_era, current_time) / 1000);
}

void	ft_start_sleep(t_philo *philo)
{
	printf("%ld ms %d %sis sleeping%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_YELLOW, END);
	ft_wait_time(philo->table->time_to_sleep);
}

void	ft_start_eat(t_philo *philo)
{
	if (philo->numb % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld ms %d %shas taken a fork%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_MAGENTA, END);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld ms %d %shas taken a fork%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_MAGENTA, END);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld ms %d %shas taken a fork%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_MAGENTA, END);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld ms %d %shas taken a fork%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_MAGENTA, END);
	}
	printf("%ld ms %d %sis eating%s\n",ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_GREEN, END);
	ft_wait_time(philo->table->time_to_eat);
	if (philo->numb % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*ft_counter_die(void *arg)
{
	t_philo		*philo;
	struct		timeval	begin_era;
	struct		timeval	current_time;
	
	philo = (t_philo *)arg;
	gettimeofday(&begin_era, NULL);
	gettimeofday(&current_time, NULL);
	while (!philo->when_eat) {
		if (difference_in_time(begin_era, current_time) < philo->table->time_to_die * 1000)
		{
			gettimeofday(&current_time, NULL);
		}
		else
		{
			pthread_mutex_lock(&philo->table->death);
			*philo->flag_die = 1;
			printf("%ld ms %d %sdied%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_RED, END);
		}
	}
	
	return (SUCCESS);
}

void	ft_start_think(t_philo *philo)
{
	pthread_t	thread_die;
	
	printf("%ld ms %d %sis thinking%s\n", ft_calc_time_stamp(philo->table), philo->numb, BRIGHT_BLUE, END);
	pthread_create(&thread_die, NULL, ft_counter_die, philo);
}

void	*start_routin(void *atr)
{
	t_philo *thread_philo;
	
	thread_philo = (t_philo *)atr;
	while(!thread_philo->table->who_is_die)
	{
		pthread_mutex_unlock(&thread_philo->table->death);
		ft_start_eat(thread_philo);
		ft_start_sleep(thread_philo);
		ft_start_think(thread_philo);
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
	int i;
	
	i = 0;
	table = (t_table *) malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->count_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->time_to_die -= (table->time_to_eat + table->time_to_sleep);
	gettimeofday(&table->begin_era, NULL);
	if (av[5])
		table->count_eat = ft_atoi(av[5]);
	else
		table->count_eat = 0;
	pthread_mutex_init(&table->death, NULL);
	table->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * table->count_philos);
	if (!table->forks)
		return (NULL);
	while (i < table->count_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->who_is_die = 0;
	return (table);
}

void	ft_create_threads(t_table *table, t_philo *philos)
{
	pthread_t	thread_philo[table->count_philos];
	int			i;
	int			thread_status;

	i = 0;
	while (i < table->count_philos)
	{
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
}

int		ft_start_simul(char **av)
{
	t_table	*table;
	t_philo	*philos;

	table = ft_create_table(av);
	philos = ft_creat_philo(table);
	ft_create_threads(table, philos);
	
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
