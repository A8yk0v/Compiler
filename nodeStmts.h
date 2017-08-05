#ifndef NODESTMTS_H
#define NODESTMTS_H

#include "nodeBase.h"

class NodeStmts : public NodeBase
{
public:
    NodeStmts(NodeBase *stmt, NodeStmts *stmts);

private:
    NodeBase *stmt;
    NodeStmts *stmts;
};

#endif // NODESTMTS_H
