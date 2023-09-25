#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
class RBTree
{
    Node<T>* root=nullptr;
  //  T t_val;
    int size=0;
    bool IsRightSon(Node<T>*node){
        if(node->parent==nullptr)
            return false;
        if(node->parent->right==node)
            return true;
        return false;
    }
    bool IsLeftSon(Node<T>*node){
        if(node->parent==nullptr)
            return false;
        if(node->parent->left==node)
            return true;
        return false;
    }
    void SetRoot(Node<T>*&root) {
        if(root==nullptr)
            return;
        while(root->parent!=NULL) {
            root=root->parent;
        }
    }
    Node<T>* InsertBin(Node<T>*node,const T&val,Node<T>*&ret,bool& OK){
        if(node==nullptr){
            node = new Node<T>(val,BLACK);
            ret = node;
            return node;
        }
        if(val==node->data){
            OK=0;
        }
        if(val<node->data){
            node->left = InsertBin(node->left,val,ret,OK);
            node->left->parent=node;
        }
        else if(val>node->data){
            node->right = InsertBin(node->right,val,ret,OK);
            node->right->parent=node;
        }
        return node;
    }
    Node<T>* GetUncle(Node<T>*node){
        T help;
        Node<T> save(help);
        if(node->parent==nullptr)
            return nullptr;
        node=node->parent;
        save=*node;
        if(node->parent==nullptr)
            return nullptr;
        node=node->parent;
        if(node->left == nullptr||node->right== nullptr)
            return nullptr;
        if(*(node->left)==save)
            return node->right;
        else if(*(node->right)==save)
            return node->left;
        return nullptr;
    }
    Node<T>*GetGrandFather(Node<T>*node){
        if(node->parent==nullptr)
            return nullptr;
        node=node->parent;
        return node->parent;
    }
    Node<T>*GetBrother(Node<T>*node){
        if(node->parent==nullptr)
            return nullptr;
        if(IsRightSon(node))
            return node->parent->left;
        else
            return node->parent->right;

    }

    Node<T>* LeftRotation(Node<T>* x){
       Node<T>*y=x->right;
       x->right=y->left;
       if(y->left!= nullptr)
           y->left->parent=x;

       y->parent=x->parent;
       if(IsLeftSon(x))
           x->parent->left=y;
       else if(x->parent!=nullptr)
           x->parent->right=y;
       y->left=x;
       x->parent=y;
       return y;
    }
    Node<T>* RightRotation(Node<T>* y){//передаем узел, который был ниже, а должен быть верхушкой поддерева
        Node<T>*x=y->left;
        y->left=x->right;
        if(x->right!= nullptr)
            x->right->parent=y;
        x->parent=y->parent;
        if(y->parent!= nullptr) {
            if (IsRightSon(y))
                y->parent->right = x;
            else if(y->parent!=nullptr)
                y->parent->left = x;
        }
        x->right=y;
        y->parent=x;
        return x;
    }
    void deleteFixup(Node<T>* node, Node<T>* parent)
    {
        Node<T>* sibling;
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == parent->left) {
                sibling = parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    LeftRotation(parent);
                    sibling = parent->right;

                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;

                }
                else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        RightRotation(sibling);
                        sibling = parent->right;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->right->color = BLACK;
                    LeftRotation(parent);
                    node = root;
                    break;
                }
            }
            else {
                sibling = parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    RightRotation(parent);
                    sibling = parent->left;
                }


                if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;

                }
                else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        LeftRotation(sibling);
                        sibling = parent->left;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->left->color = BLACK;
                    RightRotation(parent);
                    node = root;
                    break;
                }
            }
        }
        if (node != nullptr) {
            node->color = BLACK;
        }
    }
    Node<T>*successor(Node<T>* node) const  // ищем следующего по увеличению элемента.
    {
        if (node->right != nullptr) {
            node = node->right;
            while (node->left != nullptr)
                node = node->left;
            return node;
        }
        Node<T>* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;

        }
        return parent;
    }
    bool BinIsCorrect(){
        vector<T>vec;
        ToVector(root,vec);
        bool sorted = is_sorted(vec.begin(), vec.end());
        return sorted;
    }
    Node<T>* SearchRec(Node<T>* node, const T& value) {
        if (node == nullptr)
            return nullptr; // Элемент не найден
        if (value == node->data)
            return node; // Элемент найден
        else if (value < node->data)
            return SearchRec(node->left, value);
        else
            return SearchRec(node->right, value);
    }
    void ToVector(Node<T>*node,vector<T>&vec){
        if(node==nullptr)
            return;
        ToVector(node->left,vec);
        vec.push_back(node->data);
        ToVector(node->right,vec);
        return;
    }
