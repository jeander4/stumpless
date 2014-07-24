#include <stdlib.h>
#include <string.h>

#include "private/container/dictionary.h"

#include "static/container/dictionary.h"

void
DestroyDictionary
( Dictionary * dictionary )
{
  if( dictionary == NULL )
    return;

  DestroyNode( dictionary->root );

  free( dictionary );
}

void *
GetDictionaryValue
( Dictionary *dictionary, const char *key )
{
  if( !dictionary || !key )
    return NULL;

  Node *result = GetNode( key, dictionary->root );

  if( !result )
    return NULL;

  Splay( dictionary, result );
  return result->value;
}

Dictionary *
NewDictionary
()
{
  Dictionary * dictionary = malloc( sizeof( Dictionary ) );
  if( dictionary == NULL )
    return NULL;

  dictionary->root = NULL;

  return dictionary;
}

void *
RemoveDictionaryValue
( Dictionary * dictionary, const char * key )
{
  Node * node = GetNode( key, dictionary->root );
  if( node == NULL )
    return NULL;

  Splay( dictionary, node );

  if( node->left_child == NULL ){
    ReplaceNode( dictionary, node, node->right_child );
  } else if( node->right_child == NULL ){
    ReplaceNode( dictionary, node, node->left_child );
  } else {
    Node * minimum = SubtreeMinimum( node->right_child );
    if( minimum->parent != node ){
      ReplaceNode( dictionary, minimum, minimum->right_child );
      minimum->right_child = node->right_child;
      minimum->right_child->parent = minimum;
    }
    ReplaceNode( dictionary, node, minimum );
    minimum->left_child = node->left_child;
    minimum->left_child->parent = minimum;
  }

  void * removed_value = node->value;
  DestroyNode( node );
  return removed_value;
}

Dictionary *
SetDictionaryValue
( Dictionary * dictionary, const char * key, void * value )
{
  // todo add a search for existing keys
  if( dictionary == NULL )
    return NULL;

  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return NULL;

  node->key = key;
  node->value = value;
  node->parent = NULL;
  node->left_child = NULL;
  node->right_child = NULL;

  if( dictionary->root == NULL ){
    dictionary->root = node;
    return dictionary;
  }

  AddNode( dictionary->root, node );
  Splay( dictionary, node );

  return dictionary;
}

static
void
AddNode
( Node * node, Node * addition )
{
  int comparison =  strcmp( addition->key, node->key );
  if( comparison == 0 ){
    node->value = addition->value;
    DestroyNode( addition );
    return;
  }

  Node * next;
  if( comparison < 0 ){
    next = node->left_child;
    if( next == NULL ){
      node->left_child = addition;
      addition->parent = node;
      return;
    }
  } else {
    next = node->right_child;
    if( next == NULL ){
      node->right_child = addition;
      addition->parent = node;
      return;
    }
  }

  return AddNode( next, addition );
}

static
void
DestroyNode
( Node * node )
{
  if( node == NULL )
    return;

  DestroyNode( node->left_child );
  DestroyNode( node->right_child );

  free( node );
}

static
Node *
GetNode
( const char * key, Node * node )
{
  if( node == NULL )
    return NULL;

  int comparison =  strcmp( key, node->key );
  if( comparison == 0 )
    return node;

  Node * next;
  if( comparison < 0 )
    next = node->left_child;
  else
    next = node->right_child;

  return GetNode( key, next );
}

static
void
LeftRotate
( Dictionary * dictionary, Node * node )
{
  Node * old_right = node->right_child;
  node->right_child = old_right->left_child;
  if( old_right->left_child != NULL )
    old_right->left_child->parent = node;
  old_right->parent = node->parent;
  if( node->parent == NULL )
    dictionary->root = old_right;
  else if( node == node->parent->left_child )
    node->parent->left_child = old_right;
  else
    node->parent->right_child = old_right;
  old_right->left_child = node;
  node->parent = old_right;
}

static
void
ReplaceNode
( Dictionary * dictionary, Node * previous, Node * replacement )
{
  if( previous->parent == NULL )
    dictionary->root = replacement;
  else if( previous == previous->parent->left_child )
    previous->parent->left_child = replacement;
  else
    previous->parent->right_child = replacement;

  if( replacement != NULL )
    replacement->parent = previous->parent;
}
static
void
RightRotate
( Dictionary * dictionary, Node * node )
{
  Node * old_left = node->left_child;
  node->left_child = old_left->right_child;
  if( old_left->right_child != NULL )
    old_left->right_child->parent = node;
  old_left->parent = node->parent;
  if( node->parent == NULL )
    dictionary->root = old_left;
  else if( node == node->parent->left_child )
    node->parent->left_child = old_left;
  else
    node->parent->right_child = old_left;
  old_left->right_child = node;
  node->parent = old_left;
}

static
void
Splay
( Dictionary * dictionary, Node * node )
{
  if( node->parent == NULL )
    return;

  if( node->parent->parent == NULL ){
    if( node->parent->left_child == node )
      RightRotate( dictionary, node->parent );
    else
      LeftRotate( dictionary, node->parent );
  } else if( node->parent->left_child == node
             && node->parent->parent->left_child == node->parent ){
    RightRotate( dictionary, node->parent->parent );
    RightRotate( dictionary, node->parent );
  } else if( node->parent->right_child == node
             && node->parent->parent->right_child == node->parent ){
    LeftRotate( dictionary, node->parent->parent );
    LeftRotate( dictionary, node->parent );
  } else if( node->parent->left_child == node
             && node->parent->parent->right_child == node->parent ){
    RightRotate( dictionary, node->parent );
    LeftRotate( dictionary, node->parent );
  } else {
    LeftRotate( dictionary, node->parent );
    RightRotate( dictionary, node->parent );
  }

  Splay( dictionary, node );
}

static
Node *
SubtreeMinimum
( Node * node )
{
  if( node->left_child == NULL )
    return node;

  return SubtreeMinimum( node->left_child );
}
