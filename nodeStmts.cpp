#include "nodeStmts.h"

NodeStmts::NodeStmts(NodeBase *_stmt, NodeStmts *_stmts)
    : stmt(_stmt), stmts(_stmts)
{

}
