/**
 *  Filename: test.c
 *   Created: 2014-02-27 01:07:38
 *      Desc: list.h test program
 *    Author: xutao(Tony Xu), butbueatiful@gmail.com
 *   Company: myself
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct student {
	int age;
	struct list_head list;
};

int main(void)
{
	struct student *list_node = NULL;
	struct list_head *pos = NULL, *n = NULL;
	struct student *pnode = NULL;
	int i;

	struct student *head = (struct student *)malloc(sizeof(struct student));
	if (head == NULL) {
		fprintf(stderr, "file: %s line,%d:malloc error!\n", __FILE__, __LINE__);
		exit(1);
	}

	INIT_LIST_HEAD(&head->list);

	for (i = 0; i < 10; i++) {
		list_node = (struct student *)malloc(sizeof(struct student));
		if (list_node == NULL) {
			fprintf(stderr, "file: %s line,%d: malloc error!\n", __FILE__,
					__LINE__);
			exit(1);
		}

		list_node->age = i + 20;
#ifdef TAIL
		list_add_tail(&list_node->list, &head->list);
#else
		list_add(&list_node->list, &head->list);
#endif
	}

	if (list_empty(&head->list))
		printf("list is empty!\n");
	else {
		list_for_each(pos, &head->list) {
			pnode = list_entry(pos, struct student, list);
			printf("age: %d\n", pnode->age);
		}
	}

	printf("======================\n");

	list_for_each_safe(pos, n, &head->list) {
		pnode = list_entry(pos, struct student, list);
		if (pnode->age % 2 == 0) {
			printf("age %d has removed from the list!\n", pnode->age);
			list_del(pos);
			free(pnode);
		}
	}

    printf("------------------------\n");
	if (list_empty(&head->list))
		printf("list is empty!\n");
	else {
		list_for_each(pos, &head->list) {
			pnode = list_entry(pos, struct student, list);
			printf("age: %d\n", pnode->age);
		}
	}

	return 0;
}
