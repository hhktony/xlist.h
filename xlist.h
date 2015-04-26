/**
 *  Filename: xlist.h
 *   Created: 2014-02-26 05:23:03
 *      Desc:
 *    Author: xutao(Tony Xu), butbueatiful@gmail.com
 *   Company: myself
 */

#ifndef XLIST_H
#define XLIST_H

typedef struct xlist_head {
     struct xlist_head *next, *prev;
} xlist_head_t;

#define XLIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	xlist_head_t name = XLIST_HEAD_INIT(name)

static inline void INIT_XLIST_HEAD(xlist_head_t *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __xlist_add(xlist_head_t *new,
                               xlist_head_t *prev,
                               xlist_head_t *next)
{
      next->prev = new;
      new->next  = next;
      new->prev  = prev;
      prev->next = new;
}

/**
 * xlist_add_head - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void xlist_add(xlist_head_t *new, xlist_head_t *head)
{
	__xlist_add(new, head, head->next);
}

/**
 * xlist_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
 static inline void xlist_add_tail(xlist_head_t *new, xlist_head_t *head)
 {
      __xlist_add(new, head->prev, head);
 }

/**
  * xlist_for_each    -   iterate over a list
  * @pos:    the &xlist_head_t to use as a loop cursor.
  * @head:   the head for your list.
  */
#define xlist_for_each(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                    \
         const typeof( ((type *)0)->member ) *__mptr = (ptr); \
         (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

/**
  * xlist_entry - get the struct for this entry
  * @ptr:    the &xlist_head_t pointer.
  * @type:   the type of the struct this is embedded in.
  * @member: the name of the list_struct within the struct.
  */
#define xlist_entry(ptr, type, member) \
       container_of(ptr, type, member)

/**
 * xlist_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:    the &xlist_head_t to use as a loop cursor.
 * @n:      another &xlist_head_t to use as temporary storage
 * @head:   the head for your list.
 */
#define xlist_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __xlist_del(xlist_head_t * prev, xlist_head_t * next)
{
     next->prev = prev;
     prev->next = next;
}

static inline void xlist_del(xlist_head_t *entry)
{
     __xlist_del(entry->prev, entry->next);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const xlist_head_t *head)
{
    return head->next == head;
}

#endif /* end of include guard: XLIST_H */
