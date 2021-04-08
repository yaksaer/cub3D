/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:26 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 21:27:35 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		sort_sprites(t_cub *cub, int i)
{
	int		step;

	step = cub->spr.count;
	while (step >= 1)
	{
		i = -1;
		while (++i + step <= cub->spr.count)
		{
			if (cub->spr.dist[i] < cub->spr.dist[i + step])
			{
				cub->iter.tmp_d = cub->spr.dist[i];
				cub->iter.tmp_x = cub->spr.x[i];
				cub->iter.tmp_y = cub->spr.y[i];
				cub->spr.dist[i] = cub->spr.dist[i + step];
				cub->spr.dist[i + step] = cub->iter.tmp_d;
				cub->spr.x[i] = cub->spr.x[i + step];
				cub->spr.x[i + step] = cub->iter.tmp_x;
				cub->spr.y[i] = cub->spr.y[i + step];
				cub->spr.y[i + step] = cub->iter.tmp_y;
			}
		}
		step /= 1.247;
	}
}

void		print_sprites(t_cub *cub, int s, int i)
{
	int		j;

	while (++i < cub->spr.size[s])
	{
		if (cub->spr.first_x[s] + i < 0 ||
			cub->spr.first_x[s] + i >= cub->parsed.width)
			continue;
		if (cub->plr.ray_len[(int)cub->spr.first_x[s] + i] < cub->spr.dist[s]
			&& cub->plr.ray_len[(int)cub->spr.first_x[s] + i] > 0)
			continue;
		j = -1;
		while (++j < cub->spr.size[s])
		{
			if (cub->spr.first_y[s] + j < 0 || cub->spr.first_y[s] + j >=
				cub->parsed.height)
				continue;
			cub->text.color = pixel_get(cub, (i * cub->text.hei[4] /
			cub->spr.size[s]), (j * cub->text.hei[4] /
			cub->spr.size[s]), 4);
			cub->text.color != 0 ? pixel_put(cub, cub->spr.first_x[s] + i,
			cub->spr.first_y[s] + j, cub->text.color) : 0;
		}
	}
}

void		calculate_sprites(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < cub->spr.count)
	{
		cub->spr.dir[i] = atan2f(cub->spr.y[i] - cub->plr.pos_y,
					cub->spr.x[i] - cub->plr.pos_x);
		while (cub->spr.dir[i] - cub->plr.angle > M_PI)
			cub->spr.dir[i] -= 2 * M_PI;
		while (cub->spr.dir[i] - cub->plr.angle < -M_PI)
			cub->spr.dir[i] += 2 * M_PI;
		cub->spr.size[i] = cub->parsed.height / cub->spr.dist[i] *
				cub->parsed.width / cub->parsed.height;
		if (cub->spr.size[i] > 2000)
			cub->spr.size[i] = 2000;
		cub->spr.first_x[i] = ((cub->spr.dir[i] - cub->plr.angle) *
				cub->parsed.width / FOV + (cub->parsed.width / 2) -
				cub->spr.size[i] / 2);
		cub->spr.first_y[i] = (cub->parsed.height / 2) - (cub->spr.size[i] / 2);
		i++;
	}
}

void		alloc(t_cub *cub)
{
	if (!(cub->spr.size = ft_calloc(cub->spr.count + 1, sizeof(float))))
		return_error(cub, 11);
	if (!(cub->spr.dir = ft_calloc(cub->spr.count + 1, sizeof(float))))
		return_error(cub, 11);
	if (!(cub->spr.first_x = ft_calloc(cub->spr.count + 1, sizeof(int))))
		return_error(cub, 11);
	if (!(cub->spr.first_y = ft_calloc(cub->spr.count + 1, sizeof(int))))
		return_error(cub, 11);
}

void		start_sprites(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->spr.count)
	{
		cub->spr.dist[i] = (hypot(cub->plr.pos_x - cub->spr.x[i],
			cub->plr.pos_y - cub->spr.y[i]));
		i++;
	}
	sort_sprites(cub, i);
	calculate_sprites(cub);
	i = 0;
	while (i < cub->spr.count)
	{
		j = -1;
		if (cub->spr.dist[i] > 0.3)
			print_sprites(cub, i, j);
		i++;
	}
}
