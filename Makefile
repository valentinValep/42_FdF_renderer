NAME := fdf

CC := cc

FLAGS := -Wall -Werror -Wextra

SOURCES_DIR := ./
BINARIES_DIR := ./
LIBRARIES_DIR := lib/

INCLUDES := -Isources -I/usr/include -I$(LIBRARIES_DIR)minilibx-linux

LIBRARIES := -L$(LIBRARIES_DIR)minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRC := fdf.c \
	render.c \
	shapes.c \

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR)/,$(SRC))
OBJ := $(addprefix $(BINARIES_DIR)/,$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	make -C $(LIBRARIES_DIR)minilibx-linux
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO rm -g3
$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -g3

all : $(NAME)

clean :
	make -C $(LIBRARIES_DIR)minilibx-linux clean
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
