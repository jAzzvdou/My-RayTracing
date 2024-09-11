NAME	=	memorycard.a

SRCS	=	memorycard.c      \
		memnode.c          \
		memlist.c           \
		memorycard_utils.c   \
		memorycard_cleaners.c \
		types_functions.c      \


OBJS	=	$(SRCS:.c=.o)

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra

RM	=	rm -rf 

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

.c.o:
		$(CC) $(CFLAGS) -c $<

clean:
		$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
