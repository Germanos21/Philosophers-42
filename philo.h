/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchernys <gchernys@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:51:38 by gchernys          #+#    #+#             */
/*   Updated: 2023/02/23 16:59:42 by gchernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum e_error
{
	ERR_ARG = 1,
	ERR_NUM_ARG,
	ERR_MALLOC,
	ERR_MUTEX
};

typedef struct s_forks
{
	pthread_mutex_t	*mutex;
	int				fingerprint;
}				t_forks;

typedef struct s_philosopher
{
	int				id;
	int				eat_count;
	long long int	last_meal;
	t_forks			*right_fork;
	t_forks			*left_fork;
	pthread_t		thread;
	struct s_rules	*rules;
}				t_philos;

typedef struct s_rules
{
	int					death;
	int					philo_num;
	int					time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	long long int		num_to_eat;
	long long int		start_time;
	t_philos			*philosophers;
	t_forks				*forks;
	pthread_mutex_t		printing;
	pthread_mutex_t		fingerprint_fork;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		death_mutex;
}				t_rules;

int				philosopher_atoi(char *str);
int				init_all(t_philos **philo, t_rules *rules, char **av, int argc);
int				initialize_philosopher(t_rules *rules, t_philos **philo);
void			error_handle(enum e_error ret);
int				initialize_mutex(t_rules *rules);
long long int	gettime(void);
void			print_message(t_philos *philo, t_rules *rules, char *message);
int				philosopher_eats(t_philos *philo, t_rules *rules);
int				philosopher_sleeps(t_philos *philo, t_rules *rules);
void			philosopher_thinks(t_philos *philo, t_rules *rules);
void			philosopher_death(t_philos *philo, t_rules	*rules, int i);
int				ft_usleep(int time, t_philos *philo);
int				philosopher_launcher(t_philos *philo, t_rules *rules);
int				check_death(t_rules *rules);
void			check_params(char **argv);
void			print_eat_message(t_philos *philo, t_rules *rules);

#endif