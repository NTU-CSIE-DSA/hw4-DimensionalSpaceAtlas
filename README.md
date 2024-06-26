# [HW4.P3] Dimensional Space Atlas Tutorial


## Sample Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// The structure of a treap node
struct Node {
    struct Node *left, *right;  // Left and right child nodes
    int priority;               // Priority of the node (decided by random)
    int value;                  // Value in the node
    int size;                   // Number of nodes in the subtree
    long long sum;              // Sum of nodes' values in the subtree
};

// To store the return treaps after split
struct NodePair {
    struct Node *left, *right;
};

// Create a new node
struct Node *create(int value) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->priority = rand();
    new_node->value = value;
    new_node->size = 1;
    new_node->sum = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Return the root's order add `shift` in the sequence
int order(struct Node *root, int shift) {
    return shift + (root->left ? root->left->size : 0) + 1;
}

// Update root's size and sum tag
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

// Use order as its key to split the treap into two treaps
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
    } 
    else {
        np = split(root->left, k, shift);
        root->left = np.right;
        update(root);
        np.right = root;
    }
    return np;
}

// Merge two treaps into one treap
struct Node *merge(struct Node *left, struct Node *right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } 
    else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

// Insert a node with value `value` into the `k`-th position of the treap
struct Node *insert(struct Node *root, int k, int value) {
    struct Node *new_node = create(value);
    if (!root) return new_node;
    struct NodePair np = split(root, k, 0);
    root = merge(np.left, new_node);
    root = merge(root, np.right);
    return root;
}

// Remove the `k`-th element of the treap
struct Node *erase(struct Node *root, int k) {
    assert(root);
    struct NodePair np1 = split(root, k - 1, 0);
    struct NodePair np2 = split(np1.right, 1, 0);
    return merge(np1.left, np2.right);
}

/* Calculate the sum of the `l + shift`-th element to `r + shift`-th element of the treap
   `shift = 0` at the beginning */
long long calc_sum(struct Node *root, int l, int r, int shift) {
    if (!root) return 0;
    assert(l <= r);
    int ord = order(root, shift);
    int L = shift + 1, R = shift + root->size;
    if (l <= L && r >= R) return root->sum;
    long long sum = 0;

    // Divide the sum into three parts: root node, left subtree, right subtree
    if (l <= ord && r >= ord) sum += root->value;
    if (l < ord) sum += calc_sum(root->left, l, r, shift);
    if (r > ord) sum += calc_sum(root->right, l, r, ord);
    return sum;
}

/* Print the sequence
   Whether you print one more space in the last line, the verdict won't change. */
void traverse(struct Node *root, bool last) {
    if (!root) return;
    traverse(root->left, 0);
    printf("%d%c", root->value, " \n"[last && !root->right]);
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
        sequence = insert(sequence, i - 1, a);
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

    if (sequence) printf("%d\n", sequence->size);
    else printf("0\n");
    traverse(sequence, 1);
    return 0;
}
```

## Common Mistakes
* Carefully handle cases involving `NULL`.
* When searching for an element's position, remember to shift when traversing to the right child.

## Coding Tips
* Make the update process a function to reduce coding complexity.
* Let the return value of split be `NodePair` to avoid using double pointers.
* Use a fixed seed to ensure the code is deterministic.
  
