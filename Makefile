# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 15:13:49 by eperperi          #+#    #+#              #
#    Updated: 2024/09/24 12:52:56 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME	=	cub3D

CC			=	gcc -g -fsanitize=address
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
CFLAGS		=	-Wall -Wextra -Werror
MLXFLAGS	=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

SRC_DIR	=	./srcs/
OBJ_DIR	=	./objs/
GNL_DIR =	./Get_next_line/

SRC		 =	$(SRC_DIR)main.c \
			$(SRC_DIR)parsing.c
GNL_SRC  =	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c 
			
OBJ		 =	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
GNL_OBJ	 =	$(GNL_SRC:$(GNL_DIR)%.c=$(OBJ_DIR)%.o)
LIB		 =	Libft/libft.a
MLX42	 =	MLX42/build/libmlx42.a

$(NAME): $(MLX42) $(OBJ) $(LIB) $(GNL_OBJ)
		@$(MAKE) -C Libft
		@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(MLX42) $(OBJ) $(LIB) $(GNL_OBJ)
		@echo "$(GREEN)Cub3D compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C Libft

$(MLX42):
	@if [ ! -d "./MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4

all:	$(MLX42) $(NAME)

cleanmlx:
		@rm -rf MLX42
		@echo "$(CYAN)MLX42 folder is deleted!$(WHITE)"
		
clean:	
		@$(MAKE) -C Libft clean
		@rm -rf $(OBJ_DIR)
		@rm -f libmlx42.a
		@echo "$(CYAN)Object files cleaned!$(WHITE)"

fclean:	clean
		@$(MAKE) -C Libft fclean
		@rm -f $(NAME)
		@echo "$(CYAN)Executable and object files cleaned!$(WHITE)"

cleanEverything: fclean cleanmlx

re:		fclean all

.PHONY: all clean fclean cleanmlx cleanEverything re