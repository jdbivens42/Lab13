#if !defined (TREENODE_H)
#define TREENODE_H

#include "Color.h"
#include "Circle.h"
#include "String.h"
using CSC2110::String;

template < class T >
class TreeNode 
{

   private:
      TreeNode* left;
      TreeNode* right;
      T* item;

   public:
      TreeNode(T* item);
      ~TreeNode();

      TreeNode<T>* getLeft();
      TreeNode<T>* getRight();
      T* getItem();

      void setLeft(TreeNode<T>* tNode);
      void setRight(TreeNode<T>* tNode);
      void setItem(T* item);

      void draw(Cairo::RefPtr<Cairo::Context> cr, int x, int y);

};

template < class T >
TreeNode<T>::TreeNode(T* itm)
{
   left = NULL;
   right = NULL;
   item = itm;
}

template < class T >
TreeNode<T>::~TreeNode()
{}

template < class T >
TreeNode<T>* TreeNode<T>::getLeft()
{
   return left;
}

template < class T >
TreeNode<T>* TreeNode<T>::getRight()
{
   return right;
}

template < class T >
T* TreeNode<T>::getItem()
{
   return item;
}

template < class T >
void TreeNode<T>::setLeft(TreeNode<T>* l)
{
   left = l;
}

template < class T >
void TreeNode<T>::setRight(TreeNode<T>* r)
{
   right = r;
}

template < class T >
void TreeNode<T>::setItem(T* itm)
{
  item = itm;
}

template < class T >
void TreeNode<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int x, int y)
{
   T* item = getItem();
   String* key = item->getKey();
   Color* color = new Color(0.886, 0.49, 0.067);
   Circle* circle = new Circle(color, 20, key);
   circle->draw(cr, x, y);

   delete circle;
}

#endif
