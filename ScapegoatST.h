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
    int getSize();
    void insert(T d);
    void remove(T d);
    bool contains(T d);
    void printTreeInOrder();
    void printTreePostOrder();
    T getMin();
    T getMax();
    T getMedian();
	void printToFile();
    T getByID(int id);
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

// template <typename T>
// int ScapegoatST<T>::getSize(TreeNode<T>* subtreeRoot){
//   if (subtreeRoot == NULL){ 
//     return 0;
//   } 
//   return 1 + getSize(subtreeRoot->m_left) + getSize(subtreeRoot->m_right); 
// }

template <typename T>
int ScapegoatST<T>::getSize()
{
  return m_size;
}

template <typename T>
void ScapegoatST<T>::insert(T d)
{
	m_depth = 0;
	TreeNode<T> *newNode = new TreeNode<T>(d);
	insertHelper(m_root, newNode);
	++m_size;
	++m_del;
  // TreeNode<T> *scapeGoat = new TreeNode<T>;
  if (m_depth > log2(m_del)/log2(1.5))
  {
    // rebuild
  }
}

template <typename T>
void ScapegoatST<T>::insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode)
{
  if (subTreeRoot == NULL)
  {
    subTreeRoot = newNode;
  }
  // this is comparing the pointers
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
    //cout << subTreeRoot->m_data << endl;
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

template <typename T>
void ScapegoatST<T>::remove(T d)
{
  // check if empty
  TreeNode<T> *target = NULL;
  TreeNode<T> *parent = NULL;
  target = m_root;
  findTarget(d, target, parent);
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
        // cout << "I'm here!" << endl;
        parent->m_left = child;
      }
      else
      {
        parent->m_right = child;
      }
    }
    delete target;
    delete target;
    if (m_del > 2 * m_size)
    {
      // rebuild
    }
  }
  --m_size;
}

template <typename T>
void ScapegoatST<T>::printToFile() {
	ofstream writer("runLog.txt");
	printToFileHelper(m_root, writer);
	writer.close();
}

template <typename T>
void ScapegoatST<T>::printToFileHelper(TreeNode<T> *subTreeRoot, ofstream &writer) {
	if (subTreeRoot != NULL) {
    printToFileHelper(subTreeRoot->m_left, writer);
    //cout << subTreeRoot->m_data << endl;
	subTreeRoot->getData()->printToFile(writer);
    printToFileHelper(subTreeRoot->m_right, writer);
	}
}

// need to implement these three
template <typename T>
T ScapegoatST<T>::getByID(int id) {
	return getByIDHelper(id, m_root);
}

template <typename T>
T ScapegoatST<T>::getByIDHelper(int id, TreeNode<T> *subTreeRoot)
{
  if (subTreeRoot == NULL)
  {
    return NULL;
  }
  else if (subTreeRoot->getData()->getid() == id)
  {
    return subTreeRoot->getData();
  }
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
bool ScapegoatST<T>::containsByID(int id) {
	//if (m_root == NULL) return false;
	return containsByIDHelper(m_root, id);
}

template <typename T>
bool ScapegoatST<T>::containsByIDHelper(TreeNode<T> *subTreeRoot, int id)
{
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

template <typename T>
void ScapegoatST<T>::removeByID(int id) {
	if (m_root == NULL) return;
	if (m_root->getData()->getid() == id) remove(m_root->getData());
	// recursive call
}

#endif
