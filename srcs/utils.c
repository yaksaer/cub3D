/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:29 by kseed             #+#    #+#             */
/*   Updated: 2021/03/28 20:31:30 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				define_quarter(t_cub *cub, float ray_angle)
{
	if (sin(ray_angle) <= 0 && cos(ray_angle) >= 0)
		cub->plr.quarter = 4;
	else if (sin(ray_angle) <= 0 && cos(ray_angle) <= 0)
		cub->plr.quarter = 3;
	else if (sin(ray_angle) >= 0 && cos(ray_angle) <= 0)
		cub->plr.quarter = 2;
	else if (sin(ray_angle) >= 0 && cos(ray_angle) >= 0)
		cub->plr.quarter = 1;
	return (1);
}

unsigned int	pixel_get(t_cub *cub, int x, int y, int flag)
{
	char	*dst;

	dst = cub->text.adr[flag] + (y * cub->text.line_sz[flag] +
		x * (cub->text.bpp[flag] / 8));
	return (*(unsigned int*)dst);
}

void			pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0)
		x = 0;
	dst = cub->mlx.adr + (y * cub->mlx.line_sz + x * (cub->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

float			max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float			check_wall_ray(t_cub *cub, float start, char c)
{
	if (cub->plr.ray_x < cub->parsed.max_str && cub->plr.ray_y <
												cub->parsed.map_str)
	{
		if (cub->parsed.map[(int)(cub->plr.ray_y)][(int)(cub->plr.ray_x)]
			== '1')
			return (calculate_walls(cub, start, c));
	}
	return (0);
}
