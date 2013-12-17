#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/tree.h"
#include "private/stack.h"
#include "private/static/tree.h"
#include "private/type.h"

Dimension *
AddComparisonToDimension
( Dimension * dimension, comparison_t comparison )
{
  if( dimension == NULL )
    return NULL;
  
  if( dimension->comparisons == NULL ){
    dimension->comparisons = NewList();
    if( dimension->comparisons == NULL )
      return NULL;
  }
  
  if( AppendToList( dimension->comparisons, comparison ) == NULL )
    return NULL;
  
  return dimension;
}

Tree *
AddComparisonToTree
( Tree * tree, comparison_t comparison )
{
  if( tree == NULL )
    return NULL;
  
  if( AddComparisonToDimension( tree->current_dimension, comparison ) == NULL )
    return NULL;
  
  return tree;
}

Dimension *
AddDimensionToTree
( Tree * tree, const char * name )
{
  Dimension * dimension = malloc( sizeof( Dimension ) );
  if( dimension == NULL )
    return NULL;
  
  dimension->comparisons = NULL;
  dimension->name = name;
  dimension->tree = tree;
  
  // todo finish
  
  return dimension;
}

Tree *
AddToTree
( Tree * tree, void * value )
{
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return NULL;
  
  node->left_children = malloc( sizeof( Node ) );
  if( node->left_children == NULL )
    return NULL;
  
  node->right_children = malloc( sizeof( Node ) );
  if( node->right_children == NULL )
    return NULL;
  
  node->value = value;
  
  Dimension * dimension = BeginList( tree->dimensions );
  while( dimension != NULL ){
    if( AddToDimension( dimension, node ) == NULL )
      return NULL;
    
    dimension = NextInList( tree->dimensions );
  }
  
  return tree;
}

Tree *
AddListToTree
( Tree * tree, List * list )
{
  if( tree == NULL || list == NULL )
    return NULL;
  
  void * value = BeginList( value );
  while( value != NULL ){
    AddToTree( tree, value );
    
    value = NextInList( value );
  }
  
  return tree;
}

void *
BeginDimension
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

void *
BeginTree
( Tree * tree )
{
  // todo finish
  
  return NULL;
}

Tree *
CopyTree
( Tree * tree )
{
  // todo finish
  
  return NULL;
}

void
DestroyDimension
( Dimension * dimension )
{
  if( dimension == NULL )
    return;
  
  DestroyList( dimension->comparisons );
  
  // todo remove dimension from tree's list
  
  free( dimension );
  
  return;
}

void
DestroyTree
( Tree * tree )
{
  if( tree == NULL )
    return;
  
  Dimension * dimension = BeginList( tree->dimensions );

  if( dimension != NULL )
    DestroyNode( dimension->root );
  
  while( dimension != NULL ){
    DestroyDimension( dimension );
    dimension = NextInList( tree->dimensions );
  }
  
  DestroyList( tree->dimensions );
  
  return;
}

Tree *
MergeTrees
( Tree * tree_1, Tree * tree_2 )
{
  // todo finish
  
  return NULL;
}

void *
NextInDimension
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

void *
NextInTree
( Tree * tree )
{
  // todo finish
  
  return NULL;
}

Tree *
NewTree
()
{
  Tree * tree = malloc( sizeof( Tree ) );
  if( tree == NULL )
    return NULL;
  
  tree->dimensions = NewList();
  if( tree->dimensions == NULL )
    return NULL;
  
  Dimension * dimension = malloc( sizeof( Dimension ) );
  if( dimension == NULL )
    return NULL;
  
  if( AppendToList( tree->dimensions, dimension ) != NULL )
    return NULL;
  
  tree->current_dimension = dimension;
  tree->dimension_capacity = 20;
  tree->options = NULL;
  
  dimension->comparisons = NULL;
  dimension->index = 0;
  dimension->name = NULL;
  dimension->options = NULL;
  dimension->root = NULL;
  dimension->tree = tree;
  
  return tree;
}

Dimension *
SetDimensionName
( Dimension * dimension, const char * name )
{
  if( dimension == NULL )
    return NULL;
  
  dimension->name = name;
  
  return dimension;
}

Dimension *
SetDimensionOptions
( Dimension * dimension, Dictionary * options )
{
  if( dimension == NULL )
    return NULL;
  
  dimension->options = options;
  
  return dimension;
}

Tree *
SetTreeDimension
( Tree * tree, Dimension * dimension )
{
  if( tree == NULL )
    return NULL;
  
  tree->current_dimension = dimension;
  
  return tree;
}

Tree *
SetTreeOptions
( Tree * tree, Dictionary * options )
{
  if( tree == NULL )
    return NULL;
  
  tree->options = options;
  
  return tree;
}

unsigned short
TreeContains
( Tree * tree, void * value )
{
  // todo finish
  return 0;
}

unsigned short
TreeIsEmpty
( Tree * tree )
{
  return tree == NULL
      || BeginDimension( BeginList( tree->dimensions ) ) == NULL;
}

static
Dimension *
AddToDimension
( Dimension * dimension, Node * node )
{
  // todo finish
  
  return NULL;
}

static
Node *
BeginDimensionNodes
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

static
void
DestroyNode
( Node * node )
{
  if( node == NULL )
    return;
  
  Node * left = node->left_children[0];
  Node * right = node->right_children[0];
  
  free( node->left_children );
  free( node->right_children );
  free( node );
  
  DestroyNode( left );
  DestroyNode( right );
  
  return;
}

static
Node *
NextNodeInDimension
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

static
Dimension *
RestructureDimension
( Dimension * dimension, Stack * stack )
{
  // todo finish
  
  return dimension;
}
