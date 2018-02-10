#include "build_tree.h"
#include"Node.h"
#include <bits/stdc++.h>

// read from text & calculate occ
map<char, int>  build_tree::Calculate_occurence(string txt)
{
    map<char, int> Frequency;

    for(char& c : txt)
        if (!Frequency[c])
            Frequency[c] = count(txt.begin(), txt.end(), c);

    return Frequency;
}


///readt text function (from file)
string build_tree::ReadData(string path,string extention)
{
    ifstream f(path.c_str());
    if(path.substr(path.find_last_of(".")+1) != extention)
    {

        return "";
    }
    else if (!f.is_open())
        return "";
    else
    {

        stringstream buffer;
        buffer << f.rdbuf();
       //s cout<< " this is buffer "<<buffer.str()<<endl;
         return buffer.str();
    }
    f.close();
}


string build_tree::ReadDataBinary(string path,string extention)
{
    ifstream is(path.c_str(),std::ifstream::binary);
     if(path.substr(path.find_last_of(".")+1) != extention)
    {
            is.close();

        return "";
    }
    else if (!is.is_open())
    {
            is.close();
        return "";

    }
    else
    {
     // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);
    char * buffer = new char [length];

          std::cout << "Reading " << length << " characters... \n";
    // read data as a block:
    is.read (buffer,length);

    if (is)
      std::cout << "all characters read successfully.\n";
    else
      std::cout << "error: only " << is.gcount() << " could be read\n";
    is.close();

    // ...buffer contains the entire file...
    string res="";
    //printf("%c",buffer[i]),
    for(int i=0;i<length;i++)
    res+=buffer[i];
    is.close();
    delete[] buffer;
    return res;
    }
}


// transform text readed from table file to map
map<string,char> build_tree::createDecryptMap(string text )
{
    map<string, char > res;
    string buff_code="";
    char carac;
    bool Reading_char_or_code=true;
    for(int i=0; i<text.length(); i++)
    {
        if(Reading_char_or_code)
            carac=text[i],Reading_char_or_code=0,i+=1;
        else
        {
            if(text[i]!='0'&&text[i]!='1')
                Reading_char_or_code=1,res[buff_code]=carac,buff_code="";
            else
                buff_code+=text[i];
        }
    }
    return res;
}
// generate coding table
void build_tree::generate_table()
{

    std::ofstream ofs ("table.hft", std::ofstream::out);
    for(map<char,string>::iterator it=Coding.begin(); it!=Coding.end(); it++)
        ofs <<it->first<< " "<<it->second<<endl;
    ofs.close();

    return;


}

// decrypt function
void build_tree::decrypt(map<string,char> m,string encrypted_text)
{
    int i=0;
    int rest_from_encryption=encrypted_text[encrypted_text.length()-1]-'0';
    encrypted_text.pop_back();
    string tmp_encrypted_text=Ascii_to_Binary(encrypted_text,rest_from_encryption);
   // cout<<tmp_encrypted_text<<endl;
    string text="",tmp="";
    map<string,char>::iterator pos;
    std::ofstream ofs ("Original.txt", std::ofstream::out);
    while(i<tmp_encrypted_text.size())
    {
        tmp+=tmp_encrypted_text[i];
        // GREEDY IMPLEMENTATION
        if (m.find(tmp)!=m.end())
        {
            pos=m.find(tmp);
            text+=(pos->second);
            tmp="";
        }
        i++;
    }
    ofs<<text;
    ofs.close();
    return;
}




