#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <linux/list.h>
#include <linux/slab.h>

struct node {
	char *str;
	struct list_head link;
};

struct node *new_node(char *s)
{
	struct node *re = kmalloc(sizeof(struct node), GFP_KERNEL);
	re->str = s;
	INIT_LIST_HEAD(&(re->link));
	return re;
}

void add_node(struct node *new_item, struct list_head *list)
{
	list_add(&(new_item->link), list);
}

void add_node_tail(struct node *new_item, struct list_head *list)
{
	list_add_tail(&(new_item->link), list);
}

void del_node(struct node *del_item)
{
	list_del(&(del_item->link));
	kfree(del_item->str);
	kfree(del_item);
}

#endif
