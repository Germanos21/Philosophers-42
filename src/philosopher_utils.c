/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:06:26 by gchernys          #+#    #+#             */
/*   Updated: 2023/02/26 16:10:16 by gchernys         ###   ########.fr       */
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
		philosopher_death(philo, philo->rules, philo->id);
		usleep(100);
	}
	return (0);
}

void	print_eating(t_philos *philo, t_rules *rules)
{
	print_message(philo, rules, "has taken a fork");
	print_message(philo, rules, "has taken a fork");
	print_message(philo, rules, "is eating");
}