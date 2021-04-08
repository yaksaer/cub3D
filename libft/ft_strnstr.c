/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:12:45 by kseed             #+#    #+#             */
/*   Updated: 2020/11/09 22:54:55 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!little[0])
		return ((char*)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j] && i + j < len &&
				big[i + j] == little[j])
		{
			j++;
		}
		if (!little[j])
			return (((char*)big) + i);
		i++;
	}
	return (NULL);
}
