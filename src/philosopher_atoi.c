/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_atoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:57:00 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/14 20:24:30 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	error_atoi(void)
{
	write(2, "Error: Incorrect Arguments\n", 27);
	return (-10);
}

static void	check_not_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		error_atoi();
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			error_atoi();
		i++;
	}
	if (i >= 11)
		error_atoi();
}

int	philosopher_atoi(char *str)
{
	long long int	z;

	z = 0;
	while (ft_isspace(*str) == 1)
		str++;
	check_not_number(str);
	while ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+')
	{
		if (*str == '-' || *str == '+')
			error_atoi();
		z = (*str - '0') + (z * 10);
		str++;
	}
	return (z);
}