/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:52 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/14 18:12:23 by mcardoso         ###   ########.fr       */
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
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->mutex->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex->eat_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex->death_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->arr_philo = malloc(sizeof(t_philo) * data->info->nbr_philos);
	if (!data->arr_philo)
		return (1);
	i = 0;
	while(i < data->info->nbr_philos)
	{
		data->arr_philo[i].id = i + 1;
		data->arr_philo[i].meals_eaten = 0;
		data->arr_philo[i].last_meal_eaten = data->info->start_time;
		data->arr_philo[i].left_fork = &data->mutex->forks[i];
		data->arr_philo[i].right_fork = &data->mutex->forks[(i + 1)
			% data->info->nbr_philos];
		data->arr_philo[i].data = data;
		i++;
	}
	return (0);
}
