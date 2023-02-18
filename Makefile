NAME := fdf_renderer.a

CC := cc
AR := ar

CFLAGS := -Wall -Werror -Wextra
ARFLAGS := -rc

SOURCES_DIR := ./src
BINARIES_DIR := ./build
INCLUDES_DIR := includes/

INCLUDES := -I$(INCLUDES_DIR) -I/usr/include

SRC := render.c \
	shapes.c \

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR)/,$(SRC))
OBJ := $(addprefix $(BINARIES_DIR)/,$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

main : $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) main.c $(NAME) -o $@ -g3

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c | $(BINARIES_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -g3

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
