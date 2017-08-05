#ifndef NODEFUNCTION_H
#define NODEFUNCTION_H

#include "nodeBase.h"
#include "nodeStmts.h"
#include "token.h"

class NodeFunction : public NodeBase
{
public:
    NodeFunction(Token *id, NodeStmts *stmts);

private:
    Token *id;
    NodeStmts *stmts;
};

#endif // NODEFUNCTION_H
