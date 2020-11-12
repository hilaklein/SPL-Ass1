#include "Tree.h"
#include <vector>
#include "Session.h"
using namespace std;


Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {

}

void Tree::addChild(const Tree &child){
    children.push_back((Tree*)&child);
}

const Tree& Tree::getChild(int nodeIndex) const{
    for(Tree* itr:children){
        if(itr->node==nodeIndex)
            return *itr;
        //verify that there is no NullPointerException in case node with nodeIndex does not exist in current tree
    }
}

Tree* Tree::createTree(const Session &session, int rootLabel) {

    switch (session.getTreeType()) {
        case MaxRank :
            return new MaxRankTree(rootLabel);
            break;
        case Root :
            return new RootTree(rootLabel);
            break;
        case Cycle :
            return new CycleTree(rootLabel, session.cycleCounter);
            break;
    }

//createTree(){
//Tree* output;
// switch(of tree types which will define the instance of a desired Tree){
// case m :
// output = new maxranktree();
//return output;
}

int Tree::getNodeIndex() const {return node;}

const vector<Tree *> Tree::getChildren() const {
    return children;
}