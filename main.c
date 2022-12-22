/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:33 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/22 17:36:03 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_everything(t_rules *rules, t_philos *philo)
{
	int i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_mutex_destroy(((rules->forks)[i]).mutex);
		free((rules->forks)[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&(rules->last_meal_mutex));
	pthread_mutex_destroy(&(rules->death_mutex));
	pthread_mutex_destroy(&(rules->printing));
	i = 0;
	free(rules->forks);
	free(rules);
	free(philo);
}

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
		exit(0);
	}
	philosopher_launcher(philosophers, rules);
	return (0);
}
