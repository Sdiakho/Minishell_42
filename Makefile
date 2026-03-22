NAME    := minishell

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g3 -fsanitize=address
LDLIBS  := -lreadline -lncurses

ifeq ($(shell uname -s),Darwin)
  INCLUDES := -Iincludes -I/opt/homebrew/opt/readline/include
  LDFLAGS := -L/opt/homebrew/opt/readline/lib
else
  INCLUDES := -Iincludes
endif

OBJDIR  := obj

# Trouve automatiquement tous les .c (même dans les futurs dossiers)
SRC     := $(shell find . -type f -name "*.c" \
	-not -path "./.git/*" \
	-not -path "./$(OBJDIR)/*")

# Transforme ./path/file.c -> obj/path/file.o
OBJ     := $(patsubst ./%.c,$(OBJDIR)/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re