#include "insert_nbrs.h"

void	*gen_and_insert_nbrs(void *arg)
{
	t_main_struct	*main;
	t_retval		*retval;
	int				new_nbr;
	t_lst			*new_node;

	retval = calloc(sizeof(t_retval), 1);
	if (retval == NULL)
		pthread_exit(NULL);
	main = (t_main_struct *)arg;
	for (int i = 0; i < main->nbrs_per_thread; ++i)
	{
		new_nbr = gen_nbr();
		new_node = lst_new(new_nbr);
		if (new_node == NULL)
			continue ;
		if (new_nbr < 0)
		{
			pthread_mutex_lock(&main->mutex_n);
			lst_add_back(&main->lst_neg, new_node);
			pthread_mutex_unlock(&main->mutex_n);
		}
		else
		{
			pthread_mutex_lock(&main->mutex_p);
			lst_add_back(&main->lst_pos, new_node);
			pthread_mutex_unlock(&main->mutex_p);
		}
		retval->generated++;
	}
	pthread_exit(retval);
	return (NULL);
}

int	create_lists(t_main_struct *main_struct)
{
	const unsigned	seed = create_srandom_seed();
	int				error_in_gen_nbrs;
	pthread_t		*threads;
	t_retval		*retval;

	srandom(seed);
	threads = calloc(sizeof(pthread_t), main_struct->threads_ammount);
	if (threads == NULL)
	{
		perror("malloc");
		return (1);
	}
	for (int i = 0; i < main_struct->threads_ammount; ++i)
	{
		pthread_create(&threads[i], NULL, gen_and_insert_nbrs, (void *)main_struct);
	}
	error_in_gen_nbrs = 0;
	for (int i = 0; i < main_struct->threads_ammount; ++i)
	{
		retval = NULL;
		pthread_join(threads[i], (void *)&retval);
		if (retval != NULL)
		{
			if (retval->generated != main_struct->nbrs_per_thread && error_in_gen_nbrs == 0)
				error_in_gen_nbrs = 1;
			free(retval);
		}
	}
	free(threads);
	return (error_in_gen_nbrs);
}
