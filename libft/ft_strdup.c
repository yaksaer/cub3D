/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:26:36 by kseed             #+#    #+#             */
/*   Updated: 2020/11/04 21:53:31 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int			i;
	int			j;
	char		*dest;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (!(dest = ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	while (j < i + 1)
	{
		dest[j] = s[j];
		j++;
	}
	return (dest);
}
