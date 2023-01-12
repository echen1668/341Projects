#include "dtree.h"

DTree::~DTree() {
    clear(); //calls clear function
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {
    if(&rhs != this){
        clear(); //clears previous tree
        _root = traverseInOrderAssigmentOperator(rhs._root); //calls helper function to copy rhs into this tree
        return *this;
    }else{
        cout << "Cannot Self Assign" << endl; //if self assign occurs
        return *this;
    }
}

/**
 * Dynamically allocates a new DNode in the tree.
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {
    if(_root == nullptr){ //if tree is empty
        _root = new DNode(newAcct); //assign new root
        updateSize(_root);
        return true;
    }else{
        DNode *curr = _root;
        return traverseTreeInsert(curr,newAcct); //calls helper function to insert new account to tree
    }
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed) {
    if(_root == nullptr){ //if tree is empty
        return false;
    }else{
        DNode* curr = traverseTreeRemove(_root,disc); //get node to delete
        if(curr->getDiscriminator() == disc){ //sets node to vacant
            curr->_vacant = true;
            curr->_numVacant++;
            removed = curr;
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            return true;
        }else{
            return false;
        }
    }
}

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc){
    if(_root == nullptr){ //if tree is empty
        return nullptr;
    }
    DNode *curr = traverseTreeRetrive(_root, disc); //get node by helper function
    if(curr == nullptr){
        return nullptr;
    }
    if(curr->getDiscriminator() == disc && curr->isVacant() == false){ //returns node with the same disc
        return curr;
    }else{
        return nullptr;
    }
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {
    traverseTreeDelete(_root); //calls helper function to clear tree
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {
    traverseInOrder(_root); //calls helper function to print all nodes
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
    int nonVacant = 0;
    DNode *curr = _root;
    if(curr != nullptr){
        nonVacant = curr->getSize() - curr->getNumVacant(); //gets number of users by subtracting the size by number of vacant nodes
        return nonVacant;
    }else{
        return 0;
    }
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node) {
    node->_size = traverseInOrderUpdateSize(node); //calls helper function to update size
}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {
    node->_numVacant = traverseInOrderVacantSize(node); //calls helper function to update number of vacant nodes
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node) {
    if(node == nullptr){ //if node is a nullptr
        return false;
    }
    DNode *leftNode = node->_left;
    DNode *rightNode = node->_right;
    if(leftNode == nullptr || rightNode == nullptr){ //if either left or right nodes don't exist
        if(leftNode != nullptr){ //if left node exists, get size
            if(leftNode->getSize() >= 4) {
                return true;
            }else{
                return false;
            }
        }else if(rightNode != nullptr){ //if right node exists, get size
            if(rightNode->getSize() >= 4) {
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        if(leftNode->getSize() < 4 && rightNode->getSize() < 4){ //if sizes of each child is less than 4, there is no imbalance
            return false;
        }else if(leftNode->getSize() > rightNode->getSize()){
            if((100*(leftNode->getSize() - rightNode->getSize())/rightNode->getSize()) >= 50){ //if the size of left child is 50% bigger than size of right
                return true;
            }else{
                return false;
            }
        }else if (leftNode->getSize() < rightNode->getSize()){
            if((100*(rightNode->getSize() - leftNode->getSize())/leftNode->getSize()) >= 50){ //if the size of right child is 50% bigger than size of left
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
void DTree::rebalance(DNode*& node){
    DNode **nodeArray;
    nodeArray = new DNode*[node->getSize()]; //array to store the nodes in order
    int size = node->getSize();
    int newSize = node->getSize() - node->getNumVacant();
    int index = 0;
    arrayTreeConvert(node,nodeArray,index); //converts tree into an array
    for(int i = 0; i < size; i++){
        nodeArray[i]->_left = nullptr;
        nodeArray[i]->_right = nullptr;
    }
    for(int i = 0; i < size; i++){ //removes all vacant nodes
        if(nodeArray[i]->isVacant() == true){
            delete nodeArray[i];
            nodeArray[i] = nullptr;
        }
    }
    DNode** newNodeArray;
    newNodeArray = new DNode*[newSize];
    int counter = 0;
    int newCounter = 0;
    while(counter < size){
        if(nodeArray[counter]!= nullptr){ //creates new array with the vacant nodes removed
            newNodeArray[newCounter] = nodeArray[counter];
            counter++;
            newCounter++;
        }else{
            counter++;
        }
    }
    treeArrayConvert(newNodeArray, 0, newCounter-1, node); //calls helper function to convert array into a balanced tree
    traverseInOrderUpdateAllNodesSize(_root); //updates sizes
    traverseInOrderUpdateAllNodesVacant(_root); //updates vacant nodes
    for(int i = 0; i < newCounter; i++){ //deletes arrays
        newNodeArray[i] = nullptr;
    }
    for(int i = 0; i < counter; i++){
        nodeArray[i] = nullptr;
    }
    delete [] nodeArray;
    delete [] newNodeArray;
}

// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
//DNode* DTree::rebalance(DNode*& node) {

//}

//Helper Functions
void DTree::traverseTreeDelete(DNode* node){
    if(node == nullptr){ //base case
        return;
    }
    traverseTreeDelete(node->_left); //recursive cases
    traverseTreeDelete(node->_right);
    delete node;
}

bool DTree::traverseTreeInsert(DNode* node, Account newAcct){ //helper function for insert
    if(node->getDiscriminator() == newAcct.getDiscriminator() && node->isVacant() == false){ //if account with disc already exists and is not vacant
        return false;
    }
    if(node->getDiscriminator() == newAcct.getDiscriminator() && node->isVacant() == true){ //if account with disc already exists and is vacant
        node->_account = newAcct; //replaces nodes
        node->_vacant = false;
        traverseInOrderUpdateAllNodesSize(_root); //updates size
        traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant
        checkAllImbalance(_root); //check each node for imbalance
        return true;
    }
    if(node->isVacant() == true){ //if a node is vacant
        if(node->_right != nullptr && node->_left != nullptr){
            if(newAcct.getDiscriminator() < minNodeLeft(node->_right) && newAcct.getDiscriminator() > maxNodeRight(node->_left)){ //inserts node
                node->_account = newAcct;
                node->_vacant = false;
                traverseInOrderUpdateAllNodesSize(_root); //updates size
                traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
                checkAllImbalance(_root); //check each node for imbalance
                return true;
            }
        }else if(node->_right != nullptr && node->_left == nullptr){  //inserts node
            if(newAcct.getDiscriminator() < minNodeLeft(node->_right)){
                node->_account = newAcct;
                node->_vacant = false;
                traverseInOrderUpdateAllNodesSize(_root); //updates size
                traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
                checkAllImbalance(_root); //check each node for imbalance
                return true;
            }
        }else if(node->_right == nullptr && node->_left != nullptr){ //inserts node
            if(newAcct.getDiscriminator() > maxNodeRight(node->_left)){
                node->_account = newAcct;
                node->_vacant = false;
                traverseInOrderUpdateAllNodesSize(_root); //updates size
                traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
                checkAllImbalance(_root); //check each node for imbalance
                return true;
            }
        }else if(node->_right == nullptr && node->_left == nullptr){ //inserts node
            node->_account = newAcct;
            node->_vacant = false;
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            checkAllImbalance(_root); //check each node for imbalance
            return true;
        }
    }
    if(node->_left == nullptr && node->_right != nullptr){ //inserts node
        if(newAcct.getDiscriminator() < node->getDiscriminator()){
            node->_left = new DNode(newAcct);
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            checkAllImbalance(_root); //check each node for imbalance
            return true;
        }else{
            return traverseTreeInsert(node->_right, newAcct); //recursive case
        }
    }
    if(node->_left != nullptr && node->_right == nullptr){ //inserts node
        if(newAcct.getDiscriminator() > node->getDiscriminator()){
            node->_right = new DNode(newAcct);
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            checkAllImbalance(_root); //check each node for imbalance
            return true;
        }else{
            return traverseTreeInsert(node->_left, newAcct); //recursive case
        }
    }
    if(node->_left == nullptr && node->_right == nullptr){ //inserts node
        if(newAcct.getDiscriminator() > node->getDiscriminator()){
            node->_right = new DNode(newAcct);
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            checkAllImbalance(_root); //check each node for imbalance
            return true;
        }else if(newAcct.getDiscriminator() < node->getDiscriminator()){
            node->_left = new DNode(newAcct);
            traverseInOrderUpdateAllNodesSize(_root); //updates size
            traverseInOrderUpdateAllNodesVacant(_root); //updates number of vacant nodes
            checkAllImbalance(_root); //check each node for imbalance
            return true;
        }else{
            return false;
        }
    }
    if(newAcct.getDiscriminator() > node->getDiscriminator()){ //recursive cases
        return traverseTreeInsert(node->_right, newAcct);
    }else{
        return traverseTreeInsert(node->_left, newAcct);
    }
}


DNode* DTree::traverseTreeRemove(DNode* node, int data){ //helper function for remove
    if(node->getDiscriminator() == data){ //returns node matches data
        return node;
    }
    if(node->_left == nullptr && node->_right == nullptr){ //returns node is it has no child nodes
        return node;
    }
    if(node->_left != nullptr && node->_right == nullptr){ //recursive cases if node has only a left child
        return traverseTreeRemove(node->_left, data);
    }
    if(node->_left == nullptr && node->_right != nullptr){ //recursive cases if node has only a right child
        return traverseTreeRemove(node->_right, data);
    }
    if(data > node->getDiscriminator()){ //recursive cases
        return traverseTreeRemove(node->_right, data);
    }else{
        return traverseTreeRemove(node->_left, data);
    }
}

DNode* DTree::traverseTreeRetrive(DNode* node, int data){ //helper function for retrive
    if(node == nullptr){ //base case
        return nullptr;
    }
    if(node->getDiscriminator() == data){ //returns node matches data
        return node;
    }
    if(node->_left == nullptr && node->_right == nullptr){ //returns node is it has no child nodes
        return node;
    }
    if(data > node->getDiscriminator()){ //recursive cases
        return traverseTreeRetrive(node->_right, data);
    }else{
        return traverseTreeRetrive(node->_left, data);
    }
}
void DTree::traverseInOrder(DNode* node) const {
    if(node == nullptr){ //base case
        return;
    }
    traverseInOrder(node->_left); //recursive cases
    if(node->isVacant() == false){
        cout << node->getAccount() << endl; //prints out node in a in order traversal
    }
    traverseInOrder(node->_right);
}

int DTree::traverseInOrderUpdateSize(DNode* node){
    if(node == nullptr){ //base case
        return 0;
    }
    return traverseInOrderUpdateSize(node->_left) + 1 + traverseInOrderUpdateSize(node->_right); //recursive cases by adding 1 per node
}

int DTree::traverseInOrderVacantSize(DNode* node){
    if(node == nullptr){ //base case
        return 0;
    }
    if(node->isVacant() == true){ //recursive cases by adding 1 per vacant node
        return traverseInOrderVacantSize(node->_left) + 1 + traverseInOrderVacantSize(node->_right);
    }else{
        return traverseInOrderVacantSize(node->_left) + traverseInOrderVacantSize(node->_right);
    }
}

int DTree::minNodeLeft(DNode* node){
    if(node == nullptr){ //base case
        return -1;
    }
    int minVaule = node->getDiscriminator();
    if(node->_left != nullptr){
        minVaule = min(minVaule,minNodeLeft(node->_left)); //recursive cases by getting the minimun between minVaule and the vaule of its left node
    }
    return minVaule;
}

int DTree::maxNodeRight(DNode* node){
    if(node == nullptr){ //base case
        return -1;
    }

    int maxVaule = node->getDiscriminator();
    if(node->_right != nullptr){
        maxVaule = max(maxVaule,maxNodeRight(node->_right)); //recursive cases by getting the maximun between maxVaule and the vaule of its right node
    }

    return maxVaule;
}

void DTree::traverseInOrderUpdateAllNodesSize(DNode* node){
    if(node == nullptr){ //base case
        return;
    }
    traverseInOrderUpdateAllNodesSize(node->_left); //recursive cases
    updateSize(node); //updates the size of the node
    traverseInOrderUpdateAllNodesSize(node->_right);
}

void DTree::traverseInOrderUpdateAllNodesVacant(DNode* node){
    if(node == nullptr){ //base case
        return;
    }
    traverseInOrderUpdateAllNodesVacant(node->_left); //recursive cases
    updateNumVacant(node); //updates the number of vacant nodes
    traverseInOrderUpdateAllNodesVacant(node->_right);
}

void DTree::arrayTreeConvert(DNode* node, DNode** nodeArray, int &index){
    if(node == nullptr){ //base case
        return;
    }
    arrayTreeConvert(node->_left, nodeArray, index); //recursive cases
    nodeArray[index] = node; //moves node from tree to array
    index++;
    arrayTreeConvert(node->_right, nodeArray, index);
}

void DTree::treeArrayConvert(DNode** nodeArray, int start, int end, DNode *& node){
    if(start > end){ //base case
        return;
    }
    int mid = (start + end)/2; //moves node from array to tree by dividing array by hald
    node = nodeArray[mid];
    treeArrayConvert(nodeArray, start, mid-1,node->_left); //recursive cases
    treeArrayConvert(nodeArray, mid+1, end,node->_right);
}

void DTree::checkAllImbalance(DNode*& node){
    if(node == nullptr){ //base case
        return;
    }
    checkAllImbalance(node->_left); //recursive cases
    checkAllImbalance(node->_right);
    if(checkImbalance(node) == true){ //if balance exists, call rebalance
        rebalance(node);
    }
}


DNode* DTree::traverseInOrderAssigmentOperator(DNode* rhsNode){
    if(rhsNode == nullptr){ //base case
        return nullptr;
    }
    DNode *node = new DNode(); //copies node from rhs to this tree's node
    node->_account = rhsNode->_account;
    node->_numVacant = rhsNode->_numVacant;
    node->_vacant = rhsNode->_vacant;
    node->_size = rhsNode->_size;
    node->_left = traverseInOrderAssigmentOperator(rhsNode->_left); //recursive cases
    node->_right = traverseInOrderAssigmentOperator(rhsNode->_right);
    return node;
}

//----------------

/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() <<
         "\n\tDiscriminator: " << acct.getDiscriminator() <<
         "\n\tNitro: " << acct.hasNitro() <<
         "\n\tBadge: " << acct.getBadge() <<
         "\n\tStatus: " << acct.getStatus();
    return sout;
}

