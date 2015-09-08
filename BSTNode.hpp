#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }

  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ 
  BSTNode<Data>* successor() const {
    //Sets current and parent nodes for reference
    BSTNode<Data> const *current = this;
    BSTNode<Data> const *currentP = nullptr;

    //Checks if the successor is in the right tree and for least value
    if(current->right)
    {
      if(!current->right->left)
      {
        return current->right;
      }
      current = current->right;
      while(current->left)
      {
        if(!current->left->left)
        {
          return current->left;
        }
        current = current->left;
      }
    }
    //Checks if current is a left child and if the successor is the parent
    else if(!(current->right) && current->parent != nullptr 
            && current->parent->left == current)
    {
      return current->parent;
    }
    //Checks if current is a right child and scales up the tree for successor
    else if(!(current->right) && current->parent != nullptr 
            && current->parent->right == current)
    {
      currentP = current->parent;
      //current = cu;
      while(currentP && currentP->right == current)
      {
        current = currentP;
        currentP = current->parent;
      }
      return current->parent;
    }
    
    //Returns nullptr if it is root
    return nullptr;
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
