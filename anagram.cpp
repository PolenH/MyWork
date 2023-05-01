#include "anagram.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// partners: sv34, hpalin2, nstse2

/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the
binary tree.

Input:
std::string filename - the path to the file

Output:
N/A
***/
AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
    /**
        Your code goes below here
    **/
    std::string anagram;
    while(file >> anagram) {
        this->addWord(anagram);
        //std::cout << anagram << " ";
    }
    file.close();
   
}

/***
An AnagramDict member function. This function sorts the given word in
lexicographical order

Input:
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/
std::string AnagramDict::sortWord(std::string word) {
    /**
        Your code goes below here
    **/
    //string sort_word = word;
    sort(word.begin(), word.end());
    // std::cout << word;
    return word;
}

/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input:
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    string sorted_word = this->sortWord(word);
    //std::cout << "--" << sorted_word << "--" << endl;
    Node<string, list<string> > *node = (this->tree).find_node(sorted_word);
    if (node != NULL) {
        list<string> node_list = node->getData();
        for (list<string>::iterator it = node_list.begin(); it != node_list.end(); it++) {
            if (*it == word) {
                return;
            }
        }
        node_list.push_back(word);
        node->setData(node_list);
    } else {
        list<string> node_list;
        node_list.push_back(word);
        Node<string, list<string> > *new_node = new Node<string, list<string> >(sorted_word, node_list);
        new_node->left = NULL;
        new_node->right = NULL;
        (this->tree).insert_node((this->tree).getRoot(), new_node);
    }
}


/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line.
View on wiki for more information.

Input:
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    std::string path = "output/" + order+"_"+ filename_;
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open()) {
        //create new file
        file.open(path.c_str(),std::ios::out);
    }
    /**
        Your code goes below here
    **/

    //std::cout << order << "------";

    list<Node<string, list<string> > > node_list;
    if(order == "pre"){
       (this->tree).pre_order((this->tree).getRoot(), node_list);
       //std::cout << "pre" << "------";
    }
    else if(order == "in"){
        (this->tree).in_order((this->tree).getRoot(), node_list);
    }
    else if(order == "post"){
        (this->tree).post_order((this->tree).getRoot(), node_list);
    } else {
        //std::cout << order << "------";
        return;
    }

    for(typename list<Node<string, list<string> > >::iterator it = node_list.begin(); it != node_list.end(); it++){
        list<string> node_data = it->getData();
        for(list<string>::iterator word_list = node_data.begin(); word_list != node_data.end(); word_list++){
            file << *word_list << " ";
            //std::cout << *word_list << "-";
        }
        file << endl;
    }
    file.close();
}