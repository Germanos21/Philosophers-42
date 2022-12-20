/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:33 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/20 21:58:20 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philos		*philosophers;
	int				return_value;

	rules = malloc(sizeof(t_rules) * 1);
	philosophers = NULL;
	return_value = init_all(&philosophers, rules, argv, argc);
	error_handle(return_value);
	if (return_value != 0)
	{
		free(rules);
		free(philosophers);
		return (1);
	}
	philosopher_launcher(philosophers, rules);
	free(rules);
	free(philosophers);
	return (0);
}
