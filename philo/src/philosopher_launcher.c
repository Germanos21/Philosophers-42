/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_launcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:40:32 by gchernys          #+#    #+#             */
/*   Updated: 2023/03/06 01:16:30 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_full(void *rule)
{
	int		i;
	t_rules	*rules;

	rules = (t_rules *)rule;
	i = 0;
	while (i < rules->philo_num && check_death(rules) == 0)
	{
		pthread_mutex_lock(&rules->eat_count_mutex);
		if (rules->philosophers[i].eat_count >= rules->num_to_eat)
			i++;
		else
			i = i * 1;
		if (i == rules->philo_num)
		{
			pthread_mutex_lock(&rules->check_eat_mutex);
			rules->all_ate = 1;
			pthread_mutex_unlock(&rules->check_eat_mutex);
			pthread_mutex_unlock(&rules->eat_count_mutex);
			break ;
		}
		pthread_mutex_unlock(&rules->eat_count_mutex);
	}
	return (NULL);
}

void	*philo_thread(void *philosopher)
{
	t_philos	*philo;
	int			is_dead;

	philo = (t_philos *)philosopher;
	is_dead = check_death(philo->rules);
	while (!is_dead)
	{
		if (is_full(philo->rules))
			break ;
		if (is_full(philo->rules) || philo_think(philo, philo->rules) == 1)
			break ;
		while (!is_full(philo->rules) && !is_dead && \
		philo_eats(philo, philo->rules) != 0)
		{
			if (is_full(philo->rules) || philo_eats(philo, philo->rules) == -1)
				break ;
			is_dead = check_death(philo->rules);
		}
		is_dead = check_death(philo->rules);
		if (philo_sleep(philo, philo->rules) != 0 || is_dead)
			break ;
		if (is_full(philo->rules))
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
		usleep(100);
		i++;
	}
	pthread_create(&(rules->check_death_thread) \
	, NULL, philosopher_death, rules);
	if (rules->num_to_eat != -1)
		pthread_create(&(rules->check_eat), NULL, philo_full, rules);
	i = 0;
	while (i < (rules->philo_num))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (rules->num_to_eat != -1)
		pthread_join(rules->check_eat, NULL);
	pthread_join(rules->check_death_thread, NULL);
	return (0);
}
