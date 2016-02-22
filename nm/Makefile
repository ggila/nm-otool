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

NAME = nm

CC = gcc
FLAGS = -Wall -Werror -Wextra

INC = -I../lib/ft_printf/\
	-I../lib/libft/\
	-I./inc

LIB = libft\
	  ft_printf
LIB_DIR = $(addsuffix /, $(addprefix ../lib/, $(LIB)))
LIB_INC = $(addprefix -I./, $(LIB_DIR))
LIB_A = $(join $(LIB_DIR), $(addsuffix .a, $(LIB)))

SRC = main.c\
	  options/usage.c\
	  options/get_options.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIB_A) $(OBJ)
	$(CC) $(FLAGS) -o $@ $(LIB_A) $(OBJ)

$(LIB_A):
	@echo 'build $(notdir $@)'
	@make -C $(dir $@)
	@make clean -C $(dir $@)

obj/%.o: | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $*.c -o $@

#(OBJ_DIR)/%.o : %.c $(INC) | $(OBJ_DIR)
#	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p obj obj/options

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all
