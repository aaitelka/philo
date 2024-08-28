/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:00:45 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/28 00:49:12 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(const char *str)
{
	while (*str)
		write(STDERR_FILENO, str++, 1);
}

void	ft_print(t_philo *philo, t_state state)
{
	int		id;
	long	time;

	id = philo->id;
	sem_wait(philo->table->sem[PRINT]);
	if (!ft_is_done(philo->table))
	{
		time = ft_getstarttime(philo->table);
		if (state == TAKEN_FORK)
			printf("%ld\t%d %s", ft_gettimestamp() - time, id, MTAKEN_FORK);
		else if (state == EAT)
			printf("%ld\t%d %s", ft_gettimestamp() - time, id, MEAT);
		else if (state == SLEEP)
			printf("%ld\t%d %s", ft_gettimestamp() - time, id, MSLEEP);
		else if (state == THINK)
			printf("%ld\t%d %s", ft_gettimestamp() - time, id, MTHINK);
	}
	sem_post(philo->table->sem[PRINT]);
}
