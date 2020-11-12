#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel);

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
private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
