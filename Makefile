# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 11:42:28 by ayakoubi          #+#    #+#              #
#    Updated: 2023/04/12 17:08:28 by ayakoubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            :=      so_long
SRCS            :=      so_long ft_utils handling_errors put_image ft_key_move lst_utils 
INC             =       inc
OBJDIR          =       obj
SRCDIR			=		src
SRC             :=      $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCS)))
OBJ             :=      $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))
C_LIBFT         =       make -C libft
C_PRINTF        =       make -C ft_printf
C_GNL           =       make -C gnl
AR_LIBFT        =       libft/libft.a
AR_PRINTF       =       ft_printf/libftprintf.a
AR_GNL          =       gnl/get_next_line
CC				=		cc
CFLAGS          =       -Wall -Wextra -Werror
MLX				=		-lmlx -framework OpenGL -framework AppKit 

#########################
#		color text		#
#########################

GREEN   = \033[0;32m
RED     = \033[0;31m
C_END   = \033[0m
BOLD    = \x1b[1m
B_END   = \x1b[0m

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling >>>>>> $^"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -I $(INC) -o $@

$(NAME) : $(OBJ)
	@$(C_LIBFT) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>> $(AR_LIBFT)$(B_END)$(C_END)"
	@$(C_PRINTF) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>> $(AR_PRINTF)$(B_END)$(C_END)"
	@$(C_GNL) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>>>$(AR_GNL)$(B_END)$(C_END)"
	@$(CC) $(CFLAGS) $^ $(AR_LIBFT) $(AR_PRINTF) $(AR_GNL) $(MLX) -I $(INC) -o $@
	@echo "  $(GREEN) $(BOLD) <<<<<< Done successful! >>>>>>$(B_END) $(C_END)"

clean   :
	@echo " $(RED)$(BOLD)REMOVED OBJECTS$(B_END)$(C_END)"
	@$(C_LIBFT) clean
	@$(C_PRINTF) clean
	@$(C_GNL) clean
	@rm -rf $(OBJDIR)

fclean  :	clean
	@rm -rf $(NAME)
	@$(C_LIBFT) fclean
	@$(C_PRINTF) fclean
	@$(C_GNL) fclean
	@echo "$(RED)$(BOLD)removed $(AR_LIBFT)\nremoved $(AR_PRINTF)\nremoved $(NAME)$(B_END)$(C_END)"

re:	fclean all

.PHONY: all clean fclean re
