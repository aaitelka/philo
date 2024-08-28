/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:01:26 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/28 00:37:33 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	ft_is_done(t_table *table)
{
	bool	done;

	sem_wait(table->sem[LOCK]);
	done = table->is_done;
	sem_post(table->sem[LOCK]);
	return (done);
}

long	ft_getstarttime(t_table *table)
{
	long	time;

	sem_wait(table->sem[TIME]);
	time = table->start_time;
	sem_post(table->sem[TIME]);
	return (time);
}
