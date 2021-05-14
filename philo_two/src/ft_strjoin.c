/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:35:41 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:59 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	buf = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buf)
		return (NULL);
	while (s2[j] != '\0' || s1[i] != '\0')
	{
		while (s1[i] != '\0')
		{
			buf[i] = s1[i];
			i++;
		}
		if (s2[j] == '\0')
			break ;
		buf[i + j] = s2[j];
		j++;
	}
	buf[i + j] = '\0';
	return (buf);
}
