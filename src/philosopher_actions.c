/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:05:22 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/20 21:25:37 by gchernys         ###   ########.fr       */
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
	if (philo->left_fork->fingerprint != philo->id \
	&& philo->right_fork->fingerprint != philo->id && check_death(rules) != 1)
	{
		philo->left_fork->fingerprint = philo->id;
		philo->right_fork->fingerprint = philo->id;
		print_message(philo, rules, "has taken a fork");
		print_message(philo, rules, "has taken a fork");
		print_message(philo, rules, "is eating");
		pthread_mutex_lock(&philo->rules->last_meal_mutex);
		philo->eat_count++;
		philo[philo->id].last_meal = gettime();
		pthread_mutex_unlock(&philo->rules->last_meal_mutex);
		status = ft_usleep(rules->time_to_eat, philo);
	}
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_unlock(philo->right_fork->mutex);
	return (status);
}

int	philosopher_sleeps(t_philos *philo, t_rules *rules)
{
	print_message(philo, rules, "is sleeping");
	return (ft_usleep(rules->time_to_sleep, philo));
}

void	philosopher_thinks(t_philos *philo, t_rules *rules)
{
	print_message(philo, rules, "is thinking");
}

void	philosopher_death(t_philos *philo, t_rules	*rules, int i)
{
	if (gettime() - philo[i].last_meal > rules->time_to_die)
	{		
		pthread_mutex_lock(&rules->printing);
		if (check_death(rules) == 0)
			printf("%lld %d died\n", gettime() - rules->start_time, i);
		pthread_mutex_lock(&rules->death_mutex);
		rules->death = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		pthread_mutex_unlock(&rules->printing);
		exit(1);
	}
}

int	check_death(t_rules *rules)
{
	int	value;

	pthread_mutex_lock(&rules->death_mutex);
	value = rules->death;
	pthread_mutex_unlock(&rules->death_mutex);
	return (value);
}