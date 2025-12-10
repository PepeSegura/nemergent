MAKEFLAGS = --silent

NAME = insert_nbrs

SRCS =						\
		srcs/main.c			\
		srcs/parser.c		\
		srcs/lst.c

OBJS = $(SRCS:%.c=objs/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread
CFLAGS += -I inc
LDFLAGS = -lpthread

$(NAME): objs $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

objs:
	@mkdir -p	objs/srcs/

objs/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf objs
	@rm -f $(NAME)

re: clean all

.PHONY: all clean re