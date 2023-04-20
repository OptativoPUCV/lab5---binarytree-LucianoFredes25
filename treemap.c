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
  tree->current = tree->root;

  if(tree->root == NULL){
    tree->root = createTreeNode(key, value);
    return;
  }
  
  if(searchTreeMap(tree,key) != NULL) return;
  
  /*while(tree->current != NULL)
  {
    if(tree->lower_than(tree->current->pair->key , key))
    {
      if(tree->current->right == NULL)
      {
        //printf("1");
        tree->current->right = createTreeNode(key, value);
        tree->current->right->parent = tree->current;
        tree->current = tree->current->right;
        return;
      }
      //printf("2");
      tree->current = tree->current->right;
    }
    else
    {
      if(tree->current->left == NULL)
      {
        //printf("3");
        tree->current->left = createTreeNode(key, value);
        tree->current->left->parent = tree->current;
        tree->current = tree->current->left;
        return;
      }
      //printf("4");
      tree->current = tree->current->left;
    }
  }*/
  void insertTreeMap(TreeMap* tree, void* key, void* value){
    // Step 1: Insertion into an empty tree
    if (tree->root == NULL) {
        tree->root = new TreeNode;
        tree->root->pair = new Pair(key, value);
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->parent = NULL;
        tree->current = tree->root;
        return;
    }
    
    // Step 2: Search for the position to insert the new node
    TreeNode* node = tree->root;
    TreeNode* parent = NULL;
    while (node != NULL) {
        parent = node;
        if (tree->lower_than(key, node->pair->key)) {
            node = node->left;
        } else if (tree->lower_than(node->pair->key, key)) {
            node = node->right;
        } else {
            // Key already exists, just update the value
            node->pair->value = value;
            tree->current = node;
            return;
        }
    }
    
    // Step 3: Insert the new node
    TreeNode* new_node = new TreeNode;
    new_node->pair = new Pair(key, value);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;
    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    tree->current = new_node;
}
}


TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  
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
