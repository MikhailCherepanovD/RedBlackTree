#ifndef NODE_H
#define NODE_H
class Tree;
enum COLOR{
    RED,
    BLACK
};
template <typename T>
class Node
{
public:
    T data;
    COLOR color;
    Node* parent;
    Node*left;
    Node* right;
    friend class Tree;

     Node(){
         data=0;
         color=BLACK;
         parent=nullptr;
         left=nullptr;
         right=nullptr;
     };
    Node(const T& d,COLOR c=BLACK){
        data=d;
        color=c;
        parent=nullptr;
        left=nullptr;
        right=nullptr;
    }
    Node(const T& d,COLOR c,Node* p){
        data=d;
        color=c;
        parent=p;
        left=nullptr;
        right=nullptr;
    }
    Node& operator=(const Node& other) {
        if (this != &other) {
            data = other.data;
            color = other.color;
            parent = other.parent;
            left = other.left;
            right = other.right;
        }
        return *this;
    }
    bool operator==(const Node& other) const {
        return (data == other.data &&
                color == other.color &&
                parent == other.parent &&
                left == other.left &&
                right == other.right);
    }
};

#endif // NODE_H
