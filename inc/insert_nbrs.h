#ifndef INSERT_NBRS_H
# define INSERT_NBRS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define USAGE "Usage: ./insert_numbers <threads> <numbers_per_thread>"

// Definition of the list of numbers
// It was the content (the generated number) and a pointer to the next node
typedef struct s_lst
{
	int				content;
	struct s_lst	*next;
}	t_lst;

// Struct used for sending from the threads to the main thread the number of generated numbers in each thread
// It will be used to check if all the numbers where generated correctly
typedef struct s_retval
{
	int	generated;
}	t_retval;

// Struct for the whole program, it has the 2 lists (positives, negatives)
typedef struct s_main_struct
{
	int				threads_amount;		// argv[1]
	int				numbers_per_thread;	// argv[2]
	t_lst			*lst_neg;			// list where negative numbers will be stored
	t_lst			*lst_pos;			// list where positive numbers will be stored
	pthread_mutex_t	mutex_n;			// mutex to protect writes/reads in the list of negative numbers
	pthread_mutex_t	mutex_p;			// mutex to protect writes/reads in the list of positive numbers
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
