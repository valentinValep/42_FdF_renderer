NAME := libfdf_renderer.a

CC := cc
AR := ar

CFLAGS := -Wall -Werror -Wextra
ARFLAGS := -rc

SOURCES_DIR := ./src
BINARIES_DIR := ./build
INCLUDES_DIR := includes/

INCLUDES := -I$(INCLUDES_DIR) -I/usr/include

SRC := renderer.c \
	render.c \
	shapes.c \
	images.c \
	lines.c \

OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SOURCES_DIR)/,$(SRC))
OBJ := $(addprefix $(BINARIES_DIR)/,$(OBJ))

RM := rm -f

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c | $(BINARIES_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
