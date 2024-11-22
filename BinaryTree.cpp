//inserts into sorted position as per inorder traversal
#include "BinaryTree.h"  
//default constructor
BinaryTree::BinaryTree(){
    root=nullptr;
    count=0;
  }
//insert node in sorted order in the tree
  void BinaryTree::insert(int data,TreeNode * cur){

     if  (cur->getData()==data)
       return;
     if  (data<cur->getData()) {
        if ((cur->getLeft())==nullptr)
            cur->setLeft(new TreeNode(data,nullptr,nullptr));
            else { 
              insert(data, cur->getLeft());
              }
       }
     else{
        if ((cur->getRight())==nullptr)
            cur->setRight( new TreeNode(data,nullptr,nullptr));
        else {
          insert(data,cur->getRight());}
     }
  }
     

  
  //does not insert duplicates

  void BinaryTree::insert(int data){
    if (root==nullptr){
        root= new TreeNode(data,nullptr,nullptr);}
     else insert(data,root);
    count++;
  }

//releases a node to the heap
void  BinaryTree::remove(TreeNode * t){
   delete t;
 }
// checks if the node has only one child
//this method is used by delete function
 bool  BinaryTree::hasOneChild(TreeNode *t ){
   return (t->getLeft()==nullptr )^(t->getRight()==nullptr);
 }
//get the left or right successor
 TreeNode * BinaryTree::findNext(TreeNode * t){
   if (t->getLeft()!=nullptr) 
     return t->getLeft();
   else
     return t->getRight();
 }

//TODO
//delete node
void BinaryTree::deleteNode(int data)

{
 TreeNode * prev=root;
 TreeNode * found;
  //if tree is empty exit - no deletion needs to be done
    if (root==nullptr) exit(-1);
    else {
      // search for the node that is to be deleted
      //if not found  exit
       found =searchNode(data,prev);
       if (found ==nullptr)
        {std::cout<<"\nNODE NOT FOUND "<<data<<"\n";
          exit(-1);
        }
       else 
       {
         // if found, search for its parent (prev) using the searchPrev(data)
         //method
         // there are three cases to be taken care of
         
         count--;    
         prev=searchPrev(data);
         TreeNode* next;
         // Case 1. if the node to be deleted is a leaf (use isLeaf Method)
         // determine if its the left or right child of parent and set that link to null pointer and release memory of (using remove method) the found node
         if (found->isLeaf()) 
         {
            if (prev->getLeft() == nullptr) {
              prev->setRight(nullptr);
              remove(found);
            }
            else {
              prev->setLeft(nullptr);
              remove(found);
            }
            
          }
    //2. has either One child right or left branch
       else if (hasOneChild(found))
           
               {
                 // find the successor using the findNext method
                 // set the parents right or left node to successor
                 // this will depend on whether the found node is the right or left child of parent
                // release found node
                 //TODO 
                 TreeNode* temp = findNext(found);
                 if (found->getRight() == nullptr) {
                  found->setRight(temp);
                  delete temp; 
                 }
                 else if (found->getLeft() == nullptr) {
                  found->setLeft(temp);
                  delete temp; 
                 }
      }
   //two child nodes
   else {

     // Case 3. The found node has a right and left child (or possibly right and left subtree)
     // This case is a little more complex.In this case, the inOrder successor of the found node needs to be searched and attached to the parent.
     // find in order successor
     TreeNode * successor = inorderSuccessor(found);
     //determine if the found node is the left or right child of the parent and set the next of the parent to the inorder successor
     if (prev->getLeft() == nullptr) {
      prev->setRight(successor);
     }
     else {
      prev->setLeft(successor);
     }
     // if the node to be deleted is the root then the root also has be 
     if (found == root) {
      if (root->getLeft() == nullptr) {
        root->setRight(successor);
      }
      else {
        root->setLeft(successor);
      }
     }
     // set accordindly
    // TODO
    }
    }
  }
  }
//return the number of nodes in the tree
  int BinaryTree::getCount(){
    return count;
  }
//search for a node. If found it returns 0 otherwise -1
//also counts the number of steps taken for the search
  int BinaryTree::search(int data, int &noOfSteps){
    int depth=0;
    if (root==nullptr) return -1;
    return search(data,root,noOfSteps);
  }

  int BinaryTree::search(int data, TreeNode * cur, int &noOfSteps){
    if (cur==nullptr) return -1;
    else  {
      if (cur->getData()==data) return 0;
      else if (data<cur->getData()){ noOfSteps++;
           return 
          search(data,cur->getLeft(),noOfSteps);
        }
      else { 
        noOfSteps=noOfSteps+1;
        return search(data,cur->getRight(),noOfSteps);
        }
      }
    }
// search function that returns the pointer to the node containing the data if found. Otherwise returns nullptr
    TreeNode * BinaryTree::searchNode(int data){

       if (root==nullptr) return nullptr;
    return searchNode(data,root);
    }
    TreeNode * BinaryTree::searchNode(int data, TreeNode * cur){
      if (cur==nullptr) return nullptr;
    else  {
      if (cur->getData()==data) return cur;
      else if (data<cur->getData()) return searchNode(data,cur->getLeft());
      else return searchNode(data,cur->getRight());
      }
    }

//find the parent node
  TreeNode *BinaryTree::searchPrev(int data){
    int depth=0;
 
    if (root==nullptr) return nullptr;
    if(root->getData()==data) return root;
    return searchPrev(data,root);
  }
  TreeNode *BinaryTree::searchPrev(int data, TreeNode * prev){
 
       if( prev->getLeft()==nullptr && prev->getRight()==nullptr) {
        
        
         return prev;
       }
       if (prev->getLeft()!=nullptr&&(prev->getLeft())->getData()==data)         
         return prev;
      else if (prev->getRight()!=nullptr&&(prev->getRight())->getData()==data)
          
          
          return prev;
      

 if (data<prev->getData())
      return searchPrev(data,prev->getLeft());
       
 else
   return searchPrev(data,prev->getRight());
}
   
// find the in order successor
  TreeNode * BinaryTree::inorderSuccessor(TreeNode * cur){
    if (cur ==nullptr) return nullptr;
    else if (cur->getRight()!=nullptr){cur=cur->getRight();}
      while (cur->getLeft()!=nullptr)
        cur=cur->getLeft();
    return cur;
  }
//in order traversal - achieved by processing the left most node
//then the parent of this leftmose node. This is followed by the in order traversal of the right child of the parent.
  void BinaryTree::inorderTraversal(TreeNode * cur){
   if (cur==nullptr) return;
   if (cur->getLeft()!=nullptr)
   {
  
      inorderTraversal(cur->getLeft());
      {std::cout<<cur->getData()<<" "; }
   }
  else 
    { 
    std::cout<<cur->getData()<<" "; 
    }  
    if (cur->getRight()!=nullptr){
      inorderTraversal(cur->getRight());
  }
    }
  void BinaryTree::inorderTraversal(){
    if (root==nullptr)
    std::cout<<"TREE IS EMPTY \n";
    else inorderTraversal(root);
    std::cout<<"\n";
  }
