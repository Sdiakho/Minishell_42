NAME    := minishell

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g3
CPPFLAGS:= -Iincludes

OBJDIR  := obj

# Trouve automatiquement tous les .c (même dans les futurs dossiers)
SRC     := $(shell find . -type f -name "*.c" \
	-not -path "./.git/*" \
	-not -path "./$(OBJDIR)/*")

# Transforme ./path/file.c -> obj/path/file.o
OBJ     := $(patsubst ./%.c,$(OBJDIR)/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re