/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:49:41 by rjoella           #+#    #+#             */
/*   Updated: 2020/11/07 19:48:27 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putnbr_fd(int n, int fd)
{
	long long int m;

	m = n;
	if (m < 0)
	{
		ft_putchar_fd('-', fd);
		m = m * -1;
	}
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10, fd);
		ft_putchar_fd(m % 10 + 48, fd);
	}
	if (m >= 0 && m < 10)
		ft_putchar_fd(m % 10 + 48, fd);
}
