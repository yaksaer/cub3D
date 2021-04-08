/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:18:51 by kseed             #+#    #+#             */
/*   Updated: 2020/11/04 21:41:20 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*b;
	unsigned int	i;

	b = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		b[i] = c;
		i++;
	}
	return (b);
}
