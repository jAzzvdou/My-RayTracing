NAME	=	miniRT

SRCS	=	main.c                                  \
		1TuplesPointsVectors/tuple_and_point.c  \
		1TuplesPointsVectors/tuple_utils.c      \
		1TuplesPointsVectors/vector.c           \
		2Canvas/canvas.c                        \
		2Canvas/color.c                         \
		2Canvas/color2.c                        \
		3Matrices/matrix.c                      \
		3Matrices/matrix2.c                     \
		3Matrices/matrix3.c                     \
		4MatrixTransformation/rotations.c       \
		4MatrixTransformation/transformations.c \
		5RayIntersections/inter_cy_and_cn.c     \
		5RayIntersections/inter_sp_and_pl.c     \
		5RayIntersections/intersect_utils.c     \
		5RayIntersections/new_object.c          \
		5RayIntersections/ray.c                 \
		6LightAndShading/light_and_shading.c    \
		6LightAndShading/normal.c               \
		7Scene/camera.c                         \
		7Scene/color_at.c                       \
		7Scene/ray_for_pixel.c                  \
		7Scene/world.c                          \
		10Patterns/pattern.c                    \
		11Reflection/reflection.c               \
		Parse/amb_parse.c                       \
		Parse/cam_parse.c                       \
		Parse/cone_parse.c                      \
		Parse/cy_parse.c                        \
		Parse/light_parse.c                     \
		Parse/parse.c                           \
		Parse/parse_utils.c                     \
		Parse/plane_parse.c                     \
		Parse/sphere_parse.c                    \
		Screen/render.c                         \
		Screen/screen.c                         \
		Utils/get_next_line.c                   \
		Utils/lib1.c                            \
		Utils/lib2.c                            \
		Utils/lib3.c                            \
		Utils/lib4.c                            \
		Utils/lib5.c                            \
		Utils/lib6.c                            \
		Utils/space.c                           \

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
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT Scenes/simple.rt

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
