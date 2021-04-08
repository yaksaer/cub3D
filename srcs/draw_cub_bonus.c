/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:35 by kseed             #+#    #+#             */
/*   Updated: 2021/04/03 14:25:50 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		draw_floor_cellar(t_cub *cub)
{
	int		y;

	y = 0;
	while (y < cub->parsed.height)
	{
		if (y <= (cub->parsed.height / 2))
			pixel_put(cub, cub->wall.x, y, cub->parsed.ce_color);
		else if (y > (cub->parsed.height / 2))
			pixel_put(cub, cub->wall.x, y, cub->parsed.fl_color);
		y++;
	}
}

void		print_e_w(t_cub *cub, float start, float end)
{
	int		y;
	int		i;
	float	x;
	int		flag;

	y = (int)start;
	i = 0;
	if (cub->wall.size > (float)cub->parsed.height)
		i = (int)(cub->wall.size - (float)cub->parsed.height) / 2;
	if (cub->plr.quarter == 1 || cub->plr.quarter == 4)
		flag = 2;
	else if (cub->plr.quarter == 3 || cub->plr.quarter == 2)
		flag = 3;
	start = cub->wall.size / (float)cub->text.hei[flag];
	x = (cub->plr.ray_y - (int)cub->plr.ray_y) * cub->text.hei[flag];
	while ((float)y < end)
	{
		cub->text.color = pixel_get(cub, x, i / start, flag);
		shadow_coef(cub, cub->wall.dist);
		pixel_put(cub, cub->wall.x, y++, cub->text.color / cub->wall.koef);
		i++;
	}
}

void		print_s_n(t_cub *cub, float start, float end)
{
	int		y;
	int		i;
	float	x;
	int		flag;

	y = (int)start;
	i = 0;
	if (cub->wall.size > cub->parsed.height)
		i = (cub->wall.size - cub->parsed.height) / 2;
	if (cub->plr.quarter == 1 || cub->plr.quarter == 2)
		flag = 0;
	else if (cub->plr.quarter == 3 || cub->plr.quarter == 4)
		flag = 1;
	start = cub->wall.size / cub->text.hei[flag];
	x = (cub->plr.ray_x - (int)cub->plr.ray_x) * cub->text.hei[flag];
	while (y < end)
	{
		cub->text.color = pixel_get(cub, x, i / start, flag);
		shadow_coef(cub, cub->wall.dist);
		pixel_put(cub, cub->wall.x, y++, cub->text.color / cub->wall.koef);
		i++;
	}
}

float		calculate_walls(t_cub *cub, float ray_angle, char c)
{
	float		start;
	float		end;
	float		dist;
	float		tmp;

	tmp = ray_angle - cub->plr.angle;
	tmp = cosf(tmp) + 0.1;
	cub->wall.dist = (hypotf(cub->plr.ray_x - cub->plr.pos_x, cub->plr.ray_y -
		cub->plr.pos_y)) * tmp;
	cub->wall.size = cub->parsed.height / cub->wall.dist * cub->parsed.width /
			cub->parsed.height;
	start = (cub->parsed.height / 2) - (cub->wall.size / 2);
	end = (cub->parsed.height / 2) + (cub->wall.size / 2);
	if (start < 0)
		start = 0;
	if (end > cub->parsed.height)
		end = cub->parsed.height - 1;
	define_quarter(cub, ray_angle);
	if (c == 'y')
		print_s_n(cub, start, end);
	else if (c == 'x')
		print_e_w(cub, start, end);
	return (cub->wall.dist);
}

void		ft_ray(t_cub *cub)
{
	float	start;
	float	tmp;

	start = cub->plr.angle - (FOV / 2);
	cub->wall.x = 0;
	while (cub->wall.x < cub->parsed.width)
	{
		cub->plr.ray_x = cub->plr.pos_x;
		cub->plr.ray_y = cub->plr.pos_y;
		draw_floor_cellar(cub);
		while ((cub->plr.ray_x <= cub->parsed.max_str && cub->plr.ray_y <=
		cub->parsed.map_str) && (cub->plr.ray_x > 0 && cub->plr.ray_y > 0))
		{
			cub->plr.ray_x += cosf(start) / 120;
			if ((tmp = check_wall_ray(cub, start, 'x')) > 0)
				break ;
			cub->plr.ray_y += sinf(start) / 120;
			if ((tmp = check_wall_ray(cub, start, 'y')) > 0)
				break ;
		}
		cub->plr.ray_len[++cub->wall.x] = tmp;
		start += (FOV) / cub->parsed.width;
	}
	start_sprites(cub);
}
