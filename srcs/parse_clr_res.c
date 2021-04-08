/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clr_res.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:22 by kseed             #+#    #+#             */
/*   Updated: 2021/04/02 20:53:16 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		write_resolution(t_cub *cub, char *tmp, int flag)
{
	int		j;

	if (cub->list != NULL)
		return_error(cub, 13);
	j = 0;
	if (flag == 0)
	{
		while (tmp[j] != '\0')
		{
			cub->parsed.width = (10 * cub->parsed.width) + (tmp[j++] - '0');
			if (cub->parsed.width > 100000)
				cub->parsed.width /= 10;
		}
	}
	else
	{
		while (tmp[j] != '\0')
		{
			cub->parsed.height = (10 * cub->parsed.height) + (tmp[j++] - '0');
			if (cub->parsed.height > 100000)
				cub->parsed.height /= 10;
		}
	}
	return (++flag);
}

void	pars_resolution(char *line, t_cub *cub)
{
	int		i;
	int		j;
	char	tmp[128];
	int		flag;

	ft_bzero(tmp, 128);
	flag = 0;
	i = 0;
	cub->parsed.height > 0 ? return_error(cub, 12) : 0;
	cub->parsed.width > 0 ? return_error(cub, 12) : 0;
	while (line[i++] != '\0')
		if (!(ft_isdigit(line[i])) && line[i] != ' ' && line[i] != '\0')
			(return_error(cub, 1));
	i = 1;
	while ((ft_isdigit(line[i]) || line[i] == ' ') && line[i] != '\0')
	{
		j = 0;
		i = ft_isspace(line, i);
		while (ft_isdigit(line[i]))
			tmp[j++] = line[i++];
		tmp[j] = '\0';
		if ((flag = write_resolution(cub, tmp, flag)) > 2)
			break ;
	}
	flag > 2 ? return_error(cub, 8) : 0;
}

void	pars_floor_clr(char *line, t_cub *cub, int i)
{
	int		count;

	cub->iter.g = 0;
	cub->iter.b = 0;
	cub->parsed.fl_color != -1 ? return_error(cub, 12) : 0;
	while (line[i++] != '\0')
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		while (ft_isdigit(line[i]))
		{
			if (count == 0)
				cub->iter.r = (10 * cub->iter.r) + (line[i++] - '0');
			if (count == 1)
				cub->iter.g = (10 * cub->iter.g) + (line[i++] - '0');
			if (count == 2)
				cub->iter.b = (10 * cub->iter.b) + (line[i++] - '0');
			if (cub->iter.r > 255 || cub->iter.g > 255 || cub->iter.b > 255)
				return_error(cub, 2);
		}
		count++;
	}
	cub->parsed.fl_color = ((cub->iter.r << 16) | (cub->iter.g << 8) |
			cub->iter.b);
}

void	pars_ceiling_clr(char *line, t_cub *cub, int i)
{
	int		count;

	cub->iter.g = 0;
	cub->iter.b = 0;
	cub->parsed.ce_color != -1 ? return_error(cub, 12) : 0;
	while (line[i++] != '\0')
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		while (ft_isdigit(line[i]))
		{
			if (count == 0)
				cub->iter.r = (10 * cub->iter.r) + (line[i++] - '0');
			if (count == 1)
				cub->iter.g = (10 * cub->iter.g) + (line[i++] - '0');
			if (count == 2)
				cub->iter.b = (10 * cub->iter.b) + (line[i++] - '0');
			if (cub->iter.r > 255 || cub->iter.g > 255 || cub->iter.b > 255)
				return_error(cub, 2);
		}
		count++;
	}
	cub->parsed.ce_color = ((cub->iter.r << 16) | (cub->iter.g << 8) |
			cub->iter.b);
}

void	pars_color(char *line, t_cub *cub)
{
	int		i;
	int		count;
	int		num;

	if (cub->list != NULL)
		return_error(cub, 13);
	i = 1;
	count = 0;
	num = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isdigit(line[i])) && line[i] != ',' && line[i] != ' ' &&
			line[i] != '\0')
			return_error(cub, 2);
		(ft_isdigit(line[i]) && line[i + 1] == ' ') ? return_error(cub, 2) : 0;
		ft_isdigit(line[i]) ? count++ : 0;
		line[i++] == ',' ? num++ : 0;
		count > 9 ? return_error(cub, 2) : 0;
	}
	i = 0;
	cub->iter.r = 0;
	if (num != 2)
		return_error(cub, 2);
	line[0] == 'F' ? pars_floor_clr(line, cub, i) : 0;
	line[0] == 'C' ? pars_ceiling_clr(line, cub, i) : 0;
}
