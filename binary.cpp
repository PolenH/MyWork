#include "binary.h"
using namespace std;

// partners: sv34, hpalin2, nstse2

/***
A Tree Node constructor. Set all the Part
member variables (key_, data_, left, right)
of the Node class.
of the Node class.

of the Node class.

Input:
T key - The key for the node
Y data - The actual value from the node
Output:
N/A
***/
template <class T, class Y>
Node<T, Y>::Node(T key, Y data){
    /**
        Your code goes below here
    **/
    left = NULL;
    right = NULL;
    key_ = key;
    data_ = data;
}

/***
A Node member getter function. This returns the
key of the node.
key of the node.

key of the node.

Input:
N/A
Output:
T - returns the key of the node that is of type T
***/
template <class T, class Y>
T Node<T, Y>::getKey(){
    /**
        Your code goes below here
    **/
    return key_;
}

/***
A Node member getter function. This returns the
actual data of the node.
actual data of the node.

actual data of the node.

Input:
N/A
Output:
Y - Returns the data of the node that is of type Y
***/
template <class T, class Y>
Y Node<T, Y>::getData(){
    /**
        Your code goes below here
    **/
   return (Y) data_;
}

/***
A Node member setter function. This sets the key
of a Node.
Input:
T key - Sets the key of the Node of type T
Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setKey(T key){
    /**
        Your code goes below here
    **/
    key_ = key;
}

/***
A Node member setter function. This sets the actual
data of a Node.
Input:
Y data - Sets the value of the Node of type Y
Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setData(Y data){
    /**
        Your code goes below here
    **/
    data_ = data;
}


/***
The BinaryTree constructor. Implicitly set the
values of the member variables
Input:
N/A
Output:
N/A
***/

template <class T, class Y>
BinaryTree<T,Y>::BinaryTree(){
    /**
        Your code goes below here
    **/
    this->root = NULL;
}


/***
A BinaryTree Member fuction. This function takes in two arguments
and inserts a node. If the key already exists in the tree do nothing.
Input:
Node<T,Y> *parent_node - The current root node
Node<T,Y> *data - The Node that you want to insert into the tree
Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T, Y>::insert_node(Node<T, Y> *parent_node, Node<T, Y> *data) {
    if (parent_node == NULL) {
        //std::cout << "I got no roots";
        this->root = data;
        return;
    }
    if (parent_node->getKey() == data->getKey()) {
        return;
    } else if (parent_node -> getKey() > data -> getKey()) {
        if (parent_node -> left == NULL) {
            parent_node -> left = data;
            return;
        } else {
            insert_node(parent_node -> left, data);
            return;
        }
    } else {
        if (parent_node->right == NULL) {
            parent_node->right = data;
            return;
        } else {
            insert_node(parent_node->right, data);
            return;
        }
    }
}





/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the parent of a node given a key.
If the key does not exist in the tree return NULL.
Input:
T key - The key of the node you are searching for.
Output:
Node<T,Y> * - returns the parent of the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node_parent(T key){
    /**
        Your code goes below here
    **/
    Node<T,Y> * root = this->getRoot();
    if(root == NULL){
        return NULL;
    }
    if(key == root->getKey()){
        return NULL;
    }
    else {
        return find_node_parent(this->getRoot(), key);
    }
    return NULL;
}

/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the node given a key.
If the key does not exist in the tree return NULL.
Input:
T key - The key of the node you are searching for.
Output:
Node<T,Y> * - returns the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node(T key){
    /**
        Your code goes below here
    **/
    //std::cout << "In find_node";
   return find_node(root, key);
}


/***
A BinaryTree Member fuction. This function deletes a node in
the binary tree. If the key does not exist do not do anything.
Input:
T key - The key of the node you are trying to delete.
Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::delete_node(T key){
    /**
        Your code goes below here
    **/
    delete_node(this->getRoot(), key);
}


/***
A BinaryTree helper fuction. This function deletes a node in
the binary tree. If the key does not exist in the tree return NULL.
Input:
T key - The key of the node you are trying to delete.
Node<T,Y>*node - The root of the current subtree
Output:
Node<T,Y> * - The new root since the root can be deleted.
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::delete_node(Node<T,Y>* node, T key){
    /**
        Your code goes below here
    **/
    Node<T, Y>* temp;
    if(node == NULL){
        return node;
    }
    else if(key < node->getKey()){
        node->left = delete_node(node->left, key);
    }
    else if(key > node->getKey()){
        node->right = delete_node(node->right, key);
    }
    else{
        if(node->left == NULL && node->right == NULL) {
            delete(node);
            return NULL;
        }
        else if(node->left == NULL) {
            temp = node->right;
            delete(node);
            return temp;
        }
        else if(node->right == NULL) {
            temp = node->left;
            delete(node);
            return temp;
        }
        else{
            temp = node->right;
            while(temp->left != NULL) {
                temp = temp->left;
            }
            node->setKey(temp->getKey());
            node->setData(temp->getData());
            node->right = delete_node(node->right, temp->getKey());
        }        
    }
   return node;
}


