/*
Ben Fellows
ID: 02369768
bfellows@chapman.edu

Partner:
Spencer Au
ID: 002385256
spau@chapman.edu

CPSC 350 - Section 2
PA5

ScapegoatST.h is based upon the BST code that was written in class which modifies the given remove and insert functions to check if the tree is becoming imbalanced
methods to rebalance the tree have been implemented including rebuildSubTree, buildArray, buildBalancedArray

rebuildSubtree() - uses buildArray and buildBalancedArray rebuild the subtree to be balanced.
buildArray() - treverses the tree and copies the elements to an array
buildBalancedArray() - takes in an Array of elements and seperates them into two halfs of the array to build a balanced tree
getScapeGoat() - finds the scapegoat in a tree by treversing up the insertion path and checking the size of current node respective to its parents node
getByID() - searches for a node and returns based on the id

*/


#ifndef SCAPEGOATST_H
#define SCAPEGOATST_H

#include "TreeNode.h"
#include <fstream>
#include <cmath>
template <typename T>
class ScapegoatST
{
public:
  ScapegoatST();
  virtual ~ScapegoatST();
  int getSize(TreeNode<T> *subTreeRoot);
  int getSize();
  void insert(T d);
  void remove(T d);
  bool contains(T d);
  void printTreeInOrder();
  void printTreePostOrder();
  T getMin();
  T getMax();
  T getMedian();
  void printToFile(ofstream &writer);
  T getByID(int id);
  TreeNode<T> *getScapeGoat(TreeNode<T> *newNode);
  void rebuildSubTree(TreeNode<T> *subTreeRoot);
  int buildArray(TreeNode<T> *node, TreeNode<T> *arr[], int i);
  TreeNode<T> *buildBalancedArray(TreeNode<T> **arr, int i, int n);
  bool containsByID(int id);
  void removeByID(int id);

private:
  double m_del;
  double m_depth;
  double m_size;
  TreeNode<T> *m_root;
  T getMinHelper(TreeNode<T> *subTreeRoot);
  T getMaxHelper(TreeNode<T> *subTreeRoot);
  void insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode);
  bool containsHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *newNode);
  void printTreeInOrderHelper(TreeNode<T> *subTreeRoot);
  void printTreePostOrderHelper(TreeNode<T> *subTreeRoot);
  void findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent);
  TreeNode<T> *getSuccessor(TreeNode<T> *rightChild);
  void printToFileHelper(TreeNode<T> *subTreeRoot, ofstream &writer);
  T getByIDHelper(int id, TreeNode<T> *subTreeRoot);
  bool containsByIDHelper(TreeNode<T> *subTreeRoot, int id);
  void findTargetByID(int id, TreeNode<T> *&target, TreeNode<T> *&parent);
};

template <typename T>
ScapegoatST<T>::ScapegoatST()
{
  m_root = NULL;
  m_size = 0;
}

template <typename T>
ScapegoatST<T>::~ScapegoatST()
{
  if (m_root != NULL)
  {
    delete m_root;
  }
}

//overloaded getsize method that takes in a node and returns the size of the subtree under the node passed in
template <typename T>
int ScapegoatST<T>::getSize(TreeNode<T> *subtreeRoot)
{
  //if subroot is null return 0 as size if so
  if (subtreeRoot == NULL)
  {
    return 0;
  }
  return getSize(subtreeRoot->m_left) + getSize(subtreeRoot->m_right) + 1;
}

template <typename T>
int ScapegoatST<T>::getSize()
{
  return m_size;
}
//same as provided insert function but checks if tree is becoming imbalanced
template <typename T>
void ScapegoatST<T>::insert(T d)
{
  TreeNode<T> *newNode = new TreeNode<T>(d);
  insertHelper(m_root, newNode);
  //increments m_size and m_del to keep track of difference between size and number of deletions
  ++m_size;
  ++m_del;
  //sets depth = 0 so that the inserthelper can keep track of the current node being inserted
  m_depth = 0;
}

