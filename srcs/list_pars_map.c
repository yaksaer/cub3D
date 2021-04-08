/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:22:19 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 20:05:14 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			close_map(t_cub *cub, int i, int j)
{
	if (cub->parsed.map[j][i] == '0' || cub->parsed.map[j][i] == '2' ||
		cub->parsed.map[j][i] == 'N' || cub->parsed.map[j][i] == 'S' ||
		cub->parsed.map[j][i] == 'W' || cub->parsed.map[j][i] == 'E')
	{
		if (j + 1 >= cub->parsed.map_str || i + 1 >= cub->parsed.max_str ||
			j - 1 < 0 || i - 1 < 0)
			return (-1);
		else if (cub->parsed.map[j + 1][i] == ' ' ||
		cub->parsed.map[j][i + 1] == ' ' || cub->parsed.map[j - 1][i] == ' '
		|| cub->parsed.map[j][i - 1] == ' ')
			return (-1);
		return (1);
	}
	return (1);
}

void		recognize_list_size(t_cub *cub)
{
	t_list		*tmp;
	int			i;

	tmp = cub->list;
	cub->parsed.map_str = ft_lstsize(cub->list);
	while (tmp)
	{
		cub->parsed.max_str = max(ft_strlen(tmp->content), cub->parsed.max_str);
		tmp = tmp->next;
	}
	if (!(cub->parsed.map = (char**)ft_calloc(cub->parsed.map_str + 1,
		sizeof(char*))))
		return_error(cub, 11);
	tmp = cub->list;
	i = 0;
	while (tmp)
	{
		if (!(cub->parsed.map[i] = (char*)ft_calloc(cub->parsed.max_str + 1,
				sizeof(char))))
			return_error(cub, 11);
		ft_strlcpy(cub->parsed.map[i], tmp->content, cub->parsed.max_str + 1);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&cub->list, free);
}

void		fill_list(t_cub *cub, char *line)
{
	t_list		*tmp;
	int			i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		i = ft_isspace(line, i);
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' &&
		line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
		&& line[i] != '\0')
			return_error(cub, 0);
	}
	if (cub->parsed.empt >= 2)
		return_error(cub, 16);
	if (!(tmp = ft_lstnew(line)))
		return_error(cub, 11);
	ft_lstadd_back(&cub->list, tmp);
}

void		improve_resolution(t_cub *cub)
{
	int		w;
	int		h;

	if (cub->parsed.width == 0 && cub->parsed.height == 0)
		return_error(cub, 14);
	if (cub->parsed.width < 10 || cub->parsed.height < 10)
		return_error(cub, 15);
	mlx_get_screen_size(&w, &h);
	if (cub->parsed.save_flg == 0)
	{
		cub->parsed.width > w ? cub->parsed.width = w : 0;
		cub->parsed.height > h ? cub->parsed.height = h : 0;
	}
	else if (cub->parsed.save_flg == 1)
	{
		cub->parsed.width > 8000 ? cub->parsed.width = 8000 : 0;
		cub->parsed.height > 8000 ? cub->parsed.height = 8000 : 0;
	}
}
