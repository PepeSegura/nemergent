#include "insert_nbrs.h"

t_lst	*get_middle(t_lst *lst)
{
	t_lst	*slow;
	t_lst	*fast;

	if (lst == NULL)
		return (NULL);
	slow = lst;
	fast = lst->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return (slow);
}

t_lst	*sorted_merge(t_lst *left, t_lst *right)
{
	if (left == NULL)
		return (right);
	if (right == NULL)
		return (left);
	if (left->content <= right->content)
	{
		left->next = sorted_merge(left->next, right);
		return (left);
	}
	else
	{
		right->next = sorted_merge(left, right->next);
		return (right);
	}
}

void	merge_sort(t_lst **lst)
{
	t_lst	*left;
	t_lst	*middle;
	t_lst	*right;

	if (lst == NULL || *lst == NULL || (*lst)->next == NULL)
		return ;
	left = *lst;
	middle = get_middle(left);
	right = middle->next;
	middle->next = NULL;
	merge_sort(&left);
	merge_sort(&right);
	*lst = sorted_merge(left, right);
}
