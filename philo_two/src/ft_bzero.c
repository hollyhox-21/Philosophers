/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:59 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:53 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	k;

	k = 0;
	while (k < n)
	{
		*((char *)s + k) = '\0';
		k++;
	}
}