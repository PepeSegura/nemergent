# ===========================
#     UNIT TESTS CONFIG
# ===========================

CFLAGS_TESTER = -Wall -Werror -Wextra #-g3 -fsanitize=thread
CFLAGS_TESTER += -I inc -I tests
LDFLAGS_TESTER = -lpthread #-fsanitize=thread


# ---- LST TESTER ----
NAME_TEST_LST = tester_lst
SRCS_TEST_LST = tests/unity.c tests/test_lst.c srcs/lst.c
OBJS_TEST_LST = $(SRCS_TEST_LST:.c=.o)

$(NAME_TEST_LST): $(OBJS_TEST_LST)
	$(CC) $(CFLAGS_TESTER) $(LDFLAGS_TESTER) $(OBJS_TEST_LST) -o $(NAME_TEST_LST)


# ---- PARSER TESTER ----
NAME_TEST_PARSER = tester_parser
SRCS_TEST_PARSER = tests/unity.c tests/test_parser.c srcs/parser.c
OBJS_TEST_PARSER = $(SRCS_TEST_PARSER:.c=.o)

$(NAME_TEST_PARSER): $(OBJS_TEST_PARSER)
	$(CC) $(CFLAGS_TESTER) $(LDFLAGS_TESTER) $(OBJS_TEST_PARSER) -o $(NAME_TEST_PARSER)


# ---- Build all testers ----
test: $(NAME_TEST_LST) $(NAME_TEST_PARSER)
	./$(NAME_TEST_LST)
	./$(NAME_TEST_PARSER)

# ---- Clean test objects and binaries ----
clean_test:
	rm -f $(OBJS_TEST_LST) $(OBJS_TEST_PARSER)
	rm -f $(NAME_TEST_LST) $(NAME_TEST_PARSER)


.PHONY: test clean_tests
