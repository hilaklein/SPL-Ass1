#ifndef TREE_H_
#define TREE_H_

#include <vector>
using namespace std;

class Session;

class Tree {
public:
    Tree();
    Tree(int rootLabel);
    virtual ~Tree(); // destructor
    Tree(const Tree& other); // copy constructor Tree t1(t2)
    Tree &operator=(const Tree &other); // copy Assignment T1=T2
    Tree(Tree &&other) noexcept; // move ctr
    Tree& operator=(Tree &&other) noexcept; // move assignment

    void addChild(const Tree &child);

    Tree & getChild(int) const;

    static Tree *createTree(Session &session, int rootLabel);

    virtual int traceTree()=0;


    vector<Tree*> getChildren() const;

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

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    Tree& traceMaxTree(Tree* tree);
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
