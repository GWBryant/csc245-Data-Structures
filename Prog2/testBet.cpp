#include <iostream>
#include "bet.h"
#include <cstring>

using namespace std;

void PrintMenu(char &expressionType, string &expression);
void buildPostfix(string expression,BET &myTree);
void buildPrefix(string expression, BET &myTree);
void buildInfix(string expression, BET &myTree);
void printTree(BET &myTree);
string infixToPostfix(string infixExpression);
bool isOp(char c);
bool opIsGE(char c, char d);

int main()
{
    //instantiate variables
    BET myTree;
    char expressionType;
    string expression;
    char exitChoice;
    //loop to keep in loop until user exits program
    do
	{
        //empties tree before making a new one
        myTree.makeEmpty();
		PrintMenu(expressionType, expression); //prints menu and takes input
        //performs operation depending on input
		switch (expressionType)
		{
			case '1' :   buildPrefix(expression,myTree); printTree(myTree); break;
			case '2' :   buildInfix(expression,myTree); printTree(myTree); break;
			case '3' :   buildPostfix(expression,myTree); printTree(myTree); break;
			default  :   cout << "\tError.  Invalid input." << endl;	
		}
        //check if user wants to print a tree, if not exit the loop and end program
        cout << "Build another tree? (Y/N) ";
        cin >> exitChoice;
	}while(toupper(exitChoice) != 'N');
    cout << "Program now deconstructing tree and exiting ..." << endl;
    return 0;
}

//method to print menu and take input
void PrintMenu(char &expressionType, string &expression)
{
    //print out menu and take input
    cout << "--------------------- Building Binary Expression Trees ---------------------" << endl;
    cout << "        (1) prefix                (2) Infix                (3) Postfix      " << endl;
    cout << "Your expression type ==> ";
    cin >> expressionType;
    cout << "Your expression ==> ";
    cin.ignore();   //getline didn't work without this, ignores items already in input buffer
    getline(cin,expression);
}

//builds tree for postfix input, ignores spaces
void buildPostfix(string expression,BET &myTree)
{
    for(int i = 0; i < expression.length(); i++)
    {
        if(expression[i] == ' ')
            i++;
        if(!isOp(expression[i]) && expression[i] != ' ')
        {
            myTree.insertOperand(expression[i]);
        }
        else if(isOp(expression[i]))
        {
            myTree.insertPostfixOperator(expression[i]);
        }
    }
}

//builds tree from prefix input starting from back to front of string
//ignores spaces
void buildPrefix(string expression, BET &myTree)
{
    for(int i = expression.length(); i >= 0; i--)
    {
        if(expression[i] == ' ')
            i--;
        if(!isOp(expression[i]) && expression[i] != ' ')
            myTree.insertOperand(expression[i]);
        else if(isOp(expression[i]))
            myTree.insertPrefixOperator(expression[i]);
    }
}

//builds tree from infix input by converting infix to postfix and building a postfix tree
void buildInfix(string expression, BET &myTree)
{
    expression = infixToPostfix(expression);
    buildPostfix(expression,myTree);
}

//converts infix to postfix
string infixToPostfix(string f)
{
    Stack<char> s;
    string postfixExpression;
    //add parenthesis around every equation
    f.insert(0,"(");
    f += ')';
    for(int i = 0; i < f.length(); i++)
    {
        if(f[i] == ' ')
            i++;
        if(!isOp(f[i]) && f[i] != '(' && f[i] != ')')
            postfixExpression += f[i];
        else if(f[i] == '(')
            s.push(f[i]);
        else if(f[i] == ')')
        {
            while(s.top() != '(')
                postfixExpression += s.topAndPop();
            s.pop();
        }
        else if(isOp(f[i]) && (s.isEmpty() || !isOp(s.top())))
            s.push(f[i]);
        else if(isOp(f[i]) && isOp(s.top()))
        {
            if(opIsGE(f[i],s.top()))
            {
                while(opIsGE(f[i],s.top()))
                {
                    postfixExpression += s.topAndPop();
                }
                s.push(f[i]);
            }
        }
    }
    //print all remaining operators in stack
    while(!s.isEmpty())
    {
       postfixExpression += s.topAndPop();
    }
    return postfixExpression;
}

//print tree in all formats
void printTree(BET &myTree)
{
    cout << "Prefix expression produced from tree:" << endl;
    myTree.preorder();
    cout << "Infix expression produced from tree:" << endl;
    myTree.inorder();
    cout << "Postfix expression produced from tree:" << endl;
    myTree.postorder();
}

//check if a character is an operator
bool isOp(char c)
{
    if(c == '+' || c == '-' || c== '*' || c == '/')
        return true;
    else
        return false;
}

//check if the current operator is of equal or greater precedence than the one
//on the top of the stack
bool opIsGE(char c, char d)
{
    if(isOp(d))
    {
        if(c == '*' || c == '/' && d == '*' || d == '/')
            return true;
        else if(c == '+' || c =='-')
            return true;
        else
            return false;
    }
    else
        return false;
}