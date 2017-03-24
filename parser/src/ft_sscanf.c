/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 21:56:16 by vdaviot           #+#    #+#             */
/*   Updated: 2017/03/24 21:04:53 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static	void	skip_space(char **format, char **str)
{
	(*format) += 2;
	while (ft_isspace(**str))
		(void)(*str)++;
}

static int		skip_string(char **format, char **str)
{
	while (**format != '\\' && **format != '%')
	{
		if (**format != **str)
			return (0);
		else
			(void)((long)(*str)++ + (long)++(*format));
	}
	return (1);
}

static int		convert_float(char **format, char **str, float *f)
{
	if (!(ft_isdigit(**str) || **str == '-'))
		return (0);
	*f = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	(*format) += 2;
	return (1);
}

static int		convert_int(char **format, char **str, int *i)
{
	if (!(ft_isdigit(**str)))
		return (0);
	*i = ft_atoi(*str);
	while (ft_isdigit(**str) || **str == '-')
		(void)(*str)++;
	(*format) += 2;
	return (1);
}

static	int		convert_word(char **format, char **str, char *ptr, int buffsize)
{
	int				worldlen = 0;
	const char	*begin_word = ptr;

	while (**str && !ft_isspace(**str) && **str != ',' && **str != ':' && **str != '|')
		_((*str)++, worldlen++);
	ft_strlcpy(ptr, begin_word, (worldlen < buffsize + 1) ? worldlen + 1 : buffsize);
	(*format) += 2;
	return (1);
}

static	int		convert_str(char **format, char **str, char *ptr, int buffsize)
{
	const char	*begin_str = ptr;
	int					i;

	i = 0;
	while (**str && i < buffsize)
		_((*str)++, i++);
	ft_strlcpy(ptr, begin_str, buffsize);
	(*format) += 2;
	return (1);
}

static int	convert_color(char **format, char **str, float *r, float *g, float *b)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) *3);
	if (**str == '#')
	{
		(void)(*str)++;
		*r = (float)ft_deconvert(ft_strncpy(dest, *str, 2), 16);
		(void)(*str)++;
		(void)(*str)++;
		*g = (float)ft_deconvert(ft_strncpy(dest, *str, 2), 16);
		(void)(*str)++;
		(void)(*str)++;
		*b = (float)ft_deconvert(ft_strncpy(dest, *str, 2), 16);
	}
	else if ((ft_isdigit(**str) || **str == '-'))
	{
	*r = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	while (ft_isspace(**str))
		(void)(*str)++;
	*g = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	*b = (float)ft_atof(*str);
	}
	(*format) += 2;
	return (1);
}

static int	convert_vect(char **format, char **str, float *x, float *y, float *z, float *w)
{
	*x = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	while (ft_isspace(**str))
		(void)(*str)++;
	*y = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	while (ft_isspace(**str))
		(void)(*str)++;
	*z = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.' || **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	while (ft_isspace(**str))
		(void)(*str)++;
	*w = (float)ft_atof(*str);
	(*format) += 2;
	return (1);
}

int			sscanf_return(int value, va_list *vargs)
{
	va_end(*vargs);
	return value;
}

int			ft_sscanf(char *format, char *str, ...)
{
	va_list	vargs;

	va_start(vargs, str);
	while (42)
	{
		if (*format == '\\' && format[1] == 's')
			skip_space(&format, &str);
		if (!*str)
			break ;
		if (*format == '%' && format[1] == 'f')
			if (!convert_float(&format, &str, va_arg(vargs, float *)))
				return sscanf_return (-1, &vargs);
		if (*format == '%' && format[1] == 'd')
			if (!convert_int(&format, &str, va_arg(vargs, int *)))
				return sscanf_return (-1, &vargs);
		if (*format == '%' && format[1] == 'w')
			if (!convert_word(&format, &str, va_arg(vargs, char *), va_arg(vargs, int)))
				return sscanf_return (-1, &vargs);
		if (*format == '%' && format[1] == 's')
			if (!convert_str(&format, &str, va_arg(vargs, char *), va_arg(vargs, int)))
				return sscanf_return (-1, &vargs);
		if (*format == '%' && format[1] == 'z')
			if (!convert_color(&format, &str, va_arg(vargs, float *), va_arg(vargs, float *), va_arg(vargs ,float *)))
				return sscanf_return (-1, &vargs);
		if (*format == '%' && format[1] == 'v')
			if (!convert_vect(&format, &str, va_arg(vargs, float *), va_arg(vargs, float *), va_arg(vargs ,float *), va_arg(vargs, float *)))
				return sscanf_return (-1, &vargs);
		if (!skip_string(&format, &str))
			return sscanf_return (-1, &vargs);
	}
	if (!*format)
		return sscanf_return (0, &vargs);
	return sscanf_return (-1, &vargs);
}
