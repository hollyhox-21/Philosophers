#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "ft_atoi.c"
#include "ft_putchar_fd.c"
#include "ft_putnbr_fd.c"
#include "ft_putstr_fd.c"
#include "ft_putendl_fd.c"
#include "ft_strlen.c"
#include "ft_bzero.c"
#include "ft_itoa.c"
#include "ft_strjoin.c"
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

typedef struct		s_table {
	long int		begin_era;
	struct timeval	begin_era_struct;
	int				count_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int 			count_eat;
	pthread_mutex_t wait;
	pthread_mutex_t time;
	pthread_mutex_t death;
	pthread_mutex_t	*forks;
	int				who_is_die;
}					t_table;

typedef struct		s_philo {
	int				numb;
	long int		when_eat;
	int				count_eat;
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
	printf("begin_era\t\t%ld\n", table->begin_era);
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

long int		ft_calc_time_stamp(t_table *table)
{
	struct timeval	current_time;
	long int	time;

	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec * 1000 +
			current_time.tv_usec / 1000) - table->begin_era);
	return (time);
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
			continue;
		}
		break ;
	}
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	char *tmp_1;
	char *tmp_2;
	char *tmp_res;
	char *res;
	
	tmp_1 = ft_itoa((int)ft_calc_time_stamp(philo->table));
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
	pthread_mutex_unlock(&philo->table->wait);
	if (!*philo->flag_die)
		write(1, res, ft_strlen(res));
	free(res);
}

void	ft_start_think(t_philo *philo)
{
	if (!philo->table->who_is_die && philo->count_eat != philo->table->count_eat)
	{
		ft_print_msg(philo, " \x1B[94mis thinking\033[0m\n");
	}
}

void	ft_start_sleep(t_philo *philo)
{
	if (!philo->table->who_is_die && philo->count_eat != philo->table->count_eat)
	{
		ft_print_msg(philo, " \x1B[93mis sleeping\033[0m\n");
		ft_wait_time(&philo->table->time_to_sleep);
	}
}

void	ft_start_eat(t_philo *philo)
{
	if (philo->numb % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(philo, " \x1B[95mhas taken a fork LEFT\033[0m\n");
		pthread_mutex_lock(philo->right_fork);
		ft_print_msg(philo, " \x1B[95mhas taken a fork RIGHT\033[0m\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_msg(philo, " \x1B[95mhas taken a fork RIGHT\033[0m\n");
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(philo, " \x1B[95mhas taken a fork LEFT\033[0m\n");
	}
	if (!philo->table->who_is_die && philo->count_eat != philo->table->count_eat)
	{
		philo->when_eat = ft_calc_time_stamp(philo->table);
		philo->count_eat++;
		ft_print_msg(philo, " \x1B[92mis eating\033[0m\n");
		ft_wait_time(&philo->table->time_to_eat);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_counter_die(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_calc_time_stamp(philo->table) - philo->when_eat > philo->table->time_to_die)
			break ;
		usleep(20);
	}
	if (philo->table->count_eat == -1)
		ft_print_msg(philo, " \x1B[91mdied\033[0m\n");
	pthread_mutex_lock(&philo->table->wait);
	*philo->flag_die = 1;
	return (SUCCESS);
}

void	*start_routin(void *atr)
{
	t_philo		*thread_philo;
	thread_philo = (t_philo *)atr;
	
	pthread_t	thread_die;
	pthread_create(&thread_die, NULL, ft_counter_die, (void *)thread_philo);
	while(!thread_philo->table->who_is_die && thread_philo->count_eat != thread_philo->table->count_eat)
	{
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
		philos[i].count_eat = 0;
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
	
	i = -1;
	table = (t_table *) malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	table->count_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&table->begin_era_struct, NULL);
	table->begin_era = (table->begin_era_struct.tv_sec * 1000 + table->begin_era_struct.tv_usec / 1000);
	if (av[5])
		table->count_eat = ft_atoi(av[5]);
	else
		table->count_eat = -1;
	pthread_mutex_init(&table->wait, NULL);
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->time, NULL);
	table->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * table->count_philos);
	if (!table->forks)
		return (NULL);
	while (++i < table->count_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	table->who_is_die = 0;
	return (table);
}

void	ft_create_threads(t_table *table, t_philo *philos)
{
	pthread_t	thread_philo[table->count_philos];
	int			i;

	i = 0;
	while (i < table->count_philos)
	{
		pthread_create(&thread_philo[i], NULL, start_routin, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < table->count_philos)
	{
		pthread_join(thread_philo[i], NULL);
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


//	int a = 800;
//	printf("%ld\n", ft_calc_time_stamp(table));
//	ft_wait_time(&a);
//	printf("%ld\n", ft_calc_time_stamp(table));
//	PRINT STRUCT
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
