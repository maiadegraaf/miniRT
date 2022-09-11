NAME = minirt
MKDIR = mkdir

CC = gcc

LIBFTP	=	libft
PATHB	=	build/
PATHO	=	build/objs/
PATHS	=	src/
PATHSU	=	src/utils/
PATHSE	=	src/error/
PATHSP	=	src/parser/

BUILD_PATHS = $(PATHB) $(PATHO)

src	=	src/main.c\
		src/utils/vec_utils.c \
		src/utils/color_utils.c \
		src/utils/ray_utils.c \
		src/utils/hit_utils.c \
		src/utils/sphere_utils.c \
		src/utils/hittable_utils.c \
		src/utils/hit_record_utils.c \
		src/utils/hittable_lst_utils.c \
		src/utils/utils.c \
		src/utils/lighting_utils.c \
		src/utils/elements_utils.c \
		src/error/error.c \
		src/parser/ambient.c \
		src/parser/camera.c \
		src/parser/light.c \
		src/parser/object.c \
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/vec4_parse.c \
		# src/utils/vec3_dot_cross.c \
		# src/ray_tracer/test.c

OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(src))))

FLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address 

LIBFT	=	libft/libft.a

MLX42	=	MLX42/libmlx42.a

HEADER	=	.includes/minirt.h \
			.includes/ray.h \
			.includes/hittable.h \
			.includes/sphere.h \
			.includes/hittable_lst.h \
			.includes/lighting.h \
			.includes/parser.h \
			.includes/error.h
	
INCLUDES =	-Iincludes -I$(LIBFTP)

# GLFW_LIB = -L /Users/$(USER)/.brew/opt/glfw/lib/ # CODAM
# GLFW_LIB = -L /opt/homebrew/Cellar/glfw/3.3.6/lib # HOME
GLFW_LIB = -L /opt/homebrew/Cellar/glfw/3.3.8/lib # HOME

all: $(BUILD_PATHS) $(NAME)

$(PATHO)%.o:: $(PATHS)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHS)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSU)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSE)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSE)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}			in	$(PATHSP)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(MLX42) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBFT) $(MLX42) $(OBJS) $(GLFW_LIB) -lglfw -o $(NAME)
	@echo "Success"

$(LIBFT):
	@$(MAKE) -C libft

$(MLX42):
	$(MAKE) -lglfw -C MLX42

$(PATHB):
	@$(MKDIR) $(PATHB)

$(PATHO):
	@$(MKDIR) $(PATHO)

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@rm -r $(PATHO) $(PATHB)
	@make fclean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PRECIOUS: $(PATHO)%.o