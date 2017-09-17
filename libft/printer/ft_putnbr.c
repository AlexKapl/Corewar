/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:13:24 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/01 18:04:44 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr(int n)
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
		ft_putchar(45);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		(sign ? ft_putnbr(n % 10 + 1) : ft_putnbr(n % 10));
	}
	else
		ft_putchar(n + 48);
}
