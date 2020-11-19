#ifndef TREE_H_
#define TREE_H_

#include <vector>
using namespace std;

class Session;

class Tree {
public:
    Tree(int rootLabel);
    virtual ~Tree(); // destructor
    Tree(const Tree& other); // copy constructor Tree t1(t2)
    Tree &operator=(const Tree &other); // copy Assignment T1=T2
    Tree(Tree &&other); // move ctr
    Tree &operator=(Tree &&other); // move assignment

    void addChild(const Tree &child);

    const Tree &getChild(int) const;

    static Tree *createTree(const Session &session, int rootLabel);
    //createTree(){
    //Tree* output;
    // switch(of tree types which will define the instance of a desired Tree){
    // case m :
    // output = new maxranktree();
    //return output;
    //}

    virtual int traceTree()=0;

    //maybe there is another way to receive children vector????????????????????????????????????????
    const vector<Tree*> getChildren() const;

    int getNodeIndex() const;

    virtual Tree* clone() const=0;

protected:
    int node;
    std::vector<Tree*> children;
};




class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;

    //destructor - not needed - there is Tree destructor, and 'currCircle' is on the stack
    CycleTree(const CycleTree& other); //copy constructor
    CycleTree & operator=(const CycleTree &other); //copy assignment
    CycleTree(CycleTree &&other); //move constructor
    CycleTree operator=(CycleTree &&other); //move assignment


private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
