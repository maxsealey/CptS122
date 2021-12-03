#pragma once


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Node Class

class Node
{
public:
    Node(string &newData);
    ~Node();
    
    void setData(string &newData); // SETTERS
    void setLeftPtr(Node *&newLeftPtr);
    void setRightPtr(Node *&newRightPtr);
    
    string getData(); // GETTERS
    Node *& getLeftPtr();
    Node *& getRightPtr();
    
    virtual void printData() = 0;
    
private:
    string mData;
    Node * mpLeft;
    Node * mpRight;
};

// TransactionNode Class

class TransactionNode : public Node
{
public:
    TransactionNode(string &newData, int &newUnits);
    ~TransactionNode();
    
    void setUnits(int &newUnits);
    
    int getUnits();
    
    void printData();
    
private:
    int mUnits;
};

// BST Class

class BST
{
public:
    BST();
    ~BST();
    
    Node *& getRoot(); // GETTER
    
    void setRoot(Node *& pNewRoot); // SETTER
    
    void insert(string & newData, int & newUnits); // calls private insert
    
    void inOrderTransversal(); // traverses tree in order
    
    TransactionNode & findSmallest(); // finds smallest
    
    TransactionNode & findLargest(); // finds largest
    
    
private:
    Node * mpRoot;
    
    // private member functions
    void destroyTree(Node * pT);
    
    void insert(string & newData, int & newUnits, Node *& pT);
    
    void inOrderTransversal(Node *& pT);
    
    TransactionNode & findSmallest(Node *& pT);
    TransactionNode & findLargest(Node *& pT);
};

// Data Analysis Class

class DataAnalysis
{
public:
    void runAnalysis();
    
private:
    BST mTreeSold;
    BST mTreePurchased;
    ifstream mCsvStream;
    
    void openFile(); // opens file
    
    void closeFile(); // closes file
    
    int readLine(string & fData, int & fUnits, string & fTransaction); //
    
    void readFile();
    
    void insertData(string & newData, int & newUnits, string & transaction);
    
    void printTrends();
};






