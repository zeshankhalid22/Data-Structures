#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
using namespace std;

class Node {
public:
    string word;
    string meaning;
    Node *left;
    Node *right;

    Node(string word, string meaning);
};

class Dictionary {
public:
    Node *root;

    Node *insert(Node *root, string word, string meaning);
    Node *minValueNode(Node *node);
    Node *deleteNode(Node *root, string word);
    Node *search(Node *root, string word);
    void inorder(Node *root, string word, vector<string> &suggestions);
    void LoadDictionary(Node *&root);
    void AddWord(Node *&root, string word, string meaning);
    void SearchWord(Node *&root, string word);
    void DeleteWord(Node *&root, string word);
    void UpdateWord(Node *&root, string word, string newMeaning);
    void WordSuggestion(Node *root, string word);
    void writeInorder(Node *root, ofstream &file);
    void writeDictionary(Node *root);
};

#endif // DICTIONARY_H
