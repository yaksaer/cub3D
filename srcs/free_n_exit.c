/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:38 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 20:08:40 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		free_map(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < cub->parsed.map_str)
	{
		if (cub->parsed.map[i] != NULL)
			free(cub->parsed.map[i]);
		i++;
	}
}

void		free_all(t_cub *cub)
{
	free_map(cub);
	if (cub->parsed.map != NULL)
		free(cub->parsed.map);
	if (cub->spr.size != NULL)
		free(cub->spr.size);
	if (cub->spr.dist != NULL)
		free(cub->spr.dist);
	if (cub->spr.dir != NULL)
		free(cub->spr.dir);
	if (cub->spr.x != NULL)
		free(cub->spr.x);
	if (cub->spr.y != NULL)
		free(cub->spr.y);
	if (cub->spr.first_x != NULL)
		free(cub->spr.first_x);
	if (cub->spr.first_y != NULL)
		free(cub->spr.first_y);
	if (cub->plr.ray_len != NULL)
		free(cub->plr.ray_len);
	if (cub->mlx.win != NULL)
		mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
}

void		error_code_two(t_cub *cub, int err)
{
	if (err == 10)
		printf("Error\nThere is no floor/ceiling color!\n");
	else if (err == 11)
		printf("Error\nMalloc error\n");
	else if (err == 12)
		printf("Error\nStrings are repeat!\n");
	else if (err == 13)
		printf("Error\nGarbage in parameters!\n");
	else if (err == 14)
		printf("Error\nNo resolution!\n");
	else if (err == 15)
		printf("Error\nMinimum resolution is 10!\n");
	else if (err == 16)
		printf("Error\nToo many empty lines in map!\n");
	else if (err == 17)
		printf("Error\nGarbage in map!\n");
	else if (err == 18)
		printf("Error\nMLX error!\n");
	else if (err == 19)
		printf("Error\nScreenshot error!\n");
}

void		return_error(t_cub *cub, int err)
{
	free_all(cub);
	if (err == 0)
		printf("Error\nMap is't valid!\n");
	else if (err == 1)
		printf("Error\nResolution is't valid!\n");
	else if (err == 2)
		printf("Error\nFloor/ceiling color is't valid!\n");
	else if (err == 3)
		printf("Error\nNumber of arguments is't valid!\n");
	else if (err == 4)
		printf("Error\nArgumets error!\n");
	else if (err == 5)
		printf("Error\nOpen textures error!\n");
	else if (err == 6)
		printf("Error\nTwo players on map!\n");
	else if (err == 7)
		printf("Error\nNo player/not valid letter of the player!\n");
	else if (err == 8)
		printf("Error\nToo many numbers in resolution string!\n");
	else if (err == 9)
		printf("Error\nThere is no resolution in map file!\n");
	error_code_two(cub, err);
	exit(0);
}

void		remember_sprites(t_cub *cub)
{
	int		i;

	i = 0;
	if (!(cub->spr.x = (float*)ft_calloc(cub->spr.count + 1, sizeof(float))))
		return_error(cub, 11);
	if (!(cub->spr.y = (float*)ft_calloc(cub->spr.count + 1, sizeof(float))))
		return_error(cub, 11);
	if (!(cub->spr.dist = (float*)ft_calloc(cub->spr.count + 1, sizeof(float))))
		return_error(cub, 11);
	cub->iter.y = -1;
	while (++cub->iter.y < cub->parsed.map_str)
	{
		cub->iter.x = -1;
		while (++cub->iter.x < cub->parsed.max_str)
		{
			if (cub->parsed.map[cub->iter.y][cub->iter.x] == '2')
			{
				cub->spr.x[i] = (float)cub->iter.x + 0.5;
				cub->spr.y[i] = (float)cub->iter.y + 0.5;
				i++;
			}
		}
	}
}
