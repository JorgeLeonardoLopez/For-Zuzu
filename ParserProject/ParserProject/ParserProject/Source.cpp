#include <stack>
#include <string>
#include <vector>
#include <map>
#include <math.h> 
using namespace std;


/* Need to check for:
 ! ++ -- () - ^ * / % + - > >= < <= == != && || 
 */

/*NOTICE ME SENPAI:
- Assumed that 3 _ 2  == 32
- Have not implemented a check for subtration or for being negativee*/

/*Will Check if operator is a double one*/
bool sameOperator(char _originalOP, char _nextOP)
{
	return _originalOP == _nextOP;
}

/*Will check if the operator is a special double one*/
bool equalsOperator(char _originalOP, char _nextOP)
{
	return (_originalOP == '>' || _originalOP == '<' || _originalOP == '!') && _nextOP == '=';
}


/*Will Build our stacks for later user*/
void ParseString(string _givenString, stack<int>& Operands, stack<string>& Operations)
{
	/*Now we want to go through the string and seperate out the operands from the operators*/
	for (int i = 0; i < _givenString.length(); i++)
	{
		/*If it is a space than we want to ignore it*/
		if (_givenString[i] == ' ')
		{
			continue;
		}
		/*We need to check if it is*/
		if (isdigit(_givenString[i]))
		{
			string number = "";
			while (isdigit(_givenString[i]))
			{
				number += _givenString[i];
				i++;
			}
			Operands.push(stoi(number, nullptr));
			Operations.push("Indicator");
			i--;
		}
		else
		{
			string operation = "";
			operation += _givenString[i];
			if (sameOperator(_givenString[i], _givenString[i + 1]))
			{
				i++;
				operation += _givenString[i];
			}
			else if (equalsOperator(_givenString[i], _givenString[i + 1]))
			{
				i++;
				operation += _givenString[i];
			}
			Operations.push(operation);
		}


	}
}

/*Checking that string does not start with Closing Paranthesis*/
bool VerifyInputValidStart(string _input)
{
	vector<string> invalidStarts = {">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" };
	vector<string>::iterator iter;
	iter = find(invalidStarts.begin(), invalidStarts.end(), _input.substr(0, 2));
	if (iter != invalidStarts.end())
	{
		return false;
	}
	if (_input[0] == ')')
		return false;
	return true;
}



/*Check that the operations are followed by a valid input (i.e indcator or a ) sign*/
bool VerifyOperationsAreInValidOrder(stack<string> _copyStack, string& message)
{
	vector<string> OperationsToCheck = { "+","/","*","%","^", ">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" };
	vector<string>::iterator iter;
	while (_copyStack.size() > 0) {
		iter = find(OperationsToCheck.begin(), OperationsToCheck.end(), _copyStack.top());
		if (iter != OperationsToCheck.end())
		{
			_copyStack.pop();
			if (_copyStack.size() != 0)
			{
				if (_copyStack.top() == "-" || (_copyStack.top() != "Indicator" && _copyStack.top() != ")"))
				{
					message = "ERROR: Illegal operation @char " + to_string(_copyStack.size() + 1) + " after '"+_copyStack.top()+"'";
					message += ". Missing operand between operators.";
					return false;
				}
				else
				{
					_copyStack.pop();
				}
			}
		}
		else
		{
			_copyStack.pop();
		}
	}
	return true;
}

int getPresc(string key)
{
	map<string, int> precs;
	precs["!"] = 8;
	precs["++"] = 8;
	precs["--"] = 8;
	precs["^"] = 7;
	precs["*"] = 6;
	precs["/"] = 6;
	precs["%"] = 6;
	precs["+"] = 5;
	precs["-"] = 5;
	precs[">"] = 4;
	precs[">="] = 4;
	precs["<"] = 4;
	precs["<="] = 4;
	precs["=="] = 3;
	precs["!="] = 3;
	precs["&&"] = 2;
	precs["||"] = 1;
	return precs[key];
}

