The problem for this project was to create a program that can take an equation as input in of one of three different formats and use that input to populate a binary expression tree. Then use different traversals of that BET to display the equation in prefix, infix, and postfix format.

We started with a specification file for and were tasked with creating an implementation file and a client file.

## functions for BET.cpp/BET.h

### public:
* isEmpty(): checks if BET is empty by checking the root
* makeEmpty(): calls private function for makeEmpty
* insertPrefixOperator(): inserts operator when using prefix input. does so by setting children to pointers to two objects on top of stack. does right and then left because when reading prefix input we read it back to front in client file.
* insertPostfixOperator():inserts operator when using postfix input. does so by setting children to pointers to two objects on top of stack. does left and then right because when reading postfix input we read it front to back in client file unlike prefix.
* insertOperand(): inserts an operand into a stack that the insert operator functions will reference to build the tree.
* preorder(): public call to preorder
* inorder():public call to preorder
* postorder(): public call to postorder
### private:
* makeEmpty(BETPtr& t): takes in pointer (root) and goes recursively left and then right and deletes nodes and sets them to NULL while the root isnt null
* preorder(BETPtr& t): prints data in node and then goes recursively right and then left
* inOrder(BETPtr& t): prints parenthesis around eqn if there arent any and goes recursively right, prints data, then goes recursively left and prints data.
* postorder(BETPtr& t): goes recursivley right then left and prints data.

## functions for testBet.cpp/cleint file

* printMenu(): prints the menu and takes input for choice, reads line to get expression
* buildPostfix(): builds a BET with postfix input ignoring spaces. If its a space it increments past the space, if its an operand it inserts an operand and if its a operator it inserts a postfix operator
* buildPostfix(): builds a BET with prefix input ignoring spaces. If its a space it increments past the space, if its an operand it inserts an operand and if its a operator it inserts a prefix operator
* buildInFix(): converts infix to postfix and then builds a postfix tree
* infixToPostfix(): first i add parenthesis around the string being sent in. Then i check if theres white space and if there is i skip that character. Next if the current character is not an operator or a parenthesis i add it to the postfix expression. next if the current char is ( then push it to the stack. Next if the current char is ) then pop and output all stack members until you reach (, and then pop (. Then if the current char is an operator and the stack is empty or the top of teh stack isnt an operator push the operator. Next if the current char is an operator and the top of the stack is an operator pop and output all operators of greater or equal precidence to the postfix expression, then push the operator onto the stack. Finally pop all remaining operators to the postfix operation.
* printTree(): print all traversals of the BET.
* isOp(): checks if char is an operator
* opIsGE(): checks if an operator is of greater or equal precidence than another.
* main(): keeps program running until the end