#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


struct Node {
  struct Node *left, *right;
  int priority;
  int value;
  int size; // number of nodes in the subtree
  long long sum; // sum of nodes' values in the subtree
  long double key;
};

struct NodePair {
  struct Node *left, *right;
};

struct Node *create(int value, long double key) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->priority = rand();
  new_node->value = value;
  new_node->size = 1;
  new_node->sum = value;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->key = key;
  return new_node;
}

int order(struct Node *root, int shift) {
  return shift + root->size - ((root->right)? root->right->size : 0);
}

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

struct Node *kth_element(struct Node *root, int k, int shift) {
  int ord = order(root, shift);
  if (ord == k) return root;
  if (ord < k) return kth_element(root->right, k, ord);
  if (ord > k) return kth_element(root->left, k, shift);
  return NULL;
}

struct NodePair split(struct Node *root, long double key) {
  struct NodePair np;
  if (!root) {
    np.left = NULL;
    np.right = NULL;
    return np;
  }
  if (root->key <= key) {
    np = split(root->right, key);
    root->right = np.left;
    update(root);
    np.left = root;
    return np;
  } else {
    np = split(root->left, key);
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
  long double key;
  if (!root) key = 0;
  else {
    if (k == 0) {
      key = kth_element(root, 1, 0)->key;
      if (key >= -10) key -= 0.01;
      else key += 0.1 * key;
    } else if (k == root->size) {
      key = kth_element(root, k, 0)->key;
      if (key <= 10) key += 0.1;
      else key += 0.1 * key;
    } else {
      Node *target1 = kth_element(root, k, 0);
      Node *target2 = kth_element(root, k+1, 0);
      key = (target1->key + target2->key) / 2;
    }
  }
  struct Node *new_node = create(value, key);
  if (!root) return new_node;
  struct NodePair np = split(root, key);
  root = merge(np.left, new_node);
  root = merge(root, np.right);
  return root;
}

struct Node *erase(struct Node *root, int k) {
  assert(root);
  long double key1, key2;
  if (k != 1) key1 = kth_element(root, k-1, 0)->key;
  else key1 = -(long double)1e150;
  if (k != root->size) key2 = kth_element(root, k, 0)->key;
  else key2 = (long double)1e150;
  struct NodePair np;
  np = split(root, key1);
  root = np.left;
  np = split(np.right, key2);
  root = merge(root, np.right);
  return root;
}

long long calc_sum(struct Node *root, int l, int r, int shift) {
  if (!root) return 0;
  assert(l <= r);
  int ord = order(root, shift);
  int L = shift + 1, R = shift + root->size;
  if (l <= L && r >= R) return root->sum;
  long long sum = 0;
  if (l <= ord && r >= ord) sum += root->value;
  if (l < ord) sum += calc_sum(root->left, l, r, shift);
  if (r > ord) sum += calc_sum(root->right, l, r, ord);
  return sum;
}

void traverse (struct Node *root) {
  if (!root) return;
  traverse(root->left);
  printf("%d ", root->value);
  traverse(root->right);
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
  int op;
  while (T--) {
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
  traverse(sequence);
  printf("\n");
	return 0;
}
