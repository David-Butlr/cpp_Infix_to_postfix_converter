/*-------------------------------------|
Written by David Butler & Justin King  |
4/27/2019                              |
Lab 4                                  |
This program converts infix to postfix |
--------------------------------------*/

#include <iostream> // this library is used to output to console
#include <cassert>  // this library is used to access assert function
#include <fstream>  // this library is used to input/output from/to file
#include <iomanip>  // this library is used to manipulate output

using namespace std;    // standard naming

#include "LinkedStack.cpp"  // used to access LinkedStack implementation file

int prec(char c);       // Function declaration for type int that take one formal parameter of type char by value. Returns an int.

void infixToPostFix(string infix);      // Function declaration for void function that converts infix to post fix notation. One formal parameter passed by value of type string to hold the infix to be converted.

ifstream fin("infixData.txt");      // Declaration of type ifstream that allows the program to read the data from the file infixData.txt

ofstream fout("inFixOut.txt");      // Declaration of type ofstream that allows the program to write to the output file inFixOut.txt after converting the data read from the input file.

void process(ifstream& fin, string& infix); // Function declaration for void process that takes two formal parameters both passed by reference.

void title();       // Function declaration for void title that displays the title of the program to the console. Takes no parameters.


int main()
{
    string infix;       // declaration of type string used to hold the data read from the file

    process(fin, infix); // Function call to process the data with two arguments being passed by reference.

    return 0;
}

// Converts infix expression to postfix expression
void infixToPostFix(string infix)  // Function definition of infixToPostFix with one parameter being passed by value
{
    LinkedStack<char> stk;        // Local object with template type char to connect object to the members of the header files
    stk.push('N');                 // Local object stk uses dot notation to call member function push
    int sLength = infix.length();   // Local int declared to hold the value of the length of the infix being passed through the function by value
    string pstFix;                  // Local string declared to hold the post fix notation after being converted
    char hold;                      // Local char variable to hold characters read from the file
    for(int i = 0; i <sLength; i++)     // For loop to read through the value stored in the string sLength
    {
        if((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '1' && infix[i] <= '9')) // if statement checking for validity of the characters being stored in the infix variable
        {
            pstFix += infix[i];     // if the characters from infix are valid then they are stored one at a time in to the pstFix variable
            pstFix += " ";          // places spaces between each character for proper output
        }
        else if(infix[i] == '(')     // else if statement checking for open parentheses
        {
            stk.push('(');          // if character is an open parentheses it uses the object stk and the member function push to push the ( onto the stack
        }
        else if(infix[i] == ')')    // else if statement checking for close parentheses
        {
            while(stk.top() != 'N' && stk.top() != '(')     // while loop that continues until the top of the stack is either a N or an (
            {
                hold = stk.top();       // char variable hold the top char of the stack
                stk.pop();              // pops the character off the stack
                pstFix += hold;         // hold is stored into pstFix string variable
                pstFix += " ";          // adds whitespace to pstFix for proper output
            }
            if(stk.top() == '(')        // if statement for when an open parentheses is encountered at the top of the stack
            {
                hold = stk.top();       // open parentheses is stored into the hold variable
                stk.pop();              // pops the open parentheses off the stack
            }
        }
        else                            // else statement
        {
            while(stk.top() != 'N' && prec(infix[i]) <= prec(stk.top())) // while loop with function call to prec to check for precedence of character on the stack
            {
                hold = stk.top();       // hold stores the character using the stk object and the member function top
                stk.pop();              // uses the object stk and member function pop to pop character off stack
                pstFix += hold;         // hold is stored into pstFix string variable
                pstFix += " ";          // adds whitespace to pstFix for proper output
            }
            stk.push(infix[i]);         // object stk uses member push to push each individual character stored in infix onto the stack
        }
    }
    while(stk.top() != 'N')     // while loop that continues until the flag value at the end of the stack is reached
    {
        hold = stk.top();               // hold stores the character using the stk object and the member function top
        stk.pop();                      // uses the object stk and member function pop to pop character off stack
        pstFix += hold;                 // hold is stored into pstFix string variable
        pstFix += " ";                  // adds whitespace to pstFix for proper output
    }

    cout << pstFix << endl;     // outputs the post fix notation to the console
    fout << pstFix << endl;     // outputs the post fix notation to the output file
}
     //Function to return precedence of operations that has one formal parameter of type char
