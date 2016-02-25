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

INC = ../lib/inc/ft_printf.h\
	../lib/inc/libft.h\
	../inc/nm.h\
	../inc/options.h

LIB = libft\
	  ft_printf
LIB_DIR = $(addsuffix /, $(addprefix ../lib/, $(LIB)))
LIB_INC = $(addprefix -I./, $(LIB_DIR))
LIB_A = $(join $(LIB_DIR), $(addsuffix .a, $(LIB)))

SRC = main.c\
	  process_flag.c\
	  ofile_process.c\
	  map_file.c\
	  options/usage.c\
	  options/get_options.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIB_A) blankline $(OBJ) blankline
	$(CC) $(FLAGS) -o $@ $(LIB_A) $(OBJ)

$(LIB_A):
	@echo 'build $(notdir $@)'
	@make -C $(dir $@)
	@make clean -C $(dir $@)

$(OBJ_DIR)/%.o: %.c $(INC)| $(OBJ_DIR)
	@echo $<
	@$(CC) $(FLAGS) $(addprefix -I, $(dir $(INC))) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj obj/options

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(LIB_A)
	@echo

blankline:
	@echo

re : fclean all
