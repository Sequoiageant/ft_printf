/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 12:13:56 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 19:27:41 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Sets the flag environment to zero before being filled
*/

void	ft_reset_env(t_format *env)
{
	env->width = 0;
	env->zero_nbr = 0;
	env->precision = 0;
	env->justify = right;
	env->is_precision = false;
}

/*
** Choose the converting base in header according to the converter char
** BASE_10 is the default
*/

char	*ft_choose_base(char c)
{
	char *base;

	if (c == 'x')
		base = LOWERBASE;
	else if (c == 'X')
		base = UPPERBASE;
	else
		base = BASE_10;
	return (base);
}

/*
** A simple atoi() not managing other char than numbers
*/

int		ft_light_atoi(const char **format)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while ((*format)[i] >= '0' && (*format)[i] <= '9')
	{
		res = res * 10 + (*format)[i] - 48;
		i++;
	}
	(*format) += (i - 1);
	return (res);
}

/*
** Searches a character in a string and returns true or false
*/

int		ft_is_in_string(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** Returns the len of a unsigned long converted into base
*/

size_t	ft_nbrsize_base_ul(unsigned long n, size_t base_len)
{
	size_t len;

	if (n == 0)
		len = 1;
	else
	{
		len = 0;
		while (n > 0)
		{
			n = n / base_len;
			len++;
		}
	}
	return (len);
}
