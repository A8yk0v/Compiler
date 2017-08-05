#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <unordered_map>

#include "lexer.h"
#include "nodeBase.h"
#include "nodeFunction.h"
#include "nodeStmts.h"
#include "nodeDeclare.h"

enum states {
              delta, e1, P1, func1, func2, P2, _void,
              id1, S1, SS1, F, id2, r, number, t1, _int, id3,
              t2, e2, stmt1, e3, stmts2, _if, S2, id4, SS2, stmt2,
              t3, stmts1, FF                                   };

class Parser
{
public:
    Parser(Lexer &lexer, std::unordered_map<std::string, Token> &symbolTable);

    NodeBase* go();

private:
    // Ссылка на таблицу символов
    std::unordered_map<std::string, Token> &symbolTable;

    Lexer &lexer;

    std::stack<states> stack;

    std::stack<NodeBase*> attr_stack;
};

#endif // PARSER_H
