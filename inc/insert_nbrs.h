#ifndef INSERT_NBRS_H
# define INSERT_NBRS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "lst.h"


#define USAGE "Usage: ./insert_numbers <number of threads> <ammount of generated numbers per thread>"

typedef struct s_main_struct
{
	int				threads_ammount;
	int				nbrs_thread;
	t_lst			*lst_neg;
	t_lst			*lst_pos;
	pthread_mutex_t	mutex_n;
	pthread_mutex_t	mutex_p;
}	t_main_struct;

int	parser(t_main_struct *main_struct, int argc, char **argv);

#endif
