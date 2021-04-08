/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:50 by kseed             #+#    #+#             */
/*   Updated: 2021/03/30 17:08:35 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	bmp_pixel_get(t_cub *cub, int x, int y)
{
	char	*dst;

	dst = cub->mlx.adr + (y * cub->mlx.line_sz + x * (cub->mlx.bpp / 8));
	return (*(unsigned int*)dst);
}

void			make_header(char *buf, int size, t_cub *cub)
{
	int		tmp;

	ft_memcpy(&buf[0], "BM", 2);
	ft_memcpy(&buf[2], &size, 4);
	tmp = 54;
	ft_memcpy(&buf[10], &tmp, 4);
	tmp = 40;
	ft_memcpy(&buf[14], &tmp, 4);
	ft_memcpy(&buf[18], &cub->parsed.width, 4);
	tmp = -cub->parsed.height;
	ft_memcpy(&buf[22], &tmp, 4);
	tmp = 1;
	ft_memcpy(&buf[26], &tmp, 2);
	ft_memcpy(&buf[28], &cub->mlx.bpp, 2);
}

void			fill_bmp(t_cub *cub, char *buf)
{
	int				i;
	int				j;
	int				pix;
	unsigned int	color;

	i = cub->parsed.height - 1;
	while (i > 0)
	{
		j = 0;
		while (j < cub->parsed.width)
		{
			color = bmp_pixel_get(cub, j, i);
			pix = (i * cub->parsed.width + j) * (cub->mlx.bpp / 8);
			*(unsigned int*)(buf + 54 + pix) = color;
			j++;
		}
		i--;
	}
}

void			make_bmp(t_cub *cub)
{
	int		fd;
	size_t	size;
	char	*buf;

	if ((fd = open("screen.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		return_error(cub, 19);
	make_window(cub);
	size = (cub->parsed.width * cub->parsed.height) * cub->mlx.bpp / 8 + 54;
	if (!(buf = (char*)ft_calloc(size, sizeof(char))))
		return_error(cub, 11);
	make_header(buf, size, cub);
	fill_bmp(cub, buf);
	if ((write(fd, buf, size)) == -1)
		return_error(cub, 19);
	close(fd);
	free(buf);
	return_error(cub, -1);
}
