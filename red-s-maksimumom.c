/* MORA SE KORISTITI DVOSTRUKO VEZANA LISTA ZA MAKSIMUME
JER ŽELIMO I BRISATI I DODAVATI S KRAJA
--- MOGLI BISMO KORISTITI STOG ZA MAKSIMUME? 
SAMO ONDA MORAMO NAPISATI SVE FUNKCIJE ZA STOG?*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif


typedef struct Node {
  int val;
  struct Node *next;
} node;

typedef struct {
  node *head, *tail;
} queue;


queue *queue_ctor() {
  queue *q = malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void queue_dtor(queue *q) {
  free(q);
}

void queue_enqueue(queue *q, int val) {
  node *n = malloc(sizeof(node));
  n->val = val;
  n->next = NULL;
  if (q->tail == NULL) {
    q->head = n;
  } else {
    q->tail->next = n;
  }
  q->tail = n;
}

void queue_dequeue(queue *q) {
  node *n = q->head;
  if (q->head == NULL) return;
  q->head = q->head->next;
  if (q->head == NULL) {
    q->tail = NULL;
  }
  free(n);
}

int queue_is_empty(queue *q) {
  return q->head==NULL;
}

int main() {
  int n;
  char *op = malloc(8*sizeof(char));
  queue *q = queue_ctor();

  queue *maximums = queue_ctor();

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf(" %s", op);
    if (strcmp(op, "enqueue")==0) {

      int x;
      scanf(" %d", &x);

      // da li se dodaje najveći x ili jednak njemu
      // da li se dodaje u još prazan red
      if(queue_is_empty(q) || x >= maximums->tail->val){
        queue_enqueue(maximums, x);
      }

      queue_enqueue(q, x);
    } else if (strcmp(op, "dequeue")==0) {

      if(q->tail->val == maximums->head->val && !queue_is_empty(q) && !queue_is_empty(maximums)){
        queue_dequeue(maximums);
      }

      if (!queue_is_empty(q)) queue_dequeue(q);
    } else {
      if(queue_is_empty(q)){
        printf("-\n");
      } else{
        printf("%d\n", maximums->tail->val);
      }
    }
  }
  queue_dtor(q);
  free(op);
  return 0;
}
