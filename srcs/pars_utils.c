/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:15 by kseed             #+#    #+#             */
/*   Updated: 2021/03/30 17:34:10 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		read_map(t_cub *cub)
{
	cub->iter.y = 0;
	while (cub->iter.y < cub->parsed.map_str)
	{
		cub->iter.x = 0;
		while (cub->iter.x < cub->parsed.max_str)
		{
			if ((close_map(cub, cub->iter.x, cub->iter.y)) < 0)
				return_error(cub, 0);
			else if (cub->parsed.map[cub->iter.y][cub->iter.x] == '2')
				cub->spr.count++;
			cub->iter.x++;
		}
		cub->iter.y++;
	}
	remember_sprites(cub);
}

void		fill_map(t_cub *cub)
{
	int		i;
	int		j;

	j = 0;
	while (j < cub->parsed.map_str)
	{
		i = 0;
		while (i < cub->parsed.max_str)
		{
			if (cub->parsed.map[j][i] == 'N' || cub->parsed.map[j][i] == 'E' ||
				cub->parsed.map[j][i] == 'S' || cub->parsed.map[j][i] == 'W')
				save_plr(cub, i, j);
			if (cub->parsed.map[j][i] != '0' && cub->parsed.map[j][i] != '1' &&
				cub->parsed.map[j][i] != '2' && cub->parsed.map[j][i] != 'N' &&
				cub->parsed.map[j][i] != 'S' && cub->parsed.map[j][i] != 'E' &&
				cub->parsed.map[j][i] != 'W')
				cub->parsed.map[j][i] = ' ';
			i++;
		}
		j++;
	}
}

void		check_text(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		if ((open(cub->parsed.path_tex[i], O_RDONLY)) < 0)
			return_error(cub, 5);
		j = ft_strlen(cub->parsed.path_tex[i]) - 1;
		if (cub->parsed.path_tex[i][j] != 'm' || cub->parsed.path_tex[i][j - 1]
			!= 'p' || cub->parsed.path_tex[i][j - 2] != 'x' ||
			cub->parsed.path_tex[i][j - 3] != '.')
			return_error(cub, 5);
		i++;
	}
	if (cub->parsed.height < 0 || cub->parsed.width < 0)
		return_error(cub, 9);
	if (cub->parsed.ce_color < 0 || cub->parsed.fl_color < 0)
		return_error(cub, 10);
}

void		check_arguments(t_cub *cub, int num, char *map, char *save)
{
	int		i;

	i = ft_strlen(map) - 1;
	if (map[i] != 'b' || map[i - 1] != 'u' || map[i - 2] != 'c' ||
		map[i - 3] != '.')
		return_error(cub, 4);
	if (num == 3)
	{
		i = ft_strlen(save) - 1;
		if (save[i] != 'e' || save[i - 1] != 'v' || save[i - 2] != 'a' ||
			save[i - 3] != 's' || save[i - 4] != '-' || save[i - 5] != '-')
			return_error(cub, 4);
		else
			cub->parsed.save_flg = 1;
	}
}
