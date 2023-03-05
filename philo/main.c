/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:33 by gchernys          #+#    #+#             */
/*   Updated: 2023/03/06 03:37:10 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_params_two(char **argv, t_rules *rules)
{
	long long int	i;

	i = 0;
	while (argv[i])
	{
		if (philosopher_atoi(argv[i]) > INT_MAX || \
		philosopher_atoi(argv[i]) < INT_MIN)
		{
			printf("Error\n");
			exit (1);
		}
		i++;
	}
	if (argv[5])
	{
		if (philosopher_atoi(argv[5]) <= 0)
		{
			free(rules);
			printf("Error\n");
			exit (1);
		}
	}
}

void	free_everything(t_philos *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		free(((rules->forks)[i]).mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->death_mutex);
	pthread_mutex_destroy(&rules->printing);
	pthread_mutex_destroy(&rules->last_meal_mutex);
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
	rules = malloc(sizeof(t_rules) + 1);
	check_params_two(argv, rules);
	philosophers = NULL;
	return_value = init_all(&philosophers, rules, argv, argc);
	error_handle(return_value, rules);
	philosopher_launcher(philosophers, rules);
	free_everything(philosophers, rules);
	return (0);
}
