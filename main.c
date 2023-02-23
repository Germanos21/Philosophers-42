/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:33 by gchernys          #+#    #+#             */
/*   Updated: 2023/02/23 16:37:43 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_everything(t_philos *philo, t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->philo_num)
	{
		free(((rules->forks)[i]).mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->death_mutex);
	pthread_mutex_destroy(&rules->printing);
	pthread_mutex_destroy(&rules->last_meal_mutex);
	pthread_mutex_destroy(&rules->fingerprint_fork);
	free(rules->forks);
	free(philo);
	free(rules);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philos		*philosophers;
	int				return_value;

	check_params(argv);
	rules = malloc(sizeof(t_rules) * 1);
	philosophers = NULL;
	return_value = init_all(&philosophers, rules, argv, argc);
	error_handle(return_value);
	if (return_value != 0)
	{
		free(rules);
		free(philosophers);
		exit(0);
	}
	philosopher_launcher(philosophers, rules);
	free_everything(philosophers, rules);
	return (0);
}
