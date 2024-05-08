#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int sz, val, pri;
  long long sum;
  struct Node *left, *right;
} node;

node *treap = NULL;

void pull(node **a) {
  if(!a) return;
  int sz_l = ((*a) -> left)? (*a) -> left -> sz: 0;
  int sz_r = ((*a) -> right)? (*a) -> right -> sz: 0;
  long long sum_l = ((*a) -> left)? (*a) -> left -> sum: 0;
  long long sum_r = ((*a) -> right)? (*a) -> right -> sum: 0;
  (*a) -> sz = sz_l + sz_r + 1;
  (*a) -> sum = sum_l + sum_r + (*a) -> val;
}

void split(node *a, node **b, node **c, int k) {
  if(!a) {
    *b = NULL;
    *c = NULL;
    return;
  }
  if(k == 0) {
    *c = a;
    *b = NULL;
    return;
  }
  if(a -> left && a -> left -> sz >= k) {
    *c = a;
    split(a -> left, b, &((*c) -> left), k);
    pull(c);
  }
  else {
    *b = a;
    int sz_l = (a -> left)? a -> left -> sz: 0;
    split(a -> right, &((*b) -> right), c, k - sz_l - 1);
    pull(b);
  }
}

node *merge(node *a, node *b) {
  if(!a) return b;
  if(!b) return a;
  if(a -> pri > b -> pri) {
    a -> right = merge(a -> right, b);
    pull(&a);
    return a;
  }
  else {
    b -> left = merge(a, b -> left);
    pull(&b);
    return b;
  }
}

void insert(int val, int pos) {
  node *tmp = (node*) malloc(sizeof(node));
  tmp -> val = val;
  tmp -> sz = 1;
  tmp -> pri = rand();
  tmp -> sum = val;
  tmp -> left = NULL;
  tmp -> right = NULL;
  node *t1, *t2;
  split(treap, &t1, &t2, pos);
  treap = merge(t1, tmp);
  treap = merge(treap, t2);
}

void remove(int pos) {
  node *t1, *t2, *t3, *t4;
  split(treap, &t1, &t2, pos - 1);
  split(t2, &t3, &t4, 1);
  treap = merge(t1, t4);
}

long long query(int l, int r) {
  node *t1, *t2, *t3, *t4;
  split(treap, &t1, &t2, l - 1);
  split(t2, &t3, &t4, r - l + 1);
  long long sum =  (t3)? t3 -> sum: 0;
  treap = merge(t1, t3);
  treap = merge(treap, t4);
  return sum;
}

int main () {
  int n, t;
  scanf("%d%d", &n, &t);
  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    insert(x, i);
  }
  for(int i = 0; i < t; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int pos;
      scanf("%d", &pos);
      remove(pos);
    }
    else if(op == 2) {
      int pos, val;
      scanf("%d%d", &pos, &val);
      insert(val, pos);
    }
    else {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", query(l, r));
    }
  }
  printf("%d\n", treap? treap -> sz: 0);
  while(treap != NULL) {
    node *t1, *t2;
    split(treap, &t1, &t2, 1);
    treap = t2;
    printf("%d ", t1 -> val);
  }

  return 0;
}
