#ifndef _LISTADT_H_
#define _LISTADT_H_
    #define SUCCESS 1
    #define FAILURE 0

    typedef struct node
    {
        struct node *next;
        struct node *prev;
        void *data;
    } Node;

    typedef struct list
    {
        Node *head;
        Node *tail;
        int size;
    } List;

    List *create_list();
    int size(List *);
    int is_empty(List *);
    int push(List *, void *);
    int append(List *, void *);
    int remove_value(List *, void *, int (*)(void *, void *));
    int in_list(List *, void *, int (*)(void *, void *));
    void *get_nth(List *, int);
    int remove_nth(List *, int);
    void empty_list(List *);
    void destroy_list(List *);

    int comparator_int_equals(void *, void *);
    int comparator_float_equals(void *, void *);
    int comparator_double_equals(void *, void *);
    int comparator_string_equals(void *, void *);
#endif