/***
A BinaryTree helper fuction. This function finds the parent node of
a node with a given key for the binary tree. If the key does not exist in the tree return NULL.
Input:
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree
Output:
Node<T,Y> * - Returns the parent of the key you were searching for
***/
template <class T, class Y>
Node<T, Y> *BinaryTree<T, Y>::find_node_parent(Node<T, Y> *node, T key) {
    if (node == NULL || node->getKey() == key) {
        return NULL;
    }
    if ((node->left != NULL && node->left->getKey() == key)) {
        return node;
    } else if (node->right != NULL && node->right->getKey() == key){
        return node;
    }
    if (node->getKey() > key) {
        Node<T,Y> * node_parent = find_node_parent(node->left, key);
        return node_parent;
    } else {
        Node<T,Y> * node_parent =  find_node_parent(node->right, key);
        return node_parent;
    }
}
/***
A BinaryTree helper fuction. This function finds the node with
a given key for the binary tree. If the key does not exist in
the tree return NULL.
Input:
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree
Output:
Node<T,Y> * - Returns the Node in the Tree
              for the key you were searching for
***/
template <class T, class Y>
Node<T, Y> *BinaryTree<T, Y>::find_node(Node<T, Y> *node, T key) {
    //
    if (node == NULL) {
        //std::cout << "NULL" << endl;
        return NULL;
    }

    if (node -> getKey() == key) {
        //std::cout << node -> getKey() << " vs " << key << " equal " << endl;
        return node;
    }
   
    else if (node -> getKey() > key) {
        //std::cout << node -> getKey() << " vs " << key << endl;
        //std::cout << "going left" << endl;
        if(node->left != NULL)
            return find_node(node->left, key);
        else {
            //std::cout << "No left child" << endl;
            return NULL;
        }

    } else {
        //std::cout << node -> getKey() << " vs " << key << endl;
        //std::cout << "going right" << endl;
        if(node->right != NULL)
            return find_node(node->right, key);
        else {
            //std::cout << "No right child" << endl;
            return NULL;
        }
       
    }
    return NULL;
}


/***
A BinaryTree member fuction. This function performs
pre_order traversal on the tree and stores the nodes
inside a list
Input:
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.
Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::pre_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if(node != NULL) {
        list.push_back(*node);
        pre_order(((*node).left), list);
        pre_order(((*node).right), list);
    }

    // for(typename list<Node<T,Y> >::iterator it = list.begin(); it != list.end(); it++){
    //     std::cout << it -> getKey();
    // }
    //std::cout << "hi";
    return;
}

/***
A BinaryTree member fuction. This function performs
in_order traversal on the tree and stores the nodes
inside a list
Input:
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.
Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::in_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if(node != NULL) {
        in_order((node -> left), list);
        list.push_back(*node);
        in_order((node -> right), list);
    }
    return;
}

/***
A BinaryTree member fuction. This function performs
post_order traversal on the tree and stores the nodes
inside a list
Input:
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.
Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::post_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if(node != NULL) {
        post_order((node -> left), list);
        post_order((node -> right), list);
        list.push_back(*node);
    }
    return;
}

/***
A BinaryTree getter fuction. This function gets
the current root of the binary tree.
Input:
N/A
Output:
Outputs the root of the binary tree
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::getRoot(){
    /**
        Your code goes below here
    **/
   return this->root;
}


/***
The BinaryTree destructor. Make sure all
the TreeNodes that have been created get destroyed
and make sure there are no memory leaks.
Input:
N/A
Output:
N/A
***/



template <class T, class Y>
BinaryTree<T,Y>::~BinaryTree(){
    /**
        Your code goes below here
    **/
    list<Node<T,Y> > node_list;
    post_order(this->getRoot(), node_list);
    for(typename list<Node<T,Y> >::iterator nodes = node_list.begin(); nodes != node_list.end();nodes++) {
        delete_node(nodes->getKey());
    }
   
}


template class Node<int, std::string>;
template class Node<std::string, std::string>;
template class Node<int, int>;
template class Node<double, double>;
template class Node<std::string, long>;
template class Node<std::string, std::list<std::string> >;
template class Node<std::string, int >;

template class BinaryTree<std::string, std::list<std::string> >;
template class BinaryTree<std::string, std::string>;
template class BinaryTree<int, int>;
template class BinaryTree<int, std::string>;
template class BinaryTree<std::string, int>;