/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:44 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 19:15:35 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		close_win(t_cub *cub)
{
	mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
	mlx_destroy_image(cub->mlx.ptr, cub->mlx.img);
	cub->mlx.win = NULL;
	cub->mlx.img = NULL;
	cub->mlx.ptr = NULL;
	return_error(cub, -1);
	return (0);
}

void	move_back_forw(t_cub *cub, int key)
{
	if (key == 13)
	{
		cub->plr.pos_y += sinf(cub->plr.angle) * SPEED;
		cub->plr.pos_x += cosf(cub->plr.angle) * SPEED;
	}
	else if (key == 1)
	{
		cub->plr.pos_y -= sinf(cub->plr.angle) * SPEED;
		cub->plr.pos_x -= cosf(cub->plr.angle) * SPEED;
	}
}

int		movement(int key, t_cub *cub)
{
	if (key == 53)
		close_win(cub);
	else if (key == 13 || key == 1)
		move_back_forw(cub, key);
	else if (key == 0)
	{
		cub->plr.pos_y -= cosf(cub->plr.angle) * SPEED;
		cub->plr.pos_x += sinf(cub->plr.angle) * SPEED;
	}
	else if (key == 2)
	{
		cub->plr.pos_y += cosf(cub->plr.angle) * SPEED;
		cub->plr.pos_x -= sinf(cub->plr.angle) * SPEED;
	}
	else if (key == 123)
		cub->plr.angle -= 0.1;
	else if (key == 124)
		cub->plr.angle += 0.1;
	if (cub->plr.pos_x > cub->parsed.width || cub->plr.pos_y >
		cub->parsed.height)
		return (0);
	return (1);
}

int		key_hook(int key, t_cub *cub)
{
	cub->plr.cord_y = cub->plr.pos_y;
	cub->plr.cord_x = cub->plr.pos_x;
	if (key == 53 || key == 13 || key == 1 || key == 0 || key == 2 ||
		key == 123 || key == 124)
	{
		if (!movement(key, cub))
		{
			cub->plr.pos_y = cub->plr.cord_y;
			cub->plr.pos_x = cub->plr.cord_x;
		}
		make_image(cub);
		mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win,
			cub->mlx.img, 0, 0);
	}
	return (1);
}
