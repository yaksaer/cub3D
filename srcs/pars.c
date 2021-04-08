/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:31:19 by kseed             #+#    #+#             */
/*   Updated: 2021/04/02 20:47:27 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_repeat(t_cub *cub, int flag)
{
	if (cub->parsed.path_tex[flag][0] != '\0')
		return_error(cub, 12);
}

int		pars_textures(char *line, t_cub *cub, int flag)
{
	int		i;
	int		j;

	j = 0;
	if (cub->list != NULL)
		return_error(cub, 13);
	check_repeat(cub, flag);
	i = ft_isspace(line, 2);
	while (line[i] != '\0')
		cub->parsed.path_tex[flag][j++] = line[i++];
	return (i);
}

void	check_empty_line(t_cub *cub, char *line)
{
	int		i;

	i = 0;
	i = ft_isspace(line, i);
	if (cub->list != NULL && line[i] == '\0')
	{
		cub->parsed.empt++;
		fill_list(cub, line);
	}
	if (cub->parsed.empt >= 2)
		return_error(cub, 16);
}

void	pars_line(char *line, t_cub *cub)
{
	int		i;

	i = 0;
	i = ft_isspace(line, i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		pars_resolution(line, cub);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		pars_textures(line, cub, 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		pars_textures(line, cub, 1);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		pars_textures(line, cub, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		pars_textures(line, cub, 3);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		pars_textures(line, cub, 4);
	else if ((line[i] == 'C' || line[i] == 'F') && line[i + 1] == ' ')
		pars_color(line, cub);
	else if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		fill_list(cub, line);
	else if (line[i] == '\0')
		check_empty_line(cub, line);
	else
		return_error(cub, 13);
}

void	ft_pars(t_cub *cub, int fd)
{
	int		i;
	char	*line;

	i = 1;
	line = NULL;
	while (i > 0)
	{
		if ((i = get_next_line(fd, &line)) < 0)
			return_error(cub, 4);
		pars_line(line, cub);
		if (cub->list == NULL)
			free(line);
		line = NULL;
	}
	recognize_list_size(cub);
	if (cub->parsed.map_str > 2000)
		return_error(cub, 0);
	improve_resolution(cub);
	fill_map(cub);
	read_map(cub);
	if (line != NULL)
		free(line);
}
