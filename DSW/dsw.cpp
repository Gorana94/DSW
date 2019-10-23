#include "dsw.h"
#include <QFile>
#include <QDir>
#include <QElapsedTimer>
#include <QDebug>


DSW::DSW()
{
    this->root = nullptr;
}

void DSW::DestroyRecursive(Node* node)
{
    if (node)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

DSW::~DSW()
{
    DestroyRecursive(this->root);
}

Node *DSW::newNode(int value)
{
    Node* tmp = new Node;
    tmp->key = value;
    tmp->left = nullptr;
    tmp->right = nullptr;
    return tmp;
}

Node *DSW::insert(Node *node, int value)
{
    if(node == nullptr)
        return newNode(value);

    if(value < node->key)
        node->left = insert(node->left, value);
    else if(value > node->key)
        node->right = insert(node->right, value);

    return node;
}

void DSW::insert(int value)
{
    this->root=insert(this->root, value);
}

void DSW::preorder(Node *root)
{
    if(root != nullptr){
        cout << root->key << " ";
        this->preorder(root->left);
        this->preorder(root->right);
    }
}

void DSW::preorder()
{
    cout << "Preorder walk: ";
    this->preorder(this->root);
    cout << endl;
}

void DSW::inorder(Node* root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void DSW::inorder()
{
    cout << "Inorder walk: ";
    this->inorder(this->root);
    cout << endl;
}

void DSW::postorder(Node* root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

void DSW::postorder()
{
    cout << "Postorder walk: ";
    this->postorder(this->root);
    cout << endl;
}

void DSW::_graphWalk(Node* p, QTextStream *stream) {
    if (p != nullptr){
        *stream << "\t\t" << "n" << p->key << "[label=\"" << p->key <<"\"];" << endl;

        if(p->left != nullptr){
            *stream << "\t\tn" << p->key << "--" << "n" << p->left->key << ";" << endl;
            this->_graphWalk(p->left, stream);
        }else{
            *stream << "\t\t" << "n" << p->key << "leftnullptr" << "[shape=point,width=\".1\", height=\".1\"];" << endl;
            *stream << "\t\tn" << p->key << "--" << "n" << p->key << "leftnullptr" << endl;
        }

        if(p->right != nullptr){
            *stream << "\t\tn" << p->key << "--" << "n" << p->right->key << ";" << endl;
            this->_graphWalk(p->right, stream);
        }else{
            *stream << "\t\t" << "n" << p->key << "rightnullptr" << "[shape=point,width=\".1\", height=\".1\"];" << endl;
            *stream << "\t\tn" << p->key << "--" << "n" << p->key << "rightnullptr" << endl;
        }
    }
}

QByteArray DSW::_prepareGraph(){

    QByteArray a = QByteArray();

    QTextStream stream(&a, QIODevice::ReadWrite);
    stream << "graph ""{" << endl;
    stream << "\tNode[fontsize=10,margin=0,width=\".4\", height=\".4\"];" << endl;

    if(this->root->key < 0) this->_graphWalk(this->root->right, &stream);
    else this->_graphWalk(this->root, &stream);
    stream << "}" << endl;
    stream.flush();

    return a;
}

Node *DSW::rotation(Node *root, int numberOfRotations)
{
    Node* tmp;
    tmp = root;
    while(numberOfRotations){
        tmp->right = leftRotation(tmp->right);
        tmp = tmp->right;
        --numberOfRotations;
    }
    return root;
}

Node *DSW::arrayToTree(Node *root)
{

    int n, t;
    int last, lastC;

    /* n - broj cvorova*/
    n = treeHeight(root);

    /*last = log2(n+1) */
    t = n + 1;

    last = 0;
    while (t > 1) {
       ++last;
       t /= 2;
    }

    /*lastC = n + 1 - 2^(log2(n+1))*/
    lastC = n + 1 - (1 << last);

    if (lastC == 0) lastC = (1 << (last - 1));
    root = rotation(root,lastC);

    n -= lastC;

    while (n > 1) {
       n /= 2;
       root = rotation(root,n);
    }

    return root;
}

Node *DSW::getRoot() const
{
    return root;
}

void DSW::setRoot(Node *value)
{
    root = value;
}

void DSW::arrayToTree()
{
    this->root = arrayToTree(this->root);
}

QPixmap DSW::show(){


    QProcess* p = new QProcess();
    QByteArray a = this->_prepareGraph();

    QDir dir;

    QString str=dir.absolutePath() + "/proba1";
    QString str1=dir.absolutePath() + "/output.png";

    QFile file(str);
    file.open(QIODevice::WriteOnly);
    file.write(a);
    file.close();

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start("dot", QStringList() << "-Tpng" << "-Gsize=9,15\\!" << "-Gdpi=100" << str <<  "-o" << str1);

    QByteArray data;

    while(p->waitForReadyRead(1000)){
        data.append(p->readAll());
    }

    QPixmap pixmap = QPixmap(str1);

    return pixmap;
}

int DSW::treeHeight(Node *root)
{
    int leftH, rightH;
    if(root == nullptr)
        return -1;
    leftH = treeHeight(root->left);
    rightH = treeHeight(root->right);

    return 1 + ((leftH >= rightH) ? leftH : rightH);

}

Node *DSW::leftRotation(Node *root)
{
    Node* right, *rightLeft;
    if((root == nullptr) || (root->right == nullptr))
        return root;

    right = root->right;
    rightLeft = right->left;
    right->left = root;
    root->right = rightLeft;
    return right;

}

Node *DSW::rightRotation(Node *root)
{
    Node* left, *leftRight;
    if((root==nullptr) || (root->left == nullptr))
        return root;

    left = root->left;
    leftRight = left->right;
    left->right = root;
    root->left = leftRight;

    return left;

}

Node* DSW::treeToArray(Node* root)
{

    Node* p, *r;
    r = new Node;
    r->key = -1;
    r->left = nullptr;
    r->right = root;

    p = r;
    while(p->right){
        if(p->right->left == nullptr){
            p = p->right;
        }
        else{
            p->right = rightRotation(p->right);
        }
    }

    return r;
}

void DSW::treeToArray()
{
    this->root = treeToArray(this->root);
}





