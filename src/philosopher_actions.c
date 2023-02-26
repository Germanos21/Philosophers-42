/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:05:22 by gchernys          #+#    #+#             */
/*   Updated: 2023/02/26 21:17:56 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosopher_eats(t_philos *philo, t_rules *rules)
{	
	int	status;

	status = 1;
	if (philo->right_fork == philo->left_fork)
		return (status);
	pthread_mutex_lock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->left_fork->mutex);
	if (check_death(rules) == 1 || philo->eat_count == rules->num_to_eat || \
	philosopher_death(philo, rules, philo->id) == 1)
	{
		pthread_mutex_unlock(philo->left_fork->mutex);
		pthread_mutex_unlock(philo->right_fork->mutex);
		return (-1);
	}
	if (philo->left_fork->fingerprint != philo->id \
	&& philo->right_fork->fingerprint != philo->id)
	{
		philo->last_meal = gettime();
		print_eating(philo, rules);
		philo->eat_count++;
		status = ft_usleep(rules->time_to_eat, philo);
	}
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
	return (status);
}

int	philosopher_sleeps(t_philos *philo, t_rules *rules)
{
	if (philosopher_death(philo, rules, philo->id) == 1)
		return (1);
	print_message(philo, rules, "is sleeping");
	return (ft_usleep(rules->time_to_sleep, philo));
}

int	philosopher_thinks(t_philos *philo, t_rules *rules)
{
	print_message(philo, rules, "is thinking");
	return (0);
}

int	philosopher_death(t_philos *philo, t_rules	*rules, int i)
{
	if (gettime() - philo->last_meal > rules->time_to_die)
	{		
		pthread_mutex_lock(&rules->printing);
		if (check_death(rules) == 0)
			printf("%lld %d died\n", gettime() - rules->start_time, i + 1);
		pthread_mutex_lock(&rules->death_mutex);
		rules->death = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		pthread_mutex_unlock(&rules->printing);
		return (1);
	}
	return (0);
}

int	check_death(t_rules *rules)
{
	int	value;

	pthread_mutex_lock(&rules->death_mutex);
	value = rules->death;
	pthread_mutex_unlock(&rules->death_mutex);
	return (value);
}
