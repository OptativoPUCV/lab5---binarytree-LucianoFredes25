#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
#include <stdbool.h>
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
    //new->lower_than = lower_than;
    TreeMap * arbol = (TreeMap *) malloc(sizeof(TreeMap));
    arbol->root = NULL;
    arbol->current = NULL;
    arbol->lower_than = lower_than;
    return arbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree->root == NULL){
    tree->root = createTreeNode(key, value);
    return;
  }
  
  if(searchTreeMap(tree,key) != NULL) 
    return;
  else
  {
    tree->current = tree->root;
    
    while(tree->current != NULL)
    {
      if(tree->lower_than(tree->current->pair->key , key))
      {
        if(tree->current->right == NULL)
        {
          tree->current->right = createTreeNode(key, value);
          tree->current->right->parent = tree->current;
          tree->current = tree->current->right;
          return;
        }
        tree->current = tree->current->right;
      }
      else
      {
        if(tree->current->left == NULL)
        {
          tree->current->left = createTreeNode(key, value);
          tree->current->left->parent = tree->current;
          tree->current = tree->current->left;
          return;
        }
        tree->current = tree->current->left;
      }
    }
  }
}
  
  
  TreeNode * minimum(TreeNode * x){
    //TreeNode * aux = (TreeNode *) malloc(sizeof(TreeNode));
    while(true)
    {
      if(x->left != NULL)
        x = x->left;
      else
        return x;
    }
}


void removeNode(TreeMap * tree, TreeNode* node) {
  //sin hijos
  if(node->left == NULL && node->right == NULL)
  {
    if(node->parent->left == node){
      node->parent->left = NULL;
    }
    else{
      node->parent->right = NULL;
    }
  }
  //hijo derecho
  else if(node->left == NULL && node->right != NULL)
  {
    if(node->parent->left == node){
      node->parent->left = node->right;
      node->right->parent = node->parent;
    }
    else{
      node->parent->right = node->right;
      node->right->parent = node->parent;
    }
  }
  //hijo izquierdo
  else if(node->left != NULL && node->right == NULL)
  {
    if(node->parent->left == node){
      node->parent->left = node->left;
      node->left->parent = node->parent;
    }
    else{
      node->parent->right = node->left;
      node->left->parent = node->parent;
    }
  }
  else if(node->left != NULL && node->right != NULL)
  {
    tree->current = node->right;
    TreeNode * min = minimum(tree->current);
    node->pair = min->pair;
    eraseTreeMap(tree, min->key);
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
  while(true){
    if(tree->current == NULL) return NULL;
    if(is_equal(tree, tree->current->pair->key, key))
      return tree->current->pair;

    if(tree->lower_than(tree->current->pair->key , key))
      tree->current = tree->current->right;
    else
      tree->current = tree->current->left;
  }
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
