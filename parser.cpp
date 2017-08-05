#include "parser.h"

// test
#include <iostream>

Parser::Parser(Lexer &lex, std::unordered_map<std::string, Token> &sTable)
    : symbolTable(sTable), lexer(lex)
{
    stack.push(delta);
}

NodeBase* Parser::go()
{
    Token T("!", "!");

    bool flag = true;
    while ( flag )
    {
        switch ( stack.top() )
        {
        case delta:
            T = lexer.getNextToken();
            if ( T.name == "void" )
                stack.push(_void);
            else if ( T.name == "End" )
                stack.push(e1);
            break;

        case P1:
            T = lexer.getNextToken();
            if ( T.name == "End" )
                std::cout << "Ok" << std::endl;
                flag = false;
            break;

        case e1:
            if ( stack.top() == delta )
                stack.push(P1);
            else
                stack.push(P2);
            break;

        case func1:
            T = lexer.getNextToken();
            if ( T.name == "End" )
                stack.push(P2);
            break;

        case P2:
            stack.pop();
            stack.pop();
            stack.push(P1);
            break;

        case _void:
            T = lexer.getNextToken();
            if ( T.type == "id" )
                stack.push(id1);
            break;

        case id1:
            T = lexer.getNextToken();
            if ( T.name == "(" )
                stack.push(S1);
            // !!!
            std::cout << " function ()\n{\n";
            // e!!
            break;

        case S1:
            T = lexer.getNextToken();
            if ( T.name == ")" )
                stack.push(SS1);
            break;

        case SS1:
            T = lexer.getNextToken();
            if ( T.name == "{" )
                stack.push(F);
            break;

        case F:
            T = lexer.getNextToken();
            if ( T.name == "if" )
                stack.push(_if);
            else if ( T.name == "int" )
                stack.push(_int);
            else if ( T.name == "}" )
                stack.push(e2);
            else if ( T.type == "id" )
                stack.push(id2);
            break;

        case id2:
            T = lexer.getNextToken();
            if ( T.name == "=" )
                stack.push(r);
            break;

        case r:
            T = lexer.getNextToken();
            if ( T.type == "number" )
                stack.push(number);
            break;

        case number:
            T = lexer.getNextToken();
            if ( T.name == ";" )
                stack.push(t1);
            break;

        case t1:
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            if (stack.top() == F || stack.top() == stmt1 )
                stack.push(stmt1);
            else
                stack.push(stmt2);
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            //attr_stack.push(new NodeDeclare() );

            break;

        case _int:
            T = lexer.getNextToken();
            if ( T.type == "id" )
                stack.push(id3);
            break;

        case id3:
            T = lexer.getNextToken();
            if ( T.name == ";" )
                stack.push(t2);
            break;

        case t2:
            stack.pop();
            stack.pop();
            stack.pop();
            if (stack.top() == F || stack.top() == stmt1 )
                stack.push(stmt1);
            else
                stack.push(stmt2);
            // !!!
            std::cout << "int id;\n";
            // e!!
            break;

        case e2:
            stack.push(stmts1);
            break;

        case stmt1:
            if ( lexer.lookNextToken().name == "}" )
            {
                stack.push(e3);
                break;
            }
            T = lexer.getNextToken();
            if ( T.name == "if" )
                stack.push(_if);
            else if ( T.name == "int" )
                stack.push(_int);
            else if ( T.type == "id" )
                stack.push(id2);
            break;

        case e3:
            stack.push(stmts2);
            break;

        case stmts2:
            stack.pop();
            stack.pop();
            if ( stack.top() == stmt1 )
                stack.push(stmts2);
            else
                stack.push(stmts1);
            break;

        case _if:
            T = lexer.getNextToken();
            if ( T.name == "(" )
                stack.push(S2);
            break;

        case S2:
            T = lexer.getNextToken();
            if ( T.name == "id" )
                stack.push(id4);
            break;

        case SS2:
            T = lexer.getNextToken();
            if ( T.name == "int" )
                stack.push(_int);
            else if ( T.name == "if" )
                stack.push(_if);
            else if ( T.type == "id" )
                stack.push(id2);
            break;

        case stmt2:
            T = lexer.getNextToken();
            if ( T.name == ";" )
                stack.push(t3);
            break;

        case t3:
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.push(stmt1);
            break;

        case stmts1:
            T = lexer.getNextToken();
            if ( T.name == "}" )
                stack.push(FF);
            break;

        case FF:
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.pop();
            stack.push(func1);
            // !!!
            std::cout << "}\n";
            // e!!
            break;
        } // End of switch
    } // End of while


    // !!!!!!
    NodeBase tmp;
    return &tmp;
}
