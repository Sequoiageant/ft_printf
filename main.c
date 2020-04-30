/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:24:55 by julnolle          #+#    #+#             */
/*   Updated: 2020/04/30 20:23:15 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	int ret;
	int myret;

	ft_putendl("--------MY FONCTION--------");
	myret = ft_printf("arg 1 : %%% -.15d%%%p\n", 5, &ret);

	ft_putendl("-------REAL FONCTION-------");
	ret = printf("arg 1 : %%% -.15d%%%p\n", 5, &ret);
	printf("----------RETURNS----------\n");
	printf("My fction: %d\n", myret);
	printf("Real one : %d\n", ret);

	printf("-----------OTHER-----------\n");
	// printf("0 avec prec 0: %.0d\n", 0);
	// printf("%010.5d\n", -42);
	// printf("%-10.5d\n", -42);
	// printf("%050.d\n", -42);
	// ret = printf("%010d\n", -42);
	// ret = printf("%-15.05d\n", -42);
	printf("%*.*d\n", 50, 10, 42);
	printf("%d\n", ret);
	return (0);
}
