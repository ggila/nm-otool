# **************************************************************************** #
#                __  __   _   _  _____ ___ ___ _    ___                        # 
#               |  \/  | /,\ | |/ / __| __|_ _| |  | __|                       #
#               | |\/| |/ - \| ' <| _|| _| | || |__| _|                        # 
#               |_|  |_/_/ \_\_|\_\___|_| |___|____|___|                       #
#                                                                    ggilaber  #
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
FLAGS = -Wall -Werror -Wextra

MACHO_LIB = macho/macho.a
MACHO_INC = -I./macho/

LIB = libft\
	hash_tables\
	ft_printf
LIB_DIR = $(addsuffix /, $(addprefix lib/, $(LIB)))
LIB_INC = $(addprefix -I./, $(LIB_DIR))
LIB_A = $(join $(LIB_DIR), $(addsuffix .a, $(LIB)))

all: nm

nm:
	@make -C $@
	@mv nm/nm .

stat: $(LIB_A) $(MACHO_LIB)
	@echo
	$(CC) $(FLAGS) -o $@ $(LIB_INC) $(MACHO_INC) $(LIB_A) $(MACHO_LIB) stat.c

$(LIB_A):
	@echo 'build $(notdir $@)'
	@make -C $(dir $@)
	@make clean -C $(dir $@)

$(MACHO_LIB):
	@echo "\nbuild macho.a"
	@make -C $(dir $@)

#clean:
#	@echo

fclean: clean
	@echo fclean
	@rm -rf $(LIB_A)
	@rm -rf $(MACHO_LIB)
	@rm -rf stat

re: fclean blankline all blankline stat

blankline:
	@echo
