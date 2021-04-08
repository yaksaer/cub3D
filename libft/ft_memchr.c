/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:00:44 by kseed             #+#    #+#             */
/*   Updated: 2020/11/04 21:39:23 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	ch;
	unsigned int	i;

	a = (unsigned char*)arr;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (a[i] == ch)
			return (a + i);
		i++;
	}
	return (NULL);
}
