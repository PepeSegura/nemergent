#include "insert_nbrs.h"

int init_mutex(t_main_struct *main_struct)
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


int main(int argc, char **argv)
{
	t_main_struct	main_struct = {0};

	if (parser(&main_struct, argc, argv) == 1)
		return (1);

	if (init_mutex(&main_struct) == 1)
		return (1);

	create_lists(&main_struct);
	print_lists(&main_struct);
	clear_lists(&main_struct);
	destroy_mutex(&main_struct);
	return (0);
}
