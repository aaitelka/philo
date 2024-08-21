/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:24:29 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 14:24:32 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_tolong(const char *str)
{
	int		index;
	long	result;

	index = 0;
	result = 0;
	if (str[index] == '\0')
		return (-1);
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (-1);
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}

// table->timeto[MUST_EAT] < 0) //TODO check this condition
int	ft_check_args(t_table *table)
{
	if (table->timeto[DIE] < MINTIME
		|| table->timeto[EAT] < MINTIME
		|| table->timeto[SLEEP] < MINTIME)
		return (-1);
	else if (table->philo_count > 200)
		return (EOUTOFRANGE);
	return (SUCCESS);
}
