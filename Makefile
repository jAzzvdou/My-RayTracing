NAME	=	miniRT

SRCS	=	main.c \

OBJDIR	=	Objects

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

MEMLIB	=	Includes/MemoryCard/memorycard.a

INCLUDES	=	-I Includes

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra $(INCLUDES)

RM	=	rm -rf

TOTAL_SRCS	=	$(words $(SRCS))

COMPILED_SRCS	=	0

all: $(NAME)

$(MEMLIB):
	@make -C Includes/MemoryCard --silent

$(NAME): $(OBJS) $(MEMLIB)
		@$(CC) -o $(NAME) $(OBJS) $(MEMLIB)
		@echo "\033[1;97m👾 MiniRT Is Ready! 👾\033[0m"

$(OBJDIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
		$(eval COLOR_VALUE=$(shell echo $$((255*$(COMPILED_SRCS)/$(TOTAL_SRCS)))))
		@echo -n "\033[38;2;$(COLOR_VALUE);$(COLOR_VALUE);$(COLOR_VALUE)m  MiniRT Is Ready!\033[0m\r"
		@sleep 0.01

val: re
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT

clean:
		@$(RM) $(OBJDIR)
		@make -C Includes/MemoryCard clean --silent
		@echo "\033[38;2;255;165;0m🗑️  Objects Are Cleaned! 🗑️\033[0m"

fclean: clean
		@$(RM) $(NAME)
		@make -C Includes/MemoryCard fclean --silent
		@echo "\033[31m🗑️  MiniRT Is Cleaned! 🗑️\033[0m"

re: fclean all

.PHONY: all clean fclean re
