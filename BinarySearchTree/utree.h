#include <fstream>
#include <sstream>
#include "dtree.h"
using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
#define DEFAULT_HEIGHT 0

class Grader;   /* For grading purposes */
class Tester;   /* Forward declaration for testing class */

class UNode {
    friend class Grader;
    friend class Tester;
    friend class UTree;
public:
    UNode() {
        _dtree = new DTree();
        _height = DEFAULT_HEIGHT;
        _left = nullptr;
        _right = nullptr;
    }

    ~UNode() {
        delete _dtree;
        _dtree = nullptr;
    }

    /* Getters */
    DTree*& getDTree() {return _dtree;}
    int getHeight() const {return _height;}
    string getUsername() const {return _dtree->getUsername();}

private:
    DTree* _dtree;
    int _height;
    UNode* _left;
    UNode* _right;

    /* IMPLEMENT (optional): Additional helper functions */

};

class UTree {
    friend class Grader;
    friend class Tester;

public:
    UTree():_root(nullptr){}

    /* IMPLEMENT: destructor */
    ~UTree();

    /* IMPLEMENT: Basic operations */

    void loadData(string infile, bool append = true);
    bool insert(Account newAcct);
    bool removeUser(string username, int disc, DNode*& removed);
    UNode* retrieve(string username);
    DNode* retrieveUser(string username, int disc);
    int numUsers(string username);
    void clear();
    void printUsers() const;
    void dump() const {dump(_root);}
    void dump(UNode* node) const;


    /* IMPLEMENT: "Helper" functions */

    void updateHeight(UNode* node);
    int checkImbalance(UNode* node);
    //----------------
    void rebalance(UNode*& node);
    // -- OR --
    //UNode* rebalance(UNode* node);
    //----------------

private:
    UNode* _root;

    /* IMPLEMENT (optional): any additional helper functions here! */
    bool traverseTreeInsert(UNode *curr, Account newAcct);
    UNode* traverseTreeRemove(UNode *node, string username);
    string maxNode(UNode* node);
    string minNode(UNode* node);
    UNode* traverseTreeRetrive(UNode* node, string username);
    void traverseInOrder(UNode* node) const;
    int traverseHeight(UNode* node);
    void traverseAllHeight(UNode* node);
    void traverseTreeDelete(UNode* node);
    void checkAllImbalance(UNode* node);
    int getBalanceFactor(UNode* node);
    void rightRotate(UNode*& c);
    void leftRotate(UNode*& a);
    UNode* getParentNode(UNode* curr, UNode* oldNode);
};

#ifndef INC_341PROJECT2_UTREE_H
#define INC_341PROJECT2_UTREE_H

#endif //INC_341PROJECT2_UTREE_H
