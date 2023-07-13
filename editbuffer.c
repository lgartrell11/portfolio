/* COMP 211 Homework 10:  Using linked bufs to implement an editor buffer
 *
 * Lance Gartrell
 * May 4, 2023
 * Professor Danner
 * Computer Science I
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*  A struct node representing a doubly linked list
 */
struct node {
    char val;
    struct node *prev;
    struct node *next;
};

typedef struct node node ;

/*
 *  A struct buffer value b represents a character sequence with position.  We
 *  write <c_0,...,c_{pos}, |c_{pos+1},...,c_{size-1}> to represent such a sequence with
 *  size characters, where the insertion mark is between c_{i-1} and c_i.
 *  
 *  Invariants:
 * 
 *  buf->back->next = NULL
 *  buf->front->prev = NULL
 *  0 <= buf->loc <= buf->size 
 *  buf->front = c_0
 *  buf->back = c_size-1
 */
struct buffer {
    int size;
    int loc;
    node *front;
    node *back;
    node *ins_mark;
};

/* This line just makes 'buffer' an abbreviation for 'struct buffer'.
 */
typedef struct buffer buffer ;

/* empty = <>. returns a newly createdd empty buffer structure.
 */
buffer* buf_empty() {
    buffer *buf = malloc(sizeof(buffer));
    buf->front = NULL;
    buf->back = NULL; 
    buf->ins_mark = NULL;
    buf->size = 0;
    return buf;
}

/* insert(buf, c) inserts c to the left of the insertion point of buf.  After
 * the insertion, the insert mark is to the right of c.
 *
 * Pre-condition:   buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 * Post-condition:  buf = <c_0,...,c_{i-1}, c, |c_i,...,c_{n-1}>.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
void buf_insert(buffer *buf, char c) {

    /* assertion affirms the size and loc of insertion mark are valid for an insertion */
    assert(buf->loc <= buf->size && buf->size >= 0);

    node* cnode = malloc(sizeof(node));
    cnode->val = c;

    /* reassign the prev and next node pointer of the surrounding nodes to the newly inserted node */
    if (buf->ins_mark != NULL){
        cnode->prev = buf->ins_mark->prev;
        cnode->next = buf->ins_mark->next;
        
        /* conditionals to check if node exist before and after the inserted node 
         * - next and prev pointers are updated accordingly
         */
        if (buf->ins_mark->prev != NULL) {
            buf->ins_mark->prev->next = cnode;
        }else {
            buf->front = cnode;
        }
        if (buf->ins_mark->next != NULL) {
            buf->ins_mark->next->prev = cnode;
        }else {
            buf->back = cnode;
        }
        
        buf->ins_mark->prev = cnode;
    } else {
        /* reassign the inserted node as the head of the buffer if insertion mark was NULL */
        cnode->next = buf->front;
        cnode->prev = NULL;
        if (buf->front != NULL) {
            buf->front->prev = cnode;
        } else {
            buf->back = cnode;
        }
        buf->front = cnode;
    }
    buf->size++;
    buf->loc++;

}

/* delete_left(buf) deletes the character to the left of the insert mark.  If
 * there is no character to the left of the insert mark, this function has no
 * effect.
 *
 * Pre-condition:  buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 * Post-condition: buf = <c_0,...,c_{i-2}, |c_i,...,c_{n-1}>.
 *   If i=0, this function has no effect.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
void buf_delete_left(buffer *buf) {

    /* assertion to verify that the insertion mark location and size of buffer are valid for deletion*/
    assert(buf->loc <= buf->size && buf->size >= 0);
    if (buf->loc > 0){
        assert(buf->ins_mark->prev != NULL || buf->ins_mark->prev == buf->front);
    }

    /* reassigns the pointers if the insertion mark has a character to the left of it (or, its loc is above 0)*/
    if (buf->loc > 0){
        node* dnode = buf->ins_mark->prev;

        /* conditionals to check if nodes exist before and after the deleted node
         * - next and prev pointers are updated accordingly
         */
        if (dnode == buf->front) {
            buf->front = dnode->next;
        }else {
            dnode->prev->next = dnode->next;
        }
        if (dnode == buf->back) {
            buf->back = dnode->prev;
        } else {
            dnode->next->prev = dnode->prev;
        }
    free(dnode);
    buf->loc--;
    buf->size--;
    } 
}

