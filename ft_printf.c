/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:57:38 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 20:21:33 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns a function pointer from a character
*/

static void	*func_choose(char c)
{
	void	*tab[127];

	tab['c'] = ft_put_c;
	tab['s'] = ft_put_string;
	tab['p'] = ft_put_addr;
	tab['d'] = ft_put_nbr;
	tab['i'] = ft_put_nbr;
	tab['u'] = ft_put_hex;
	tab['x'] = ft_put_hex;
	tab['X'] = ft_put_hex;
	tab['%'] = ft_put_c;
	return (tab[(unsigned int)c]);
}

/*
** Parse the format looking for wildcards and sets the env accordingly
*/

static void	ft_check_wild(const char **format, va_list *args, t_format *env)
{
	if (**format == '0')
	{
		(*format)++;
		if (**format == '*')
		{
			env->zero_nbr = va_arg(*args, int);
			if (env->zero_nbr < 0)
			{
				env->zero_nbr = -env->zero_nbr;
				env->width = env->zero_nbr;
				env->justify = left;
			}
		}
		else
			env->zero_nbr = ft_light_atoi(format);
	}
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
			env->precision = va_arg(*args, int);
		else
			env->precision = ft_light_atoi(format);
		env->is_precision = (env->precision < 0 ? false : true);
	}
}

/*
** Parse the format looking for flags and sets the env accordingly
*/

static void	ft_check_flag(const char **format, t_format *env, va_list *args)
{
	while (!ft_is_in_string(**format, CONV_CHAR))
	{
		if (**format == '-')
			env->justify = left;
		if (**format == '*')
		{
			env->width = va_arg(*args, int);
			if (env->width < 0)
			{
				env->width = -env->width;
				env->justify = left;
			}
		}
		if (**format > '0' && **format <= '9')
			env->width = ft_light_atoi(format);
		if (**format == '0')
			ft_check_wild(format, args, env);
		if (**format == '.')
		{
			env->is_precision = true;
			ft_check_wild(format, args, env);
		}
		(*format)++;
	}
}

static void	ft_parse_format(const char **format, va_list *args, size_t *written)
{
	t_format	env;
	size_t		(*f)(va_list *, t_format *);

	ft_reset_env(&env);
	if (**format == '%')
	{
		ft_putchar('%');
		(*written)++;
	}
	else
	{
		ft_check_flag(format, &env, args);
		env.converter = **format;
		f = func_choose(**format);
		(*written) += f(args, &env);
	}
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	written;

	written = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			ft_parse_format(&format, &args, &written);
		}
		else
		{
			ft_putchar(*format);
			written++;
		}
		format++;
	}
	va_end(args);
	return (written);
}
