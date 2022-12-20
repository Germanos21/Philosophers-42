/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:06:26 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/20 21:28:06 by gchernys         ###   ########.fr       */
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
		gettime() - rules->start_time, philo->id, message);
	pthread_mutex_unlock(&rules->printing);
}

int	ft_usleep(int time, t_philos *philo)
{
	long long int	start_time;

	start_time = gettime();
	while (gettime() - start_time < time)
	{
		usleep(100);
		philosopher_death(philo, philo->rules, philo->id);
	}
	return (0);
}

void	*philo_thread(void *philosopher)
{
	t_philos	*philo;

	philo = (t_philos *)philosopher;
	while (1)
	{
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
		// pthread_detach(philo[i].thread);
		i++;
	}
	i = 0;
	while (i < (rules->philo_num))
	{
		pthread_join((philo[i]).thread, NULL);
		i++;
	}
	return (0);
}
