/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_launcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:40:32 by gchernys          #+#    #+#             */
/*   Updated: 2023/03/04 00:20:56 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *philosopher)
{
	t_philos	*philo;
	int			is_dead;

	philo = (t_philos *)philosopher;
	is_dead = check_death(philo->rules);
	while (!is_dead && philo->eat_count != philo->rules->num_to_eat)
	{
		while (!is_dead && philosopher_eats(philo, philo->rules) != 0)
		{
			if (philosopher_eats(philo, philo->rules) == -1)
				break ;
			is_dead = check_death(philo->rules);
		}
		if (philo->eat_count == philo->rules->num_to_eat || is_dead)
			break ;
		is_dead = check_death(philo->rules);
		if (philosopher_thinks(philo, philo->rules) == 1)
			break ;
		is_dead = check_death(philo->rules);
		if (philosopher_sleeps(philo, philo->rules) != 0)
			break ;
	}
	return (NULL);
}

int	philosopher_launcher(t_philos *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_create(&(philo[i].thread), NULL, philo_thread, &(philo[i]));
		i++;
	}
	pthread_create(&(rules->check_death_thread) \
	, NULL, philosopher_death, rules);
	i = 0;
	while (i < (rules->philo_num))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(rules->check_death_thread, NULL);
	return (0);
}
