# ---------------------------------------Name
NAME = philo

# ---------------------------------------Colors
ESC = \033
NORMAL = $(ESC)[m\017
BOLD = $(ESC)[1m
GREEN = $(ESC)[0;92m$(BOLD)
BLUE = $(ESC)[0;94m$(BOLD)

# ---------------------------------------Files
FILES_SRCS =	philo.c \
				parsing.c \
				error_msg.c \
				init_table.c \
				init_philos.c \
				init_forks.c \
				init_utils.c \
				flag_utils.c \
				time_utils.c \
				printing_utils.c \
				philo_routine.c \
				philo_monitor.c \
				philo_state.c \

FILES_SRCS +=	ft_itoa.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_calloc.c \

FILES_OBJS = $(FILES_SRCS:.c=.o)

# ---------------------------------------Directories
DIR_SRCS = ./srcs/
DIR_OBJS = ./objs/
DIR_NOT_LIBFT = $(DIR_SRCS)not_libft/
vpath %.c $(DIR_SRCS) $(DIR_NOT_LIBFT)

#----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

#----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)

#----------------------------------------Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinc

#------------------------------Debug
ifdef WITH_ADDRESS
CFLAGS += -g -fsanitize=address
endif

ifdef WITH_THREAD
CFLAGS += -g -fsanitize=thread
endif

#----------------------------------------Making
all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) made$(NORMAL)"

$(DIR_OBJS)%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

#------------------------------Directories
$(DIR_OBJS):
	@mkdir -p $@

#------------------------------Debug
address: $(DIR_OBJS) $(OBJS)
	@$(MAKE) re WITH_ADDRESS=1

thread: $(DIR_OBJS) $(OBJS)
	@$(MAKE) re WITH_THREAD=1

#----------------------------------------Cleaning
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re address thread