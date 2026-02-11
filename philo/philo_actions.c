/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:13:44 by martim            #+#    #+#             */
/*   Updated: 2026/02/11 15:45:36 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	get_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	if (is_dead(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex->eat_lock);
	philo->last_meal_eaten = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex->eat_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->data, philo->data->info->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->info->nbr_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data, philo->data->info->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data, 10);
	while (!is_dead(philo->data))
	{
		eat(philo);
		if (is_dead(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->info->time_to_sleep);
		if (is_dead(philo->data))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	data->info->start_time = get_time();
	i = 0;
	while (i < data->info->nbr_philos)
	{
		data->arr_philo[i].last_meal_eaten = data->info->start_time;
		if (pthread_create(&data->arr_philo[i].thread, NULL, philo_routine,
				&data->arr_philo[i]) != 0)
			return (1);
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->info->nbr_philos)
	{
		pthread_join(data->arr_philo[i].thread, NULL);
		i++;
	}
	return (0);
}
