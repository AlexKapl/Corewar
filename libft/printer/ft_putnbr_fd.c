/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:30:24 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/01 18:05:43 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 0;
	if (n == -2147483648)
	{
		n++;
		sign++;
	}
	if (n < 0)
	{
		ft_putchar_fd(45, fd);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		(sign ? ft_putnbr_fd(n % 10 + 1, fd) : ft_putnbr_fd(n % 10, fd));
	}
	else
		ft_putchar_fd(n + 48, fd);
}
