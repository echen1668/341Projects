#include "utree.h"
#include <random>
#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsertRemove(DTree& dtree);
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeInsertOneNode(DTree& dtree);
    bool testBasicDTreeInsertSameNode(DTree& dtree);
    bool testBasicDTreeInsertVacantNodes(DTree& dtree);
    bool testBasicDTreeBalance(DTree& dtree);
    bool testBasicDTreeBST(DTree& dtree);
    bool testBasicDTreeRetrive(DTree& dtree);
    bool testBasicDTreeRetriveNodeNotInTree(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);
    bool testBasicDTreeRemoveOneNode(DTree& dtree);
    bool testBasicDTreeRemoveNodeNotInTree(DTree& dtree);
    bool testBasicDTreeRemoveZeroNodes(DTree& dtree);
    bool testBasicDTreeAssigmentOperator(DTree& dtree);
    bool testBasicDTreeAssigmentOperatorOneNode(DTree& dtree);
    bool testBasicDTreeAssigmentOperatorZeroNodes(DTree& dtree);
    void testBasicDTreeAssigmentOperatorSelfAssign(DTree& dtree);
    void testBasicDTreePrintAccounts(DTree& dtree);
    bool testBasicUTreeInsertRemove(UTree& utree);
    bool testBasicUTreeInsert(UTree& utree);
    bool testBasicUTreeInsertOneNode(UTree& utree);
    bool testBasicUTreeInsertSameNode(UTree& utree);
    bool testBasicUTreeBalance(UTree& utree);
    bool testBasicUTreeBST(UTree& utree);
    bool testBasicUTreeRemove(UTree& utree);
    bool testBasicUTreeRemoveOneNode(UTree& utree);
    bool testBasicUTreeRemoveZeroNodes(UTree& utree);
    bool testBasicUTreeRemoveNodeNotInDTree(UTree& utree);
    bool testBasicUTreeRemoveNodeNotInUTree(UTree& utree);
    bool testBasicUTreeDNodeRetrive(UTree& utree);
    bool testBasicUTreeUNodeRetrive(UTree& utree);
    bool testBasicUTreeDNodeRetriveNotInTree(UTree& utree);
    bool testBasicUTreeUNodeRetriveNotInTree(UTree& utree);
    void testBasicUTreePrintAccounts(UTree& utree);
private:
    void traverseDTreeBalance(DTree* dtree, DNode* dnode, bool &isBalance);
    void traverseDTreeBST(DTree* dtree, DNode* dnode, bool &isBST);
    void traverseDTreeAssigment(DNode* dnode, DNode* dnode2, bool &assigment);
    void traverseUTreeBalance(UTree* utree, UNode* unode, bool &isBalance);
    void traverseUTreeBST(UTree* utree, UNode* unode, bool &isBST);
};

