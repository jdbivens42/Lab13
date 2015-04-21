#if !defined (BINARYTREEITERATOR_H)
#define BINARYTREEITERATOR_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;
#include "TreeNode.h"

template < class T >
class BinaryTreeIterator
{

   private:
      QueueLinked<T>* q;
      TreeNode<T>* root;

      void inorder(TreeNode<T>* tNode);
      void preorder(TreeNode<T>* tNode);
      void postorder(TreeNode<T>* tNode);

   public:
      BinaryTreeIterator(TreeNode<T>* root);
      ~BinaryTreeIterator();

      bool hasNext();
      T* next();

      void setInorder();
      void setPreorder();
      void setPostorder();

};

template < class T >
BinaryTreeIterator<T>::BinaryTreeIterator(TreeNode<T>* r)
{
   q = new QueueLinked<T>();
   root = r;
}

template < class T >
BinaryTreeIterator<T>::~BinaryTreeIterator()
{
   delete q;
}

template < class T >
bool BinaryTreeIterator<T>::hasNext()
{
   return (!q->isEmpty());
}

template < class T >
T* BinaryTreeIterator<T>::next()
{
   if (hasNext())
   {
      return q->dequeue();
   }
}

template < class T >
void BinaryTreeIterator<T>::setInorder()
{
   q->dequeueAll();
   inorder(root);
}

template < class T >
void BinaryTreeIterator<T>::inorder(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      inorder(tNode->getLeft());
      q->enqueue(tNode->getItem());
      inorder(tNode->getRight());
   }
}

template < class T >
void BinaryTreeIterator<T>::setPreorder()
{
   q->dequeueAll();
   preorder(root);
}

template < class T >
void BinaryTreeIterator<T>::preorder(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      q->enqueue(tNode->getItem());
      preorder(tNode->getLeft());
      preorder(tNode->getRight());
   }
}

template < class T >
void BinaryTreeIterator<T>::setPostorder()
{
   q->dequeueAll();
   postorder(root);
}

template < class T >
void BinaryTreeIterator<T>::postorder(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      postorder(tNode->getLeft());
      postorder(tNode->getRight());
      q->enqueue(tNode->getItem());
   }
}

#endif
