#include "insert_nbrs.h"


/**
 * @brief Function to initialize the mutexes that will be used for protecting write/reads in each thead
 * 
 * Returns 0 on success, 1 on error
 * @param main_struct 
 * @return int 
 */
static int	init_mutex(t_main_struct *main_struct)
{
	if (pthread_mutex_init(&main_struct->mutex_n, NULL))
	{
		perror("mutex_init");
		return (1);
	}
	if (pthread_mutex_init(&main_struct->mutex_p, NULL))
	{
		perror("mutex_init");
		pthread_mutex_destroy(&main_struct->mutex_n);
		return (1);
	}
	return (0);
}


/**
 * @brief Function to destroy the mutexes
 * 
 * @param main_struct 
 */
static void	destroy_mutex(t_main_struct *main_struct)
{
	pthread_mutex_destroy(&main_struct->mutex_n);
	pthread_mutex_destroy(&main_struct->mutex_p);
}


/**
 * @brief Program that will generate 2 list of random numbers, then sort them, and print the lists.
 * 
 * Returns 0 on success, 1 on error
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_main_struct	main_struct = {0};

	if (parser(&main_struct, argc, argv) == 1)
		return (1);

	if (init_mutex(&main_struct) == 1)
		return (1);

	if (create_lists(&main_struct) == 1)
	{
		dprintf(2, "There was an error generating all the numbers\n");
		lst_clear(&main_struct.lst_neg);
		lst_clear(&main_struct.lst_pos);
		destroy_mutex(&main_struct);
		return (1);
	}

	merge_sort(&main_struct.lst_neg);
	merge_sort(&main_struct.lst_pos);

	lst_iter(&main_struct.lst_neg, print_node);
	lst_iter(&main_struct.lst_pos, print_node);

	lst_clear(&main_struct.lst_neg);
	lst_clear(&main_struct.lst_pos);

	destroy_mutex(&main_struct);
	return (0);
}
