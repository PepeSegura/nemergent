#include "insert_nbrs.h"

/**
 * @brief Program parser, it will trow an error if argc is not 3, and if the numbers in the input are not bigger than 0
 * 
 * Returns 0 on success, 1 on error
 * @param main_struct 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	parser(t_main_struct *main_struct, int argc, char **argv)
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Error: invalid args\n%s\n", USAGE);
		return (1);
	}
	main_struct->threads_amount = atoi(argv[1]);
	main_struct->numbers_per_thread = atoi(argv[2]);
	if (main_struct->threads_amount <= 0 || main_struct->numbers_per_thread <= 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid args\n%s\n", USAGE);
		return (1);
	}
	return (0);
}
