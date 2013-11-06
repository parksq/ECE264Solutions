#include "pa08.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */

SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * sn = malloc(sizeof(SparseNode));
  sn -> index = index;
  sn -> value = value;
  sn -> left = NULL;
  sn -> right = NULL;
  return sn;
}

/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_insert ( SparseNode * array, int index, int value )
{
  if (array == NULL)
  {
    return SparseNode_create(index,value);
  }
  if (array -> index == index)
  {
    array -> value = value;
    return array;
  }
  if (array -> index > index)
  {
    array -> left = SparseArray_insert(array -> left,index,value);
    return array;
  }
  array -> right = SparseArray_insert(array -> right,index,value);
  return array;
}

/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */

SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  int i;
  SparseNode * array = NULL;
  for (i=0;i<length;i++)
  {
    if (values[i] != 0)
      array = SparseArray_insert(array,indicies[i],values[i]);
  }
  return array;
}

/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy ( SparseNode * array )
{
  if (array == NULL)
  {
    return;
  }
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);
  free(array);
}

/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  if (array -> left == NULL)
  {
    return(array -> index);
  }
  return SparseArray_getMin(array -> left);
}

/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{
  if (array -> right == NULL)
  {
    return(array -> index);
  }
  return SparseArray_getMax(array -> right);
}

/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if (array == NULL)
  {
    return NULL;
  }
  if (array -> index == index)
  {
    return array;
  }
  if (array -> index < index)
  {
    return SparseArray_getNode(array -> right, index);
  }
  return SparseArray_getNode(array -> left, index);
}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
*/
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
/*printf("\n2");
  if (array == NULL);
  {
    return NULL;
  }
  SparseNode * find_parent(SparseNode *, int);
  SparseNode * delete = SparseArray_getNode(array,index);
  SparseNode * delete_parent = find_parent(array,index);
  if (delete -> left == NULL && delete -> right == NULL)
  {
printf("\n3");
    if (delete -> index > delete_parent -> index)
    {
      delete_parent -> right = NULL;
      free(delete);
    }
    else
    {
      delete_parent -> left = NULL;
      free(delete);
    }
  }
  if(delete -> right != NULL && delete -> left != NULL)
  {
printf("\n4");
    SparseNode * min_child = SparseArray_getNode(delete,SparseArray_getMin(delete));
    delete -> index = min_child -> index;
    delete -> value = min_child -> value;
    SparseArray_remove(array,min_child -> index);
  }
  else
  {
printf("\n6");
    if (delete -> right == NULL)
    {
      if (delete -> index > delete_parent -> index)
      {
        delete_parent -> right = delete -> left;
        free(delete);
      }
      else
      {
        delete_parent -> left = delete -> left;
        free(delete);
      }
    }
    else
    {
      if (delete -> index > delete_parent -> index)
      {
        delete_parent -> right = delete -> left;
        free(delete);
      }
      else
      {
        delete_parent -> left = delete -> left;
        free(delete);
      }
    }
  }
  return array ;
}

SparseNode * find_parent(SparseNode * array, int index)
{
printf("\n5");
  if (array == NULL)
  {
    return NULL;
  }
  if (index < array -> left -> index)
  {
    return (find_parent(array -> left,index));
  }
  if (index > array -> right -> index)
  {
    return (find_parent(array -> right,index));
  }
  return array;*/
  int temp;
printf("\nindex:%d\n",index);
  if (array == NULL) { return NULL; }
  if (index < (array -> index))
  {
printf("\nright\n");
    array -> left = SparseArray_remove(array -> left, index);
    return array;
  }
  if (index > (array -> index))
  {
printf("\nleft\n");
    array -> right = SparseArray_remove(array -> right, index);
    return array;
  }
/* v is the same as tn -> value */
  if (((array -> left) == NULL) && ((array -> right) == NULL))
  /* r has no child */
  {
printf("\nno\n");
    free (array);
    return NULL;
  }
  if ((array -> left) == NULL)
  {
    if (array -> right != NULL) 
    {
      SparseNode * rc = array -> right;
      free (array);
      return rc;
    }
  }
  if ((array -> right) == NULL)
  {
    if (array -> left != NULL)
    {
      SparseNode * lc = array -> left;
      free (array);
      return lc;
    }
  }
/* r have two children */
/* find the immediate successor */
printf("\ntwo\n");
  SparseNode * su = array -> right; /* su must not be NULL */
  while ((su -> left) != NULL)
  {
    su = su -> left;
  }
/* su is r.s immediate successor */
/* swap their values */
  array -> value = su -> value;
  temp = array -> index;
  array -> index = su -> index;
  su -> index = temp;
/* delete su */
  array -> right = SparseArray_remove(array -> right, index);
  return array;
}

/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */

SparseNode * SparseArray_copy(SparseNode * array)
{
  if (array == NULL)
  {
    return NULL;
  }
  SparseNode * tree_copy = malloc(sizeof(SparseNode));
  tree_copy -> value = array -> value;
  tree_copy -> index = array -> index;
  tree_copy -> left = SparseArray_copy(array -> left);
  tree_copy -> right = SparseArray_copy(array -> right);
  return(tree_copy);
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
/*printf("\n1");
  SparseNode * copy1 = SparseArray_copy(array_1);
  SparseNode * copy2 = SparseArray_copy(array_2);
  while(array_2 != NULL)
  {
printf("\n2");
    SparseNode * min = SparseArray_getNode(copy2,SparseArray_getMin(copy2));
printf("\nmin index:%d min value:%d",min -> index, min -> value);
printf("\n3");
    copy1 = SparseArray_insert(copy1,min -> index,min -> value);
printf("\n4");
    copy2 = SparseArray_remove(copy2,min -> index);
printf("\ncopy index:%d copy value:%d",copy2 -> index, copy2 -> value);
printf("\nmin index:%d min value:%d",min -> index, min -> value);
printf("\n5");
  }
printf("\n6");
free(copy2);
  return (copy1);*/
  SparseNode * copy1 = SparseArray_copy(array_1);
  SparseNode * SparseArray_mergehelp(SparseNode *,SparseNode *);
  copy1 = SparseArray_mergehelp(copy1,array_2);
  return copy1;
}

SparseNode * SparseArray_mergehelp(SparseNode * array_1, SparseNode * array_2)
{
  if (array_2 == NULL)
  {
    return array_1;
  }
  SparseArray_mergehelp(array_1,array_2 -> left);
  SparseArray_mergehelp(array_1,array_2 -> right);
  SparseNode * merge_insert(SparseNode*,int,int);
  array_1 = merge_insert(array_1,array_2 -> index, array_2 -> value);
  return array_1;
}

SparseNode * merge_insert ( SparseNode * array, int index, int value )
{
  if (array == NULL)
  {
    return SparseNode_create(index,value);
  }
  if (array -> index == index)
  {
    array -> value = (array -> value + value);
    if (array -> value == 0)
    {
      array = SparseArray_remove(array,index);
    }
    return array;
  }
  if (array -> index > index)
  {
    array -> left = merge_insert(array -> left,index,value);
    return array;
  }
  array -> right = merge_insert(array -> right,index,value);
  return array;
}
 














