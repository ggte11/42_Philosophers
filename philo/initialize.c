/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martim <martim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:52 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/27 14:54:24 by martim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_info(t_data *data, char **str)
{
	data->info = malloc(sizeof(t_info));
	if (!data->info)
		return (1);
	data->info->nbr_philos = atoi(str[1]);
	data->info->all_philos_alive = true;
	data->info->start_time = get_time();
	data->info->time_to_die = atoi(str[2]);
	data->info->time_to_eat = atoi(str[3]);
	data->info->time_to_sleep = atoi(str[4]);
	if (str[5])
		data->info->meal_amount = atoi(str[5]);
	else
		data->info->meal_amount = -1;
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->mutex = malloc(sizeof(t_mutex));
	if (!data->mutex)
		return (1);
	data->mutex->forks = malloc(sizeof(pthread_mutex_t)
		* data->info->nbr_philos);
	if (!data->mutex->forks)
		return (1);
	i = 0;
	while(i < data->info->nbr_philos)
	{
		if (pthread_mutex_init(&data->mutex->forks[i], NULL) != 0)
		{
			while(--i >= 0)
				pthread_mutex_destroy(&data->mutex->forks[i]);
			return (1);
		}
		i++;
	}
	pthread_mutex_init(&data->mutex->write_lock, NULL);
	pthread_mutex_init(&data->mutex->eat_lock, NULL);
	pthread_mutex_init(&data->mutex->death_lock, NULL);
	return (0);
}

int	init_philo(t_data *data, int i)
{
	data->arr_philo[i].id = i + 1;
	data->arr_philo[i].meals_eaten = 0;
	data->arr_philo[i].last_meal_eaten = data->info->start_time;
	data->arr_philo[i].left_fork = &data->mutex->forks[i];
	data->arr_philo[i].right_fork = &data->mutex->forks[(i + 1)
		% data->info->nbr_philos];
	data->arr_philo[i].data = data;
	return (0);
}

int	init_all_philos(t_data *data)
{
	int	i;

	i = 0;
	data->arr_philo = malloc(sizeof(t_philo) * data->info->nbr_philos);
	if (!data->arr_philo)
		return (1);
	while (i < data->info->nbr_philos)
	{
		if (init_philo(data, i))
			return (1);
		i++;
	}
	return (0);
}
