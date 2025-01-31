/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:07:30 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 18:17:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdarg.h>
void		ft_exit(char *f, ...)
{
	(void)f;
	va_list		ap;

	va_start(ap, f);
	ft_putstr("\033[38;5;196m");
	//ft_vprintf(f, ap);
	ft_putstr("\033[0m");
	va_end(ap);
	exit(-1);
}
