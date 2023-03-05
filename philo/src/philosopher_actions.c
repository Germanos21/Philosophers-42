/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:05:22 by gchernys          #+#    #+#             */
/*   Updated: 2023/03/05 06:08:13 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_eats(t_philos *philo, t_rules *rules)
{	
	int	status;

	status = 1;
	if (philo->right_fork == philo->left_fork)
		return (status);
	pthread_mutex_lock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	if (philo->left_fork->fingerprint != philo->id && \
	philo->right_fork->fingerprint != philo->id)
	{
		pthread_mutex_lock(&rules->last_meal_mutex);
		philo->last_meal = gettime();
		pthread_mutex_unlock(&rules->last_meal_mutex);
		pthread_mutex_lock(&rules->eat_count_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(&rules->eat_count_mutex);
		print_eating(philo, rules);
		philo->left_fork->fingerprint = philo->id;
		philo->right_fork->fingerprint = philo->id;
		status = ft_usleep(rules->time_to_eat, philo);
	}
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
	return (status);
}

int	philo_sleep(t_philos *philo, t_rules *rules)
{
	if (check_death(rules) || is_full(rules))
		return (1);
	print_message(philo, rules, "is sleeping");
	return (ft_usleep(rules->time_to_sleep, philo));
}

int	philo_think(t_philos *philo, t_rules *rules)
{
	if (check_death(rules) == 1)
		return (1);
	print_message(philo, rules, "is thinking");
	return (0);
}

void	*philosopher_death(void *rule)
{
	int		i;
	t_rules	*rules;

	rules = (t_rules *)rule;
	while (check_death(rules) == 0)
	{
		if (is_full(rules) == 1)
			break ;
		i = -1;
		while (++i < rules->philo_num)
		{
			if (gettime() - check_last_meal(rule, rules->philosophers, i) > \
			rules->time_to_die)
			{
				pthread_mutex_lock(&rules->printing);
				if (check_death(rules) == 0)
					printf("%lld %d died\n", \
					gettime() - rules->start_time, i + 1);
				rules->death = 1;
				pthread_mutex_unlock(&rules->printing);
				break ;
			}
		}
	}
	return (NULL);
}

int	check_death(t_rules *rules)
{
	int	value;

	pthread_mutex_lock(&rules->death_mutex);
	value = rules->death;
	pthread_mutex_unlock(&rules->death_mutex);
	return (value);
}
