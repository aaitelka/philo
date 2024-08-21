/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 02:42:32 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 13:57:33 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_is_done(t_table *table)
{
	bool	done;

	pthread_mutex_lock(&table->lock);
	done = table->is_done;
	pthread_mutex_unlock(&table->lock);
	return (done);
}

long	ft_getstarttime(t_table *table)
{
	long	time;

	pthread_mutex_lock(&table->lock);
	time = table->start_time;
	pthread_mutex_unlock(&table->lock);
	return (time);
}
