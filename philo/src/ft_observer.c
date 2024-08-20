/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:38:47 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 16:08:08 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	observer(t_philo *philo)
{
	int		index;

	index = 0;
		printf("----------> is_done: %d\n", philo->table->is_done);
	while (true)
	{
		printf("----------> is_done: %d\n", philo->table->is_done);
		if (get_timestamp() - philo[index].last_eat > philo->table->timeto[DIE])
		{
			philo->table->is_done = true;
			ft_print(&philo[index], DIE);
			break ;
		}
		index++;
		if (index == philo->table->philo_count)
			index = 0;
	}
}
