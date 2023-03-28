# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 00:51:30 by mbourgeo          #+#    #+#              #
#    Updated: 2023/03/28 06:22:28 by mbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Maze

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g

#SRCS	 	= Game.cpp Maze.cpp Cell.cpp Player.cpp Path.cpp Strategies.cpp \
#			  DepthSearchFirst.cpp Dijkstra.cpp Display.cpp Utils.cpp main.cpp

SRCS	 	= Game.cpp Maze.cpp Cell.cpp Player.cpp Route.cpp Path.cpp Utils.cpp Step.cpp \
			  Dijkstra.cpp Point.cpp Action.cpp Movement.cpp main.cpp

OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
