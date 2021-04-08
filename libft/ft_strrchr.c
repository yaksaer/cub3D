/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:52:49 by kseed             #+#    #+#             */
/*   Updated: 2020/11/12 17:28:44 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*d;
	char	sim;
	int		i;

	d = (char*)s;
	sim = (char)c;
	i = ft_strlen(d);
	while (i >= 0 && !(d[i] == sim))
		i--;
	if (d[i] == sim)
		return (d + i);
	return (NULL);
}
