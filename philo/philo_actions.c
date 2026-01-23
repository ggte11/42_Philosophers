#include "philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex->eat_lock);
	philo->last_meal_eaten = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex->eat_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->data->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->info->nbr_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->info->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo->data))
	{
		eat(philo);
		if (is_dead(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->info->time_to_sleep);
		if (is_dead(philo->data))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}

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
		if (&data->arr_philo[i].meals_eaten >= &data->info->meal_amount)
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
			if (is_dead(data))
				return ;
			i++;
		}
		if (all_ate_enough(data))
			return ;
		usleep(100);
	}
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->info->nbr_philos)
	{
		if (pthread_create(&data->arr_philo[i].thread, NULL,
				philo_routine, &data->arr_philo[i]) != 0)
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
