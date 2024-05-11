# [HW4.P3] Dimensional Space Atlas Tutorial


## sample code
```c
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


struct Node {
  struct Node *left, *right;
  int priority;
  int value;
  int size; // number of nodes in the subtree
  long long sum; // sum of nodes' values in the subtree
};

struct NodePair {
  struct Node *left, *right;
};

/* Create a new node.  */
struct Node *create(int value) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->priority = rand();
  new_node->value = value;
  new_node->size = 1;
  new_node->sum = value;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

/* Return the root's order in the sequence.  */
int order(struct Node *root, int shift) {
  return shift + root->size - ((root->right)? root->right->size : 0);
}

/* Update roots' size and sum.  */
void update(struct Node *root) {
  root->size = 1;
  root->sum = root->value;
  if (root->left) {
    root->size += root->left->size;
    root->sum += root->left->sum;
  }
  if (root->right) {
    root->size += root->right->size;
    root->sum += root->right->sum;
  }
}

/* Use root's order as its key.  */
struct NodePair split(struct Node *root, int k, int shift) {
  struct NodePair np;
  if (!root) {
    np.left = NULL;
    np.right = NULL;
    return np;
  }
  int ord = order(root, shift);
  if (ord <= k) {
    np = split(root->right, k, ord);
    root->right = np.left;
    update(root);
    np.left = root;
    return np;
  } else {
    np = split(root->left, k, shift);
    root->left = np.right;
    update(root);
    np.right = root;
    return np;
  }
}

struct Node *merge(struct Node *left, struct Node *right) {
  if (!left) return right;
  if (!right) return left;
  if (left->priority > right->priority) {
    left->right = merge(left->right, right);
    update(left);
    return left;
  } else {
    right->left = merge(left, right->left);
    update(right);
    return right;
  }
}

struct Node *insert(struct Node *root, int k, int value) {
  struct Node *new_node = create(value);
  if (!root) return new_node;
  struct NodePair np = split(root, k, 0);
  root = merge(np.left, new_node);
  root = merge(root, np.right);
  return root;
}

struct Node *erase(struct Node *root, int k) {
  assert(root);
  struct NodePair np = split(root, k-1, 0);
  root = np.left;
  np = split(np.right, 1, 0);
  root = merge(root, np.right);
  return root;
}

long long calc_sum(struct Node *root, int l, int r, int shift) {
  if (!root) return 0;
  assert(l <= r);
  int ord = order(root, shift);
  int L = shift + 1, R = shift + root->size;
  // printf("l: %d, r: %d\n", l, r);
  // printf("%d %d %lld %d %d\n", ord, root->value, root->sum, L, R);
  if (l <= L && r >= R) return root->sum;
  long long sum = 0;
  if (l <= ord && r >= ord) sum += root->value;
  if (l < ord) sum += calc_sum(root->left, l, r, shift);
  if (r > ord) sum += calc_sum(root->right, l, r, ord);
  return sum;
}

/* Print the sequence.
   Whether you print one more space in the last line, the verdict won't change.  */
void traverse (struct Node *root, bool last) {
  if (!root) return;
  traverse(root->left, 0);
  printf("%d%c", root->value, " \n"[last & !root->right]);
  traverse(root->right, last);
}

int main() {
  srand(100);
  struct Node *sequence = NULL;
  int N, T;
  scanf("%d%d", &N, &T);
  for (int i = 1; i <= N; i++) {
    int a;
    scanf("%d", &a);
    sequence = insert(sequence, i-1, a);
  }

  while (T--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int k;
      scanf("%d", &k);
      sequence = erase(sequence, k);
    } else if (op == 2) {
      int k, b;
      scanf("%d%d", &k, &b);
      sequence = insert(sequence, k, b);
    } else if (op == 3) {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", calc_sum(sequence, l, r, 0));
    }
  }

  if(sequence) printf("%d\n", sequence->size);
  else printf("0\n");
  traverse(sequence, 1);
  return 0;
}
```

## common mistakes
<!--
* One may want to create an $(N\times T)$-size 2D array. The maximum size of this array is approximately $c \cdot 10^6 \cdot 5\cdot 10^5 (\text{bytes})\approx c\cdot 480000 (\text{MB})$, which exceeds the memory limit.
* You should ensure your binary search finds the last rank even if there are multiple classmates with the same power.
* You should use store power-related data using `long long` to prevent overflow.
-->

## coding tips
<!--
* In order to directly update the power for each player, use `n_up` and `last_up` to record the information of operation 2.
* Always call `update()` when you want to inquire a classmate's power to ensure you obtain the correct power. Let the return value of `update()` be the power can simplify your code.
-->
  
