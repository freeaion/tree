/* -------------------------------------------------------------------------
 * nary_tree.h: implement template for n-ary tree
 *
 * Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.  Some rights reserved.
 * -------------------------------------------------------------------------*/
#ifndef NARY_TREE_T
#define NARY_TREE_T

#include <cassert>

// implements tree links only
template <typename T>
class NaryTreeLink {
public:
   void addChild(T * pChild) {
      if (pChild == nullptr) return;

      if (this->mpChild) {
         // always add a new child at the end of sibs
         T * pEndNode = mpChild->mpLSibling;
         assert(pEndNode != nullptr && "internal error. please report a bug");

         pEndNode->addRSibling(pChild);
      }
      else {
         this->mpChild = pChild;
         pChild->mpParent = static_cast<T*>(this);

         pChild->mpLSibling = pChild; // first child mpLSibling points to the end of sibs
         return;
      }
   }

   void addRSibling(T * pRSibling) {
      if (pRSibling == nullptr) return;

      assert(this->mpParent && "cannot add a right sibling to a root node");

      pRSibling->mpParent = this->mpParent;

      pRSibling->mpRSibling = this->mpRSibling;
      pRSibling->mpLSibling = static_cast<T*>(this);

      if (mpRSibling != nullptr) {
         mpRSibling->mpLSibling = pRSibling;
      }
      else {
         // need to update end pointer
         this->mpParent->mpChild->mpLSibling = pRSibling;
      }

      mpRSibling = pRSibling;
   }

   void addLSibling(T * pLSibling) {
      if (pLSibling == nullptr) return;

      assert(this->mpParent && "cannot add a left sibling to a root node");

      if (this->mpParent->mpChild == this) {
         // this is the first child
         pLSibling->mpRSibling = static_cast<T*>(this);
         pLSibling->mpLSibling = this->mpLSibling;
         this->mpLSibling = pLSibling;

         pLSibling->mpParent = this->mpParent;
         this->mpParent->mpChild = pLSibling;
      }
      else {
         this->mpLSibling->addRSibling(pLSibling);
      }
   }

   T * getRSibling(void) {
      return mpRSibling;
   }

   T * getLSibling(void) {
      return mpLSibling;
   }

   T * getChild(void) {
      return mpChild;
   }

   T * getParent(void) {
      return mpParent;
   }

   T * getPreOrderNext(void) {

      if (mpChild) return mpChild;

      T * pNode = static_cast<T*>(this);
      while (pNode->mpRSibling == nullptr) {
         if (pNode->mpParent == nullptr) return nullptr;
         pNode = pNode->mpParent;
      }

      return pNode->mpRSibling;
   }

   T * getPreOrderPrev(void) {

      if (mpParent == nullptr) return nullptr;

      T * pNode = static_cast<T*>(this);
      if (pNode == mpParent->mpChild) return mpParent;

      pNode = pNode->mpLSibling;
      while (pNode->mpChild) {
         pNode = pNode->mpChild;
         pNode = pNode->mpLSibling;
      }

      return pNode;
   }

private:
   T * mpParent {nullptr};
   T * mpChild  {nullptr};
   T * mpRSibling {nullptr};
   T * mpLSibling {nullptr};
};

#endif // NARY_TREE_H
