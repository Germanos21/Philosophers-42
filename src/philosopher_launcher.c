/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_launcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:40:32 by gchernys          #+#    #+#             */
/*   Updated: 2023/02/26 16:01:14 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *philosopher)
{
	t_philos	*philo;

	philo = (t_philos *)philosopher;
	while (philosopher_death(philo, philo->rules, philo->id) == 0)
	{
		if (philo->eat_count == philo->rules->num_to_eat)
			break ;
		if (philosopher_thinks(philo, philo->rules) == 1)
			break ;
		while (philosopher_death(philo, philo->rules, philo->id) != 1 && \
		philosopher_eats(philo, philo->rules) != 0)
		{
			usleep(100);
			if (philosopher_eats(philo, philo->rules) == -1)
				break ;
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
