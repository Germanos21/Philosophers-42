/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:06:26 by gchernys          #+#    #+#             */
/*   Updated: 2023/03/02 19:42:17 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long int	gettime(void)
{
	struct timeval	time;
	long long int	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

void	print_message(t_philos *philo, t_rules *rules, char *message)
{
	pthread_mutex_lock(&rules->printing);
	if (check_death(rules) == 0)
		printf("%lld %d %s\n", \
		gettime() - rules->start_time, philo->id + 1, message);
	pthread_mutex_unlock(&rules->printing);
}

int	ft_usleep(int time, t_philos *philo)
{
	long long int	start_time;

	start_time = gettime();
	while (gettime() - start_time < time)
	{
		if (check_death(philo->rules) == 1)
			return (1);
		usleep(100);
	}
	return (0);
}

void	print_eating(t_philos *philo, t_rules *rules)
{
	print_message(philo, rules, "has taken a fork");
	print_message(philo, rules, "has taken a fork");
	print_message(philo, rules, "is eating");
	philo->left_fork->fingerprint = philo->id;
	philo->right_fork->fingerprint = philo->id;
}

long long int	check_last_meal(t_rules *rules, t_philos *philo, int i)
{
	long long int	last_meal_time;

	pthread_mutex_lock(&rules->last_meal_mutex);
	last_meal_time = philo[i].last_meal;
	pthread_mutex_unlock(&rules->last_meal_mutex);
	return (last_meal_time);
}
