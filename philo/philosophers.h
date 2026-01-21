/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:57 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/21 17:29:07 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	death_lock;
}	t_mutex;

typedef struct	s_info
{
	long	start_time;
	int		nbr_philos;
	bool	all_philos_alive;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	int		meal_amount;
}	t_info;

typedef struct	s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct	s_data
{
	t_info	*info;
	t_philo	*arr_philo;
	t_mutex	*mutex;
}	t_data;

// utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
long	get_time(void);

// initializer
int		init_info(t_data *data, char **str);
int		init_mutex(t_data *data);
int		init_philo(t_data *data, int i);
int		init_all_philos(t_data *data);


#endif