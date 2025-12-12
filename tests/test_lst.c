#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "insert_nbrs.h"

static int	counter = 0;

void	*count_callback(void *context)
{
	(void)context;
	counter++;
	return (NULL);
}

// ---------- setUp / tearDown ---------- //
void	setUp(void)
{
    counter = 0;
}

void	tearDown(void)
{
}

/* ---------- TESTS ---------- */
void	test_lst_new_creates_node(void)
{
	t_lst	*node = lst_new(42);

	TEST_ASSERT_NOT_NULL(node);
	TEST_ASSERT_EQUAL_INT(42, node->content);
	TEST_ASSERT_NULL(node->next);

	free(node);
}

void	test_lst_last_returns_last_node(void)
{
	t_lst	*a = lst_new(1);
	t_lst	*b = lst_new(2);
	t_lst	*c = lst_new(3);

	a->next = b;
	b->next = c;

	TEST_ASSERT_EQUAL_PTR(c, lst_last(a));

	free(a);
	free(b);
	free(c);
}

void	test_lst_add_back_on_empty_list(void)
{
	t_lst	*list = NULL;
	t_lst	*node = lst_new(10);

	lst_add_back(&list, node);

	TEST_ASSERT_EQUAL_PTR(node, list);
	TEST_ASSERT_EQUAL_INT(10, list->content);
	TEST_ASSERT_NULL(list->next);

	free(node);
}

void	test_lst_add_back_on_existing_list(void)
{
	t_lst	*a = lst_new(1);
	t_lst	*b = lst_new(2);

	t_lst	*list = a;

	lst_add_back(&list, b);

	TEST_ASSERT_EQUAL_PTR(a, list);
	TEST_ASSERT_EQUAL_PTR(b, a->next);
	TEST_ASSERT_NULL(b->next);

	free(a);
	free(b);
}

void	test_lst_add_front_on_empty_list(void)
{
	t_lst	*list = NULL;
	t_lst	*node = lst_new(99);

	lst_add_front(&list, node);

	TEST_ASSERT_EQUAL_PTR(node, list);
	TEST_ASSERT_EQUAL_INT(99, list->content);

	free(node);
}

void	test_lst_add_front_on_existing_list(void)
{
	t_lst	*a = lst_new(1);
	t_lst	*b = lst_new(2);

	t_lst	*list = a;

	lst_add_front(&list, b);

	TEST_ASSERT_EQUAL_PTR(b, list);
	TEST_ASSERT_EQUAL_PTR(a, b->next);
	TEST_ASSERT_EQUAL_INT(2, b->content);
	TEST_ASSERT_EQUAL_INT(1, a->content);

	free(a);
	free(b);
}

void	test_lst_iter_calls_function_on_each_node(void)
{
	t_lst	*a = lst_new(1);
	t_lst	*b = lst_new(2);
	t_lst	*c = lst_new(3);

	a->next = b;
	b->next = c;

	lst_iter(&a, count_callback);

	TEST_ASSERT_EQUAL_INT(3, counter);

	free(a);
	free(b);
	free(c);
}

void	test_lst_clear_frees_entire_list(void)
{
	t_lst	*a = lst_new(1);
	t_lst	*b = lst_new(2);
	t_lst	*c = lst_new(3);

	a->next = b;
	b->next = c;

	lst_clear(&a);

	TEST_ASSERT_NULL(a);  // after clearing, pointer must be NULL
}

int	main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_lst_new_creates_node);
	RUN_TEST(test_lst_last_returns_last_node);
	RUN_TEST(test_lst_add_back_on_empty_list);
	RUN_TEST(test_lst_add_back_on_existing_list);
	RUN_TEST(test_lst_add_front_on_empty_list);
	RUN_TEST(test_lst_add_front_on_existing_list);
	RUN_TEST(test_lst_iter_calls_function_on_each_node);
	RUN_TEST(test_lst_clear_frees_entire_list);

	UNITY_END();
}
