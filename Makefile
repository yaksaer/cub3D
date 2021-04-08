# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseed <kseed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 23:31:41 by kseed             #+#    #+#              #
#    Updated: 2021/04/02 16:50:58 by kseed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  srcs/pars.c      ./srcs/make_window.c   ./srcs/cub3d.c     ./srcs/key_hook.c \
		./srcs/utils.c     ./srcs/draw_cub.c ./srcs/sprite.c    ./srcs/parse_clr_res.c \
        ./srcs/free_n_exit.c ./srcs/make_bmp.c ./srcs/pars_utils.c ./srcs/list_pars_map.c

SRCS_BO = srcs/pars.c         ./srcs/make_window_bonus.c ./srcs/cub3d_bonus.c      ./srcs/key_hook_bonus.c \
          ./srcs/utils.c         ./srcs/draw_cub_bonus.c ./srcs/sprite_bonus.c       ./srcs/parse_clr_res.c \
          ./srcs/free_n_exit_bonus.c ./srcs/make_bmp.c ./srcs/paint_bonus.c ./srcs/list_pars_map.c \
		  ./srcs/pars_utils.c

NAME = cub3D

OBJ = ${SRCS:.c=.o}

OBJ_BO = ${SRCS_BO:.c=.o}

HEAD = ./srcs/cub.h

EXEC = gcc -Wall -Wextra -Werror

MAP_PATH = ./maps/map.cub

MLX_FL = -lmlx -Lmlx/ -framework OpenGL -framework Appkit

MLX_LB = ./mlx/libmlx

LIBFT = -lft -Llibft

INCS = -I $(HEAD)

RM = rm -f

$(NAME): $(OBJ) $(HEAD)
		make bonus -C ./libft/
		make -C ./mlx/
		$(EXEC) -o $(NAME) $(OBJ) $(INCS) $(MLX_FL) $(LIBFT)

$(MLX_M):
		make -C ./mlx/

$(LIBFT_M):
		make bonus -C ./libft/

all: $(NAME)

run:
		./$(NAME) $(MAP_PATH)
runb:
		./$(NAME) ./maps/bonus.cub

save: $(NAME)
		./$(NAME) $(MAP_PATH) --save

bonus:	$(OBJ_BO)
		make bonus -C ./libft/
		make -C ./mlx/
		$(EXEC) -o $(NAME) $(OBJ_BO) $(INCS) $(MLX_FL) $(LIBFT)
		sleep 1
		touch ./srcs/cub.h


clean:
	make clean -C ./libft/
	make clean -C ./mlx/
	$(RM) $(OBJ) $(OBJ_BO)

fclean: clean
	make fclean -C ./libft/
	make fclean -C ./mlx/
	$(RM) $(NAME)

re: fclean all
