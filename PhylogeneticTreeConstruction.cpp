#include<iostream>
using namespace std;

// Binary  tree (BT) is a data structure used for both searching and sorting. Any node
// contains at most two children. 
    class node  
{  
    public: 
    string data;  
    node* left, *right;  
      
    /* Constructor that allocates a new node with the  
    given data and NULL left and right pointers. */
    node(string data)
    { 
        this->data = data; 
        this->left = NULL; 
        this->right = NULL; 
    } 
};  

void printTree(node* t, char spaces)
{
  if(t != NULL)
  {
    printTree(t->right, spaces +6);
    for(int i = 0; i < spaces; i++)
      	cout << ' ';
    	cout << "---" << t->data << endl;
    printTree(t->left, spaces+6);
  }
}

int main() 
{
    //BST t;
    node *root = new node("62.4");  
    root->left = new node("67.27");  
    root->right = new node("82.96");  
  
    root->left->left = new node("82.95");  
    root->left->right = new node("88.18");  
    root->right->left = new node("90.91");  
    root->right->right = new node("Dog");  
  
    root->left->left->left = new node("98.18");  
    root->left->left->right = new node("94.55");  
    root->left->right->left = new node("Cat");  
    root->left->right->right = new node("Horse");  
    root->right->left->left = new node("Rat");  
    root->right->left->right = new node("hamster");  
    root->left->left->right->left=new node("Mouse");
    root->left->left->right->right=new node("Pig");
    root->left->left->left->left=new node("100");
    root->left->left->left->right=new node("Monkey");
    root->left->left->left->left->left=new node("Human");
    root->left->left->left->left->right=new node("Gorilla");
    printTree(root,3);
    return 0; 
}