// reccur down and get leafs values and path
//assemble two Node
void build_tree::assemble(Node *left, Node *right,Node *position)
{
    position->left_child=left;
    position->right_child=right;
    position->name='0';
    position->value=(left->value)+(right->value);
}
//allocate memory space for the tree
Node *build_tree::allocate_tree()
{
    return (Node*)malloc(512*sizeof(Node));
}
//build the tree
Node *build_tree::build(Node *root,int taille)
{
    Node *tree=root,*left,*right;
    priority_queue<Node*,vector<Node*>,Compare> pq;
    for(int i=0; i<taille; i++)
    {
        pq.push(root+i);
    }
    tree+=taille;
    while(pq.size()!=1)
    {
        right=pq.top();
        pq.pop();
        left=pq.top();
        pq.pop();
        assemble(left,right,tree);
        pq.push(tree);
        tree++;
    }
    return pq.top();
}
//check for the existance of a certain member in a map<char,int>
bool build_tree::exist(map<char,int> m,char element)
{
    return m.find(element)!=m.end();
};
// function that take map and transform it into Nodes and give back the number of generated Nodes
//input map  && pointer to Node
//output number of generated Nodes
int build_tree::generate_Nodes(map<char,int> m,Node *root)
{
    int length=0;
    Node *tree=root;
    char s;
    map<char,int>::iterator pos;
    for(int i=0; i<256; i++)
    {
        if(exist(m,(char)i))
        {
            s=i;
            ((tree+length)->name)=s;
            pos=m.find((char)i);
            (tree+length)->value=pos->second;
            (tree+length)->left_child=NULL;
            (tree+length)->right_child=NULL;
            length++;
        }
    }
    return length;
}
// explore the tree  and fill the map
void build_tree::get_path(Node *leaf,string path)
{


    if(leaf->left_child==NULL && leaf->right_child==NULL)
    {
        if(path=="")
        {
            //its one char text
                    Coding[leaf->name]=("0");
                    return;
        }
        Coding[leaf->name]=(path);
        return ;
    }
    else if(leaf->left_child!=NULL && leaf->right_child!=NULL)
    {
        get_path(leaf->right_child,path+"1");
        get_path(leaf->left_child,path+"0");
        return ;
    }
    else if(leaf->right_child==NULL)
    {
        get_path(leaf->left_child,path+"0");
        return ;
    }
    else
    {
        get_path(leaf->right_child,"1");
        return ;
    }
    return ;
}

string build_tree::Binary_to_Ascii(string input )
{
    int length = (input.length());     //get length of string
    int z = 0;   //counter used
    string res="";
    for(int x = 0; x < ((length / 7)+((length % 7)!=0)); x++)     //reading in bytes. total characters = length / 8
    {
        int tmp_int=0;
        for(int i=0; i<7&&((x*7+i)<length); i++)
        {
            tmp_int+=((int)pow(2,(6-i))*(input[x*7+i]=='1'));


        }
        res+=(char)tmp_int;
    }
    int rest=(((length / 7)+((length % 7)!=0))*7)-length;
    //cout<<" the rest is "<<res<<endl;
    return res+(char)(rest+'0');
}

string build_tree::Ascii_to_Binary(string input,int rest_from_encryption)
{

    int ascii;           // used to store the ASCII number of a character
    int length = (input.length());        //find the length of the user's input
    //cout<< " length of the binary input "<<input.length()<<endl;
    string res="";
     for(int x = 0; x < length; x++)          //repeat until user's input have all been read
        // x < length because the last character is "\0"
    {
         ascii=(int)input[x];
         //cout<<" asciuii "<<ascii<< " "<<input[x]<<endl;
        for(int i=0;i<7;i++)
            if((1<<(6-i))&ascii)
            res+='1';
            else
            res+='0';
     }
     while(rest_from_encryption--)
        res.pop_back();
    return res;

}
void build_tree::CryptData(string text)
{
    string tmp="";
    std::ofstream ofs ("CryptedText.hfw", ofstream::binary);

    for(int i=0; i<text.length(); i++)
    {
        tmp+=Coding[text[i]];
    }
   // ofs<< " the crypted file size is "<<Binary_to_Ascii(tmp).size()<<endl;
    ofs<<Binary_to_Ascii(tmp);
    ofs.close();


    return ;
}

