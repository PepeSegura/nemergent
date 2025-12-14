#include "insert_nbrs.h"

/**
 * @brief Function to create a node with the content received as an argument
 * 
 * @param content 
 * @return t_lst* 
 */
t_lst	*lst_new(int content)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}


/**
 * @brief Function that returns the last node of the list
 * 
 * @param lst 
 * @param node 
 */
t_lst	*lst_last(t_lst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/**
 * @brief Function for adding a node at the end of the list
 * 
 * @param lst 
 * @param node 
 */
void	lst_add_back(t_lst **lst, t_lst *node)
{
	t_lst	*last;

	if (lst == NULL)
	{
		lst = &node;
		return ;
	}
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	last = lst_last(*lst);
	last->next = node;
}


/**
 * @brief Function for adding a node at the front of the list
 * 
 * @param lst 
 * @param node 
 */
void	lst_add_front(t_lst **lst, t_lst *node)
{
	if (lst == NULL)
	{
		lst = &node;
		return ;
	}
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	node->next = *lst;
	*lst = node;
}

/**
 * @brief Function to clear a list
 * 
 * @param lst 
 */
void	lst_clear(t_lst **lst)
{
	t_lst	*aux;

	while (lst && *lst)
	{
		aux = (*lst)->next;
		free(*lst);
		*lst = aux;
	}
}


/**
 * @brief Function send to lst_iter for printing the content of a node
 * 
 * @param context 
 * @return void* 
 */
void	*print_node(void *context)
{
	t_lst	*node;

	node = (t_lst *)context;
	printf("%d\n", node->content);
	return (NULL);
}


/**
 * @brief Function that iterates a list applying the received function to every node
 * 
 * @param lst 
 * @param func 
 */
void	lst_iter(t_lst **lst, void *(func)(void *context))
{
	t_lst	*aux;

	if (lst == NULL)
		return ;
	aux = *lst;
	while (aux)
	{
		func((void *)(aux));
		aux = aux->next;
	}
}
