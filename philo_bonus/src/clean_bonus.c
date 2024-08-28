/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:19:48 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/27 17:27:38 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unlink_all(t_table *table)
{
	int	index;

	index = -1;
	while (++index < SEM_SIZE)
		sem_unlink(table->name[index]);
	index = -1;
	while (++index < table->philo_count)
		sem_unlink(table->name[index]);
}
