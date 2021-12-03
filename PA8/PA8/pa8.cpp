#include "pa8.hpp"

/*
    Node Class
*/

Node::Node(string &newData) // Constructor
{
    mData = newData;
    mpLeft = nullptr;
    mpRight = nullptr;
}

Node::~Node() // Destructor
{
    cout << "accessing Node's destructor" << endl;
}

void Node::setData(string &newData) // set data
{
    mData = newData;
}
void Node::setLeftPtr(Node *&newLeftPtr) // set left pointer
{
    mpLeft = newLeftPtr;
}
void Node::setRightPtr(Node *&newRightPtr) // set right pointer
{
    mpRight = newRightPtr;
}

string Node::getData() // return data
{
    return mData;
}
Node *& Node::getLeftPtr() // return reference to left pointer
{
    return mpLeft;
}
Node *& Node::getRightPtr() // return reference to right pointer
{
    return mpRight;
}

/*
    TransactionNode Class
*/

TransactionNode::TransactionNode(string &newData, int &newUnits) : Node(newData) // Constructor, derived from Node
{
    mUnits = newUnits;
}
TransactionNode::~TransactionNode() // Destructor
{
    cout << "accessing TransactionNode's destructor" << endl;
}

void TransactionNode::setUnits(int &newUnits)
{
    mUnits = newUnits;
}

int TransactionNode::getUnits()
{
    return mUnits;
}

void TransactionNode::printData()
{
    cout << getData() << " -> " << getUnits() << endl;
}

/*
    BST Class
*/

BST::BST() // constructor
{
    mpRoot = nullptr;
}

BST::~BST() // destructor
{
    destroyTree(getRoot());
}

void BST::setRoot(Node *& pNewRoot) // setter
{
    mpRoot = pNewRoot;
}

Node *& BST::getRoot() // getter
{
    return mpRoot;
}

void BST::insert(string & newData, int & newUnits)
{
    insert(newData, newUnits, getRoot());
}

void BST::inOrderTransversal()
{
    inOrderTransversal(getRoot());
}

TransactionNode & BST::findSmallest()
{
    return findSmallest(getRoot());
}

TransactionNode & BST::findLargest()
{
    return findLargest(getRoot());
}

// private helper functions

void BST::destroyTree(Node * pT)
{
    if (pT != nullptr)
    {
        destroyTree(pT->getLeftPtr());
        destroyTree(pT->getRightPtr());
        
        delete pT; // not sure why the error here
    }
}

void BST::insert(string & newData, int & newUnits, Node *& pT)
{
    TransactionNode * pTree = dynamic_cast<TransactionNode *>(pT);
    
    if (pT == nullptr)
    {
        TransactionNode * pTemp = new TransactionNode(newData, newUnits);
        pT = pTemp;
    }
    
    else
    {
        if (pTree->getUnits() > newUnits)
        {
            insert(newData, newUnits, pT->getLeftPtr());
        }
        
        else if (pTree->getUnits() < newUnits)
        {
            insert(newData, newUnits, pT->getRightPtr());
        }

        else
        {
            cout << "duplicate" << endl;
        }
    }
}

void BST::inOrderTransversal(Node *& pT)
{
    if (pT != nullptr)
    {
        inOrderTransversal(pT->getLeftPtr());
        TransactionNode * pTree = dynamic_cast<TransactionNode *>(pT);
        pTree->printData();
        inOrderTransversal(pTree->getRightPtr());
    }
}

TransactionNode & BST::findSmallest(Node *& pT)
{
    if (pT->getLeftPtr() == nullptr)
    {
        return  *(dynamic_cast<TransactionNode *>(pT));
    }
    else
    {
        return findSmallest(pT->getLeftPtr());
    }
}

TransactionNode & BST::findLargest(Node *& pT)
{
    if (pT->getRightPtr() == nullptr)
    {
        return  *(dynamic_cast<TransactionNode *>(pT));
    }
    else
    {
        return findLargest(pT->getRightPtr());
    }
}

/*
    DataAnalysis Class
*/

void DataAnalysis::runAnalysis()
{
    readFile();
    closeFile();
    
    printTrends();
}

void DataAnalysis::openFile()
{
    mCsvStream.open("data.csv");
}

void DataAnalysis::closeFile()
{
    mCsvStream.close();
}

int DataAnalysis::readLine(string & fData, int & fUnits, string & fTransaction)
{
    int success = 0;
    
    char tempLine[100];
    
    mCsvStream.getline(tempLine, 100, ',');
    
    if (tempLine[0] != '\0')
    {
        fUnits = stoi(tempLine);
        
        mCsvStream.getline(tempLine, 100, ',');
        fData = tempLine;
        
        mCsvStream.getline(tempLine, 100);
        fTransaction = tempLine;
        
        success = true;
    }
    else
    {
        return success;
    }
    return success;

}

void DataAnalysis::readFile()
{
    char tempBuffer[100];
    string Data, Tran;
    int Units;
    
    mCsvStream.getline(tempBuffer, 100);
    
    while (!mCsvStream.eof())
    {
        int lineCheck = readLine(Data, Units, Tran);
        
        if (lineCheck != 0)
        {
            insertData(Data, Units, Tran); // if readLine worked, inserts Data
        }
    }
    
    cout << "Purchased" << endl;
    mTreePurchased.inOrderTransversal();
    
    cout << "Sold" << endl;
    mTreeSold.inOrderTransversal();
}

void DataAnalysis::insertData(string & newData, int & newUnits, string & transaction)
{
    if (transaction == "Purchased")
    {
        mTreePurchased.insert(newData, newUnits);
    }
    else if (transaction == "Sold")
    {
        mTreeSold.insert(newData, newUnits);
    }
    else
    {
        cout << "invalid" << endl;
    }
}

void DataAnalysis::printTrends()
{
    cout << "Purchased" << endl;
    cout << "Largest - ";
    mTreePurchased.findLargest().printData(); // prints largest purchased
    cout << endl;
    
    cout << "Smallest - ";
    mTreePurchased.findSmallest().printData(); // prints largest lurchased
    cout << endl << endl;
    
    cout << "Sold" << endl;
    cout << "Largest - ";
    this->mTreeSold.findLargest().printData(); // prints largest sold
    cout << endl;
    
    cout << "Smallest - ";
    this->mTreeSold.findSmallest().printData(); // prints largest sold
    cout << endl << endl;
}




