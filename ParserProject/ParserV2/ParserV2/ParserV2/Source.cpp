#include<stack>
#include<string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

//Get Precedence
int getPresc(string key)
{
	/*Create a map where the key is the operation and the value is the precedence*/
	map<string, int> precs;
	/*Fill the map with the given operation, precedence pairs*/
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

	/*Our return variable*/
	int returnPrs;

	/*Try to find the given key*/
	try { returnPrs = precs[key]; }
	/*If not found then return -1*/
	catch (int) { returnPrs = -1; }
	return returnPrs;
}

/*Verify that the char we pass is an operation*/
bool isOperator(string _operator)
{
	/*Create a vector that holds all the possible operation values*/
	vector<string> Operators = { "+","-" ,"/","*","%","^","++", "--", ">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" };

	/*Declare an iterator to traverse the vector*/
	vector<string>::iterator iter;

	/*Search for the given operator in the vector*/
	iter = find(Operators.begin(), Operators.end(), _operator);

	/*If the iter is not the same as the end of the vector that means that the _operator was in fact one of the valid operations*/
	if (iter != Operators.end())
	{
		return true;
	}
	return false;
}

/*This will do the math logic*/
int doOperation(int leftHand, int rightHand, string Operation)
{
	/*NOTE: Not sure if the boolean checks are 100% correct*/
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
	/*for example ++ or --*/
	return _originalOP == _nextOP;
}

/*Will check if the operator is a special double one*/
bool equalsOperator(char _originalOP, char _nextOP)
{
	/*For example >= or ==*/
	return (_originalOP == '>' || _originalOP == '<' || _originalOP == '!' || _originalOP == '=') && _nextOP == '=';
}

/*This will build the character for us to add to the stack so that things like && or ++ are added as one element*/
string buildOperation(string _expressionCopy, int pos)
{
	/*We are passing the string and the position that we are currently on in the evaluation portion to check if the following value in the 
	string is an instance of a double operatoin (++ or --) or a = operation (>= or ==)*/
	
	/*Our returnString is set to "" so that we can convert the chars into a string*/
	string returnString = "";

	/*From the start we add the current char to the returnstring*/
	returnString += _expressionCopy[pos];

	/*The we check if it could be a double or an equals operation*/
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
	stack<int> values; /*This stack will hold our number values (i.e our operands)*/
	stack<string> operations; /*This stack will hold our operators*/
	int val = 0; /*This variable will help in keeping track of the value as we go through the expression*/
	int pos = 0; /*This variable will help keep track of our position in the expression string*/
	string topOperation; /*This will help when we pop an operation from the opertions stack*/
	string converter = ""; /*This will help turn our chars to strings*/

	/*This while loop will be used to go through the expression and pop/push/evaluate as we go*/
	while (pos < _expression.length())
	{
		/*First thing, if it is a ' ' then ignor it*/
		if (_expression[pos] == ' ')
		{ }

		/*Check if the current positoin is a digit*/
		if (isdigit(_expression[pos]))
		{
			/*If it is a digit then we do some math to get the correct values
			Explanation: Say that we have a string that has 101 as a value.
			We need to make sure that it is added to the stack as 101 and not 1 0 1
			So the math below takes care of that.
			The first time it find 101 the situation will look like this:

			val is currently 0 so val * 10 is zero, then (int)(_expression[pos] - '0') will take the '1' and convert it to an int type 1 
			it will then set val equal to 1

			as if continues, the next char in the string is 0
			so at this time 
			val is 1 so val * 10 = 10
			then again it cast the 0 as an it and 10 + 0 = 10
			now val is 10
			then it wil read the last 1 from the string, at this time:

			val is 10 so val * 10 = 100
			and (int)(_expression[pos] - '0') will turn that 1 into an int
			so in the end we get 100 + 1 = 101
			val will be 101, the full number that we wanted to be before we push it to the values stack
			*/
			val = (val * 10) + (int)(_expression[pos] - '0');
		}

		/*If it is not an int then it should be an opertion, there for we check if it is*/
		else if (isOperator((converter + _expression[pos])))
		{
			/*Now we must do a quick building of the operation to later add to the stack
			 The below statement, will call our build operation that will check it is a ++, &&, +, etc... so that we can have them as 
			 one neat value in the operations stack
			*/
			string builtOperation = buildOperation(_expression, pos);

			/*This will make sure that if we build an operatoin that is for example ++ it increase our position so that
			we dont count the second + again*/
			if(builtOperation.length() > 1)
			{
				pos++;
			}

			/*This condition will check if the current char is a ( character, if it is then it is automatically pushed to the stack
			and the val tracker is reset to 0*/
			if (builtOperation == "(")
			{
				operations.push(builtOperation);
				val = 0;
			}
			/* Next condition will check if the values stack is empty, then we want to add
			it to the stack but also push either zero or current val for mathmatical logic (i.e. -5+3 is actuall 0-5+3)
			*/
			if (values.size() <= 0)
			{
				values.push(val); //Push current value to stack
				operations.push(builtOperation); //Push operator to stack
				val = 0; // reset val tracker
			}
			/*else if the current char is a ) we need to do operations untill we get to the (*/
			else if (builtOperation == ")")
			{
				values.push(val); //Push the val that we have
				while (operations.top() != "(") //Loop until the top value in the operations stack is the (
				{
					topOperation = operations.top(); //take the top operation
					operations.pop(); // Remove it from the stack
					val = values.top(); // take the top value
					values.pop(); // remove it from the stack
					int prevVal = values.top(); // take the second value
					values.pop(); //remove it  from the stack
					val = doOperation(prevVal, val, topOperation); // do the operation
					values.push(val); //push the calculated value to the stack
				}
				operations.pop(); // pop the ( from the stack
				values.pop(); // pop the top value from the stack because it is a duplicate
			}

			/*Finally if it was none of the above, we need to evaluate precedence before pushing to the stack*/
			else
			{
				/*Take the top operation from the operations stack to compare the prec of the current position*/
				string prevOp = operations.top();

				/*If the current position operator is of higher pres then push it to the stack because till will need to be evaluated before the one
				below it*/
				if (getPresc(builtOperation) > getPresc(prevOp))
				{
					values.push(val); //push current val to stack
					operations.push(builtOperation); // push current operator to stack
					val = 0; //reset value tracker
				}
				else // If it is not of a higher prec then we need to do an evaluation before we push it to the stack
				{
					int prevval = values.top(); // Take the top value form the stack, it will be our lefthand side in the doOperations function
					values.pop(); // pop it from the stack
					string prevOp = operations.top(); // take the previous operator from the stack, it will get evaluated
					operations.pop(); // pop it from the stack
					prevval = doOperation(prevval, val, prevOp); // set the prevval = to the result of our doOperation
					values.push(prevval); //Push the result to the stack
					operations.push(builtOperation); // push the operation that we build to the stack
					val = 0; // reset the current value
				}
			}
		}
		pos++; // update our position
	}

	/*Lastly there could be operations and values in the stacks once we finish reading the string
	The below will do all the math until the operations stack is empty*/
	while (operations.size() > 0)
	{
		int prev = values.top();
		values.pop();
		string op = operations.top();
		operations.pop();
		val = doOperation(prev, val, op);
	}
	/*Return result*/
	return val;
}

