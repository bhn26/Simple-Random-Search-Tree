#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  static BSTNode<Data>* pointer(BSTIterator<Data> p)
  {
    return p.curr;
  }

public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */
  virtual ~BST() {
    clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ 
  virtual std::pair<iterator,bool> insert(const Data& item) {
    //Creates the a new node for the tree
    BSTNode<Data> *node = new BSTNode<Data>(item);
    
    //Creates the pair for the node to check for succession
    std::pair<iterator,bool> file(iterator(nullptr), false);
    
    //If it is the first element in tree, then make root
    if(root == nullptr)
    {
      root = node;
      node->parent = nullptr;
      isize++;
      file.first = iterator(node);
      file.second = true;
      return file;
    }
    
    //Creates a new node to compare with
    BSTNode<Data> *current = root;
    while(current) {
      //Checks the current node to see if it is less than the item
      if(current->data < item)
      {
        if(current->right)
        {
          current = current->right;
        }
        //Sets the item in the correct spot of the tree
        else
        {
          node->parent = current;
          current->right = node;
          ++isize;
          file.first = iterator(node);
          file.second = true;
          return file;
        }
      }
      //Checks the current node id it is greater than the item
      else if(item < current->data)
      {
        if(current->left)
        {
          current = current->left;
        }
        //Sets the item in the correct spot of the tree
        else
        {
          node->parent = current;
          current->left = node;
          ++isize;
          file.first = iterator(node);
          file.second = true;
          return file;
        }
      }
      else 
      {
        break;
      }
    }
    //Sets that the item already exists and returns false
    file.first = iterator(node);
    file.second = false;
    return file;
  }




  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ 
  iterator find(const Data& item) const {
    //Checks to see if the tree is empty
    if(root == nullptr)
    {
      return end();
    }
    
    //Creates a node at the root of the tree
    BSTNode<Data> *current = this->root;

    //Traverses through the tree to find the correct item
    while(current)
    {
      if(item < current->data)
      {
        current = current->left;
      }
      else if(current->data < item)
      {
        current = current->right;
      }
      //Returns iterator of current node indicating foun item
      else
      {
        return iterator(current);
      }
    }
    //Returns end iterator if item is not found
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ 
  void clear() {
    //Checks to see if tree is empty
    if(!root)
    {
      return;
    }

    //Creates current and parent pointers for reference
    BSTNode<Data> *current = root;
    BSTNode<Data> *currentP = nullptr;

    //Checks through the tree by going to the far left leaf
    while(1)
    {
      //Sets the pointers back at the top of the tree
      current = root;
      currentP = nullptr;
          
      //Checks if it is the root of the tree and deletes it
      if(!current->left && !current->right)
      {
        delete current;
        current = nullptr;
        return;
      }

      //Traverses down to any leaf of the tree to delete it and continue
      while(current->left || current->right)
      {
        if(current->left)
        {
          currentP = current;
          current = current->left;
        }
        else if(current->right)
        {
          currentP = current;
          current = current->right;
        }
      }      

      //Deletes current pointer and sets it to nullptr
      if(currentP->left == current)
      {
        delete current;
        current = nullptr;
        currentP->left = nullptr;
        continue;
      }

      //Deletes current pointer and sets it to nullptr
      if(currentP->right == current)
      {
        delete current;
        current = nullptr;
        currentP->right = nullptr;
        continue;
      }
    }
  } 
 
  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const {
    return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ 
  iterator begin() const {
    //Creates current node at root
    BSTNode<Data> *current = root;

    //Checks if tree is empty
    if(!current)
    {
      return nullptr;
    }

    //Traverses down the left side of the tree to find least node
    while(current->left)
    {
      current = current->left;
    }
    
    //Returns the iterator for it
    return iterator(current);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
