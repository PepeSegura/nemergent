#include "insert_nbrs.h"

int	init_mutex(t_main_struct *main_struct)
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

void	destroy_mutex(t_main_struct *main_struct)
{
	pthread_mutex_destroy(&main_struct->mutex_n);
	pthread_mutex_destroy(&main_struct->mutex_p);
}

int	main(int argc, char **argv)
{
	t_main_struct	main_struct = {0};

	if (parser(&main_struct, argc, argv) == 1)
		return (1);

	if (init_mutex(&main_struct) == 1)
		return (1);

	if (create_lists(&main_struct) == 1)
	{
		dprintf(2, "There was an error generating all the nummbers\n");
		lst_clear(&main_struct.lst_neg);
		lst_clear(&main_struct.lst_pos);
		destroy_mutex(&main_struct);
		return (1);
	}

	lst_iter(&main_struct.lst_neg, print_node);
	lst_iter(&main_struct.lst_pos, print_node);
	// print_lists(&main_struct);
	// clear_lists(&main_struct);
	destroy_mutex(&main_struct);
	return (0);
}
