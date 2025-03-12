NAME	=	miniRT

SRCS	=	main.c                                  \
		1TuplesPointsVectors/tuple.c            \
		1TuplesPointsVectors/vector_and_point.c \
		2Canvas/canvas.c                        \
		2Canvas/color.c                         \
		2Canvas/color2.c                        \
		3Matrices/matrix.c                      \
		4MatrixTransformation/rotations.c       \
		4MatrixTransformation/transformations.c \
		5RayIntersections/ray.c                 \
		6LightAndShading/light_and_shading.c    \
		6LightAndShading/normal.c               \
		7Scene/world.c                          \
		10Patterns/pattern.c                    \
		11Reflection/reflection.c               \
		Screen/render.c                         \
		Screen/screen.c                         \
		Utils/get_next_line.c                   \
		Utils/lib1.c                            \
		Utils/lib2.c                            \
		Utils/lib3.c                            \
		Utils/lib4.c                            \
		Utils/lib5.c                            \
		Utils/space.c                           \
		Utils/splitline.c                       \
		Parse/parse.c                           \

OBJDIR	=	Objects

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

INCLUDES	=	-I Includes

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra $(INCLUDES)

LIBMATH	=	-lm

RM	=	rm -rf

TOTAL_SRCS	=	$(words $(SRCS))

COMPILED_SRCS	=	0

MEMLIB	=	Includes/MemoryCard/memorycard.a
MLXLIB	=	Includes/minilibx-linux/libmlx.a

all: $(NAME)

$(MEMLIB):
	@make -C Includes/MemoryCard --silent

$(NAME): $(OBJS) $(MEMLIB) $(MLXLIB)
		@$(CC) -o $(NAME) $(OBJS) $(MEMLIB) $(MLXLIB) -Imlx_linux -lXext -lX11 -lm
		@echo "\033[1;97m👾 MiniRT Is Ready! 👾\033[0m"

$(OBJDIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
		$(eval COLOR_VALUE=$(shell echo $$((255*$(COMPILED_SRCS)/$(TOTAL_SRCS)))))
		@echo -n "\033[38;2;$(COLOR_VALUE);$(COLOR_VALUE);$(COLOR_VALUE)m  MiniRT Is Ready!\033[0m\r"
		@sleep 0.01

test:
	./miniRT "bonus_scene.rt"

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
