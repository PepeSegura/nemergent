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
	t_lst	new_head = {0};
	t_lst	*new_end;

	if (left == NULL)
		return (right);
	if (right == NULL)
		return (left);
	new_end = &new_head;
	while (left && right)
	{
		if (left->content <= right->content)
		{
			new_end->next = left;
			left = left->next;
		}
		else
		{
			new_end->next = right;
			right = right->next;
		}
		new_end = new_end->next;
	}
	if (left)
		new_end->next = left;
	else
		new_end->next = right;
	return (new_head.next);
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