int prec(char c)
{
    if( c == '^')       // if statement to check for exponents and return it with the highest precedence
        return 3;
    else if(c == '*' || c == '/')   // else if statement to check for either either multiplication or division and return it with highest precedence other than exponents
        return 2;
    else if(c == '+' || c == '-')   // else if statement to check for either either addition or subtraction and return it with highest precedence other than exponents, multiplication and division
        return 1;
    else               // else statement to return to function if none of the char characters are part of PEMDOS
        return -1;
}

void process(ifstream& fin, string& infix)  // Function definition for process that takes two formal parameters both being passed by reference
{
    string infixws;     // Local string type declared to hold the infix notation along with the whitespace read from the file
    char hold;          // Local char type declared to hold each char read from the file to be used in a loop to skip over the whitespace read from the file

    title();            // Function call to title to display the title of the program to the console
    getline(fin >> skipws,infixws);     // Priming read call to getline to read the data from the file using the ifstream fin along with the extraction operator and store the data in the string argument infixws

    while(!fin.eof())                   // While loop that continues to read from the file until end of the file is reached
    {
        for (int i =0; i < infixws.length(); i++)  // For loop that reads the length of what is stored in the string variable
        {
            hold = infixws.at(i);       // Each character is stored in the hold variable while being cycled through the for loop

            if (hold != ' ')            // if statement to check each character stored in the hold variable to check for whitespace
            {
                infix.push_back(hold);   // if the character in the hold variable is not whitespace then it uses push_back to store the result in the infix string variable being passed by reference through the function. The result is the infix without the whitespace read from the file
            }
        }
        cout << setw(31) << infixws << "   ";  // cout statement using setw for proper spacing that displays the string to the console
        fout << setw(31) << infixws << "   ";  // cout statement using setw for proper spacing that displays the string to the output file
        infixToPostFix(infix);                 // Function call to infixToPostFix that take one argument of type string to be converted to post fix notation
        infix = "";                            // Clears out what is stored in the string variable infix so it can be used again to continue storing data from the file
        getline(fin >> skipws, infixws, '\n'); // Call to getline to continue reading data from the file using newline as a delim
    }
}


void title()                // Function definition for title function that is void and takes no parameters
{
    cout << "---------------------------------------------------------------"           // cout statement for the boarder of the program that outputs it to the console
         << "\n\n" << "T H E    I N F I X    T O    P O S T F I X    C O N V E R T E R" // cout statement for the title of the program that outputs it to the console with newline characters for proper spacing
         << "\n\n" << "---------------------------------------------------------------" // cout statement for the boarder of the program that outputs it to the console
         << "\n\n" << setw(50) << "Written By David Butler & Justin King"               // cout statement for the names of the program authors that outputs it to the console with setw for proper spacing
         << "\n\n\n" << "A L G E B R A I C     I N F I X   R P N     P O S T F I X      "       // cout statement for the title of the program that outputs it to the console with newline characters for proper spacing
         << "\n" << "-------------------------------   -----------------------------" << "\n\n";    // cout statement for the title of the program that outputs it to the console with newline characters for proper spacing

    fout << "---------------------------------------------------------------"           // cout statement for the boarder of the program that outputs it to the output file
         << "\n\n" << "T H E    I N F I X    T O    P O S T F I X    C O N V E R T E R" // cout statement for the title of the program that outputs it to file with newline characters for proper spacing
         << "\n\n" << "---------------------------------------------------------------" // cout statement for the boarder of the program that outputs it to the file
         << "\n\n" << setw(50) << "Written By David Butler & Justin King"               // cout statement for the names of the program authors that outputs it to the file with setw for proper spacing
         << "\n\n\n" << "A L G E B R A I C     I N F I X   R P N     P O S T F I X      "       // cout statement for the title of the program that outputs it to the file with newline characters for proper spacing
         << "\n" << "-------------------------------   -----------------------------" << "\n\n";    // cout statement for the title of the program that outputs it to file with newline characters for proper spacing

}
