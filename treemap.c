#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if(new == NULL) return NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  tree->current = tree->root;
  TreeNode * current = NULL;
  TreeNode *nuevoNodo = createTreeNode(key, value);

  if(tree->current == NULL)
  {
    tree->root = nuevoNodo;
    return;
  }
  while(tree->current != NULL)
    {
      current = tree->current;
      if(is_equal(tree,current->pair->key, key))
        return;
      else if(tree->lower_than(key,current->pair->key))
        tree->current = tree->current->left;
      else
        tree->current = tree->current->right;
    }
  
  nuevoNodo->parent = current;
  if(tree->lower_than(key, current->pair->key))
  {
    current->left = nuevoNodo;
  }
  else
  {
    current->right = nuevoNodo;
  }
  tree->current = nuevoNodo;
}

TreeNode * minimum(TreeNode * x){
  if(x == NULL) return NULL;
  while(x->left != NULL)
  {
      x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->right == NULL && node->left == NULL)
  {
    if(node->parent == NULL) tree->root = NULL;
    if(node->parent->right == node) node->parent->right = NULL;
    else node->parent->left = NULL;
    free(node);
  }
  else if(node->right != NULL && node->left == NULL)
  {
    if(node->parent == NULL) tree->root = node->right;
    else{
      if(node->parent->right == node) node->parent->right = node->right;
      else node->parent->right = node->right;
      node->right->parent = node->parent;
    }
    free(node);
  }
  else if(node->right == NULL && node->left != NULL)
  {
    if(node->parent == NULL) tree->root = node->left;
    else{
      if(node->parent->right == node) node->parent->right = node->left;
      else node->parent->left = node->left;
      node->left->parent = node->parent;
    }
    free(node);
  }
  else
  {
    TreeNode *nodoMinimo = minimum(node->right);
    node->pair->key = nodoMinimo->pair->key;
    node->pair->value = nodoMinimo->pair->value;
    removeNode(tree, nodoMinimo);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  if(tree->root == NULL)
    return NULL;
  while(tree->current != NULL)
    {
      if(is_equal(tree, tree->current->pair->key, key))
        return(tree->current->pair);
      if(tree->lower_than(tree->current->pair->key, key))
        tree->current = tree->current->right;
      else
        tree->current = tree->current->left;
    }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree)
{
  tree->current = tree->root;
  if(tree->root == NULL) return NULL;

  while(tree->current->left != NULL)
    tree->current = tree->current->left;
  return tree->current->pair;

}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
