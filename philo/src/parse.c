/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:24:29 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/22 03:28:58 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_tolong(const char *str)
{
	int		index;
	long	result;

	index = 0;
	result = 0;
	if (str[index] == '\0')
		return (ERROR);
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (ERROR);
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > INT_MAX)
		return (ERROR);
	return (result);
}

int	ft_check_args(t_table *table)
{
	if (table->timeto[DIE] < MINTIME
		|| table->timeto[EAT] < MINTIME
		|| table->timeto[SLEEP] < MINTIME
		|| (table->timeto[MUST_EAT] < 1 && table->has_must_eat))
		return (ERROR);
	else if (table->philo_count > 200)
		return (EOUTOFRANGE);
	return (SUCCESS);
}
