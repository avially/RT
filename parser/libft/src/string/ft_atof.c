/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 16:13:49 by alelievr          #+#    #+#             */
/*   Updated: 2017/03/23 18:25:13 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	atoi_double(const char *str, double ret, int signe)
{
	double	index;
	double	tmp;

	index = 10;
	if (*str == '.' || *str == ',')
		str++;
	while ((*str >= '0' && *str <= '9'))
	{
		tmp = (*str++ - '0');
		tmp /= index;
		ret += tmp;
		index *= 10;
	}
	return (ret * signe);
}

double			ft_atof(const char *str)
{
	double	ret;
	int		signe;

	ret = 0;
	if (!str)
		return (ret);
	signe = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		signe = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str >= '0' && *str <= '9'))
		ret = ret * 10 + (*str++ - '0');
	if (*str == '.' || *str == ',')
		return (atoi_double(str, ret, signe));
	return (ret * signe);
}