/*Checking that string does not start with Closing Paranthesis*/
bool VerifyInputValidStart(string _input, string& message)
{
	vector<string> invalidStarts = { ">=", "<=", "==", "!=", "&&", "||" }; // This creates a stack of double signed operators that cannot be at the start
	vector<string> invalidStartSingle = { "!", ">", "<", "/","*","%","^" }; // This creates a stakc of singled signed operator that cannot be at the start
	vector<string>::iterator iter; // create iter to go through the stack
	vector<string>::iterator iter2; // create iter to go through the stack
	iter = find(invalidStarts.begin(), invalidStarts.end(), _input.substr(0, 2)); //Check
	iter2 = find(invalidStartSingle.begin(), invalidStartSingle.end(), _input.substr(0, 1));
	if (iter != invalidStarts.end())
	{
		message = "ERROR: Input cannot start with a binary expresson.";
		return false;
	}
	else if (_input[0] == ')')
	{
		message = "ERROR: Input cannot start with ) character.";
		return false;
	}
	else if (iter2 != invalidStarts.end())
	{
		message = "ERROR: Input cannot start with a mathematical expresson.";
		return false;
	}
	else
	{
		return true;
	}
}

/*Check that the operations are followed by a valid input*/
bool VerifyOperationsAreInValidOrder(stack<string> _copyStack, string& message)
{
	vector<string> OperationsToCheck = { "+","/","*","%","^", ">=", "<=", "!", ">", "<", "==", "!=", "&&", "||" }; // Create a stack of the possible issue cases follow ups
	vector<string>::iterator iter; // iterator 
	while (_copyStack.size() > 0) { //While the copystack is not empty
		iter = find(OperationsToCheck.begin(), OperationsToCheck.end(), _copyStack.top()); //Check if the top is a possible issue case
		if (iter != OperationsToCheck.end()) // If it is 
		{
			_copyStack.pop(); // pop it
			if (_copyStack.size() != 0) // if the stack is not empty
			{
				if (_copyStack.top() == "-" || (_copyStack.top() != "Indicator" && _copyStack.top() != ")")) // check that the following value is not also an issue case
				{
					message = "ERROR: Illegal operation @char " + to_string(_copyStack.size() + 1) + " after '" + _copyStack.top() + "'";
					message += ". Missing operand between operators.";
					return false;
				}
				else
				{
					_copyStack.pop(); // else pop it
				}
			}
		}
		else
		{
			_copyStack.pop(); // else pop it
		}
	}
	return true; // in the clear 
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
			//build out the digit
			string number = "";
			while (isdigit(_givenString[i]))
			{
				number += _givenString[i];
				i++;
			}
			Operands.push(stoi(number, nullptr));
			Operations.push("Indicator"); // add an indicator to the operands stack so it has a clue of the order
			i--;
		}
		else
		{
			//Else it should be an operator, figure out which type it is and add it to the stack
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
	string _expression = "(4>=4)&&0"; // change the test expression here
	string message = ""; // This will be passed by referance to our validation functions to get a specific error message 
	stack<int> checkValues = stack<int>(); // This will be used to parse for validation check
	stack<string> checkOperations = stack<string>(); // This will be used to parse for validation check
	ParseString(_expression, checkValues, checkOperations); // Parse the string 
	if (VerifyInputValidStart(_expression, message) && VerifyOperationsAreInValidOrder(checkOperations, message)) // check if it meets the validations
	{
		int ans = evaluateExpression(_expression); // if it does then lets evaluate
	}
	else {
		cout << message; // else cout the error message
	}
	return 0;
}