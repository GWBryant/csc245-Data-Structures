#include "bet.h"
#include <iostream>

using namespace std;

//public functions
//BET constructor
BET::BET()
{
    root = NULL;
}

//BET deconstructor
BET::~BET()
{
    makeEmpty();
    root = NULL;
}

//checks if BET is empty by looking at the root
bool BET::isEmpty () const
{
    if(root == NULL)
        return true;
    else
        return false;
}  

//public call to private make empty
void BET::makeEmpty()
{
    makeEmpty(root);
}

//inserts an operator with prefix input
void BET::insertPrefixOperator (char token)
{
    BETPtr preOp = new BinaryNode;
    preOp -> info.whichType = OPERATOR;
    preOp -> info.theContent.opsymbol = token;
    preOp -> right = s.topAndPop();
    preOp -> left = s.topAndPop();
    s.push(preOp);
    root = preOp;
}

//inserts operator with postfix input
void BET::insertPostfixOperator (char token) 
{
    BETPtr postOp = new BinaryNode;
    postOp -> info.whichType = OPERATOR;
    postOp -> info.theContent.opsymbol = token;
    postOp -> left = s.topAndPop();
    postOp -> right = s.topAndPop();
    s.push(postOp);
    root = postOp;
}

//inserts operand into stack
void BET::insertOperand (char token)
{
    BETPtr newOp = new BinaryNode;
    newOp -> info.whichType = OPERAND;
    newOp -> info.theContent.variable = token;
    newOp -> left = NULL;
    newOp -> right = NULL;
    s.push(newOp);
} 

//public call to preorder
void BET::preorder() const
{
    if(!isEmpty())
    {
        preorder(root);
        cout << endl;
    }
    else
    {
        cout << "Tree is empty." << endl;
    }
    
} 

//public call to inorder
void BET::inorder() const
{
    if(!isEmpty())
    {
        inorder(root);
        cout << endl;
    }
    else
    {
        cout << "Tree is empty." << endl;
    }
}

//public call to postorder
void BET::postorder() const
{
if(!isEmpty())
    {
        postorder(root);
        cout << endl;
    }
    else
    {
        cout << "Tree is empty." << endl;
    }
}

//private functions
//private makeEmpty
void BET::makeEmpty( BETPtr& t ) const
{
    //if root isnt null go left and right recursively and delete nodes
    if(t != NULL)
    {
        makeEmpty(t -> right);
        makeEmpty(t -> left);

        delete t;
        t = NULL;
    }
}

//prints preorder by printing node and then recursively going right and left
void BET::preorder( BETPtr t ) const
{
    if(t != NULL)
    {
            if(t->info.whichType == OPERAND)
                cout << t->info.theContent.variable << " ";
            else
                cout << t->info.theContent.opsymbol << " ";
            preorder( t->right );
            preorder( t->left );
    }
}

//prints inorder by recursively going right, printing, going recursively left, and printing
void BET::inorder( BETPtr t ) const
{
    if(t != NULL)
    {
        if(t ->left != NULL)
            cout << "( ";
        inorder(t->right);
        if(t->info.whichType == OPERAND)
            cout << t->info.theContent.variable << " ";
        else
            cout << t->info.theContent.opsymbol << " ";
        inorder(t->left);
        if(t->right != NULL)
            cout << ") ";
    }
}

//prints preorder by recursively going right and left and then printing
 void BET::postorder( BETPtr t ) const
 {
     if(t != NULL)
     {
        postorder(t->right);
        postorder(t->left);
        if(t->info.whichType == OPERAND)
            cout << t->info.theContent.variable << " ";
        else
            cout << t->info.theContent.opsymbol << " ";
     }
 }