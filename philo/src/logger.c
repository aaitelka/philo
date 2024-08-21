/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:21:01 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 14:00:11 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->table->print_lock);
	if (!ft_is_done(philo->table))
	{
		time = ft_getstarttime(philo->table);
		if (state == TAKEN_FORK)
			printf("%ld\t%d %s\n", ft_gettimestamp() - time, id, MTAKEN_FORK);
		else if (state == EAT)
			printf("%ld\t%d %s\n", ft_gettimestamp() - time, id, MEAT);
		else if (state == SLEEP)
			printf("%ld\t%d %s\n", ft_gettimestamp() - time, id, MSLEEP);
		else if (state == THINK)
			printf("%ld\t%d %s\n", ft_gettimestamp() - time, id, MTHINK);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
