#include<stack>
#include<string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

//Get Preedence
int getPresc(string key)
{
	map<string, int> precs;
	precs["("] = 9;
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
	int returnPrs;
	try { returnPrs = precs[key]; }
	catch (int) { returnPrs = -1; }
	return returnPrs;
}

/*Verify that the char we pass is an operation*/
bool isOperator(string _operator)
{
	vector<string> Operators = { "+","-" ,"/","*","%","^","++", "--", ">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" };
	vector<string>::iterator iter;
	iter = find(Operators.begin(), Operators.end(), _operator);
	if (iter != Operators.end())
	{
		return true;
	}
	return false;
}

/*This will do the math logic*/
int doOperation(int leftHand, int rightHand, string Operation)
{
	if (Operation == "!") { return !rightHand; }
	if (Operation == "++") { return ++rightHand; }
	if (Operation == "--") { return --rightHand; }
	if (Operation == "^") { return pow(leftHand, rightHand); }
	if (Operation == "*") { return leftHand * rightHand; }
	if (Operation == "/") { return leftHand / rightHand; }
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

/*Will Check if operator is a double one*/
bool sameOperator(char _originalOP, char _nextOP)
{
	return _originalOP == _nextOP;
}

/*Will check if the operator is a special double one*/
bool equalsOperator(char _originalOP, char _nextOP)
{
	return (_originalOP == '>' || _originalOP == '<' || _originalOP == '!' || _originalOP == '=') && _nextOP == '=';
}

/*This will build the character for us to add to the stack so that things like && or ++ are added as one element*/
string buildOperation(string _expressionCopy, int pos)
{
	string returnString = "";
	returnString += _expressionCopy[pos];
	if ( sameOperator(_expressionCopy[pos], _expressionCopy[pos +1]))
	{
		return returnString += _expressionCopy[pos + 1];
	}
	else if (equalsOperator(_expressionCopy[pos], _expressionCopy[pos + 1]))
	{
		return returnString += _expressionCopy[pos + 1];
	}
	return returnString;
}

/*This will do the evaluation of the expression*/
int evaluateExpression(string _expression)
{
	stack<int> values;
	stack<string> operations;
	int val = 0;
	int pos = 0;
	string topOperation;
	string converter = "";

	while (pos < _expression.length())
	{
		if (_expression[pos] == ' ')
		{ }
		if (isdigit(_expression[pos]))
		{
			val = (val * 10) + (int)(_expression[pos] - '0');
		}
		else if (isOperator((converter + _expression[pos])))
		{
			string builtOperation = buildOperation(_expression, pos);
			if(builtOperation.length() > 1)
			{
				pos++;
			}

			if (builtOperation == "(")
			{
				operations.push(builtOperation);
				val = 0;
			}
			if (values.size() <= 0)
			{
				values.push(val);
				operations.push(builtOperation);
				val = 0;
			}
			else if (builtOperation == ")")
			{
				values.push(val);
				while (operations.top() != "(")
				{
					topOperation = operations.top();
					operations.pop();
					val = values.top();
					values.pop();
					int prevVal = values.top();
					values.pop();
					val = doOperation(prevVal, val, topOperation);
					values.push(val);
				}
				operations.pop();
				values.pop();
			}
			else
			{
				string prevOp = operations.top();
				if (getPresc(builtOperation) > getPresc(prevOp))
				{
					values.push(val);
					operations.push(builtOperation);
					val = 0;
				}
				else
				{
					int prevval = values.top();
					values.pop();
					string prevOp = operations.top();
					operations.pop();
					prevval = doOperation(prevval, val, prevOp);
					values.push(prevval);
					operations.push(builtOperation);
					val = 0;
				}
			}
		}
		pos++;
	}
	while (operations.size() > 0)
	{
		int prev = values.top();
		values.pop();
		string op = operations.top();
		operations.pop();
		val = doOperation(prev, val, op);
	}
	return val;
}

/*Checking that string does not start with Closing Paranthesis*/
bool VerifyInputValidStart(string _input, string& message)
{
	vector<string> invalidStarts = { ">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" };
	vector<string>::iterator iter;
	iter = find(invalidStarts.begin(), invalidStarts.end(), _input.substr(0, 2));
	if (iter != invalidStarts.end())
	{
		message = "ERROR: Input cannot start with a binary expresson.";
		return false;
	}
	if (_input[0] == ')')
	{
		message = "ERROR: Input cannot start with ) character.";
		return false;
	}
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
					message = "ERROR: Illegal operation @char " + to_string(_copyStack.size() + 1) + " after '" + _copyStack.top() + "'";
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
int main()
{
	string _expression = "(4>=4)&&0";
	string message = "";
	stack<int> checkValues = stack<int>();
	stack<string> checkOperations = stack<string>();
	ParseString(_expression, checkValues, checkOperations);
	if (VerifyInputValidStart(_expression, message) && VerifyOperationsAreInValidOrder(checkOperations, message))
	{
		int ans = evaluateExpression(_expression);
	}
	else {
		cout << message;
	}
	return 0;
}