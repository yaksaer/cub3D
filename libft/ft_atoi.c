/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:38:42 by kseed             #+#    #+#             */
/*   Updated: 2020/11/11 19:32:46 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	size_t			i;
	unsigned long	num;
	unsigned long	max;
	int				zn;

	i = 0;
	num = 0;
	zn = 1;
	max = (unsigned long)(__LONG_MAX__ / 10);
	i = ft_isspace(nptr, i);
	zn = (nptr[i] == '-') ? -1 : 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((num > max || (num == max && (nptr[i] - '0') > 7))
												&& zn == 1)
			return (-1);
		else if ((num > max || (num == max && (nptr[i] - '0') > 8))
												&& zn == -1)
			return (0);
		num = (10 * num) + (nptr[i] - '0');
		i++;
	}
	return ((int)(num * zn));
}
