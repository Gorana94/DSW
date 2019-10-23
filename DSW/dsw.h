#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <QTextStream>
#include <QByteArray>
#include <QPixmap>
#include <QProcess>

using namespace std;

struct Node{
    int key;
    Node* left, *right;
};

class DSW
{
public:
    DSW();
    ~DSW();
    void insert(int value);
    void preorder();
    void inorder();
    void postorder();

    QPixmap show();
    int treeHeight(Node* root);
    void treeToArray();
    void arrayToTree();
    Node *getRoot() const;
    void setRoot(Node *value);
    void inorder(Node* root);
    void preorder(Node* root);
    void postorder(Node* root);

private:
    void _graphWalk(Node* p, QTextStream *stream);
    QByteArray _prepareGraph();
    Node* rotation(Node* root, int numberOfRotations);
    Node* arrayToTree(Node* root);
    Node* leftRotation(Node* root);
    Node* rightRotation(Node* root);
    Node* treeToArray(Node* root);
    Node* newNode(int value);
    void DestroyRecursive(Node* root);
    Node* insert(Node* node, int value);


    Node* root;
};

#endif // DSW_H