int doOperation(int leftHand, int rightHand, string Operation)
{
	if (Operation == "!") { return !rightHand; }
	if (Operation == "++"){	return ++rightHand;	}
	if (Operation == "--"){	return --rightHand;	}
	if (Operation == "^") {	return pow(leftHand, rightHand); }
	if (Operation == "*") {	return leftHand * rightHand; }
	if (Operation == "/") {	return leftHand / rightHand; } 
	if (Operation == "%") { return leftHand % rightHand; }
	if (Operation == "+") { return leftHand + rightHand; }
	if (Operation == "-") { return leftHand - rightHand; }
	if (Operation == ">") { return leftHand > rightHand; }
	if (Operation == "<") { return leftHand < rightHand; }
	if (Operation == "<=") { return leftHand <= rightHand; }
	if (Operation == "==") { return leftHand == rightHand; }
	if (Operation == "!=") { return leftHand != rightHand; }
	if (Operation == "&&") { return leftHand && rightHand; }
	if (Operation == "||") { return leftHand || rightHand; }
	return 0;
}

int evaluateExpression(string _expression)
{
	stack<string>Operations = stack<string>();
	stack<int>Operands = stack<int>();
	for (int i = 0; i < _expression.length(); i++)
	{
		/*If it is a space than we want to ignore it*/
		if (_expression[i] == ' ')
		{
			continue;
		}

		/*We need to check if it is*/
		if (isdigit(_expression[i]))
		{
			string number = "";
			while (isdigit(_expression[i]))
			{
				number += _expression[i];
				i++;
			}
			Operands.push(stoi(number, nullptr));
			i--;
		}
		else
		{
			string operation = "";
			operation += _expression[i];
			if (operation == "(")
			{
				Operations.push(operation);
			}
			if (sameOperator(_expression[i], _expression[i + 1]))
			{
				i++;
				operation += _expression[i];
			}
			else if (equalsOperator(_expression[i], _expression[i + 1]))
			{
				i++;
				operation += _expression[i];
			}
			else if (operation == ")")
			{
				while (Operations.top() != "(")
				{
					string op = Operations.top();
					Operations.pop();
					int rightHand = Operands.top();
					int leftHand;
					try { leftHand = Operands.top(); }
					catch (int x) { leftHand = 0; }
					Operands.push(doOperation(leftHand, rightHand, op));
				}
				Operands.pop(); //removing (
			}
			else if (Operations.size() == 0)
			{
				Operations.push(operation);
			}
			else
			{
				string prevOP = Operations.top();
				if (getPresc(operation) > getPresc(prevOP))
				{
					Operations.push(operation);
				}
				else
				{
					while (Operations.size() > 0)
					{
						prevOP = Operations.top();
						if (getPresc(operation) > getPresc(prevOP))
						{
							Operations.push(operation);
						}
						string op = Operations.top();
						Operations.pop();
						int rightHand = Operands.top();
						Operands.pop();
						int leftHand;
						try
						{
							leftHand = Operands.top();
							Operands.pop();
						}
						catch (int x) { leftHand = 0; }
						Operands.push(doOperation(leftHand, rightHand, op));
					}
					Operations.push(operation);
				}

			}
		}
	}
	while (Operations.size() > 0)
	{
		string op = Operations.top();
		Operations.pop();
		int rightHand = Operands.top();
		int leftHand;
		try { leftHand = Operands.top(); }
		catch (int x) { leftHand = 0; }
		Operands.push(doOperation(leftHand, rightHand, op));
	}
	return Operands.top();
}

int main()
{
	stack<int> Operands = stack<int>();
	stack<string> Operations = stack<string>();
	ParseString("4+3*5-6/2", Operands, Operations);
	string message;
	bool check = VerifyOperationsAreInValidOrder(Operations, message);
	int ans = evaluateExpression("4+3*5-6/2");
	return 0;
} 