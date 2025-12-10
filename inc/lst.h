#ifndef LST_H
# define LST_H

# include <pthread.h>
# include <stdlib.h>


typedef struct s_lst
{
	int				content;
	struct t_lst	*next;
}	t_lst;

#endif