int main() {
    Tester tester;

    //Basic dtree tests
    //Testing insert for DTree
    DTree dtree;
    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;
    cout << endl;

    //Testing insert for one node for DTree
    DTree dtreeOneNode;
    cout << "Testing DTree insertion of one node...";
    if(tester.testBasicDTreeInsertOneNode(dtreeOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeOneNode.dump();
    cout << endl;
    cout << endl;

    //Testing insert for the same node for DTree
    DTree dtreeSameNode;
    cout << "Testing DTree insertion of same node...";
    if(tester.testBasicDTreeInsertSameNode(dtreeSameNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeSameNode.dump();
    cout << endl;
    cout << endl;

    //Testing insert for vacant nodes for DTree
    DTree dtreeInsertVacants;
    cout << "Testing DTree insertion for vacant nodes...";
    if(tester.testBasicDTreeInsertVacantNodes(dtreeInsertVacants)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    //Testing insert and remove for DTree
    DTree dtreeInsertRemove;
    cout << "Testing DTree insertion and remove...";
    if(tester.testBasicDTreeInsertRemove(dtreeInsertRemove)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;
    cout << endl;

    //Testing for balance for DTree
    DTree dtreeBalanceTest;
    cout << "Testing DTree balance...";
    if(tester.testBasicDTreeBalance(dtreeBalanceTest)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeBalanceTest.dump();
    cout << endl;
    cout << endl;

    //Testing for BST property for DTree
    DTree dtreeBST;
    cout << "Testing DTree BST..";
    if(tester.testBasicDTreeBST(dtreeBST)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeBST.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for DTree
    DTree dtreeRetrive;
    cout << "Testing DTree retrive...";
    if(tester.testBasicDTreeRetrive(dtreeRetrive)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRetrive.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for non-existent node in DTree
    DTree dtreeRetriveNotInTree;
    cout << "Testing DTree non-existent retrive...";
    if(tester.testBasicDTreeRetriveNodeNotInTree(dtreeRetriveNotInTree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRetriveNotInTree.dump();
    cout << endl;
    cout << endl;

    //Testing remove for DTree
    DTree dtreeRemove;
    cout << "Testing DTree remove...";
    if(tester.testBasicDTreeRemove(dtreeRemove)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRemove.dump();
    cout << endl;
    cout << endl;

    //Testing remove for one node for DTree
    DTree dtreeRemoveOneNode;
    cout << "Testing DTree remove of one node...";
    if(tester.testBasicDTreeRemoveOneNode(dtreeRemoveOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRemoveOneNode.dump();
    cout << endl;
    cout << endl;

    //Testing remove for zero nodes for DTree
    DTree dtreeRemoveZeroNodes;
    cout << "Testing DTree remove of zero nodes...";
    if(tester.testBasicDTreeRemoveZeroNodes(dtreeRemoveZeroNodes)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRemoveZeroNodes.dump();
    cout << endl;
    cout << endl;

    //Testing remove for non exisent node for DTree
    DTree dtreeRemoveNodeNotInTree;
    cout << "Testing DTree remove of nodes not in the tree...";
    if(tester.testBasicDTreeRemoveNodeNotInTree(dtreeRemoveNodeNotInTree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtreeRemoveNodeNotInTree.dump();
    cout << endl;
    cout << endl;

    //Testing assigment operator for DTree
    DTree dtreeAssigment;
    cout << "Testing DTree assigment operator...";
    if(tester.testBasicDTreeAssigmentOperator(dtreeAssigment)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;
    cout << endl;

    //Testing assigment operator for DTree with one node
    DTree dtreeAssigmentOneNode;
    cout << "Testing DTree assigment operator with one node...";
    if(tester.testBasicDTreeAssigmentOperatorOneNode(dtreeAssigmentOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;
    cout << endl;

    //Testing assigment operator for DTree with zero nodes
    DTree dtreeAssigmentZeroNode;
    cout << "Testing DTree assigment operator with zero nodes...";
    if(tester.testBasicDTreeAssigmentOperatorZeroNodes(dtreeAssigmentZeroNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;
    cout << endl;


    //Testing self assigment for assigment operator for DTree
    DTree dtreeAssigmentSelfAssign;
    cout << "Testing DTree assigment operator self assign. Should print out 'Cannot self-assign'..." << endl;
    tester.testBasicDTreeAssigmentOperatorSelfAssign(dtreeAssigmentSelfAssign);
    cout << endl;
    cout << endl;

    //Testing print accounts for DTree
    DTree dtreePrintAccounts;
    cout << "Testing DTree print accounts'..." << endl;
    tester.testBasicDTreePrintAccounts(dtreePrintAccounts);
    cout << endl;

    //Basic UTree tests
    //Testing insert for UTree
    UTree utree;
    cout << "\n\nTesting UTree insertion...";
    if(tester.testBasicUTreeInsert(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utree.dump();
    cout << endl;
    cout << endl;

    //Testing insert and remove for UTree
    UTree utreeInsertRemove;
    cout << "\n\nTesting UTree insertion and remove...";
    if(tester.testBasicUTreeInsertRemove(utreeInsertRemove)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeInsertRemove.dump();
    cout << endl;
    cout << endl;

    //Testing insert for one node for UTree
    UTree utreeInsertOneNode;
    cout << "\n\nTesting UTree insertion one node ...";
    if(tester.testBasicUTreeInsertOneNode(utreeInsertOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeInsertOneNode.dump();
    cout << endl;
    cout << endl;

    //Testing insert for the same node for UTree
    UTree utreeInsertSameNode;
    cout << "\n\nTesting UTree insertion same node...";
    if(tester.testBasicUTreeInsertSameNode(utreeInsertSameNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeInsertSameNode.dump();
    cout << endl;
    cout << endl;

    //Testing for BST property for UTree
    UTree utreeBST;
    cout << "\n\nTesting UTree BST...";
    if(tester.testBasicUTreeBST(utreeBST)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeBST.dump();
    cout << endl;
    cout << endl;

    //Testing for balance for UTree
    UTree utreeBalance;
    cout << "\n\nTesting UTree Balance...";
    if(tester.testBasicUTreeBalance(utreeBalance)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeBalance.dump();
    cout << endl;
    cout << endl;

    //Testing remove for UTree
    UTree utreeRemove;
    cout << "Testing UTree remove...";
    if(tester.testBasicUTreeRemove(utreeRemove)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRemove.dump();
    cout << endl;
    cout << endl;

    //Testing remove for one node for UTree
    UTree utreeRemoveOneNode;
    cout << "Testing UTree remove one node...";
    if(tester.testBasicUTreeRemoveOneNode(utreeRemoveOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRemoveOneNode.dump();
    cout << endl;
    cout << endl;

    //Testing remove for zero node for UTree
    UTree utreeRemoveZeroNodes;
    cout << "Testing UTree remove zero nodes...";
    if(tester.testBasicUTreeRemoveZeroNodes(utreeRemoveZeroNodes)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRemoveZeroNodes.dump();
    cout << endl;
    cout << endl;

    //Testing remove for non existent DNode for UTree
    UTree utreeRemoveNodeNotInTree1;
    cout << "Testing UTree remove not existent DNode...";
    if(tester.testBasicUTreeRemoveNodeNotInDTree(utreeRemoveNodeNotInTree1)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRemoveNodeNotInTree1.dump();
    cout << endl;
    cout << endl;

    //Testing remove for non existent UNode for UTree
    UTree utreeRemoveNodeNotInTree2;
    cout << "Testing UTree remove non existent UNode...";
    if(tester.testBasicUTreeRemoveNodeNotInUTree(utreeRemoveNodeNotInTree2)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRemoveNodeNotInTree2.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for DNodes forUTree
    UTree utreeRetriveDNode;
    cout << "Testing UTree retriving DNodes in the same UNode...";
    if(tester.testBasicUTreeDNodeRetrive(utreeRetriveDNode)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRetriveDNode.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for UNodes forUTree
    UTree utreeRetriveUNode;
    cout << "Testing UTree retriving UNodes...";
    if(tester.testBasicUTreeUNodeRetrive(utreeRetriveUNode)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRetriveUNode.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for non-existent DNode for UTree
    UTree utreeRetriveDNodeNotInTree;
    cout << "Testing UTree retriving non-existent DNodes...";
    if(tester.testBasicUTreeDNodeRetriveNotInTree(utreeRetriveDNodeNotInTree)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRetriveDNodeNotInTree.dump();
    cout << endl;
    cout << endl;

    //Testing retrive for non-existent UNode for UTree
    UTree utreeRetriveUNodeNotInTree;
    cout << "Testing UTree retriving non-existent UNodes...";
    if(tester.testBasicUTreeUNodeRetriveNotInTree(utreeRetriveUNodeNotInTree)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting UTree:" << endl;
    utreeRetriveUNodeNotInTree.dump();
    cout << endl;
    cout << endl;


    //Testing print accounts for UTree
    UTree utreePrintAccounts;
    cout << "Testing UTree print accounts'..." << endl;
    tester.testBasicUTreePrintAccounts(utreePrintAccounts);

    return 0;
}

bool Tester::testBasicDTreeInsertRemove(DTree& dtree) {
    for (int i = 0; i < 10; i++) {
        int disc = i;
        Account newAcct = Account("", disc, 0, "", "");
        while (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    cout << endl;
    cout << "Tree:" << endl;
    dtree.dump();
    cout << endl;
    bool isRemoved = true;
    DNode* placeHolder = nullptr;
    for (int i = 0; i < 10; i++) {
        int disc = i;
        isRemoved = dtree.remove(disc,placeHolder);
        if(isRemoved == false && placeHolder->getDiscriminator() != i){
            return false;
        }
    }
    if(dtree.getNumUsers() == 0){
        return true;
    }else{
        return false;
    }

}


bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++){ //inserts nodes, checks if all are inserted
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testBasicDTreeInsertOneNode(DTree& dtree) {
    bool allInserted = true;
    for (int i = 0; i < 1; i++){ //inserts one node, checks if all are inserted
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testBasicDTreeInsertSameNode(DTree& dtree) {
    Account acct = Account("", 1, 0, "", "");
    dtree.insert(acct);
    if (!dtree.insert(acct)){ //dtree.insert(acct) should return false since its inserting the same node twice
        return true;
    } else {
        return false;
    }
}

bool Tester::testBasicDTreeInsertVacantNodes(DTree& dtree) {
    Account newAcct1 = Account("", 2, 0, "", "");
    Account newAcct2 = Account("", 5, 0, "", "");
    Account newAcct3 = Account("", 7, 0, "", "");
    dtree.insert(newAcct1);
    dtree.insert(newAcct2);
    dtree.insert(newAcct3);
    int oldSize = dtree.getNumUsers();
    cout << endl;
    cout << "First Tree is " << endl;
    dtree.dump();
    cout << endl;
    DNode* placeHolder = nullptr;
    dtree.remove(2,placeHolder);
    dtree.remove(5,placeHolder);
    dtree.remove(7,placeHolder);
    Account newAcct4 = Account("", 1, 0, "", "");
    Account newAcct5 = Account("", 4, 0, "", "");
    Account newAcct6 = Account("", 9, 0, "", "");
    dtree.insert(newAcct4);
    dtree.insert(newAcct5);
    dtree.insert(newAcct6);
    cout << "Second Tree is " << endl;
    dtree.dump();
    cout << endl;
    if(dtree.getNumUsers() == oldSize){
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicDTreeBalance(DTree& dtree) {
    bool isBalanced = true;
    for(int i = 0; i < NUMACCTS; i++){ //inserts nodes
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        while(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    traverseDTreeBalance(&dtree,dtree._root, isBalanced); //calls helper functions to check for balance
    return isBalanced;
}

bool Tester::testBasicDTreeBST(DTree& dtree) {
    bool isBST = true;
    for(int i = 0; i < NUMACCTS; i++) { //inserts nodes
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        while(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    traverseDTreeBST(&dtree,dtree._root, isBST); //calls helper functions to check for BST property
    return isBST;
}

bool Tester::testBasicDTreeRemove(DTree& dtree) {
    bool isRemove = true;
    for (int i = 0; i < 10; i++){ //inserts nodes
        int disc = i;
        Account newAcct = Account("", disc, 0, "", "");
        while (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    dtree.dump();
    cout << endl;
    cout << endl;
    DNode *placeHolder = nullptr;
    dtree.remove(3, placeHolder); //removes node
    dtree.remove(5, placeHolder);
    dtree.remove(0, placeHolder);
    dtree.remove(9, placeHolder);
    dtree.remove(7, placeHolder);
    for (int i = 10; i < 20; i++) { //insers nodes again to trigger a rebalance
        int disc = i;
        Account newAcct = Account("", disc, 0, "", "");
        while (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    if (dtree.retrieve(3) != nullptr) { //checks if vacant nodes are removed
        isRemove = false;
    }
    if (dtree.retrieve(5) != nullptr) {
        isRemove = false;
    }
    if (dtree.retrieve(0) != nullptr) {
        isRemove = false;
    }
    if (dtree.retrieve(9) != nullptr) {
        isRemove = false;
    }
    if (dtree.retrieve(7) != nullptr) {
        isRemove = false;
    }
    return isRemove;
}

bool Tester::testBasicDTreeRemoveOneNode(DTree& dtree) {
    bool isRemoved = true;
    for (int i = 0; i < 1; i++) { //inserts a node
        int disc = i;
        Account newAcct = Account("", disc, 0, "", "");
        while (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    dtree.dump();
    cout << endl;
    DNode *placeHolder = nullptr;
    for (int i = 0; i < 1; i++) { //removes the node
        int disc = i;
        isRemoved = dtree.remove(disc, placeHolder);
    }
    if(isRemoved == true && dtree.getNumUsers() == 0 && dtree._root->isVacant() && placeHolder->getDiscriminator() == 0) { //checks if node is removed and tree is empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testBasicDTreeRemoveZeroNodes(DTree& dtree){
    DNode *placeHolder = nullptr;
    if(!dtree.remove(1,placeHolder)){ //dtree.remove should return false since node to remove does not exists
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicDTreeRemoveNodeNotInTree(DTree& dtree){
    Account newAcct = Account("", 2, 0, "", "");
    dtree.insert(newAcct);
    DNode *placeHolder = nullptr;
    if(!dtree.remove(1,placeHolder)){ //dtree.remove should return false since node to remove does not exists
        return true;
    }else{
        return false;
    }
}


bool Tester::testBasicDTreeRetrive(DTree& dtree) {
    bool isRetrive = true;
    for (int i = 0; i < 11; i++) { //inserts node
        int disc = i;
        Account newAcct = Account("", disc, 0, "", "");
        while (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    for (int i = 0; i < 11; i++) { //retrives each node
        int num = i;
        if (dtree.retrieve(num) == nullptr) { //returns false if node to retrive does not exists
            isRetrive = false;
        }
    }
    return isRetrive;
}

bool Tester::testBasicDTreeRetriveNodeNotInTree(DTree& dtree){
    Account newAcct = Account("", 2, 0, "", "");
    dtree.insert(newAcct);
    if(dtree.retrieve(1) == nullptr){ //dtree.retrive should return false since node to retrive does not exist
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicDTreeAssigmentOperator(DTree& dtree){
    bool assigment = true;
    for(int i = 0; i < NUMACCTS; i++){ //inserts node
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }
    DTree copyTree;
    copyTree = dtree; //copies dtree into copy tree
    if(&copyTree == &dtree){ //checks address
        cout << "Address test fails" << endl;
        return false;
    }
    if(copyTree.getNumUsers() != dtree.getNumUsers()){ //checks number of users
        cout << "Num Users test fails" << endl;
        return false;
    }
    traverseDTreeAssigment(dtree._root,copyTree._root,assigment); //checks each node
    cout << endl;
    cout << "Inital Tree" << endl; //prints both trees
    dtree.dump();
    cout << endl;
    cout << "Copy Tree" << endl;
    copyTree.dump();
    cout << endl;
    return assigment;
}

bool Tester::testBasicDTreeAssigmentOperatorOneNode(DTree& dtree){
    bool assigment = true;
    for(int i = 0; i < 1; i++){ //inserts node
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }
    DTree copyTree;
    copyTree = dtree; //copies dtree into copy tree
    if(&copyTree == &dtree){ //checks address
        cout << "Address test fails" << endl;
        return false;
    }
    if(copyTree.getNumUsers() != dtree.getNumUsers()){ //checks number of users
        cout << "Num Users test fails" << endl;
        return false;
    }
    traverseDTreeAssigment(dtree._root,copyTree._root,assigment); //checks each node
    cout << endl;
    cout << "Inital Tree" << endl; //prints both trees
    dtree.dump();
    cout << endl;
    cout << "Copy Tree" << endl;
    copyTree.dump();
    cout << endl;
    return assigment;
}

bool Tester::testBasicDTreeAssigmentOperatorZeroNodes(DTree& dtree){
    bool assigment = true;
    for(int i = 0; i < 0; i++){ //inserts node
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }
    DTree copyTree;
    copyTree = dtree; //copies dtree into copy tree
    if(&copyTree == &dtree){ //checks address
        cout << "Address test fails" << endl;
        return false;
    }
    if(copyTree.getNumUsers() != dtree.getNumUsers() && copyTree.getNumUsers() != 0 && dtree.getNumUsers() != 0){ //checks number of users
        cout << "Num Users test fails" << endl;
        return false;
    }
    traverseDTreeAssigment(dtree._root,copyTree._root,assigment); //checks each node
    cout << endl;
    cout << "Inital Tree" << endl; //prints both trees
    dtree.dump();
    cout << endl;
    cout << "Copy Tree" << endl;
    copyTree.dump();
    cout << endl;
    return assigment;
}

void Tester::testBasicDTreeAssigmentOperatorSelfAssign(DTree& dtree) {
    for (int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }
    dtree = dtree; //self assigns, should result in print out of "Cannot Self-Assign"
}

void Tester::testBasicDTreePrintAccounts(DTree& dtree){
    for(int i = 0; i < 5; i++){ //inserts nodes
        int disc = RANDDISC;
        Account newAcct = Account("Eric", disc, true, "Defensive Tackle", "College Level");
        while(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, false, "", "");
        }
    }
    cout << endl;
    cout << "Resulting Tree:" << endl;
    dtree.dump();
    cout << endl;
    dtree.printAccounts(); //prints all accounts
}

bool Tester::testBasicUTreeInsert(UTree& utree){
    bool allInserted = true;
    Account account1("Brandon", 13, false, "Left Tackle", "Level 1"); //accounts to insert
    Account account2("Eric", 14, false, "Left Tackle", "Level 1");
    Account account3("Allen", 2, false, "Left Tackle", "Level 1");
    Account account4("Wally", 1, false, "Left Tackle", "Level 1");
    Account account5("Danny", 5, false, "Left Tackle", "Level 1");
    if(!utree.insert(account1)){ //checks if each node is successfully inserted
        allInserted = false; //if insertion fails, then function returns false
    }
    if(!utree.insert(account2)){
        allInserted = false;
    }
    if(!utree.insert(account3)){
        allInserted = false;
    }
    if(!utree.insert(account4)){
        allInserted = false;
    }
    if(!utree.insert(account5)){
        allInserted = false;
    }
    return allInserted;
}

bool Tester::testBasicUTreeInsertRemove(UTree& utree) {
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    Account account2("Elron", 14, false, "Left Tackle", "Level 1");
    Account account3("Allen", 2, false, "Left Tackle", "Level 1");
    Account account4("Allen", 3, false, "Left Tackle", "Level 1");
    Account account5("Chad", 2, false, "Left Tackle", "Level 1");
    Account account6("Danny", 3, false, "Left Tackle", "Level 1");
    Account account7("Danny", 2, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts nodes
    utree.insert(account2);
    utree.insert(account3);
    utree.insert(account4);
    utree.insert(account5);
    utree.insert(account6);
    utree.insert(account7);
    cout << endl;
    cout << "Inital Tree:" << endl;
    utree.dump();
    cout << endl;
    DNode *placeHolder = nullptr;
    utree.removeUser("Eric", 13, placeHolder); //remove nodes
    utree.removeUser("Elron", 14, placeHolder);
    utree.removeUser("Allen", 2, placeHolder);
    utree.removeUser("Allen", 3, placeHolder);
    utree.removeUser("Chad", 2, placeHolder);
    utree.removeUser("Danny", 3, placeHolder);
    utree.removeUser("Danny", 2, placeHolder);
    if(utree._root == nullptr){ //checks if tree is empty
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeInsertOneNode(UTree& utree) {
    Account account1("Eric", 13, false, "Left Tackle", "Level 1"); //inserts node
    if(utree.insert(account1) && utree.numUsers("Eric") == 1){ //checks if node is inserted
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeInsertSameNode(UTree& utree) {
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    if(!utree.insert(account1)){ //utree.insert should return false since it is inserting a node that already exists in the tree
        return true;
    }else{
        return false;
    }
}


bool Tester::testBasicUTreeBalance(UTree& utree) {
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    Account account2("Elron", 14, false, "Left Tackle", "Level 1");
    Account account3("Allen", 2, false, "Left Tackle", "Level 1");
    Account account4("Albert", 1, false, "Left Tackle", "Level 1");
    Account account5("Lamar", 5, false, "Left Tackle", "Level 1");
    Account account6("Ottis", 16, false, "Left Tackle", "Level 1");
    Account account7("Mike", 7, false, "Left Tackle", "Level 1");
    Account account8("Sam", 8, false, "Left Tackle", "Level 1");
    Account account9("Luke", 19, false, "Left Tackle", "Level 1");
    Account account10("Zed", 10, false, "Left Tackle", "Level 1");
    Account account11("Manny", 20, false, "Left Tackle", "Level 1");
    Account account12("Chad", 22, false, "Left Tackle", "Level 1");
    Account account13("Benny", 21, false, "Left Tackle", "Level 1");
    Account account14("Wally", 58, false, "Left Tackle", "Level 1");
    Account account15("Patty", 6, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts nodes
    utree.insert(account2);
    utree.insert(account3);
    utree.insert(account4);
    utree.insert(account5);
    utree.insert(account6);
    utree.insert(account7);
    utree.insert(account8);
    utree.insert(account9);
    utree.insert(account10);
    utree.insert(account11);
    utree.insert(account12);
    utree.insert(account13);
    utree.insert(account14);
    utree.insert(account15);
    bool isBalance = true;
    traverseUTreeBalance(&utree,utree._root,isBalance); //calls for helper function for check for balance
    return isBalance;
}


bool Tester::testBasicUTreeBST(UTree& utree) {
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    Account account2("Xavier", 14, false, "Left Tackle", "Level 1");
    Account account3("Allen", 2, false, "Left Tackle", "Level 1");
    Account account4("Harold", 1, false, "Left Tackle", "Level 1");
    Account account5("Lamar", 5, false, "Left Tackle", "Level 1");
    Account account6("Lily", 16, false, "Left Tackle", "Level 1");
    Account account7("Mike", 7, false, "Left Tackle", "Level 1");
    Account account8("Sam", 8, false, "Left Tackle", "Level 1");
    Account account9("Katy", 19, false, "Left Tackle", "Level 1");
    Account account10("Taylor", 10, false, "Left Tackle", "Level 1");
    Account account11("Mitchell", 20, false, "Left Tackle", "Level 1");
    Account account12("Chad", 22, false, "Left Tackle", "Level 1");
    Account account13("Billy", 21, false, "Left Tackle", "Level 1");
    Account account14("Wally", 58, false, "Left Tackle", "Level 1");
    Account account15("Ben", 6, false, "Left Tackle", "Level 1");
    Account account16("Jeff", 0, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts nodes
    utree.insert(account2);
    utree.insert(account3);
    utree.insert(account4);
    utree.insert(account5);
    utree.insert(account6);
    utree.insert(account7);
    utree.insert(account8);
    utree.insert(account9);
    utree.insert(account10);
    utree.insert(account11);
    utree.insert(account12);
    utree.insert(account13);
    utree.insert(account14);
    utree.insert(account15);
    utree.insert(account16);
    bool isBST = true;
    traverseUTreeBST(&utree,utree._root,isBST); //calls for helper function for check for BST property
    return isBST;
}


bool Tester::testBasicUTreeRemove(UTree& utree) {
    bool removed = true;
    string string1 = "Allen";
    string string2 = "Benny";
    string string3 = "Chad";
    string string4 = "Dillon";
    string string5 = "Eric";
    Account acc1 = Account(string1, 0, 0, "", "");
    Account acc2a = Account(string2, 0, 0, "", "");
    Account acc2b = Account(string2, 2, 0, "", "");
    Account acc3 = Account(string3, 0, 0, "", "");
    Account acc4 = Account(string4, 0, 0, "", "");
    Account acc5a = Account(string5, 0, 0, "", "");
    Account acc5b = Account(string5, 1, 0, "", "");
    utree.insert(acc1); //inserts nodes
    utree.insert(acc2a);
    utree.insert(acc2b);
    utree.insert(acc3);
    utree.insert(acc4);
    utree.insert(acc5a);
    utree.insert(acc5b);
    cout << endl;
    cout << "Inital Tree:" << endl;
    utree.dump();
    cout << endl;
    DNode *placeHolder = nullptr;
    utree.removeUser(string2, 0, placeHolder); //removes nodes
    utree.removeUser(string2, 2, placeHolder);
    utree.removeUser(string5, 0, placeHolder);
    utree.removeUser(string5, 1, placeHolder);
    if (utree.retrieve(string2) != nullptr) { //checks if removed nodes are removed
        removed = false;
    }
    if (utree.retrieve(string5) != nullptr) {
        removed = false;
    }
    return removed;
}


bool Tester::testBasicUTreeRemoveOneNode(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    cout << endl;
    cout << "Inital Tree:" << endl;
    utree.dump();
    cout << endl;
    DNode *placeHolder = nullptr;
    if(utree.removeUser("Eric",13,placeHolder) && utree._root == nullptr){ //removes node, checks it it is succesfull
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeRemoveZeroNodes(UTree& utree){
    DNode *placeHolder = nullptr;
    if(!utree.removeUser("Eric",13,placeHolder)){ //utree.removeUser should return false since it is removing a node that does not exists
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeRemoveNodeNotInDTree(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    DNode *placeHolder = nullptr;
    if(!utree.removeUser("Eric",14,placeHolder)){ //utree.removeUser should return false since it is removing a node that does not exists
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeRemoveNodeNotInUTree(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    DNode *placeHolder = nullptr;
    if(!utree.removeUser("Mike",13,placeHolder)){ //utree.removeUser should return false since it is removing a node that does not exists
        return true;
    }else{
        return false;
    }
}

void Tester::traverseDTreeBalance(DTree* dtree,DNode* dnode, bool &isBalance){
    if(dnode == nullptr){ //base cases
        return;
    }
    traverseDTreeBalance(dtree, dnode->_left, isBalance); //recursive cases
    if(dtree->checkImbalance(dnode)){ //false if an imbalance exists
        isBalance = false;
    }
    traverseDTreeBalance(dtree, dnode->_right, isBalance);
}

void Tester::traverseDTreeBST(DTree* dtree, DNode* dnode, bool &isBST) {
    if (dnode == nullptr) { //base cases
        return;
    }
    traverseDTreeBST(dtree, dnode->_left, isBST); //recursive cases
    if (dnode->_left != nullptr && dnode->_right != nullptr) { //false if BST property is voilated
        if (!(dnode->_left->getDiscriminator() < dnode->getDiscriminator()) ||
            !(dnode->getDiscriminator() < dnode->_right->getDiscriminator())) {
            isBST = false;
        }
    }
    if (dnode->_left != nullptr && dnode->_right == nullptr) {
        if (!(dnode->_left->getDiscriminator() < dnode->getDiscriminator())) {
            isBST = false;
        }
    }
    if (dnode->_left == nullptr && dnode->_right != nullptr) {
        if (!(dnode->getDiscriminator() < dnode->_right->getDiscriminator())) {
            isBST = false;
        }
    }
    traverseDTreeBST(dtree, dnode->_right, isBST);
}

void Tester::traverseDTreeAssigment(DNode* dnode, DNode* dnode2, bool &assigment) {
    if (dnode == nullptr || dnode2 == nullptr) { //base cases
        return;
    }
    traverseDTreeAssigment(dnode->_left, dnode2->_left, assigment); //recursive cases
    if (dnode->getDiscriminator() != dnode2->getDiscriminator() || dnode->getSize() != dnode2->getSize()) { //false if nodes are not the same
        assigment = false;
    }
    traverseDTreeAssigment(dnode->_right, dnode2->_right, assigment);
}

void Tester::traverseUTreeBalance(UTree* utree, UNode* unode, bool &isBalance) {
    if (unode == nullptr) { //base cases
        return;
    }
    traverseUTreeBalance(utree, unode->_left, isBalance); //recursive cases
    if (utree->getBalanceFactor(unode) > 1) { //false if balance does not exists
        isBalance = false;
    }
    traverseUTreeBalance(utree, unode->_right, isBalance);
}

void Tester::traverseUTreeBST(UTree* utree, UNode* unode, bool &isBST){
    if (unode == nullptr) { //base cases
        return;
    }
    traverseUTreeBST(utree, unode->_left, isBST); //recursive cases
    if (unode->_left != nullptr && unode->_right != nullptr) {
        if (!(unode->_left->getUsername() < unode->getUsername()) || !(unode->getUsername() < unode->_right->getUsername())){ //false if BST property is voilated
            isBST = false;
        }
    }
    if (unode->_left != nullptr && unode->_right == nullptr) {
        if (!(unode->_left->getUsername()< unode->getUsername())) {
            isBST = false;
        }
    }
    if (unode->_left == nullptr && unode->_right != nullptr) {
        if (!(unode->getUsername() < unode->_right->getUsername())) {
            isBST = false;
        }
    }
    traverseUTreeBST(utree, unode->_right, isBST);
}

bool Tester::testBasicUTreeDNodeRetrive(UTree& utree){
    bool isRetrive = true;
    for (int i = 0; i < 11; i++) { //inserts nodes
        int disc = i;
        Account newAcct = Account("Eric", disc, 0, "", "");
        while (!utree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " already exists" << endl;
            disc = RANDDISC + 1;
            newAcct = Account("", disc, 0, "", "");
        }
    }
    for (int i = 0; i < 11; i++) { //retrives each node
        int num = i;
        if (utree.retrieveUser("Eric", num) == nullptr) { //returns false if node to retrive does not exists
            isRetrive = false;
        }
    }
    cout << endl;
    cout << "Resulting DTree:" << endl;
    utree.retrieve("Eric")->getDTree()->dump();
    cout << endl;
    return isRetrive;
}

bool Tester::testBasicUTreeDNodeRetriveNotInTree(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    if(utree.retrieveUser("Eric", 12) == nullptr){ //utree.retrive should return false since it is retriving a node that does not exists in the tree
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeUNodeRetriveNotInTree(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts node
    if(utree.retrieve("Erica") == nullptr){ //utree.retrive should return false since it is retriving a node that does not exists in the tree
        return true;
    }else{
        return false;
    }
}

bool Tester::testBasicUTreeUNodeRetrive(UTree& utree) {
    bool isRetrive = true;
    Account account1("Eric", 13, false, "Left Tackle", "Level 1");
    Account account2("Elron", 14, false, "Left Tackle", "Level 1");
    Account account3("Allen", 2, false, "Left Tackle", "Level 1");
    Account account4("Albert", 1, false, "Left Tackle", "Level 1");
    utree.insert(account1); //inserts nodes
    utree.insert(account2);
    utree.insert(account3);
    utree.insert(account4);
    if (utree.retrieve("Eric") == nullptr) { //returns false if node to retrive does not exists
        isRetrive = false;
    }
    if (utree.retrieve("Elron") == nullptr) {
        isRetrive = false;
    }
    if (utree.retrieve("Allen") == nullptr) {
        isRetrive = false;
    }
    if (utree.retrieve("Albert") == nullptr) {
        isRetrive = false;
    }
    return isRetrive;
}

void Tester::testBasicUTreePrintAccounts(UTree& utree){
    Account account1("Eric", 13, false, "Left Tackle", "Level 1"); //accounts
    Account account2("Xavier", 14, false, "Cornerback", "Level 1");
    Account account3("Allen", 2, false, "Middle Linebacker", "Level 1");
    Account account4("Harold", 1, false, "Defensive Tackle", "Level 1");
    Account account5("Lamar", 5, false, "Quaterback", "Level 1");
    Account account6("Eric", 16, false, "Tight End", "Level 1");
    Account account7("Jeff", 7, false, "Defensive End", "Level 1");
    Account account8("Jeff", 8, false, "Left Guard", "Level 1");
    Account account9("Lamar", 19, false, "Center", "Level 1");
    Account account10("Xavier", 10, false, "Right Guard", "Level 1");
    Account account11("Mitchell", 20, false, "Right Tackle", "Level 1");
    Account account12("Lamar", 22, false, "Outside Linebacker", "Level 1");
    Account account13("Jeff", 21, false, "Wide Reciver", "Level 1");
    Account account14("Wally", 58, false, "Running Back", "Level 1");
    Account account15("Ben", 6, false, "Strong Saftey", "Level 1");
    Account account16("Jeff", 0, false, "Free Saftey", "Level 1");
    utree.insert(account1); //inserts nodes
    utree.insert(account2);
    utree.insert(account3);
    utree.insert(account4);
    utree.insert(account5);
    utree.insert(account6);
    utree.insert(account7);
    utree.insert(account8);
    utree.insert(account9);
    utree.insert(account10);
    utree.insert(account11);
    utree.insert(account12);
    utree.insert(account13);
    utree.insert(account14);
    utree.insert(account15);
    utree.insert(account16);
    cout << endl;
    cout << "Resulting Tree:" << endl;
    utree.dump();
    cout << endl;
    utree.printUsers(); //prints all user accounts
    cout << endl;
}