template <typename T>
void ScapegoatST<T>::insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode)
{
  if (subTreeRoot == NULL)
  {
    subTreeRoot = newNode;
    //checks if tree is becoming imbalanced based on if depth of current node > log base 3/2 of tree size
    if (m_depth > log2(m_size) / log2(1.5))
    {
  }
    cout << log2(m_size) / log2(1.5) << endl;
    //find scapegoat node 
      TreeNode<T> *scapeGoat = getScapeGoat(newNode);
      if (scapeGoat->parent != NULL)
      {
        rebuildSubTree(scapeGoat->parent);
      }
      else
      {
        rebuildSubTree(scapeGoat);
      }
    }
  else if (newNode->m_data->getid() < subTreeRoot->m_data->getid())
  {
    m_depth++;
    newNode->parent = subTreeRoot;
    insertHelper(subTreeRoot->m_left, newNode);
  }
  else
  {
    newNode->parent = subTreeRoot;
    m_depth++;
    insertHelper(subTreeRoot->m_right, newNode);
  }
}

template <typename T>
bool ScapegoatST<T>::contains(T d)
{
  TreeNode<T> *newNode = new TreeNode<T>(d);
  return containsHelper(m_root, newNode);
}

template <typename T>
bool ScapegoatST<T>::containsHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *newNode)
{
  if (subTreeRoot == NULL)
  {
    return false;
  }
  else if (newNode->m_data == subTreeRoot->m_data)
  {
    return true;
  }
  else if (newNode->m_data < subTreeRoot->m_data)
  {
    return containsHelper(subTreeRoot->m_left, newNode);
  }
  else
  {
    return containsHelper(subTreeRoot->m_right, newNode);
  }
}

