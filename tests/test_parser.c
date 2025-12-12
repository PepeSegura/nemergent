#include "unity.h"
#include "insert_nbrs.h"
#include <string.h>

#ifndef USAGE
# define USAGE "USAGE: ./insert_nbrs <threads> <numbers_per_thread>"
#endif

static t_main_struct ms;

void	setUp(void)
{
	memset(&ms, 0, sizeof(t_main_struct));
}

void	tearDown(void)
{
}

/* --------------- TESTS --------------- */
void	test_parser_valid_input(void)
{
	char	*argv[] = {"./insert_nbrs", "4", "100", NULL};

	int	res = parser(&ms, 3, argv);

	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(4, ms.threads_ammount);
	TEST_ASSERT_EQUAL_INT(100, ms.nbrs_per_thread);
}

void	test_parser_invalid_argc_low(void)
{
	char	*argv[] = {"./insert_nbrs", "4", NULL};

	int	res = parser(&ms, 2, argv);

	TEST_ASSERT_EQUAL_INT(1, res);
}

void	test_parser_invalid_argc_high(void)
{
	char	*argv[] = {"./insert_nbrs", "1", "2", "3", NULL};

	int	res = parser(&ms, 4, argv);

	TEST_ASSERT_EQUAL_INT(1, res);
}

void	test_parser_non_numeric_thread_count(void)
{
	char	*argv[] = {"./insert_nbrs", "abc", "10", NULL};

	int	res = parser(&ms, 3, argv);

	TEST_ASSERT_EQUAL_INT(1, res);
}

void	test_parser_non_numeric_nbrs_per_thread(void)
{
	char	*argv[] = {"./insert_nbrs", "5", "xyz", NULL};

	int	res = parser(&ms, 3, argv);

	TEST_ASSERT_EQUAL_INT(1, res);
}

void	test_parser_zero_values(void)
{
	char	*argv1[] = {"./insert_nbrs", "0", "5", NULL};
	char	*argv2[] = {"./insert_nbrs", "5", "0", NULL};

	TEST_ASSERT_EQUAL_INT(1, parser(&ms, 3, argv1));
	TEST_ASSERT_EQUAL_INT(1, parser(&ms, 3, argv2));
}

void	test_parser_negative_values(void)
{
	char	*argv1[] = {"./insert_nbrs", "-1", "5", NULL};
	char	*argv2[] = {"./insert_nbrs", "5", "-10", NULL};

	TEST_ASSERT_EQUAL_INT(1, parser(&ms, 3, argv1));
	TEST_ASSERT_EQUAL_INT(1, parser(&ms, 3, argv2));
}

void	test_parser_large_numbers(void)
{
	char	*argv[] = {"./insert_nbrs", "999999", "888888", NULL};

	int res = parser(&ms, 3, argv);

	TEST_ASSERT_EQUAL_INT(0, res);
	TEST_ASSERT_EQUAL_INT(999999, ms.threads_ammount);
	TEST_ASSERT_EQUAL_INT(888888, ms.nbrs_per_thread);
}

int	main(void)
{
	close(STDERR_FILENO);

	UNITY_BEGIN();

	RUN_TEST(test_parser_valid_input);
	RUN_TEST(test_parser_invalid_argc_low);
	RUN_TEST(test_parser_invalid_argc_high);
	RUN_TEST(test_parser_non_numeric_thread_count);
	RUN_TEST(test_parser_non_numeric_nbrs_per_thread);
	RUN_TEST(test_parser_zero_values);
	RUN_TEST(test_parser_negative_values);
	RUN_TEST(test_parser_large_numbers);

	UNITY_END();
}
