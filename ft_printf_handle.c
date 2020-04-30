/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:30:28 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 19:27:35 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handles the precision of a nbr or hex
*/

void	ft_handle_prec(char **str, t_format *env, int len, int nb)
{
	char	*pre;
	int		i;

	pre = NULL;
	len = env->precision - len;
	if (nb < 0)
		len++;
	pre = (char *)malloc(sizeof(char) * (len + 1));
	if (pre)
	{
		i = 0;
		while (i < len)
		{
			pre[i] = '0';
			i++;
		}
		pre[i] = '\0';
		if (nb < 0)
			(pre)[0] = '-';
		if ((*str)[0] == '-' && len < env->precision)
			(*str)[0] = '0';
		ft_strjoin_front(pre, str);
		free(pre);
		pre = NULL;
	}
}

/*
** Handles the number of spaces in front or back of a string
** accordingly to the witdh
*/

void	ft_handle_width(char **str, t_format *env)
{
	size_t	len;
	char	*spaces;
	size_t	i;

	spaces = NULL;
	len = env->width - ft_strlen(*str);
	spaces = (char *)malloc(sizeof(char) * (len + 1));
	if (spaces)
	{
		i = 0;
		while (i < len)
		{
			spaces[i] = ' ';
			i++;
		}
		spaces[i] = '\0';
		if (env->justify == left)
			ft_strjoin_back(spaces, str);
		else
			ft_strjoin_front(spaces, str);
		free(spaces);
		spaces = NULL;
	}
}

/*
** Handles the number of zeros in front of a string
*/

void	ft_handle_zeros(char **str, t_format *env, int nb)
{
	size_t	len;
	char	*zeros;
	size_t	i;

	if ((*str)[0] == '-')
		(*str)[0] = '0';
	len = env->zero_nbr - ft_strlen(*str);
	zeros = (char *)malloc(sizeof(char) * (len + 1));
	if (zeros)
	{
		i = 0;
		while (i < len)
		{
			zeros[i] = '0';
			i++;
		}
		zeros[i] = '\0';
		if (env->justify == right)
			ft_strjoin_front(zeros, str);
		if (nb < 0)
			(*str)[0] = '-';
		free(zeros);
		zeros = NULL;
	}
}

/*
** Put spaces at front of a string instead of zeros
*/

void	ft_handle_spaces(char **str, t_format *env)
{
	size_t	len;
	char	*spaces;
	size_t	i;

	len = env->zero_nbr - ft_strlen(*str);
	spaces = (char *)malloc(sizeof(char) * (len + 1));
	if (spaces)
	{
		i = 0;
		while (i < len)
		{
			spaces[i] = ' ';
			i++;
		}
		spaces[i] = '\0';
		if (env->justify == right)
			ft_strjoin_front(spaces, str);
		free(spaces);
		spaces = NULL;
	}
}

/*
** Handles the width of a string except for a nbr
*/

void	ft_handle_string(char **str, t_format *env, size_t size)
{
	char	*spaces;
	size_t	i;

	spaces = (char *)malloc(sizeof(char) * (size + 1));
	if (spaces)
	{
		i = 0;
		while (i < size)
		{
			spaces[i] = ' ';
			i++;
		}
		spaces[i] = '\0';
		if (env->justify == left)
			ft_strjoin_back(spaces, str);
		else
			ft_strjoin_front(spaces, str);
	}
	free(spaces);
	spaces = NULL;
}
