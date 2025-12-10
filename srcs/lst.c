#include "insert_nbrs.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#define RANDOM_FILENAME "/dev/urandom"

unsigned	create_seed(void)
{
	int	fd = open(RANDOM_FILENAME, O_RDONLY);

	if (fd == -1)
	{
		dprintf(2, "There was creating a random seed. Seed = 1\n");
		return (1);
	}

	unsigned seed;

	if (read(fd, &seed, sizeof(seed)) == -1)
	{
		dprintf(2, "There was creating a random seed. Seed = 1\n");
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


typedef struct s_retval
{
	int a;
	int b;
} t_retval;


void *gen_x_nbrs(void *arg)
{
	int nbrs_ammount = (int)(long)(int *)arg;

	for (int i = 0; i < nbrs_ammount; ++i)
	{
		printf("Generated nbr: %d\n", gen_nbr());
	}

	t_retval *retval = calloc(sizeof(t_retval), 1);
	if (retval == NULL)
		pthread_exit(NULL);
	retval->a = 1;
	retval->b = 2;
	pthread_exit(retval);
	return (NULL);
}

int create_lists(t_main_struct *main_struct)
{
	unsigned seed = create_seed();

	srandom(seed);

	pthread_t	*threads = calloc(sizeof(pthread_t), main_struct->threads_ammount);
	if (threads == NULL)
	{
		perror("malloc");
		return (1);
	}

	for (int i = 0; i < main_struct->threads_ammount; ++i)
	{
		pthread_create(&threads[i], NULL, gen_x_nbrs, (void *)(long)main_struct->nbrs_per_thread);
	}

	for (int i = 0; i < main_struct->threads_ammount; ++i)
	{
		t_retval *ret = NULL;

		pthread_join(threads[i], (void *)&ret);
		printf("retval: %d %d\n", ret->a, ret->b);
		if (ret != NULL)
			free(ret);
	}

	free(threads);
	return (0);
}
