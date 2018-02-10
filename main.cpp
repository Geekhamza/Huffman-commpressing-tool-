#include <iostream>
#include "build_tree.h"
using namespace std;
char mat[5][30];
void print_mat()
{
    for(int i=0; i<5; i++)
    {
        cout<<'\t'<<'\t';
        for(int j=0; j<30; j++)
        {
            cout<<mat[i][j];
        }
        cout<<endl;
    }
    return ;
}
void print(string s)
{
    memset(mat,' ',sizeof mat);
    int next_char=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<30; j++)
        {
            if(i==0||i==4||((j==0||j==29)))
                mat[i][j]='#';
            else if(i==2&&(j>5)&&next_char<s.length())
            {
                mat[i][j]=s[next_char];
                next_char++;
            }
        }
    }
    print_mat();
    return ;
}
int main()
{

    // DO NOT PUT THIS INSIDE A CLASS!!!!!!!!!!
    // DO NOT PUT THIS INSIDE A CLASS!!!!!!!!!!
    // DO NOT PUT THIS INSIDE A CLASS!!!!!!!!!!
    // THIS IS PART OF THE MAIN PROGRAM
    print("huffways v1.0");
    cout<<endl;
    string path;
    string Decrypt_path;
    string Crypted_text;
    string Table_text;
    string TablePath;
    build_tree build_the_tree;
    string buffer;

    while(true)
    {
        cout<<" Write the path to the txt file :"<<endl;
        cin>>path;
        // read data into buffer
        buffer=build_the_tree.ReadData(path,"txt");
        if(buffer=="")
        {
            cout<<"Not a text file or Inexistant file"<<endl;

        }
        else
        {

            break;
        }

    }
    // transform data to map
    map<char,int>m=build_the_tree.Calculate_occurence(buffer);
    // logic is here
    Node *root,*tree;
    tree=build_the_tree.allocate_tree();
    root=tree;
    int taille=build_the_tree.generate_Nodes(m,root);
    tree=build_the_tree.build(root,taille);
    build_the_tree.get_path(tree,"");
    build_the_tree.generate_table();
    build_the_tree.CryptData(buffer);
    cout<<" Finished Crypting ..."<<endl;
    cout<<" Starting Decryption...\n"<<endl;
    //decryption
    while(true)
    {
        cout<<" Path To Crypted File ..."<<endl;
        cin>>Decrypt_path ;
        Crypted_text= build_the_tree.ReadDataBinary(Decrypt_path,"hfw");
        //cout<<"this is crypted text size  "<<Crypted_text.size()<<endl;

        if(Crypted_text=="")
        {
            cout<<"Not a Valid file or inexistant "<<endl;
        }
        else
        {
            while(true)
            {
                cout<<" Path To Coding Table ...\n";
                cin>>TablePath;
                Table_text= build_the_tree.ReadData(TablePath,"hft");
                if(Table_text!="")
                    break;
                else
                    cout<<" Verify path to the table \n";
            }
            map<string,char>Decrypt_map=build_the_tree.createDecryptMap(Table_text);
            build_the_tree.decrypt(Decrypt_map,Crypted_text);
            cout<<"done\n";
            printf(" The Ratio is :%.4f\n ",100-(100.0*(1.0*Crypted_text.length())/(1.0*buffer.length())));
            char ext;
            cout<<"Press any key to quit \n";
            cin>>ext;
            break;
        }

    }


// test


    return 0;
}
