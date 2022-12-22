/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_launcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:40:32 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/22 17:42:48 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *philosopher)
{
	t_philos	*philo;

	philo = (t_philos *)philosopher;
	while (1)
	{
		if (philo->eat_count == philo->rules->num_to_eat)
			break ;
		philosopher_thinks(philo, philo->rules);
		while (philosopher_eats(philo, philo->rules) != 0)
		{
			usleep(100);
			philosopher_death(philo, philo->rules, philo->id);
		}
		if (philo->eat_count == philo->rules->num_to_eat)
			break ;
		if (philosopher_sleeps(philo, philo->rules) != 0)
			break ;
	}
	return (NULL);
}

int	philosopher_launcher(t_philos *philo, t_rules *rules)
{
	int			i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_create(&(philo[i].thread), NULL, philo_thread, &(philo[i]));
		i++;
	}
	i = 0;
	while (i < (rules->philo_num))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
