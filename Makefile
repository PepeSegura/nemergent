MAKEFLAGS = --no-print-directory #--silent

NAME = insert_nbrs

SRCS =						\
		srcs/main.c			\
		srcs/parser.c		\
		srcs/thread.c		\
		srcs/lst.c			\
		srcs/merge_sort.c	\
		srcs/utils.c		\

OBJS = $(SRCS:%.c=objs/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=thread
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

clean_all: clean clean_test

.PHONY: all clean re clean_all

-include tests/Makefile
