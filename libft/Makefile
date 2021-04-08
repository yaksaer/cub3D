# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseed <kseed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 23:31:41 by kseed             #+#    #+#              #
#    Updated: 2020/11/14 21:21:56 by kseed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =ft_isspace.c get_next_line.c ft_strcat.c ft_strcpy.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_substr.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_split.c

SRCSB = ft_isspace.o get_next_line.o ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

NAME = libft.a

OBJ = ${SRCS:.c=.o}

OBJBO = ${SRCSB:.c=.o}

EXEC = gcc -Wall -Wextra -Werror

INCS = ft.h

RM = rm -f

.c-.o:
		$(EXEC) -c $< -o ${<:.c=.o} -I$(INCS)

$(NAME): $(OBJ)
		ar -rcs $(NAME) $(OBJ)
		ranlib $(NAME)

all: $(NAME)
$(NAME) : $(OBJ) $(OBJBO) $(HEADER)

bonus: $(OBJ) $(OBJBO)
	ar rc $(NAME) $(OBJ) $(OBJBO)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ) $(OBJBO)

fclean: clean
	$(RM) $(NAME)

re: fclean all
