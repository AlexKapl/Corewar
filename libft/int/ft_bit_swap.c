/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:10:32 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/28 15:10:35 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned long long	ft_bit_swap_ll(unsigned long long llu)
{
	return (llu >> 56 | (llu >> 40 & 0xff00) |
			(llu >> 24 & 0xff0000) | (llu >> 8 & 0xff000000) |
			(llu << 8 & 0xff00000000) | (llu << 24 & 0xff0000000000) |
			(llu << 40 & 0xff000000000000) | llu << 56);
}

unsigned			ft_bit_swap(unsigned u)
{
	return (u >> 24 | (u >> 8 & 0xff00) | (u << 8 & 0xff0000) | u << 24);
}