template <typename T>
void ScapegoatST<T>::printTreeInOrder()
{
  printTreeInOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printTreeInOrderHelper(TreeNode<T> *subTreeRoot)
{
  if (subTreeRoot != NULL)
  {
    printTreeInOrderHelper(subTreeRoot->m_left);
    subTreeRoot->getData()->printInfo();
    printTreeInOrderHelper(subTreeRoot->m_right);
  }
}

template <typename T>
void ScapegoatST<T>::printTreePostOrder()
{
  printTreePostOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printTreePostOrderHelper(TreeNode<T> *subTreeRoot)
{
  if (subTreeRoot != NULL)
  {
    printTreeInOrderHelper(subTreeRoot->m_left);
    printTreeInOrderHelper(subTreeRoot->m_right);
    cout << subTreeRoot->m_data << endl;
  }
}

template <typename T>
T ScapegoatST<T>::getMin()
{
  // check if empty
  return getMinHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMinHelper(TreeNode<T> *subTreeRoot)
{
  if (subTreeRoot->m_left == NULL)
  {
    return subTreeRoot->m_data;
  }
  else
  {
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T>
T ScapegoatST<T>::getMax()
{
  // check if empty
  return getMaxHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMaxHelper(TreeNode<T> *subTreeRoot)
{
  if (subTreeRoot->m_right == NULL)
  {
    return subTreeRoot->m_data;
  }
  else
  {
    return getMaxHelper(subTreeRoot->m_right);
  }
}

template <typename T>
T ScapegoatST<T>::getMedian()
{
  // check if empty
  return m_root->m_data;
}

template <typename T>
void ScapegoatST<T>::findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent)
{
  while (target != NULL && target->m_data != key)
  {
    parent = target;
    if (key < target->m_data)
    {
      target = target->m_left;
    }
    else
    {
      target = target->m_right;
    }
  }
}

template <typename T>
TreeNode<T> *ScapegoatST<T>::getSuccessor(TreeNode<T> *rightChild)
{
  while (rightChild->m_left != NULL)
  {
    rightChild = rightChild->m_left;
  }
  return rightChild;
}
//same as provided remove function but checks if the tree is becoming imbalanced
template <typename T>
void ScapegoatST<T>::remove(T d)
{
  //creating findtarget nodes
  TreeNode<T> *target = NULL;
  TreeNode<T> *parent = NULL;
  target = m_root;
  findTarget(d, target, parent);
  if (target == NULL)
  { // value wasn't in tree, nothing to do
    return;
  }
  // check if leaf (including the root)
  if (target->m_left == NULL && target->m_right == NULL)
  { // no children, it's a leaf
    if (target == m_root)
    { // leaf is the root of tree
      m_root = NULL;
    }
    else
    { // it's not the root
      if (target == parent->m_left)
      {
        parent->m_left = NULL;
      }
      else
      {
        parent->m_right = NULL;
      }
    }
    // delete target; //free the memory
  }
  else if (target->m_left != NULL && target->m_right != NULL)
  { // 2 child case
    TreeNode<T> *suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); // remove successor treenode
    target->m_data = value;
  }
  else
  { // 1 child
    TreeNode<T> *child;
    if (target->m_left != NULL)
    {
      child = target->m_left;
    }
    else
    {
      child = target->m_right;
    }
    if (target == m_root)
    {
      m_root = child;
    }
    else
    {
      if (target == parent->m_left)
      {
        parent->m_left = child;
      }
      else
      {
        parent->m_right = child;
      }
    }
    --m_size;
    delete target;
    delete parent;
    //checks if there have been too many consecutive deletes without insertions and therefore the tree has become unbalanced
    if (m_del > 2 * m_size)
    {
      rebuildSubTree(m_root);
    }
  }
  m_size--;
}

template <typename T>
void ScapegoatST<T>::printToFile(ofstream &writer)
{
  printToFileHelper(m_root, writer);
}

template <typename T>
void ScapegoatST<T>::printToFileHelper(TreeNode<T> *subTreeRoot, ofstream &writer)
{
  if (subTreeRoot != NULL)
  {
    printToFileHelper(subTreeRoot->m_left, writer);
    subTreeRoot->getData()->printToFile(writer);
    printToFileHelper(subTreeRoot->m_right, writer);
  }
}

//gets a node by data->id instead of just checking the nodes key
template <typename T>
T ScapegoatST<T>::getByID(int id)
{
  return getByIDHelper(id, m_root);
}

//helper function to recursevly treverse through tree to find node with matching id
template <typename T>
T ScapegoatST<T>::getByIDHelper(int id, TreeNode<T> *subTreeRoot)
{
  //checks if tree is empty
  if (subTreeRoot == NULL)
  {
    return NULL;
  }
  //checks if current node matches passed in id
  else if (subTreeRoot->getData()->getid() == id)
  {
    return subTreeRoot->getData();
  }
  //treverses if through tree recursively to find id that was passed in
  else if (subTreeRoot->getData()->getid() < id)
  {
    return getByIDHelper(id, subTreeRoot->m_right);
  }
  else
  {
    return getByIDHelper(id, subTreeRoot->m_left);
  }
}

template <typename T>
bool ScapegoatST<T>::containsByID(int id)
{
  if (m_root == NULL) return false;
  return containsByIDHelper(m_root, id);
}
//same as contains helper but checks dat
template <typename T>
bool ScapegoatST<T>::containsByIDHelper(TreeNode<T> *subTreeRoot, int id)
{
  //treverses through subtree recursively and checks each node with id passed in, returns false if reaches a leaf
  if (subTreeRoot == NULL)
  {
    return false;
  }
  else if (id == subTreeRoot->m_data->getid())
  {
    return true;
  }
  else if (id < subTreeRoot->m_data->getid())
  {
    return containsByIDHelper(subTreeRoot->m_left, id);
  }
  else
  {
    return containsByIDHelper(subTreeRoot->m_right, id);
  }
}

//same as remove but checks for data->id instead of just checking the nodes data
template <typename T>
void ScapegoatST<T>::removeByID(int id)
{
  if (m_root == NULL)
    return;
    //checks if current nodes id = the id passed in and removes using normal remove function if so
  if (m_root->getData()->getid() == id)
    remove(m_root->getData());

  // check if empty
  TreeNode<T> *target = NULL;
  TreeNode<T> *parent = NULL;
  target = m_root;
  findTargetByID(id, target, parent);
  if (target == NULL)
  { // value wasn't in tree, othing to do
    return;
  }
  // check if leaf (including the root)
  if (target->m_left == NULL && target->m_right == NULL)
  { // no children, it's a leaf
    if (target == m_root)
    { // leaf is the root of tree
      m_root = NULL;
    }
    else
    { // it's not the root
      if (target == parent->m_left)
      {
        parent->m_left = NULL;
      }
      else
      {
        parent->m_right = NULL;
      }
    }
    // delete target; //free the memory
  }
  else if (target->m_left != NULL && target->m_right != NULL)
  { // 2 child case
    TreeNode<T> *suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); // remove successor treenode
    target->m_data = value;
  }
  else
  { // 1 child
    TreeNode<T> *child;
    if (target->m_left != NULL)
    {
      child = target->m_left;
    }
    else
    {
      child = target->m_right;
    }
    if (target == m_root)
    {
      m_root = child;
    }
    else
    {
      if (target == parent->m_left)
      {
        parent->m_left = child;
      }
      else
      {
        parent->m_right = child;
      }
    }
    delete target;
    delete parent;
    if (m_del > 2 * m_size)
    {
      rebuildSubTree(m_root);
    }
  }
  --m_size;
}

//same as findtarget but checks for data->id instead of just checking the node data
template <typename T>
void ScapegoatST<T>::findTargetByID(int id, TreeNode<T> *&target, TreeNode<T> *&parent)
{
  while (target != NULL && target->m_data->getid() != id)
  {
    parent = target;
    if (id < target->m_data->getid())
    {
      target = target->m_left;
    }
    else
    {
      target = target->m_right;
    }
  }
}
//finds the scapegoat node by comparing the size of each node to its parents size and checking if its disproportionate
template <typename T>
TreeNode<T> *ScapegoatST<T>::getScapeGoat(TreeNode<T> *newNode)
{
    //climbs up through insertion path recursively and checks the size of the subtree compared to the parent
  if (newNode->parent != NULL)
  {
    TreeNode<T> *currentNode = newNode->parent;
    while (3 * getSize(currentNode) <= 2 * getSize(currentNode->parent))
    {
      currentNode = currentNode->parent;
    }
    //returns the node from last loop which didnt pass the size test to check for tree balance
    return currentNode;
  }
  //if the subtreeroot passed in is the root return the subtreeroot
  return newNode;
}

//method to build array from inorder traversal of tree
template <typename T>
int ScapegoatST<T>::buildArray(TreeNode<T> *node, TreeNode<T> *arr[], int i)
{
  if (node == NULL)
  //check if the recursive call reached end of the tree and return size if it is
  {
    return i;
  }
  else
  {
    //preform inorder treversal and copy to array by recursively calling build array
    i = buildArray(node->m_left, arr, i);
    arr[i++] = node;
    return buildArray(node->m_right, arr, i);
  }
}
//method to build balanced array representation of a tree from an array takes in the unbalanced array, int i which is used to index the array, and int j which is the size of the array
template <typename T>
TreeNode<T> *ScapegoatST<T>::buildBalancedArray(TreeNode<T> **arr, int i, int j)
{
  //chekcs if the array and tree are empty
  if (j == 0)
  {
    return NULL;
  }
  //find median index of array
  int k = j / 2;
  arr[i + k]->m_left = buildBalancedArray(arr, i, k);
  //fills the array from the left half and the right half alternating to make a balanced tree
  if (arr[i + k]->m_left != NULL)
  {
    arr[i + k]->m_left->parent = arr[i + k];
  }
  arr[i + k]->m_right = buildBalancedArray(arr, i + k + 1, j - k - 1);
  if (arr[i + k]->m_right != NULL)
  {
    arr[i + k]->m_right->parent = arr[i + k];
  }
  return arr[i + k];
}
//method to rebuild a subtree using buildarray and buildbalanced array
template <typename T>
void ScapegoatST<T>::rebuildSubTree(TreeNode<T> *subTreeRoot)
{
  TreeNode<T> *currentNode = subTreeRoot->parent;
  int size = getSize(subTreeRoot);
  TreeNode<T> **tempArr= new TreeNode<T> *[size];
  buildArray(subTreeRoot, tempArr, 0);
  //checks if the node is a right child or left child or root and rebulds the tree then respects the parents respectively
  if (currentNode == NULL)
  {
    m_root = buildBalancedArray(tempArr, 0, size);
    m_root->parent = NULL;
  }
  else if (currentNode->m_right == subTreeRoot)
  {
    currentNode->m_right = buildBalancedArray(tempArr, 0, size);
    currentNode->m_right->parent = currentNode;
  }
  else
  {
    currentNode->m_left = buildBalancedArray(tempArr, 0, size);
    currentNode->m_left->parent = currentNode;
  }
}
#endif
