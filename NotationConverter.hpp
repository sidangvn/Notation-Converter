#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <string>
#include "NotationConverterInterface.hpp"

class Node 
{ 
	public:
    		std::string ele;
    		Node *prev;
    		Node *next;
};

class lDeck 
{
	public:
    		lDeck();

    		int deck_size() const;
    		bool isEmpty() const;

    		std::string top();
    		void pushTop(std::string str);
		void popTop();
		
		std::string bot();
    		void pushBot(std::string str);
    		void popBot();

    		int size = 0;

		Node *head;
    		Node *tail;
};

class NotationConverter:public NotationConverterInterface 
{
	public:
    		bool char_valid(std::string str);
    		int pcd_valid(std::string str);
    		bool operator_valid(std::string str);

    		std::string postfixToInfix(std::string inStr);
    		std::string postfixToPrefix(std::string inStr);
    		std::string infixToPostfix(std::string inStr); 
    		std::string infixToPrefix(std::string inStr); 
    		std::string prefixToInfix(std::string inStr); 
    		std::string prefixToPostfix(std::string inStr); 
};

#endif
