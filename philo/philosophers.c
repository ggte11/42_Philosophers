/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:55 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/23 16:58:49 by mcardoso         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parsing(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_info(data, argv) || init_mutex(data) || init_all_philos(data))
		return (1);
	start_simulation(data);
	return (0);
}
