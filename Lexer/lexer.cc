/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string reserved[] = { "END_OF_FILE",
    "IF", "WHILE", "DO", "THEN", "PRINT",
    "PLUS", "MINUS", "DIV", "MULT",
    "EQUAL", "COLON", "COMMA", "SEMICOLON",
    "LBRAC", "RBRAC", "LPAREN", "RPAREN",
    "NOTEQUAL", "GREATER", "LESS", "LTEQ", "GTEQ",
    "DOT", "NUM", "ID", "ERROR",
    "REALNUM", "BASE08NUM", "BASE16NUM" 
    // TODO: Add labels for new token types here (as string)
};

#define KEYWORDS_COUNT 5
string keyword[] = { "IF", "WHILE", "DO", "THEN", "PRINT" };

void Token::Print()
{
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
}

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace()
{
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanNumber()
{
    char c, d, e;
    bool isoctdigit=true;
    bool ishexdigit=false; // is there a 'a','b','c','d','e'
    bool validbase=false; // valid values are x16 and x08
    std::string hexnum;

    input.GetChar(c);
    if (isdigit(c)) {
        if (c == '0') {
            tmp.lexeme = "0";
        } else {
            tmp.lexeme = "";
            while (!input.EndOfInput() && isdigit(c)) {
		if ((c == '8') || (c == '9'))
		    isoctdigit = false;
                tmp.lexeme += c;
                input.GetChar(c);
            }
            if (!input.EndOfInput()) {
                input.UngetChar(c);
            }
        }
        // TODO: You can check for REALNUM, BASE08NUM and BASE16NUM here!
	// check for REALNUM
	input.GetChar(c);

        if (!input.EndOfInput() && isxdigit(c)) { // getting HEXNUM scanned
            while (!input.EndOfInput() && isxdigit(c)) {
		ishexdigit = true;
		hexnum.push_back(c);
                input.GetChar(c);
            }
	}

	if (!input.EndOfInput() && (c == 'x'))  // check for BASE08NUM or BASE16NUM
	    {
    	       input.GetChar(d);
	       if(!input.EndOfInput() && (d == '1')) // valid BASE16NUM
	          {
		    input.GetChar(e);
	   	    if(!input.EndOfInput() && (e == '6')) // valid BASE16NUM
		    {
		       validbase = true;
		       tmp.lexeme += hexnum;
	               tmp.lexeme += c;
	               tmp.lexeme += d;
	               tmp.lexeme += e;
        	       tmp.token_type = BASE16NUM;
		    }
		    else
		    {
		       input.UngetChar(e);
		       input.UngetChar(d);
		       input.UngetChar(c);
	       	       for(auto it=hexnum.rbegin(); it!=hexnum.rend(); ++it)
	       		{
	          	   input.UngetChar(*it);
	       		}
        	       tmp.token_type = NUM;
		    }
	          }
		else if(isoctdigit && !input.EndOfInput() && (d == '0')) // valid BASE08NUM
		   {
		     input.GetChar(e);
		     if(!input.EndOfInput() && (e == '8')) // valid BASE08NUM
			{
			   validbase = true;
		           tmp.lexeme += c;
		           tmp.lexeme += d;
		           tmp.lexeme += e;
	        	   tmp.token_type = BASE08NUM;
			}
			else
			{
			   input.UngetChar(e);
			   input.UngetChar(d);
			   input.UngetChar(c);
	       		   for(auto it=hexnum.rbegin(); it!=hexnum.rend(); ++it)
	       		   {
	          	      input.UngetChar(*it);
	       		   }
	        	   tmp.token_type = NUM;
			}
		   }
	        else
		   {
		       	input.UngetChar(d);
		       	input.UngetChar(c);
	       		for(auto it=hexnum.rbegin(); it!=hexnum.rend(); ++it)
	       		{
	          	   input.UngetChar(*it);
	       		}
        	       	tmp.token_type = NUM;
		   }
       	      tmp.line_no = line_no;
       	      return tmp;
	    }
	
	else if (c != '.') // expected a x but did not get it
	    {
	       input.UngetChar(c);
	       for(auto it=hexnum.rbegin(); it!=hexnum.rend(); ++it)
	       {
	          input.UngetChar(*it);
	       }
	    }
	
	if (!input.EndOfInput() && (c == '.')) { // check for REALNUM
	    input.GetChar(d);
            //tmp.lexeme += c;
	    auto disdigit = false;
	    auto dotadded = false;
	    while (!input.EndOfInput() && isdigit(d)) {
		disdigit = true;
		if (!dotadded)
                {
		    tmp.lexeme += c;
		    dotadded = true;
		}
                tmp.lexeme += d;
                input.GetChar(d);
	    }
            if (!input.EndOfInput() && disdigit) {
                input.UngetChar(d);
	        tmp.token_type = REALNUM;
            }
	    else
	    {
		if (!input.EndOfInput() && !disdigit)
		{
                    input.UngetChar(d);
                    input.UngetChar(c);
		}
	        tmp.token_type = NUM;
	    }
	}
	else
	{
	    //cout<<"cNUM: " << c << endl;
            //input.UngetChar(c);
	    tmp.token_type = NUM;
	}
        tmp.line_no = line_no;
        return tmp;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
        tmp.line_no = line_no;
        return tmp;
    }
}

Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

// you should unget tokens in the reverse order in which they
// are obtained. If you execute
//
//    t1 = lexer.GetToken();
//    t2 = lexer.GetToken();
//    t3 = lexer.GetToken();
//
// in this order, you should execute
//
//    lexer.UngetToken(t3);
//    lexer.UngetToken(t2);
//    lexer.UngetToken(t1);
//
// if you want to unget all three tokens. Note that it does not
// make sense to unget t1 without first ungetting t2 and t3
//
TokenType LexicalAnalyzer::UngetToken(Token tok)
{
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken()
{
    char c;

    // if there are tokens that were previously
    // stored due to UngetToken(), pop a token and
    // return it without reading from input
    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }

    SkipSpace();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    switch (c) {
        case '.':
            tmp.token_type = DOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '*':
            tmp.token_type = MULT;
            return tmp;
        case '=':
            tmp.token_type = EQUAL;
            return tmp;
        case ':':
            tmp.token_type = COLON;
            return tmp;
        case ',':
            tmp.token_type = COMMA;
            return tmp;
        case ';':
            tmp.token_type = SEMICOLON;
            return tmp;
        case '[':
            tmp.token_type = LBRAC;
            return tmp;
        case ']':
            tmp.token_type = RBRAC;
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = LESS;
            }
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = GREATER;
            }
            return tmp;
        default:
            if (isdigit(c)) {
                input.UngetChar(c);
                return ScanNumber();
            } else if (isalpha(c)) {
                input.UngetChar(c);
                return ScanIdOrKeyword();
            } else if (input.EndOfInput())
                tmp.token_type = END_OF_FILE;
            else
                tmp.token_type = ERROR;

            return tmp;
    }
}

int main()
{
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }
}
