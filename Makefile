# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/08 19:45:49 by ggilaber          #+#    #+#              #
#    Updated: 2016/02/13 17:34:40 by ggilaber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####
# Variables internes:
#    $@ -> nom cible
#    $< -> nom premiere dependance
#    $^ -> liste dependance
#    $? -> liste depandances plus recentes que cible
#    $* -> nom fichier sans suffixe
###

.PHONY : clean fclean re all nm otool lipo

CC = gcc

MACHO_LIB = macho/macho.a
MACHO_INC = -I./macho/

LIB = libft\
	hash_tables\
	ft_printf\
	options
LIB_DIR = $(addsuffix /, $(addprefix lib/, $(LIB)))
LIB_INC = $(addprefix -I./, $(LIB_DIR))
LIB_A = $(join $(LIB_DIR), $(addsuffix .a, $(LIB)))

stat: $(LIB_A) $(MACHO_LIB)
	$(CC) $(FLAGS) -o $@ $(LIB_INC) $(MACHO_INC) $(LIB_A) $(MACHO_LIB) stat.c

$(LIB_A):
	@echo 'build $(notdir $@)'
	@make -C $(dir $@)
	@make clean -C $(dir $@)

$(MACHO_LIB):
	@echo "\nbuild macho.a"
	@make -C $(dir $@)

clean:
	@echo ''

fclean: clean
	rm -rf $(LIB_A)
	rm -rf stat

re: fclean_lib fclean all
