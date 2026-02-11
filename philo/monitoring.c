/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:01:01 by martim            #+#    #+#             */
/*   Updated: 2026/02/11 15:27:16 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Checks all philosophers for required number of meals.
/// @param data
/// @return int
static int	all_ate_enough(t_data *data)
{
	int	i;
	int	finished;

	if (data->info->meal_amount == -1)
		return (0);
	finished = 0;
	i = 0;
	pthread_mutex_lock(&data->mutex->eat_lock);
	while (i < data->info->nbr_philos)
	{
		if (data->arr_philo[i].meals_eaten >= data->info->meal_amount)
			finished++;
		i++;
	}
	pthread_mutex_unlock(&data->mutex->eat_lock);
	if (finished == data->info->nbr_philos)
	{
		pthread_mutex_lock(&data->mutex->death_lock);
		data->info->all_philos_alive = false;
		pthread_mutex_unlock(&data->mutex->death_lock);
		return (1);
	}
	return (0);
}

static int	check_if_dead(t_data *data, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&data->mutex->eat_lock);
	time_since_meal = get_time() - data->arr_philo[i].last_meal_eaten;
	pthread_mutex_unlock(&data->mutex->eat_lock);
	if (time_since_meal > data->info->time_to_die)
	{
		pthread_mutex_lock(&data->mutex->write_lock);
		pthread_mutex_lock(&data->mutex->death_lock);
		data->info->all_philos_alive = false;
		printf("%ld %d died\n", get_time() - data->info->start_time,
			data->arr_philo[i].id);
		pthread_mutex_unlock(&data->mutex->death_lock);
		pthread_mutex_unlock(&data->mutex->write_lock);
		return (1);
	}
	return (0);
}

/// @brief loop that checks for deaths and meal completion.
/// @param data
void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->info->nbr_philos)
		{
			if (check_if_dead(data, i))
				return ;
			i++;
		}
		if (all_ate_enough(data))
			return ;
		ft_usleep(data, 50);
	}
}
