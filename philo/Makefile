# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yublee <yublee@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 14:55:22 by yublee            #+#    #+#              #
#    Updated: 2024/12/21 23:24:01 by yublee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRS = src

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm

RMFLAGS = -fv

AR = ar

ARFLAGS = rcs

INCLUDE = -I include/

NAME = philo

SRC = \
		src/main.c \
		src/init_info.c \
		src/init_table.c \
		src/simulation.c \
		src/philosopher.c \
		src/timelogger.c \
		src/utils_table.c \
		src/utils.c \

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

BUILD_DIR = build

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -g -o $@

$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR) $(patsubst %,$(BUILD_DIR)/%,$(DIRS))

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean:
	$(RM) -rf $(BUILD_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
