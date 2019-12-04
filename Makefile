.PHONY: all, $(NAME), clean, fclean, re

NAME = Rtv1
FRAMEDIR = /Users/$(USER)/Library/Frameworks

SRC_A_PATH = ./src/
SRC_B_PATH = ./libXml/
SRC_C_PATH = ./libvec/
OBJ_PATH = ./objects/
INC_PATH = ./include/
LIB_PATH = ./libft

INC =		-I $(INC_PATH) -I $(LIB_PATH) -I ./ \
			-I libSDL/SDL2.framework/Headers \
			-I libSDL/SDL2_image.framework/Headers \
			-F libSDL/

FRAME = 	-F libSDL/ -framework SDL2 -framework SDL2_image -rpath libSDL/
FLAGS = 	-Ofast -c -g -MMD -MP -Wall -Wextra -Werror

LIB = 		-L$(LIB_PATH) -lft

SRC_PARSE = find_functions.c help_functions.c parse_objects.c parse_parametrs.c parser.c add_parse.c
SRC_VEC = vector.c vector2.c vector3.c
SRC_RTV = color.c draw.c event.c find.c help.c  hit.c init.c light.c main.c normal.c

OBJ_RTV = $(SRC_RTV:.c=.o)
OBJ_PARSE = $(SRC_PARSE:.c=.o)
OBJ_VEC = $(SRC_VEC:.c=.o)

OBJ_A = $(addprefix $(OBJ_PATH),$(OBJ_RTV))
OBJ_B = $(addprefix $(OBJ_PATH),$(OBJ_PARSE))
OBJ_C = $(addprefix $(OBJ_PATH),$(OBJ_VEC))

SRC_A = $(addprefix $(SRC_A_PATH),$(SRC_RTV))
DEP_A = $(OBJ_A:.o=.d)
SRC_B = $(addprefix $(SRC_B_PATH),$(SRC_PARSE))
DEP_B = $(OBJ_B:.o=.d)
SRC_C = $(addprefix $(SRC_C_PATH),$(SRC_VEC))
DEP_C = $(OBJ_C:.o=.d)


all: $(NAME)

$(NAME): $(OBJ_A) $(OBJ_B) $(OBJ_C)
	Make -C $(LIB_PATH)
	gcc $(OBJ_A) $(OBJ_B) $(OBJ_C) $(INC) $(LIB) $(FRAME) -o $(NAME)

-include $(DEP_A)
$(OBJ_PATH)%.o: $(SRC_A_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) $(INC) $< -o $@

-include $(DEP_B)
$(OBJ_PATH)%.o: $(SRC_B_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) $(INC) $< -o $@

-include $(DEP_C)
$(OBJ_PATH)%.o: $(SRC_C_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	@clear
	@Make -C $(LIB_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@Make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re: fclean all
