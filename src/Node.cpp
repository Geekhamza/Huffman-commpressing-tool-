#include "Node.h"

Node::Node()
{
    value=0;
    name=' ';
    left_child=NULL;
    right_child=NULL;

}

Node::Node(int occ, char n, Node * lc, Node  *rc)
{
    value=occ;
    name=n;
    left_child=lc;
    right_child=rc;
}

Node::Node(const Node &N)
{
    value=N.value;
    name=N.name;
    left_child=N.left_child;
    right_child=N.right_child;

}


/*returns true if current node's occurence is bigger
than the one passed in parameter,
if they're equal we compare the names */

bool Node::compare(const Node &N)
{
    if(value==N.value)
        return(name>N.name);
    return(value>N.value);
}
Node::~Node()
{
   ///no tables
}
