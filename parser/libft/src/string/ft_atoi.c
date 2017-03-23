/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:13:59 by alelievr          #+#    #+#             */
/*   Updated: 2017/03/22 23:14:58 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

int	ft_atoi(const char *str)
{
	char	sign;
	int64_t	result;

	result = 0;
	while ((*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
				|| *str == '\v' || *str == '\f') && !((result = 0)))
		str++;
	sign = (*str == '-') ? -1 : 1;
	str = (*str == '+' || *str == '-') ? str + 1 : str;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	result *= sign;
	return ((int)result);
}
