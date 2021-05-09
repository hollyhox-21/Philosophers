//
// Created by Retro Joella on 5/9/21.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void	ft_wait(int count_ms)
{
	struct timeval	begin_era;
	struct timeval	current_time;
	static long int		time_stamp = 0;
	
	gettimeofday(&begin_era, NULL);
	gettimeofday(&current_time, NULL);
	printf("%ld --- \n", ((current_time.tv_sec * 1000000 + current_time.tv_usec) - (begin_era.tv_sec * 1000000 + begin_era.tv_usec)) / 1000);
	while (((current_time.tv_sec * 1000000 + current_time.tv_usec) - (begin_era.tv_sec * 1000000 + begin_era.tv_usec)) < count_ms * 1000)
		gettimeofday(&current_time, NULL);
	time_stamp += count_ms;
	printf("%ld\n", time_stamp);
}

int main() {
	ft_wait(200);
	ft_wait(200);
	
}
