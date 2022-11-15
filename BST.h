#ifndef BST_H
#define BST_H

#include "TreeNode.h"

template <typename T>
class BST{
public:
  BST();
  virtual ~BST();
  int getSize();
  void insert(T d);
  void remove(T d);
  bool contains(T d);
  void printTreeInOrder();
  void printTreePostOrder();
  T getMin();
  T getMax();
  T getMedian();

private:
  int m_size;
  TreeNode<T>* m_root;
  T getMinHelper(TreeNode<T>* subTreeRoot);
  T getMaxHelper(TreeNode<T>* subTreeRoot);
  void insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode);
  bool containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
  void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
  void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
  void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
  TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);

};

template <typename T>
BST<T>::BST(){
  m_root = NULL;
  m_size = 0;
}

template <typename T>
BST<T>::~BST(){
  if(m_root != NULL){
    delete m_root;
  }
}

template <typename T>
int BST<T>::getSize(){
  return m_size;
}

template <typename T>
void BST<T>::insert(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  insertHelper(m_root, newNode);
  ++m_size;

}

template <typename T>
void BST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
    subTreeRoot = newNode;
  } else if(newNode->m_data < subTreeRoot->m_data){
    insertHelper(subTreeRoot->m_left,newNode);
  } else{
    insertHelper(subTreeRoot->m_right,newNode);
  }
}

template <typename T>
bool BST<T>::contains(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  return containsHelper(m_root, newNode);

}

template <typename T>
bool BST<T>::containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
    return false;
  } else if(newNode->m_data == subTreeRoot->m_data){
    return true;
  } else if(newNode->m_data < subTreeRoot->m_data){
    return containsHelper(subTreeRoot->m_left,newNode);
  } else{
    return containsHelper(subTreeRoot->m_right,newNode);
  }
}

template <typename T>
void BST<T>::printTreeInOrder(){
  printTreeInOrderHelper(m_root);
}

template <typename T>
void BST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    cout << subTreeRoot->m_data << endl;
    printTreeInOrderHelper(subTreeRoot->m_right);
  }
}

template <typename T>
void BST<T>::printTreePostOrder(){
  printTreePostOrderHelper(m_root);
}

template <typename T>
void BST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    printTreeInOrderHelper(subTreeRoot->m_right);
    cout << subTreeRoot->m_data << endl;
  }
}



/*
template <typename T>
bool BST::iterativeContains(T d){
  if(m_root == NULL){
    return false;
  }
  if(m_root->m_data ==  d){
    return true;
  }
  bool found = false;
  TreeNode<T>* currRoot = m_root;
  while(!found){
    if(d < currRoot->m_data){
      currRoot = currRoot->m_left;
    } else{
      currRoot = currRoot->m_right;
    }
    if(currRoot == NULL){
      found = false;
      break;
    }
    if(currRoot->m_data == d){
      found = true;
      break;
    }

  }
  return found;
}
*/

template <typename T>
T BST<T>::getMin(){
  //check if empty
  return getMinHelper(m_root);
}

template <typename T>
T BST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_left==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T>
T BST<T>::getMax(){
  //check if empty
  return getMaxHelper(m_root);
}

template <typename T>
T BST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_right==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMaxHelper(subTreeRoot->m_right);
  }

}

template <typename T>
T BST<T>::getMedian(){
  //check if empty
  return m_root->m_data;
}

template <typename T>
void BST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && target->m_data != key){
    parent = target;
    if(key < target->m_data){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* rightChild){
  while(rightChild->m_left != NULL){
    rightChild = rightChild->m_left;
  }
  return rightChild;
}

template <typename T>
void BST<T>::remove(T d){
  //check if empty
  TreeNode<T>* target = NULL;
  TreeNode<T>* parent = NULL;
  target = m_root;
  findTarget(d,target,parent);
  if(target == NULL){ //value wasn't in tree, othing to do
    return;
  }
  //check if leaf (including the root)
  if(target->m_left == NULL && target->m_right == NULL){ //no children, it's a leaf
    if(target == m_root){ //leaf is the root of tree
      m_root = NULL;
    } else{ //it's not the root
      if(target ==  parent->m_left){
        parent->m_left = NULL;
      } else{
        parent->m_right = NULL;
      }
    }
    //delete target; //free the memory

  } else if(target->m_left != NULL && target->m_right != NULL){ //2 child case
    TreeNode<T>* suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); //remove successor treenode
    target->m_data = value;

  } else{ //1 child
    TreeNode<T>* child;
    if(target->m_left != NULL){
      child = target->m_left;
    } else{
      child = target->m_right;
    }
    if(target ==  m_root){
      m_root = child;
    } else{
      if(target == parent->m_left){
        //cout << "I'm here!" << endl;
        parent->m_left = child;
      } else{
        parent->m_right = child;
      }
    }
      //delete target;
  }
  --m_size;
}

#endif
