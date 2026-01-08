/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:52 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/08 18:31:51 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_info(t_data *data, char **str)
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

