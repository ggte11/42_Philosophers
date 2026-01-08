/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:22:55 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/08 18:36:10 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int nb_params, char **params)
{
	int i;
	int j;

	j = 1;
	if (nb_params < 5 && nb_params > 6)
		return(write(2, "Incorrect number of arguments", 30));
	while (j < nb_params)
	{
		i = 0;
		while (params[j][i] != '\0')
		{
			if (!ft_isdigit(params[j][i]))
				return(write(2, "Invalid character", 18));
			i++;
		}
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parsing(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (initialize_info(data, argv))
		return (1);
	return (0);
}
