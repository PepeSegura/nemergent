#ifndef INSERT_NBRS_H
# define INSERT_NBRS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define USAGE "Usage: ./insert_numbers <threads> <numbers_per_thread>"

typedef struct s_lst
{
	int				content;
	struct s_lst	*next;
}	t_lst;

typedef struct s_retval
{
	int	generated;
}	t_retval;

typedef struct s_main_struct
{
	int				threads_ammount;
	int				nbrs_per_thread;
	t_lst			*lst_neg;
	t_lst			*lst_pos;
	pthread_mutex_t	mutex_n;
	pthread_mutex_t	mutex_p;
}	t_main_struct;

/* parser.c */
int		parser(t_main_struct *main_struct, int argc, char **argv);

/* thread.c */
int		create_lists(t_main_struct *main_struct);

/* lst.c */
t_lst	*lst_new(int content);
t_lst	*lst_last(t_lst *lst);
void	lst_add_back(t_lst **lst, t_lst *node);
void	lst_add_front(t_lst **lst, t_lst *node);
void	lst_clear(t_lst **lst);
void	*print_node(void *context);
void	lst_iter(t_lst **lst, void *(func)(void *context));

/* merge_sort.c */
void	merge_sort(t_lst **lst);

/* utils.c */
unsigned	create_srandom_seed(void);
int			gen_nbr(void);

#endif
