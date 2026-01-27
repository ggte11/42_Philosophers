/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martim <martim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:55 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/27 15:48:26 by martim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parsing(int nb_params, char **params)
{
	int i;
	int j;

	j = 1;
	if (nb_params != 5 && nb_params != 6)
		return(write(2, "Incorrect number of arguments", 30));
	while (j < nb_params)
	{
		i = 0;
		while (params[j][i] != '\0')
		{
			if (!ft_isdigit(params[j][i]))
				return(write(2, "Invalid parameter character", 28));
			i++;
		}
		j++;
	}
	return (0);
}

bool	is_dead(t_data *data)
{
	bool	dead;

	pthread_mutex_lock(&data->mutex->death_lock);
	dead = !data->info->all_philos_alive;
	pthread_mutex_unlock(&data->mutex->death_lock);
	return (dead);
}

static void	clean_all(t_data **data)
{
	int	i;

	if (!data || !*data)
		return ;
	if ((*data)->mutex)
	{
		if ((*data)->mutex->forks)
		{
			i = -1;
			while (++i < (*data)->info->nbr_philos)
				pthread_mutex_destroy(&(*data)->mutex->forks[i]);
			free((*data)->mutex->forks);
		}
		pthread_mutex_destroy(&(*data)->mutex->write_lock);
		pthread_mutex_destroy(&(*data)->mutex->eat_lock);
		pthread_mutex_destroy(&(*data)->mutex->death_lock);
		free((*data)->mutex);
	}
	if ((*data)->arr_philo)
		free((*data)->arr_philo);
	if ((*data)->info)
		free((*data)->info);
	free(*data);
	*data = NULL;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parsing(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->info = NULL;
	data->mutex = NULL;
	data->arr_philo = NULL;
	if (init_info(data, argv) || init_mutex(data) || init_all_philos(data))
	{
		clean_all(&data);
		return (1);
	}
	start_simulation(data);
	clean_all(&data);
	return (0);
}
