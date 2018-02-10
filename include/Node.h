#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node
{
    friend class build_tree;

protected:
 int value;
    char name;
    Node* left_child;
    Node* right_child;
public:

    Node();
    Node(int, char, Node *, Node *);
    Node(const Node &N);
    bool compare(const Node&);

    virtual ~Node();


};

#endif // NODE_H
