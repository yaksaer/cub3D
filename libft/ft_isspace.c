/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:37:01 by kseed             #+#    #+#             */
/*   Updated: 2020/11/08 22:39:02 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(const char *buff, int j)
{
	while (buff[j] == ' ' || buff[j] == '\f' || buff[j] == '\n' ||
		buff[j] == '\r' || buff[j] == '\t' || buff[j] == '\v')
	{
		j++;
	}
	return (j);
}