public:
    RBTree(T t_val){
        t_val=t_val;
        root=nullptr;
    };
    void Insert(const T& val) {
        int ty=0;
        ty++;
        Node<T>* new_node;
        bool OK=1;
        InsertBin(root,val,new_node,OK);
        if(OK==0)
            return;
        size++;
        if(size==1){
            root=new_node;
            new_node->color=BLACK;
            return;
        }
        new_node->color=RED;
        while(new_node->parent!=nullptr){//GetGrandFather(new_node)!=NULL&& GetGrandFather(new_node)!=root
            Node<T>*p=new_node->parent;
            if (new_node->color == RED && p->color == RED) {
                Node<T>* u = GetUncle(new_node);
                if(u != nullptr && u->color==RED){
                    p->color=BLACK;
                    u->color=BLACK;
                    p->parent->color = RED;
                    p = p->parent;
                }
                else{
                    bool p_is_r_s=IsRightSon(p);
                    if(IsRightSon(p)^ IsRightSon(new_node)){
                        p=p_is_r_s? RightRotation(p): LeftRotation(p);
                    }
                    p=p_is_r_s?LeftRotation(p->parent): RightRotation(p->parent);
                    p->color = BLACK;
                    if(p->left!= nullptr) p->left->color = RED;
                    if(p->right!= nullptr) p->right->color = RED;
                }
            }
            new_node = p;
        }
        SetRoot(root);
        root->color=BLACK;
    };


    bool Search(const T& value){
        if(SearchRec(root,value)== nullptr)
            return false;
        else
            return true;
    }
    int Size(){
        return size;
    }
    Node<T> *Root(){
        return root;
    }
    void PrintAll(Node<T>*node,bool flag=0){
        if(node == nullptr) {
            if(size==0)
            cout<<endl<<"Empty"<<endl;
            return;
        }
        PrintAll(node->left);
        cout<<"val: "<<node->data<<"  color: "<<node->color;
        if(node->parent== nullptr)
            cout<<"  parent: "<<"null ";
        else
            cout<<"  parent: "<<node->parent->data<<"  ";
        if(node->left== nullptr)
            cout<<", left: "<<"null ";
        else
            cout<<", left: "<<node->left->data<<"  ";
        if(node->right== nullptr)
            cout<<", right: "<<"null ";
        else
            cout<<", right: "<<node->right->data<<"  ";
        if(node->parent== nullptr)
            cout<<"                                  root";
        cout<<endl;
        PrintAll(node->right);
        return;
    };


    void Clear(){
        vector<T>vec;
        ToVector(root,vec);
        for(auto e:vec){
            Remove(e);
        }
    }

    bool Remove(const T& word)
    {
        Node<T>* node = SearchRec(root,word );   // node - указатель на узел который нужно удалить

        if (node == nullptr)
            return 0; // слово не найдено
        size--;
        Node<T>* toDelete;
        Node<T>* toFix;

        if (node->left == nullptr || node->right == nullptr)
            toDelete = node;
        else
            toDelete = successor(node);
        if (toDelete->left != nullptr)
            toFix = toDelete->left;
        else
            toFix = toDelete->right;

        if (toFix != nullptr)
            toFix->parent = toDelete->parent;
        if (toDelete->parent == nullptr)
            root = toFix;
        else if (toDelete == toDelete->parent->left)
            toDelete->parent->left = toFix;
        else
            toDelete->parent->right = toFix;
        if (toDelete != node)
            node->data = toDelete->data;
        if (toDelete->color == BLACK) {
            deleteFixup(toFix, toDelete->parent);
        }
        delete toDelete;
        SetRoot(root);
        return 1;
    }

};

#endif // TREE_H
