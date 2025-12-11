#include "insert_nbrs.h"

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

t_lst	*lst_last(t_lst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

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

void	*print_node(void *context)
{
	t_lst	*node;

	node = (t_lst *)context;
	printf("%d\n", node->content);
	return (NULL);
}

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