/* delete_right(buf) deletes the character to the right of the insert mark.  If
 * there is no character to the right of the insert mark, this function has no
 * effect.
 *
 * Pre-condition:  buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 * Post-condition: buf = <c_0,...,c_{i-1}, |c_{i+1},...,c_{n-1}>.
 *   If i=n, this function has no effect.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
void buf_delete_right(buffer *buf) {

    /* assertion to verify that the insertion mark location and size of buffer are valid for deletion*/
    assert(buf->loc <= buf->size && buf->size >= 0);
    if (buf->loc == buf->size){
        assert(buf->ins_mark->next == NULL || buf->ins_mark->next == buf->back);
    }

    /* reassigns the buffers pointers if the insertion mark has a node to the right of it */
    if (buf->loc < buf->size){
        
        node* dnode = buf->ins_mark->next;

        /* conditionals to check if nodes exist before and after the deleted node 
         * - next and prev pointers are updated accordingly
         */
         
        if (dnode == buf->front) {
            buf->front = dnode->next;
        }else {
            dnode->prev->next = dnode->next;
        }
        if (dnode == buf->back) {
            buf->back = dnode->prev;
        }else {
            dnode->next->prev = dnode->prev;
        }
        
        free(dnode);
        buf->size--;
    } 
    
}

/* move_left(buf) moves the insert mark one character to the left.  If there is
 * no character to the left of the insert mark, this functdion has no effect.
 *
 * Pre-condition:  buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 * Post-condition: buf = <c_0,...,c_{i-2}, |c_{i-1},...,c_{n-1}>.
 *   If i = 0, this function has no effect.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
void buf_move_left(buffer *buf) {
    if (buf->loc > 0){
        buf->ins_mark = buf->ins_mark->prev;
        buf->loc--;
    } else{
        buf->ins_mark = buf->front;
    }
}

/* move_right(buf) moves the insert mark one character to the right.  If there
 * is no character to the right of the insert mark, this functdion has no
 * effect.
 *
 * Pre-condition:  buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 * Post-condition: buf = <c_0,...,c_i, |c_{i+1},...,c_{n-1}>.
 *   If i = n, this function has no effect.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
void buf_move_right(buffer *buf) {
     if (buf->loc == buf->size){
        buf->ins_mark = buf->back;
    } else{
        buf->ins_mark = buf->ins_mark->next;
        buf->loc++;
    }
}

/* set(buf, i) sets the insert mark so that it is to the left of the i-th
 * character.  Characters are 0-indexed, so set(buf, 0) sets the insert mark to
 * the beginning of the buffer.  i may be equal to the length of the buffer; in
 * this case, the insert mark is set to the right of the last character.
 *
 * Pre-condition:  buf = <c_0,...,c_{n-1}>, 0 <= i <= n.
 * Post-condition: buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 *
 */
void buf_set(buffer *buf, int x) {
    buf->ins_mark = buf->front;
    buf->loc = 0;
    while (buf->ins_mark != NULL && buf->loc != x) {
        buf->ins_mark = buf->ins_mark->next;
        buf->loc++;
    }
}

/* buf_get_line(buf, s).
 *
 * Pre-condition:  buf = <c_0,...,c_{n-1}>, length(s) ≥ n.
 *
 * Post-condition:  s[i] = c_i for 0 ≤ i < n.
 *
 * Ex:  if buf represents "abcd|efg", then s must have size at least 7 and
 * after calling buf_get_line(buf, s), s will start with {'a', 'b', 'c', 'd',
 * 'e', 'f', 'g', ...}, with the characters after 'g' unspecified.
 */
void buf_get_contents(buffer* buf, char cont[]) {
    node* bf = buf->front ;
    for (int i = 0; i < buf->size; i++){
        int c = bf->val;
        cont[i] = c; 
        bf = bf->next;
    }
}

/* buf_get_pos(buf) = i, where buf = <c_0,...,c_{i-1}, |c_i,...,c_{n-1}>.
 *
 * Ex:  if buf represents "abcd|efg", then getpos(buf) = 4.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
int buf_get_pos(buffer* buf) {
    return buf->loc;
}

/* int buf_size(buf) = n, where buf = <c_0,...,c_{n-1>>.
 *
 * THIS FUNCTION MUST BE CONSTANT TIME.
 */
int buf_size(buffer*buf) {
    return buf->size;
}

/* buf_free(buf):  frees all resources associated to buf, including buf itself.
 */
void buf_free(buffer*buf) {
    node* v = buf->front;
    while (v != NULL){
        node* temp = v->next;
        free(temp);
        v = temp;
    }
    free(buf);
}

/*  print_buffer(buf).
 *
 *  Post-condition:  Some information about buf will be printed to ther
 *  terminal.  
 *
 *  The implementation of this function is entirely up to you.  It is here to
 *  help you with debugging.  We will never use it, but there is an option in
 *  the driver program that will call this function with the current buffer.
 */
void buf_print(buffer *buf) {
    node *current = buf->front;
    while (current != NULL) {
        printf("%c", current->val);
        current = current->next;
    }
    printf("\n");
}
