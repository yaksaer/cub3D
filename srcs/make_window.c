/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:03 by kseed             #+#    #+#             */
/*   Updated: 2021/04/01 20:57:59 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		save_plr(t_cub *cub, int i, int j)
{
	if (cub->plr.pos_x > -1 || cub->plr.pos_y > -1)
		return_error(cub, 6);
	else if (cub->plr.pos_y == -1 && cub->plr.pos_x == -1)
	{
		cub->plr.pos_x = (float)i + 0.5;
		cub->plr.pos_y = (float)j + 0.5;
		cub->plr.cord_x = (float)i + 0.5;
		cub->plr.cord_y = (float)j + 0.5;
		if (cub->parsed.map[j][i] == 'N')
			cub->plr.angle = (float)(3 * M_PI_2);
		else if (cub->parsed.map[j][i] == 'S')
			cub->plr.angle = M_PI_2;
		else if (cub->parsed.map[j][i] == 'E')
			cub->plr.angle = 0;
		else if (cub->parsed.map[j][i] == 'W')
			cub->plr.angle = M_PI;
	}
}

void		make_image(t_cub *cub)
{
	mlx_destroy_image(cub->mlx.ptr, cub->mlx.img);
	if (!(cub->mlx.img = mlx_new_image(cub->mlx.ptr, cub->parsed.width,
			cub->parsed.height)))
		return_error(cub, 18);
	if (!(cub->mlx.adr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bpp,
		&cub->mlx.line_sz, &cub->mlx.end)))
		return_error(cub, 18);
	ft_ray(cub);
}

void		read_textu(t_cub *cub, int i)
{
	if (!(cub->text.imgptr[i] = mlx_xpm_file_to_image(cub->mlx.ptr,
		cub->parsed.path_tex[i], &cub->text.wid[i], &cub->text.hei[i])))
		return_error(cub, 18);
	if (!(cub->text.adr[i] = mlx_get_data_addr(cub->text.imgptr[i],
			&cub->text.bpp[i], &cub->text.line_sz[i], &cub->text.end[i])))
		return_error(cub, 18);
}

void		make_window(t_cub *cub)
{
	int		i;

	i = 0;
	if (!(cub->mlx.img = mlx_new_image(cub->mlx.ptr, cub->parsed.width,
		cub->parsed.height)))
		return_error(cub, 18);
	if (!(cub->mlx.adr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bpp,
		&cub->mlx.line_sz, &cub->mlx.end)))
		return_error(cub, 18);
	while (i < 5)
		read_textu(cub, i++);
	if (!(cub->plr.ray_len = (float*)ft_calloc(cub->parsed.width + 1,
									sizeof(float))))
		return_error(cub, 11);
	alloc(cub);
	make_image(cub);
	if (cub->parsed.save_flg == 0)
	{
		mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->mlx.img,
		0, 0);
		mlx_hook(cub->mlx.win, 17, 1L << 2, close_win, cub);
		mlx_hook(cub->mlx.win, 2, 1L << 0, key_hook, cub);
		mlx_loop(cub->mlx.ptr);
	}
}
