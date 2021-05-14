/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:48:35 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:29:01 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*(s + count) != '\0')
	{
		count++;
	}
	return (count);
}
