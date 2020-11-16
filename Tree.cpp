#include "Tree.h"
#include <vector>
#include "Session.h"
using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {

}
Tree::~Tree()  {
    int size = children.size();
    for(int i = size-1; i >=0 ; i--){
        if(children[i]){
            delete children[i];
        }
        children.clear();
    }
}
Tree::Tree(Tree &other): children(other.children),node(other.node) {} // copy ctr
Tree & Tree::operator=(const Tree &other) { // copy Assignment
    if(!children.empty()) {
        int size = children.size();
        for (int i = size - 1; i >= 0; i--) {
            delete children[i];
        }
    }
        children.clear();
        int otherChildSize = other.children.size();
        for(int i = 0 ; i < otherChildSize ; i++) {
            Tree *t = (this)->children[i];
            children.push_back(t);
        }
        return *this;
}
Tree::Tree(Tree &&other) : children(other.children),node(other.node) {//move ctr
    other.node = 0;
    int size = other.children.size();
    for(int i = 0 ; i < size ; i++) {
        other.children[i] = nullptr;
    }
    other.children.clear();
}
Tree & Tree::operator=(Tree &&other) { // move Assignment
    if (this != &other) { // A1=A1
        if (&children) {
            int size = children.size();
            for (int i = size - 1; i >= 0; i--) {
                if (children[i]) {
                    delete children[i];
                }
            }

            int otherChildSize = other.children.size();
            for (int i = 0; i < otherChildSize; i++) {
                children[i] = other.children[i];
            }
        }
        node = other.node;
    }
    return *this;
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