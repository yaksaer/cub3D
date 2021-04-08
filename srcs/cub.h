/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:30:23 by kseed             #+#    #+#             */
/*   Updated: 2021/04/02 19:28:45 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define SPEED 0.4
# define FOV (M_PI / 3)

typedef struct		s_pars
{
	int				save_flg;
	int				width;
	int				height;
	char			path_tex[5][256];
	char			**map;
	int				map_str;
	int				max_str;
	int				fl_color;
	int				ce_color;
	int				empt;
}					t_pars;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*adr;
	int				bpp;
	int				line_sz;
	int				end;
}					t_mlx;

typedef struct		s_player
{
	float			pos_x;
	float			pos_y;
	float			cord_x;
	float			cord_y;
	float			ray_x;
	float			ray_y;
	float			*ray_len;
	float			angle;
	int				quarter;
}					t_player;

typedef struct		s_iter
{
	int				x;
	int				y;
	float			tmp_x;
	float			tmp_y;
	float			tmp_d;
	int				r;
	int				g;
	int				b;
}					t_iter;

typedef struct		s_wall
{
	int				x;
	float			size;
	float			dist;
	float			koef;
}					t_wall;

typedef struct		s_tex
{
	char			*adr[5];
	char			*imgptr[5];
	int				bpp[5];
	int				line_sz[5];
	int				end[5];
	int				wid[5];
	int				hei[5];
	unsigned int	color;
	char			*gun;
	char			*health;
}					t_tex;

typedef struct		s_sprite
{
	float			*x;
	float			*y;
	float			*dist;
	float			*dir;
	float			*size;
	float			*first_x;
	float			*first_y;
	float			*width;
	float			*height;
	int				count;
}					t_sprite;

typedef struct		s_cub
{
	t_mlx			mlx;
	t_pars			parsed;
	t_player		plr;
	t_wall			wall;
	t_tex			text;
	t_sprite		spr;
	t_iter			iter;
	t_list			*list;
}					t_cub;

int					main(int argc, char **argv);
void				fill_cub_mlx(t_cub *cub);
void				fill_parsed(t_cub *cub);

void				ft_pars(t_cub *cub, int fd);
void				pars_line(char *line, t_cub *cub);
int					pars_textures(char *line, t_cub *cub, int flag);
void				pars_resolution(char *line, t_cub *cub);
int					write_resolution(t_cub *cub, char *tmp, int flag);
void				pars_color(char *line, t_cub *cub);
void				pars_ceiling_clr(char *line, t_cub *cub, int i);
void				pars_floor_clr(char *line, t_cub *cub, int i);
void				save_plr(t_cub *cub, int i, int j);
void				check_arguments(t_cub *cub, int num, char *map, char *save);
void				check_text(t_cub *cub);
void				check_repeat(t_cub *cub, int flag);
void				check_map(t_cub *cub);
void				read_map(t_cub *cub);
void				fill_map(t_cub *cub);
int					close_map(t_cub *cub, int i, int j);
void				remember_sprites(t_cub *cub);
void				fill_list(t_cub *cub, char *line);
void				recognize_list_size(t_cub *cub);
void				improve_resolution(t_cub *cub);
void				check_empty_line(t_cub *cub, char *line);

void				pixel_put(t_cub *cub, int x, int y, int color);
unsigned int		pixel_get(t_cub *cub, int x, int y, int flag);
void				read_textu(t_cub *cub, int i);
int					define_quarter(t_cub *cub, float ray_angle);
float				max(float a, float b);
void				return_error(t_cub *cub, int error);
void				error_code_two(t_cub *cub, int err);
void				free_all(t_cub *cub);
void				alloc(t_cub *cub);
void				sort_sprites(t_cub *cub, int i);

void				make_window(t_cub *cub);
void				make_image(t_cub *cub);
void				ft_ray(t_cub *cub);
void				draw_floor_cellar(t_cub *cub);
float				check_wall_ray(t_cub *cub, float start, char c);
float				calculate_walls(t_cub *cub, float ray_angle, char c);
void				print_e_w(t_cub *cub, float start, float end);
void				print_s_n(t_cub *cub, float start, float end);
void				start_sprites(t_cub *cub);
void				calculate_sprites(t_cub *cub);
void				print_sprites(t_cub *cub, int s, int i);

int					key_hook(int key, t_cub *cub);
int					movement(int key, t_cub *cub);
void				move_back_forw(t_cub *cub, int key);
int					close_win(t_cub *cub);
void				shadow_coef(t_cub *cub, float dist);

void				make_bmp(t_cub *cub);
void				fill_bmp(t_cub *cub, char *buf);
void				make_header(char *buf, int size, t_cub *cub);
unsigned int		bmp_pixel_get(t_cub *cub, int x, int y);
void				free_all(t_cub *cub);

void				paint_bonus(t_cub*cub);
void				paint_health(t_cub *cub);
#endif
