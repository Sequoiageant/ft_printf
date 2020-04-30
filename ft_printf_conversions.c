/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:33:20 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 20:24:23 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_put_c(va_list *args, t_format *env)
{
	char c;
	char *tmp;

	c = (char)va_arg(*args, int);
	tmp = NULL;
	tmp = (char *)malloc(sizeof(char) * 1);
	if (tmp)
	{
		tmp[0] = '\0';
		if (env->width > 1)
			ft_handle_width(&tmp, env);
		if (env->justify == left)
			ft_putchar(c);
		if (env->width > 1)
			ft_putstr(tmp + 1);
		else
			ft_putstr(tmp);
		if (env->justify == right)
			ft_putchar(c);
		free(tmp);
		tmp = NULL;
	}
	return (env->width > 1 ? env->width : 1);
}

size_t	ft_put_string(va_list *args, t_format *env)
{
	char	*s;
	char	*tmp;
	int		len;

	s = va_arg(*args, char *);
	if (s == NULL)
		s = ft_strdup("(null)");
	len = ft_strlen(s);
	if (env->is_precision == true && env->precision < len)
		len = env->precision;
	len = (env->precision < 0 ? ft_strlen(s) : len);
	tmp = ft_substr(s, 0, len);
	if (tmp)
	{
		if (env->width > len)
			ft_handle_string(&tmp, env, env->width - len);
		ft_putstr(tmp);
		len = ft_strlen(tmp);
		free(tmp);
		tmp = NULL;
	}
	return (len);
}

size_t	ft_put_nbr(va_list *args, t_format *env)
{
	int		nb;
	char	*tmp;
	int		len;

	nb = va_arg(*args, int);
	tmp = ((env->is_precision == true && env->precision == 0 && nb == 0) ?
		ft_strdup("") : ft_itoa(nb));
	len = ft_nbrsize(nb);
	if (tmp)
	{
		if (env->precision >= len)
			ft_handle_prec(&tmp, env, len, nb);
		if (env->width > (int)ft_strlen(tmp))
			ft_handle_width(&tmp, env);
		if (env->zero_nbr > (int)ft_strlen(tmp) && env->is_precision == false)
			ft_handle_zeros(&tmp, env, nb);
		if (env->zero_nbr > (int)ft_strlen(tmp) && env->is_precision == true)
			ft_handle_spaces(&tmp, env);
		ft_putstr(tmp);
		len = ft_strlen(tmp);
		free(tmp);
		tmp = NULL;
	}
	return (len);
}

size_t	ft_put_hex(va_list *args, t_format *env)
{
	unsigned int	nb;
	char			*base;
	char			*tmp;
	int				len;

	nb = va_arg(*args, int);
	base = ft_choose_base(env->converter);
	len = ft_nbrsize_base(nb, ft_strlen(base));
	tmp = ((env->is_precision == true && env->precision == 0 && nb == 0) ?
		ft_strdup("") : ft_itoa_base_u(nb, base));
	if (tmp)
	{
		if (env->precision >= len)
			ft_handle_prec(&tmp, env, len, 1);
		if (env->width > (int)ft_strlen(tmp))
			ft_handle_width(&tmp, env);
		if (env->zero_nbr > (int)ft_strlen(tmp) && env->is_precision == false)
			ft_handle_zeros(&tmp, env, 1);
		if (env->zero_nbr > (int)ft_strlen(tmp) && env->is_precision == true)
			ft_handle_spaces(&tmp, env);
		len = ft_putstr_len(tmp);
		free(tmp);
		tmp = NULL;
	}
	return (len);
}

size_t	ft_put_addr(va_list *args, t_format *env)
{
	long	adr;
	int		len;
	char	*tmp;

	adr = va_arg(*args, long);
	len = ft_nbrsize_base_ul(adr, 16) + 2;
	if (adr == 0 && env->is_precision == true)
	{
		tmp = ft_strdup("0x");
		len--;
	}
	else
		tmp = ft_itoa_base_adr(adr, LOWERBASE, len);
	if (tmp)
	{
		tmp[0] = '0';
		tmp[1] = 'x';
		if (env->width > len)
			ft_handle_string(&tmp, env, env->width - len);
		ft_putstr(tmp);
		len = ft_strlen(tmp);
		free(tmp);
		tmp = NULL;
	}
	return (len);
}
