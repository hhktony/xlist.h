/**
 *  Filename: t_xlist.c
 *   Created: 2014-02-27 01:07:38
 *      Desc: xlist.h test program
 *    Author: xutao(Tony Xu), butbueatiful@gmail.com
 *   Company: myself
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xlist.h"

struct student {
	int age;
	xlist_head_t list;
};

void print_list(struct student *head)
{
	xlist_head_t *pos = NULL;
	struct student *pnode = NULL;

	if (list_empty(&head->list))
		printf("list is empty!\n");

    printf("age: ");
    xlist_for_each(pos, &head->list) {
        pnode = xlist_entry(pos, struct student, list);
        printf("%d ", pnode->age);
    }
    printf("\n");
}

struct student *make_node(int age)
{
    struct student *node = (struct student *)malloc(sizeof(*node));
    if (!node) {
        fprintf(stderr, "malloc error!\n");
        exit(-1);
    }

    node->age = age;

    return node;
}

int main(void)
{
	struct student *node = NULL;
	xlist_head_t *pos = NULL, *n = NULL;
	struct student *pnode = NULL;
	int i;

	struct student head;
    memset(&head, 0, sizeof(head));

	INIT_XLIST_HEAD(&head.list);

    printf("=== add node ===\n");
	for (i = 0; i < 10; i++) {
        node = make_node(i); 
#ifdef TAIL
		xlist_add_tail(&node->list, &head.list);
#else
		xlist_add(&node->list, &head.list);
#endif
	}

    print_list(&head);

	printf("=== del even ===\n");
	xlist_for_each_safe(pos, n, &head.list) {
		pnode = xlist_entry(pos, struct student, list);
		if (pnode->age % 2 == 0) {
			/* printf("age %d has removed from the list!\n", pnode->age); */
			xlist_del(pos);
			free(pnode);
		}
	}
    print_list(&head);

	printf("=== del all ===\n");
	xlist_for_each_safe(pos, n, &head.list) {
		pnode = xlist_entry(pos, struct student, list);
        /* printf("age %d has removed from the list!\n", pnode->age); */
        xlist_del(pos);
        free(pnode);
	}
    print_list(&head);

	return 0;
}
