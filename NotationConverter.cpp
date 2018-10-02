
#include <string>
#include <string.h>
#include <cstring>
#include <iostream>
#include "NotationConverter.hpp"

//Default constructor
lDeck::lDeck()  
{ 
    	head = nullptr;
	tail = nullptr; 
}

//Deque size
int lDeck::deck_size() const 
{ 
    	return size; 
}

//Check for empty deque
bool lDeck::isEmpty() const 
{ 
	return (head == nullptr); 
}

//1st element in the deck
std::string lDeck::top() 
{ 
    	if(isEmpty()) 
    	{
        	return "Storage is empty!"; 
    	}

    	return head -> ele;
}


//Push element to top of deck
void lDeck::pushTop(std::string str)
{ 
    	Node *temp = new Node;
    	temp -> ele = str;

    	if(isEmpty()) 
    	{ 
    	    	head = temp;
		tail = temp;
    	}
    	else 
    	{ 
        	temp -> next = head; 
        	temp -> prev = nullptr;
        	head = temp;
    	}
    	size++;
}

//Pop out the element from top of deck
void lDeck::popTop()
{ 
    	if(isEmpty()) 
    	{ 
    		throw("Storage is empty!");
    	}
	
    	Node *temp = head;
    	head = head -> next;
    	delete temp;

    	size--; //pop out element out of deck so the size will be decreased 
}

//Last element in the deck
std::string lDeck::bot()
{ 
    	if(isEmpty()) 
    	{
        	return "Storage is empty!"; 
    	}
    	return tail -> ele;
} 

//Push element to bottom of deck
void lDeck::pushBot(std::string str) 
{ 
    	Node *temp = new Node;
    	temp -> ele = str;
 
	if(isEmpty()) 
    	{ 
        	head = temp;
 		tail = temp;
    	}
    	else 
    	{ 
        	temp -> prev = tail; 
        	temp -> next = nullptr;
        	tail = temp;
    	}
    	size++; //add element into deck so the size will be increased
}

//Pop out the element from bottom of deck
void lDeck::popBot()
 { 
    	if(isEmpty()) 
    	{ 
        	throw("Storage is empty!");
    	}

    	Node *temp = tail;
    	tail = tail -> prev;
    	delete temp;
    
    	size--; //pop out element out of deck so the size will be decreased 
}

//Check for valid charactors
bool NotationConverter::char_valid(std::string str)
{ 
    	char c[str.size() + 1]; 
    	strcpy(c, str.c_str());

    	if(operator_valid(str)) 
    	{
        	return 1;
   	}

    	if(isalpha(c[0])) 
    	{
        	return 1;
    	}

    	if(isdigit(c[0])) 
    	{
        	return 1;
    	}

    	if(str == "(" || str == ")" || str == " ") 
    	{ 
        	return 1;
    	}
    	else 
    	{
        	return 0;
    	}
}

//Check for valid  precedence
int NotationConverter::pcd_valid(std::string str) 
{ 
    	if(str == "+" || str == "-")
    	{
        	return 1;
    	}
    	if(str == "*" || str == "/" ) 
    	{
        	return 2;
    	}
	else
	{
    		return 0;
	}
}

//Check for valid operators
bool NotationConverter::operator_valid(std::string str)
{ 
    	if(str == "+" || str == "-" || str == "*" || str == "/") 
    	{
        	return 1;
    	}
    	else 
    	{ 
        	return 0; 
    	}
}

//POSTFIX to INFIX
std::string NotationConverter::postfixToInfix(std::string inStr)
{
	lDeck temp = lDeck();

    	for(unsigned int i = 0; i < inStr.length(); i++) 
    	{ 
		//convert inStr to string
        	std::string buff = std::string(1, inStr[i]); 

        	if(!char_valid(buff)) 
        	{ 
            		throw("Input is invalid");
        	}

        	if(buff == "(" || buff == ")" || buff == " ") 
        	{ 
            		continue; 
        	}
 
        	if(operator_valid(buff)) 
        	{ 
            		std::string op1 = temp.bot(); 
            		temp.popBot();
            		std::string op2 = temp.bot();
            		temp.popBot();
            		temp.pushBot("(" + op2 + " " + buff + " " + op1 + ")");
        	}
        	else 
        	{
            		temp.pushBot(buff); 
        	}
    	}

   	std::string infix;
   	infix = temp.bot();

   	return infix;
}

