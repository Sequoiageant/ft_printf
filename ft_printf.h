/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:58:35 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 19:27:29 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

/*
** --------------------------------- Defines ---------------------------------
*/

# define CONV_CHAR "cspdiuxX%"
# define LOWERBASE "0123456789abcdef"
# define UPPERBASE "0123456789ABCDEF"
# define BASE_10 "0123456789"

/*
** -------------------------------- Structures -------------------------------
*/

typedef enum	e_justify
{
	left = 0,
	right = 1
}				t_justify;

typedef enum	e_bool
{
	false = 0,
	true = 1
}				t_bool;

typedef struct	s_struct
{
	char		converter;
	int			width;
	int			zero_nbr;
	int			precision;
	t_bool		is_precision;
	t_justify	justify;
}				t_format;

/*
** ------------------------------- ft_printf -------------------------------
*/

int				ft_printf(const char *format, ...);

/*
** ------------------------------ Conversions ------------------------------
*/

size_t			ft_put_c(va_list *arg, t_format *env);
size_t			ft_put_string(va_list *arg, t_format *env);
size_t			ft_put_nbr(va_list *arg, t_format *env);
size_t			ft_put_hex(va_list *arg, t_format *env);
size_t			ft_put_addr(va_list *arg, t_format *env);
char			*ft_itoa_base_u(unsigned int nb, char *base);
char			*ft_itoa_base_adr(unsigned long nb, char *base, size_t len);

/*
** -------------------------------- Handles --------------------------------
*/

void			ft_handle_prec(char **str, t_format *env, int len, int sign);
void			ft_handle_width(char **str, t_format *env);
void			ft_handle_zeros(char **str, t_format *env, int sign);
void			ft_handle_spaces(char **str, t_format *env);
void			ft_handle_string(char **str, t_format *env, size_t size);

/*
** --------------------------------- Utils ---------------------------------
*/

void			ft_reset_env(t_format *env);
char			*ft_choose_base(char c);
int				ft_light_atoi(const char **format);
int				ft_is_in_string(char c, const char *str);
size_t			ft_nbrsize_base_ul(unsigned long n, size_t base_len);
size_t			ft_putstr_len(char *s);

#endif
