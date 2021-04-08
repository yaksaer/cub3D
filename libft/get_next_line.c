/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:14:30 by kseed             #+#    #+#             */
/*   Updated: 2020/12/20 16:43:43 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free(char *s1, int flag)
{
	if (flag == 1)
	{
		free(s1);
		return (-1);
	}
	else
	{
		free(s1);
		s1 = NULL;
	}
	return (1);
}

int		check_error(int fd, char **remem)
{
	if (fd < 0 || (read(fd, 0, 0) < 0))
		return (-1);
	if (!*remem)
	{
		if (!(*remem = (char*)malloc(1)))
			return (-1);
		*remem[0] = '\0';
	}
	return (0);
}

char	*make_line(char *remem)
{
	char	*res;
	int		i;

	i = 0;
	while (remem[i] && remem[i] != '\n')
		i++;
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (remem[i] && remem[i] != '\n')
	{
		res[i] = remem[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*make_remem(char *remem)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (remem[i] && remem[i] != '\n')
		i++;
	while (remem[j])
		j++;
	if (!(res = (char*)malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	i++;
	j = 0;
	while (remem[i])
		res[j++] = remem[i++];
	res[j] = '\0';
	free(remem);
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char	*remem;
	char		buf[1024];
	int			byte;

	if (!line || ((check_error(fd, &remem)) == -1))
		return (-1);
	byte = 1;
	ft_bzero(buf, 1024);
	while (!(ft_strchr(remem, '\n')) && byte != 0)
	{
		if ((byte = read(fd, buf, 1023)) < 0)
			return (ft_free(remem, 1));
		buf[byte] = '\0';
		if (!(remem = ft_strjoin(remem, buf)))
			return (ft_free(remem, 1));
	}
	if (!(*line = make_line(remem)))
		return (ft_free(remem, 1));
	if (byte == 0)
		ft_free(remem, 2);
	if (byte != 0)
		if (!(remem = make_remem(remem)))
			return (ft_free(remem, 1));
	return (byte > 0 ? 1 : 0);
}
