/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:40:46 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 19:27:36 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base_u(unsigned int nb, char *base)
{
	char	*str;
	size_t	len;
	size_t	base_len;

	base_len = ft_strlen(base);
	len = ft_nbrsize_base(nb, base_len);
	str = NULL;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str)
	{
		str[len] = '\0';
		len--;
		if (nb == 0)
			str[len] = '0';
		while (nb > 0)
		{
			str[len] = base[nb % base_len];
			nb = nb / base_len;
			len--;
		}
	}
	return (str);
}

char	*ft_itoa_base_adr(unsigned long nb, char *base, size_t len)
{
	char	*str;
	size_t	base_len;

	base_len = ft_strlen(base);
	str = NULL;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str)
	{
		str[len] = '\0';
		len--;
		if (nb == 0)
			str[len] = '0';
		while (nb > 0)
		{
			str[len] = base[nb % base_len];
			nb = nb / base_len;
			len--;
		}
	}
	return (str);
}

size_t	ft_putstr_len(char *s)
{
	size_t len;

	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
