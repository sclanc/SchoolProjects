#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"
#include <map>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

ExpressionManager::ExpressionManager(){}
ExpressionManager::~ExpressionManager(){}
	/*
	* Checks whether an expression is balanced on its parentheses
	* 
	* - The given expression will have a space between every number or operator
	* 
	* @return true if expression is balanced
	* @return false otherwise
	*/

	bool ExpressionManager::isBalanced(string expression)
	{
		stack<char> opens;
		map<char,char> inv;
		inv[')']='(';
		inv[']']='[';
		inv['}']='{';

		if(expression.empty())
		{
			return false;
		}
		for(int i = 0; i < expression.length(); i++)
		{
			char c = expression.at(i); 
			if(c=='{'|| c=='}'||c=='('||c==')'||c=='['|| c==']')
			{
				if(c=='{'||c=='('||c=='[')
				{
					opens.push(c);
				}
				else
				{
					if(opens.empty())
					{
						return false;
					}
					else if(opens.top() == inv[c])
					{
						opens.pop();
					}
					else
					{
						return false;
					}
				}
			}	
		}
		if(opens.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * Converts a postfix expression into an infix expression
	 * and returns the infix expression.
	 *
	 * - The given postfix expression will have a space between every number or operator.
	 * - The returned infix expression must have a space between every number or operator.
	 * - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	 * - Check lab requirements for what will be considered invalid.
	 *
	 * return the string "invalid" if postfixExpression is not a valid postfix expression.
	 * otherwise, return the correct infix expression as a string.
	 */
	 string ExpressionManager::postfixToInfix(string postfixExpression)
	 {
	 	cout << postfixExpression << endl;
	 	if(isvalid(postfixExpression))
	 	{
	 		stack<string> TheStack;
		 	stringstream ss;
		 	ss << postfixExpression;
		 	string c;
		 	while(ss>>c)
		 	{
		 		cout << "this "<< c <<" is c"<< endl;
		 		if(!TheStack.empty())cout << TheStack.top()<<"the size is" << TheStack.size() <<endl;
		 		if(isop(c) && TheStack.size()<2)
		 		{
		 			return "invalid";
		 		}
		 		else if(isop(c)&&TheStack.size()>=2)
		 		{
		 			string d=" ";
		 			string b = TheStack.top();
		 			TheStack.pop();
		 			if(TheStack.empty())return "invalid";
		 			string a = TheStack.top();
		 			TheStack.pop();
		 			string x="("+d+a+d+c+d+b+d+")";
		 			cout << x << endl;
		 			TheStack.push(x);
		 			cout << "not here"<<endl;
		 		}
		 		else
		 		{
		 			cout << "pushing" << endl;
		 			TheStack.push(c);
		 		}
		 	}
		 	return TheStack.top();
		 }
		 else
		 {
		 	return "invalid";
		 }
	 }
	/*
	 * Converts an infix expression into a postfix expression 
	 * and returns the postfix expression
	 * 
	 * - The given infix expression will have a space between every number or operator.
	 * - The returned postfix expression must have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 * 
	 * return the string "invalid" if infixExpression is not a valid infix expression.
	 * otherwise, return the correct postfix expression as a string.
	 */
string ExpressionManager::infixToPostfix(string infixExpression)
{
	cout << "infixToPostfix" << endl;
	if(isBalanced(infixExpression)&&isvalid(infixExpression))
 	{
		map<string,string> inv;
	 		inv[")"]="(";
	 		inv["]"]="[";
	 		inv["}"]="{";
 		stack<string> TheStack;
 		stringstream ss;
 		string result;
 		ss << infixExpression;
 		string str;
 		while(ss>>str)
		{
			//cout << result << endl;
			if(isop(str))
			{
				cout << str <<"is an operator" << endl;
	 		int prec= precedence(str);
	 		if(TheStack.empty()) 
	 		{
	 			cout << "the stack is empty: push " << str <<endl;
	 			TheStack.push(str);
	 		}
	 	else if(str==")"||str=="}"||str=="]")
		{
			cout << "closing bracket" <<endl;
			while(TheStack.top()!=inv[str])
			{
				cout << "popping"<< TheStack.top() << endl;
				result+=TheStack.top() + " ";
				TheStack.pop();
			}
			cout << "popping"<< TheStack.top() << endl;
			TheStack.pop();
		}
		else if(prec<precedence(TheStack.top()))
		{
			cout << "pushing" <<str<<endl;
			TheStack.push(str);
		}
		else if(prec==3)
		{
			cout << "pushing" <<str<<endl;
			TheStack.push(str);
		}
		else if(prec>=precedence(TheStack.top()))
		{
			while(!TheStack.empty() && prec>=precedence(TheStack.top()))
			{
				cout << "popping"<< TheStack.top() << endl;
				result+=TheStack.top() + " ";
				TheStack.pop();
			}
			cout << "pushing"<<str << endl;
			TheStack.push(str);
		}
	}
	else
	{
		cout <<"This:" <<str <<"is the number to be added to the result" << endl;
		result+=str+ " ";
	}
	str.clear();
	}
	while(!TheStack.empty())
	{
		cout << "cleaning the stack" << TheStack.top() <<endl;
		result+= TheStack.top() + " ";
		TheStack.pop();                       // WTF!! why is this segfaulting 
		//if(TheStack.empty()) break;
	}
	cout << "in the clear"<< endl;
	string real_result=result.substr(0,result.length()-1);
	return real_result;
	}
	else
	{
		cout << "this is invalid" << endl;
		return "invalid";
	}
}

	/*
	 * Evaluates a postfix expression returns the result as a string
	 * 
	 * - The given postfix expression will have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 * 
	 * return the string "invalid" if postfixExpression is not a valid postfix Expression
	 * otherwise, return the correct evaluation as a string
	 */
	 int ExpressionManager::evaluation(string a, string b, string c)
	 {
	 	int one=stoi(a);
	 	int two=stoi(b);
	 	if(c=="*") 
	 	{
	 		int ret= one * two;
	 	    return ret;
	 	}
	 	else if(c=="/")
	 	{
	 		int ret= one / two;
	 	    return ret;
	 	}
	 	else if(c=="%")
	 	{
	 		int ret= one % two;
	 	    return ret;
	 	}
	 	else if(c=="-")
	 	{
	 		int ret= one - two;
	 	    return ret;
	 	}
	 	else if(c=="+")
	 	{
	 		int ret= one + two;
	 	    return ret;
	 	}
	 }

	 string ExpressionManager::postfixEvaluate(string postfixExpression)
	 {
	 	if(isvalid(postfixExpression))
	 	{
	 		stack<string> TheStack;
		 	stringstream ss;
		 	ss << postfixExpression;
		 	string c;
		 	while(ss>>c)
		 	{
		 		if(isop(c) && TheStack.size()<2)
		 		{
		 			return "invalid";
		 		}
		 		else if(isop(c)&&TheStack.size()>=2)
		 		{
		 			string b = TheStack.top();
		 			TheStack.pop();
		 			if(TheStack.empty())return "invalid";
		 			string a = TheStack.top();
		 			TheStack.pop();
		 			if(b=="0"&&c=="/")
		 			{
		 				return "invalid";
		 			}
		 			int d= evaluation(a,b,c);
		 			stringstream convert;
		 			convert << d;
		 			string fin=convert.str();
		 			TheStack.push(fin);
		 		}
		 		else
		 		{
		 			cout << "pushing" << endl;
		 			TheStack.push(c);
		 		}
		 	}
		 	return TheStack.top();
		 }
		 else
		 {
		 	return "invalid";
		 }
	 }


	 int ExpressionManager::precedence(string c)
	 {
	 	map<string,int> prec;
	 	prec["{"]= 3;
	 	prec["["]= 3;
	 		prec["("]= 3;	
	 			prec["*"]= 1;
	 			prec["/"]= 1;
	 			prec["%"]= 1;
	 			prec["+"]= 2;
	 			prec["-"]= 2;

	 			int pre = prec[c];
	 			return pre;
	 		}

	 		

	 		bool ExpressionManager::isnumber(string expression)
	 		{
	 			for(int i=0; i<expression.size();i++)
	 			{
	 				if(isdigit(expression[i]))
	 				{

	 				}
	 				else
	 				{
	 					return false;
	 				}

	 			}
	 			return true;
	 		}

	 		bool ExpressionManager::isvalid(string expression)
	 		{
	 			stack<string> ops;
	 			stack<string> nums;
	 			stringstream ss;
	 			ss << expression;
	 			string c;
	 			while(ss>> c)
	 			{
	 				if(isnumber(c))
	 				{
	 					nums.push(c);
	 				}
	 				else if(c=="*"||c=="/"||c=="%"||c=="+"||c=="-")
	 				{
	 					ops.push(c);
	 				}
	 				c.clear();
	 			}
	 			if(!nums.empty()) nums.pop();
	 			else return false;
	 			if(nums.size()==ops.size())
	 			{
	 				return true;
	 			}
	 			return false;
	 		}

	 		bool ExpressionManager::isop(string c)
	 		{
	 			if(c==")"||c=="]"||c=="}"||c=="{"||c=="["||c=="("||c=="*"||c=="/"||c=="%"||c=="+"||c=="-")
	 			{
	 				return true;
	 			}
	 			else
	 			{
	 				return false;
	 			}
	 		}

//post to in==
// if sign run precedence 

//establish precendence and instert into stack, if prec is <= stack.top then pop stack, if it's closing bracket pop until you find complement 
//