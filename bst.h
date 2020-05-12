/*bsh.h*/

//
// Binary search tree
//

#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm>  // std::max

using namespace std;


template<typename TKey, typename TValue>
class binarysearchtree{

  private:
	
	  struct NODE
	  {
	    TKey  Key;
	    TValue Value;
	    NODE* Left;
	    NODE* Right;
	  };
	  
	
	  NODE* Root;  // pointer to root node of tree (nullptr if empty)
	  int   Size;  // # of nodes in the tree (0 if empty)
	
	  
	  //helper function inorder
	  void _inorder(NODE* cur)  
	  {
	     if (cur == nullptr)
	       return;
	     else
	     {
	        _inorder(cur->Left);
	        cout<<cur->Key<< " " << cur->Value << endl;
	        _inorder(cur->Right);
	     }
	  }
	  
	  //height helper function
	  int _height(NODE* cur){
	     
		  int leftHeight;
	      int rightHeight;
	      
	      if(cur==nullptr)
	        return -1;
	            
	            
	      leftHeight=_height(cur->Left);
	      rightHeight = _height(cur->Right);
	      
			return (max(leftHeight, rightHeight)+1); 
			
	     }
	     
	    //copy constructor helper function 
	    void _binarysearchtree(NODE* curOther){
	    		
	    	if(curOther==nullptr)
	    	return;
	    		
	    	else{
				
			insert(curOther->Key, curOther->Value);	
			_binarysearchtree(curOther->Left);
			_binarysearchtree(curOther->Right);
			
			}
		} 
	
	
  public:
	   
	  //default constructor 
		binarysearchtree(){
	    	Root = nullptr;
	    	Size = 0;
	 	 }
	  
		binarysearchtree(binarysearchtree& other){
	    	Root = nullptr;
	    	Size = 0;
	    	
	    	NODE* curOther=other.Root;
			_binarysearchtree(curOther);
		}
	
	
	  //returns the size of the tree
		int size(){
	   		return Size;
	  	}
	
	  //height public function
		int height(){
	    	return (_height(Root));
	  	}
	
	  // 
	  // search:
	  //
	  // Searches the tree for the given key, returning pointer to the value if found
	  // and nullptr if not found
	  //
	  TValue* search(TKey key)
	  {
	    NODE* cur = Root;
	
	    while (cur != nullptr)
	    {
	      if (key == cur->Key)  // already in tree
	        return &(cur->Value);
	
	      if (key < cur->Key)  // search left:
	      {
	        cur = cur->Left;
	      }
	      else
	      {
	        cur = cur->Right;
	      }
	    }//while  
	  
	    // if get here, not found
	    return nullptr;
	  }
	  
	
	  //
	  // insert
	  //
	  // Inserts the given key into the tree; if the key has already been insert then
	  // the function returns without changing the tree.
	  //
	  void insert(TKey key,TValue value)
	  {
	    NODE* prev = nullptr;
	    NODE* cur = Root;
	
	    //
	    // 1. Search to see if tree already contains key:
	    //
	    while (cur != nullptr)
	    {
	      if (key == cur->Key)  // already in tree
	        return;
	
	      if (key < cur->Key)  // search left:
	      {
	        prev = cur;
	        cur = cur->Left;
	      }
	      else
	      {
	        prev = cur;
	        cur = cur->Right;
	      }
	    }//while
	    
	    NODE* newNode = new NODE;
	    newNode->Key = key;
	    newNode->Value = value;
	    newNode->Left = nullptr;
	    newNode->Right = nullptr;
	   
	   if(prev==nullptr){
	      Root = newNode;
	      }
	   else if (key < prev->Key){
	         prev->Left = newNode;
	      }
	    else{
	       prev->Right = newNode;
	       }
	       
	       Size++;

	  }
	
	  //
	  // inorder:
	  //
	  // Performs an inorder traversal of the tree, outputting
	  // the keys to the console.
	  //
	  void inorder()
	  {
	     cout << "Inorder: \n";
	     
	     _inorder(Root);
	     
	     cout << endl;
	  }	
	

};

#endif
