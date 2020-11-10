# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/05 13:54:09 by averheij      #+#    #+#                  #
#    Updated: 2020/11/10 14:52:07 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	libasmtest
CFILES	=	main.c strlentest.c strcpytest.c strcmptest.c writetest.c\
			readtest.c strduptest.c
OFILES	=	$(CFILES:%.c=%.o)
FLAGS	=	-g -no-pie #-Werror -Wall -Wextra
CCC		=	gcc $(FLAGS) $(INCLUDE)
LIBDIR	=	libasm
INCLUDE	=	-I$(LIBDIR)
LIBS	=	-L ./$(LIBDIR) -lasm

all: lib $(NAME)

$(NAME): $(OFILES)
	$(CCC) -o $(NAME) $(OFILES) $(LIBS)

clean:
	rm -f $(OFILES)
	@echo "//------libasm------\\\\\\\\"
	make -C $(LIBDIR) clean
	@echo "--------------------"

fclean: clean
	rm -f $(NAME)
	@echo "//------libasm------\\\\\\\\"
	make -C $(LIBDIR) fclean
	@echo "--------------------"

re: fclean all
	@echo "//------libasm------\\\\\\\\"
	make -C $(LIBDIR) re
	@echo "--------------------"

lib:
	@echo "//------libasm------\\\\\\\\"
	make -C $(LIBDIR)
	@echo "--------------------"

run: all
	./libasmtest
