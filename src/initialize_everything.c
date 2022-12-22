/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_everything.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:59:32 by gchernys          #+#    #+#             */
/*   Updated: 2022/12/22 16:42:25 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_handle(enum e_error ret)
{
	if (ret == ERR_ARG)
		printf("Error: Wrong number of arguments; use 4 or 5\n");
	else if (ret == ERR_MALLOC)
		printf("Error: Failed to Initialize Philosophers\n");
	else if (ret == ERR_MUTEX)
		printf("Error: Failed to initialize Mutexs\n");
	else if (ret == ERR_NUM_ARG)
		printf("Error: Invalid size of Arguments\n");
}

int	initialize_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(t_forks) * rules->philo_num);
	while (i < rules->philo_num)
	{
		((rules->forks)[i]).mutex = malloc(sizeof(pthread_mutex_t));
		rules->forks[i].fingerprint = 0;
		if (pthread_mutex_init(((rules->forks)[i]).mutex, NULL) != 0)
			return (ERR_MUTEX);
		i++;
	}
	if (pthread_mutex_init(&rules->printing, NULL) != 0)
		return (ERR_MUTEX);
	if (pthread_mutex_init(&rules->last_meal_mutex, NULL) != 0)
		return (ERR_MUTEX);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (ERR_MUTEX);
	return (0);
}

int	initialize_philosopher(t_rules *rules, t_philos **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philos) * (rules->philo_num));
	if (!*philo)
		return (ERR_MALLOC);
	i = 0;
	while (i < rules->philo_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = &rules->forks[i];
		(*philo)[i].right_fork = &rules->forks[(i + 1) % rules->philo_num];
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_meal = 0;
		(*philo)[i].rules = rules;
		i++;
	}
	(*philo)[i - 1].left_fork = &rules->forks[(i) % rules->philo_num];
	(*philo)[i - 1].right_fork = &rules->forks[i - 1];
	return (0);
}

int	init_all(t_philos **philo, t_rules *rules, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (ERR_ARG);
	if (!rules)
		return (ERR_MALLOC);
	rules->philo_num = philosopher_atoi(argv[1]);
	rules->time_to_die = philosopher_atoi(argv[2]);
	rules->time_to_eat = philosopher_atoi(argv[3]);
	rules->time_to_sleep = philosopher_atoi(argv[4]);
	rules->death = 0;
	if (rules->philo_num < 1 || rules->philo_num > 200 \
	|| rules->time_to_die < 1 || rules->time_to_eat < 1 \
	|| rules->time_to_sleep < 1)
		return (ERR_NUM_ARG);
	if (argv[5])
		rules->num_to_eat = philosopher_atoi(argv[5]);
	else
		rules->num_to_eat = -1;
	if (initialize_mutex(rules) == ERR_MUTEX)
		return (ERR_MUTEX);
	if (initialize_philosopher(rules, philo) == ERR_MALLOC)
		return (ERR_MALLOC);
	rules->start_time = gettime();
	return (0);
}
