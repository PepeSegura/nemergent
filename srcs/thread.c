#include "insert_nbrs.h"

/**
 * @brief Thread function that generates random numbers and inserts them into categorized lists
 * 
 * This function is executed by each thread created in create_lists(). It generates
 * a specified number of random integers, categorizes them as positive or negative, and
 * inserts them into the correspondent list using mutex to avoid data races
 * 
 * @param  arg 	 -> (void *)t_main_struct
 * @return void* -> (void *)t_retval
 */
static void	*gen_and_insert_nbrs(void *arg)
{
	t_main_struct	*main;
	t_retval		*retval;
	int				new_nbr;
	t_lst			*new_node;

	retval = calloc(sizeof(t_retval), 1);
	if (retval == NULL)
		pthread_exit(NULL);
	main = (t_main_struct *)arg;
	for (int i = 0; i < main->numbers_per_thread; ++i)
	{
		new_nbr = gen_nbr();
		new_node = lst_new(new_nbr);
		if (new_node == NULL)
			continue ;
		if (new_nbr < 0)
		{
			pthread_mutex_lock(&main->mutex_n);
			lst_add_front(&main->lst_neg, new_node);
			pthread_mutex_unlock(&main->mutex_n);
		}
		else
		{
			pthread_mutex_lock(&main->mutex_p);
			lst_add_front(&main->lst_pos, new_node);
			pthread_mutex_unlock(&main->mutex_p);
		}
		retval->generated++;
	}
	pthread_exit(retval);
	return (NULL);
}


/**
 * @brief Creates and manages multiple threads to generate random numbers
 * 
 * This function initializes a random seed, create multiple threads
 * to generate numbers concurrently, and waits for all threads to finish
 * while monitoring for generation errors. Each thread generates numbers
 * and inserts them into the correspondent list (positive/negative).
 * 
 * Returns 0 on success, 1 on error
 * @param main_struct 
 * @return int 
 */
int	create_lists(t_main_struct *main_struct)
{
	const unsigned	seed = create_srandom_seed();
	int				error_in_gen_nbrs;
	pthread_t		*threads;
	t_retval		*retval;

	srandom(seed);
	threads = calloc(sizeof(pthread_t), main_struct->threads_amount);
	if (threads == NULL)
	{
		perror("malloc");
		return (1);
	}
	for (int i = 0; i < main_struct->threads_amount; ++i)
	{
		pthread_create(&threads[i], NULL, gen_and_insert_nbrs, (void *)main_struct);
	}
	error_in_gen_nbrs = 0;
	for (int i = 0; i < main_struct->threads_amount; ++i)
	{
		retval = NULL;
		pthread_join(threads[i], (void *)&retval);
		if (retval != NULL)
		{
			if (retval->generated != main_struct->numbers_per_thread && error_in_gen_nbrs == 0)
				error_in_gen_nbrs = 1;
			free(retval);
		}
	}
	free(threads);
	return (error_in_gen_nbrs);
}
