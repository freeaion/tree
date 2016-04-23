#include<iostream>

#include "nary_tree.h"

// inherit nary tree links from tree::NaryTreeLink
class TreeNode : public NaryTreeLink<TreeNode> {
public:
   TreeNode(int i = 0) : i{i} {}

   void print(void) { std::cout << i << std::endl; }

private:
   int i;
};

// example code to manually create nary tree
TreeNode * create_tree(void) {
   TreeNode * pNode1 = new TreeNode{1};

   TreeNode * pNode2 = new TreeNode{2};

   pNode1->addChild(pNode2);

   TreeNode * pNode3 = new TreeNode{3};

   pNode1->addChild(pNode3);

   pNode3->addLSibling(new TreeNode{4});

   TreeNode * pNode5 = new TreeNode{5};
   pNode2->addChild(pNode5);

   pNode5->addLSibling(new TreeNode{6});

   TreeNode * pNode7 = new TreeNode{7};

   pNode3->addChild(pNode7);

   pNode5->addChild(new TreeNode{8});

   TreeNode * pNode9 = new TreeNode{9};
   pNode7->addChild(pNode9);

   pNode9->addChild(new TreeNode{10});
   pNode9->addChild(new TreeNode{11});

   return pNode1;;
}

// recursion based print
void print_tree(TreeNode * pRoot) {

   if (pRoot == nullptr) return;

   pRoot->print();
   for (TreeNode * pNode = pRoot->getChild();
        pNode != nullptr;
        pNode = pNode->getRSibling()) {
      print_tree(pNode);
   }

   return;
}

// interation based print
void print_tree_iter(TreeNode * pRoot) {
   if (pRoot == nullptr) return;

   pRoot->print();
   for (TreeNode * pNode = pRoot->getChild();
        pNode != nullptr;
        pNode = pNode->getPreOrderNext()) {
      pNode->print();
   }

   return;
}

void print_tree_iter_reverse(TreeNode * pRoot) {

   while (pRoot) {
      pRoot->print();
      pRoot = pRoot->getPreOrderPrev();
   }

   return;
}

int main(void)
{
   TreeNode * pRoot = create_tree();

   print_tree(pRoot);

   std::cout << "============================\n";

   print_tree_iter(pRoot);


   TreeNode * pNode = pRoot;
   for (int i = 0; i < 10; i++) {
      pNode = pNode->getPreOrderNext();
   }

   std::cout << "============================\n";

   print_tree_iter_reverse(pNode);

   return 0;
}
