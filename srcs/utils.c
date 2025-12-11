#include "insert_nbrs.h"

#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RANDOM_FILENAME "/dev/urandom"

unsigned	create_srandom_seed(void)
{
	const int	fd = open(RANDOM_FILENAME, O_RDONLY);
	unsigned	seed;

	if (fd == -1)
	{
		dprintf(2, "There was creating an urandom seed. Seed = 1\n");
		return (1);
	}
	if (read(fd, &seed, sizeof(seed)) == -1)
	{
		dprintf(2, "There was creating an urandom seed. Seed = 1\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (seed);
}

int	gen_nbr()
{
	const long	range = (long)INT_MAX - (long)INT_MIN + 1;

	return ((random() * range) / RAND_MAX);
}
