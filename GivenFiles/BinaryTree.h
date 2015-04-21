#if !defined BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Line.h"
#include "Drawable.h"

template < class T >
class BinaryTree : public Drawable
{

   private:
      TreeNode<T>* root;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();
      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      BinaryTree(TreeNode<T>* root_node);

      virtual void drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      BinaryTree(T* root_item);
      BinaryTree();
      ~BinaryTree();

      T* getRootItem();

      //left_tree's root is set to NULL after the attach has completed
      void attachLeftSubtree(BinaryTree<T>* left_tree);
      //right_tree's root is set to NULL after the attach has completed
      void attachRightSubtree(BinaryTree<T>* right_tree);

      BinaryTree<T>* detachLeftSubtree();
      BinaryTree<T>* detachRightSubtree();
      void makeEmpty();
      bool isEmpty();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
BinaryTree<T>::BinaryTree(T* root_item) : Drawable()
{
   root = new TreeNode<T>(root_item);
}

template < class T >
BinaryTree<T>::BinaryTree(TreeNode<T>* root_node) : Drawable()
{
   root = root_node;
}

template < class T >
BinaryTree<T>::BinaryTree() : Drawable()
{
   root = NULL;
}

template < class T >
BinaryTree<T>::~BinaryTree()
{
   destroy();
}

template < class T >
void BinaryTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinaryTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
TreeNode<T>* BinaryTree<T>::getRootNode()
{
   return root;
}

template < class T >
T* BinaryTree<T>::getRootItem()
{
   if (root == NULL) return NULL;
   T* root_item = root->getItem();
   return root_item;
}

template < class T >
void BinaryTree<T>::makeEmpty()
{
   root = NULL;
}

template < class T >
bool BinaryTree<T>::isEmpty()
{
   return root == NULL;
}

template < class T >
void BinaryTree<T>::attachLeftSubtree(BinaryTree<T>* left_tree)
{
   //additional possible check is to make sure that the binary tree is not attached to itself
   //this would create infinite recursion
   if (left_tree == this)
   {
      return;
   }

   //throw an exception if the tree is empty (can't attach without a node)
   else if (isEmpty()) 
   {
      return;
   }

   //check to see if there is a node attached to the left
   else if (getRootNode()->getLeft() != NULL) 
   {
      //if a left subtree already exists we can't attach here--  throw an exception
      return;
   }
   //everything is okay, so attach
   else 
   {
      //attach on the left
      getRootNode()->setLeft(left_tree->getRootNode());

      //don't want to leave multiple entry points into our tree
      //we can't simply set left_tree = null as the user has another reference to this object
      //we must change the contents of the object to protect our tree (null out the root node)
      left_tree->makeEmpty(); 
      //now, the user cannot enter our tree below the root node
   } 
} 

template < class T >
void BinaryTree<T>::attachRightSubtree(BinaryTree* right_tree)
{
   if (right_tree == this)
   {
      return;
   }

   //throw an exception if the tree is empty (can't attach without a node)
   else if (isEmpty()) 
   {
      return;
   }

   //check to see if there is a node attached to the right
   else if (getRootNode()->getRight() != NULL) 
   {
      //if a right subtree already exists we can't attach here--  throw an exception
      return;
   }
   //everything is okay, so attach
   else 
   {
      //attach on the right
      getRootNode()->setRight(right_tree->getRootNode());
      // don't want to leave multiple entry points into our tree
      right_tree->makeEmpty(); 
   }  
}  

template < class T >
BinaryTree<T>* BinaryTree<T>::detachLeftSubtree()
{
   //throw an exception if the tree is empty (can't detach without a node)
   if (isEmpty()) 
   {
      return new BinaryTree();
   }
   //should also check that there is a left child (if not, return an empty BinaryTree)
   else if (getRootNode()->getLeft() == NULL)
   {
      return new BinaryTree();
   }
   else 
   {
      TreeNode<T>* root_node = getRootNode();
      //create a new binary tree that has root's left node as its root
      //use the protected constructor for this
      BinaryTree<T>* left_tree = new BinaryTree<T>(root_node->getLeft());
      //remove the left reference from the root node
      root_node->setLeft(NULL);
      //return a reference to the new binary tree
      return left_tree;
    } 
}  

template < class T >
BinaryTree<T>* BinaryTree<T>::detachRightSubtree()
{
   //throw an exception if the tree is empty (can't detach without a node)
   if (isEmpty()) 
   {
      return new BinaryTree();
   }
   //should also check that there is a right child (if not, return an empty BinaryTree)
   else if (getRootNode()->getRight() == NULL)
   {
      return new BinaryTree();
   }
   else 
   {
      TreeNode<T>* root_node = getRootNode();
      //create a new binary tree that has root's right node as its root
      //use the protected constructor for this
      BinaryTree<T>* right_tree = new BinaryTree<T>(root_node->getRight());
      //remove the right reference from the root node
      root_node->setRight(NULL);
      //return a reference to the new binary tree
      return right_tree;
   }  
}

/*
template < class T >
BinaryTreeIterator<T>* BinaryTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}
*/

template < class T >
void BinaryTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void BinaryTree<T>::drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void BinaryTree<T>::mouseClicked(int x, int y) {}

#endif
