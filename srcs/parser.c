#include "insert_nbrs.h"

int	parser(t_main_struct *main_struct, int argc, char **argv)
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Error: invalid args\n%s\n", USAGE);
		return (1);
	}
	main_struct->threads_ammount = atoi(argv[1]);
	main_struct->nbrs_per_thread = atoi(argv[2]);
	if (main_struct->threads_ammount <= 0 || main_struct->nbrs_per_thread <= 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid args\n%s\n", USAGE);
		return (1);
	}
	return (0);
}
