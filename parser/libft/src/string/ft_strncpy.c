/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:58:39 by alelievr          #+#    #+#             */
/*   Updated: 2017/03/24 16:44:05 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t	size;

	size = ft_strlen(src);
	size = (size < n) ? size : n;
	ft_bzero(dst + size, n - size);
	return (ft_memcpy(dst, src, size));
}
