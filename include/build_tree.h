#ifndef BUILD_TREE_H
#define BUILD_TREE_H
#include"Node.h"
#include <bits/stdc++.h>

// a class that create a binary tree from a given map
// the public function is in the bottom
// to start the function just give her the map
// the function will return a pointer to the top of the tree
class build_tree
{
public:
    map<char,string> Coding;

    class Compare
    {
    public:
        bool operator() (Node *a, Node *b)
        {

            int i,j;
            i=(a->value);
            j=(b->value);
            return j<i;
        }
    };
// read from text & calculate occ
    map<char, int>  Calculate_occurence(string txt);
//readt text function (from file)
    string ReadData(string path,string extention);

// transform text readed from table file to map
    map<string,char> createDecryptMap(string text );

// generate coding table
    void generate_table();

    // decrypt function
    void decrypt(map<string,char> m,string encrypted_text) ;


// reccur down and get leafs values and path
//assemble two Node
    void assemble(Node *left, Node *right,Node *position);
//allocate memory space for the tree
    Node *allocate_tree();
//build the tree
    Node *build(Node *root,int taille);
//check for the existance of a certain member in a map<char,int>
    bool exist(map<char,int> m,char element);
// function that take map and transform it into Nodes and give back the number of generated Nodes
//input map  && pointer to Node
//output number of generated Nodes
    int generate_Nodes(map<char,int> m,Node *root) ;
// explore the tree  and fill the map
    void get_path(Node *leaf,string path);
    // crypt data function
    void CryptData(string text);
    string ReadDataBinary(string path,string extention);


    string Binary_to_Ascii(string);
    string Ascii_to_Binary(string,int);


};
#endif // BUILD_TREE_H
