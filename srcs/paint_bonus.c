/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:06:54 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 22:24:33 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		shadow_coef(t_cub *cub, float dist)
{
	if (dist > cub->parsed.map_str / 3)
		cub->wall.koef = 4;
	else if (dist > cub->parsed.map_str / 7)
		cub->wall.koef = 2;
	else
		cub->wall.koef = 1;
}

void		paint_health(t_cub *cub)
{
	int		w;
	int		h;

	if (cub->text.health != NULL)
		mlx_destroy_image(cub->mlx.ptr, cub->text.health);
	if (!(cub->text.health = mlx_xpm_file_to_image(cub->mlx.ptr,
		"./textures/health.xpm", &w, &h)))
		return_error(cub, 5);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->text.health, 0, 0);
}

void		paint_gun(t_cub *cub)
{
	int		w;
	int		h;

	if (cub->text.gun != NULL)
		mlx_destroy_image(cub->mlx.ptr, cub->text.gun);
	if (!(cub->text.gun = mlx_xpm_file_to_image(cub->mlx.ptr,
	"./textures/gun.xpm", &w, &h)))
		return_error(cub, 5);
	mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->text.gun,
	(cub->parsed.width - w) / 2, cub->parsed.height - h);
}

void		paint_bonus(t_cub *cub)
{
	paint_health(cub);
	paint_gun(cub);
}
