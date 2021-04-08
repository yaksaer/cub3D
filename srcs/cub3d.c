/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:29 by kseed             #+#    #+#             */
/*   Updated: 2021/03/30 17:00:13 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		fill_parsed(t_cub *cub)
{
	t_tex		text;
	t_sprite	spr;
	t_iter		iter;

	cub->text = text;
	cub->spr = spr;
	cub->iter = iter;
	ft_bzero(&cub->text, sizeof(t_tex));
	ft_bzero(&cub->spr, sizeof(t_sprite));
	ft_bzero(&cub->iter, sizeof(t_iter));
	cub->parsed.width = 0;
	cub->parsed.height = 0;
	cub->plr.pos_x = -1;
	cub->plr.pos_y = -1;
	cub->parsed.fl_color = -1;
	cub->parsed.ce_color = -1;
}

void		fill_cub_mlx(t_cub *cub)
{
	t_mlx		mlx;
	t_pars		parsed;
	t_player	plr;
	t_wall		wall;
	t_list		*list;

	cub->mlx = mlx;
	cub->parsed = parsed;
	cub->plr = plr;
	cub->wall = wall;
	cub->list = list;
	ft_bzero(&cub->mlx, sizeof(t_mlx));
	ft_bzero(&cub->parsed, sizeof(t_pars));
	ft_bzero(&cub->plr, sizeof(t_player));
	ft_bzero(&cub->wall, sizeof(t_wall));
	fill_parsed(cub);
}

int			main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	fill_cub_mlx(&cub);
	if (argc > 3 || argc == 1)
		return_error(&cub, 3);
	check_arguments(&cub, argc, argv[1], argv[2]);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return_error(&cub, 4);
	ft_pars(&cub, fd);
	check_text(&cub);
	if (cub.plr.pos_x == -1 || cub.plr.pos_y == -1)
		return_error(&cub, 7);
	cub.mlx.ptr = mlx_init();
	if (cub.parsed.save_flg == 0)
	{
		if (!(cub.mlx.win = mlx_new_window(cub.mlx.ptr, cub.parsed.width,
									cub.parsed.height, "cub3D")))
			return_error(&cub, 18);
		make_window(&cub);
	}
	make_bmp(&cub);
	return (1);
}
