#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"

template <typename Data>
class RST : public BST<Data> {

public:

 //Insert method for the RST class
 virtual std::pair<typename BST<Data>::iterator,bool> insert(const Data& item) {

   //Variables used to create a random seed for srand()
   unsigned int seed;
   FILE *urandom;
   
   //Opens urandom and gets the random seed from it
   urandom = fopen ("/dev/urandom", "r");
   fread (&seed, sizeof (seed), 1, urandom);
   srand (seed);
   
   //Closes urandom
   fclose(urandom);

   //Creates a pair with the returned value from BST's insert
   std::pair<typename BST<Data>::iterator,bool> file = BST<Data>::insert(item);

   //Checks if the insert was sucessful or not
   if (file.second)
   {
     //Creates a node pointing to the inserted one and sets a random priority
     BSTNode<Data> *node = BST<Data>::pointer(file.first);
     node->info = rand();

     //Rotates the node if isn't in the right spot
     rotate(node);

     //Returns the pair
     file.first = typename BST<Data>::iterator(node);
     file.second = true;
     return file;
   }

   //Returns the failed pair
   file.second = false;
   return file;
 }

 //Helper method that rotates if the node ins't in the right spot
 void rotate(BSTNode<Data>* node)
 {
   //Creates a parent node of the current node
   BSTNode<Data> *parent = node->parent;

   //Checks if the node was a root or not
   if(!parent)
   {
     return;
   }

   //While loop that checks the priority of the children
   while ( parent && parent->info < node->info )
   {
     //Checks to see if a new root will need to be set
     bool tempRoot = false;
     if (!node->parent->parent)
     {
       tempRoot = true;
     }

     //Calls right rotate if it's a right child
     if (parent-> right == node)
     {
       node = rightRotate(node->parent);
     }
     //Calls left rotate otherwise
     else
     {
       node = leftRotate(node->parent);
     }

     //Changes the root to current node
     if (tempRoot)
     {
       this->root = node;
       this->root->parent = nullptr;
     }

     //Helper method to reset the parent pointers
     parentPointer(this->root);
     
     //Resets the parent
     parent = node->parent;
   }
 }

 //Helper method that recursively calls itself
 void parentPointer(BSTNode<Data>* node)
 {
   //Checks if the node is a nullptr
   if(!node)
   {
     return;
   }

   //Checks for left children
   if (node->left)
   {
     node->left->parent = node;
   }

   //Checks for right children
   if (node->right)
   {
     node->right->parent = node;
   }
 
   //Calls recursively
   parentPointer(node->left);
   parentPointer(node->right);
 }

private:
 
 //Method to do an AVL left rotation
 BSTNode<Data>* leftRotate(BSTNode<Data>* node) 
 {
   BSTNode<Data> *lNode = node->left;
   node->left = lNode->right;
   if (node->parent) 
   {
     if (node->parent->data < node->data) 
     {
       node->parent->right = lNode;
     } 
     else 
     {
       node->parent->left = lNode;
     }
   }
   lNode->right = node;
   return lNode;
 }

 //Method to do an AVL right rotation
 BSTNode<Data>* rightRotate(BSTNode<Data>* node) 
 {
   BSTNode<Data> *rNode = node->right;
   node->right = rNode->left;
   if (node->parent) 
   {
     if (node->parent->data < node->data) 
     {
       node->parent->right = rNode;
     } 
     else 
     {
       node->parent->left = rNode;				
     }
   }
   rNode->left = node;
   return rNode;
  }
};
#endif // RST_HPP