//POSTFIX to PREFIX
std::string NotationConverter::postfixToPrefix(std::string inStr)
{
	lDeck temp = lDeck();   

   	for(unsigned int i = 0; i < inStr.length(); i++) 
   	{ 
        	std::string buff = std::string(1, inStr[i]);

        	if(!char_valid(buff)) 
		{
            		throw("Input is invalid");
        	}

        	if(buff == "(" || buff == ")" || buff == " ") 
        	{ 
            		continue;
        	}

        	if(operator_valid(buff)) 
        	{
            		std::string op1 = temp.bot();
            		temp.popBot();
            		std::string op2 = temp.bot();
            		temp.popBot();
            		temp.pushBot(buff + " " + op2 + " " + op1);
        	}
        	else 
        	{
            		temp.pushBot(buff);
        	}
   	}

   	std::string prefix;
   	prefix = temp.bot();

   	return prefix;
}

//INFIX to POSTFIX
std::string NotationConverter::infixToPostfix(std::string inStr)
{
	lDeck temp = lDeck();    	
	std::string postfix;

    	for(unsigned int i = 0; i < inStr.length(); i++) 
    	{ 
        	std::string buff = std::string(1, inStr[i]);
        	if(!char_valid(buff)) 
        	{
            		throw("Input is invalid");
        	}

        	if(inStr[i] == ' ') 
        	{ 
            		continue; 
        	}
	
        	if(isalpha(inStr[i]) || isdigit(inStr[i])) 
        	{ 
            		postfix += buff ;
            		postfix += " ";
        	}

        	if(inStr[i] == '(') 
        	{
            		temp.pushBot(buff);
        	}

        	if(inStr[i] == ')') 
		{ 
            		while(!temp.isEmpty() && temp.bot() != "(")
            		{
                		postfix += temp.bot();
                		postfix += " ";
                		temp.popBot();
            		}

            		if(!temp.isEmpty()) 
            		{
                		temp.popBot();
            		}
        	}

        	if(operator_valid(buff)) 
        	{
            		if(temp.isEmpty()) 
            		{ 
                		temp.pushBot(buff);
            		}
            		else 
            		{
                		while(!temp.isEmpty() && (temp.bot() != "(") && (pcd_valid(buff) <= pcd_valid(temp.bot()))) 
                		{
                    			postfix += temp.bot();
                    			postfix += " ";
                    			temp.popBot();
                		}
                
                		temp.pushBot(buff);
            		}
        	}
    	}
    	return postfix;
}


//INFIX to PREFIX
std::string NotationConverter::infixToPrefix(std::string inStr) 
{ 
    	std::string buff;
    	std::string prefix;
	
	//reverse infix to postfix to get postfix to prefix
    	buff = infixToPostfix(inStr);
    	prefix = postfixToPrefix(buff);

    	return prefix;
}

//PREFIX to INFIX
std::string NotationConverter::prefixToInfix(std::string inStr)
 { 
    	std::string buff;
    	std::string infix;

	//reverse prefix to postfix and postfix to infix to get prefix to infix
    	buff = prefixToPostfix(inStr);
    	infix = postfixToInfix(buff);

    	return infix;
}

//PREFIX to POSTFIX
std::string NotationConverter::prefixToPostfix(std::string inStr) 
{
    	lDeck temp = lDeck();

    	for(int i = inStr.size() - 1; i >= 0; i--) 
    	{ 
        	std::string buff = std::string(1, inStr[i]);
        	if(!char_valid(buff)) 
        	{
            		throw("Input is invalid");
        	}

        	if(buff == " ") 
        	{ 
            		continue; 
        	}

        	if(operator_valid(buff)) 
        	{
            		std::string op1 = temp.bot();
            		temp.popBot();
            		std::string op2 = temp.bot();
            		temp.popBot();
            		temp.pushBot(op1 + " " + op2 + " " + buff);
        	}
        	else 
        	{
            		temp.pushBot(buff);
        	}
    	}

   	std::string postfix;
   	postfix = temp.bot();

   	return postfix;
   
}

