#include "utree.h"
/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
    clear(); //calls clear function
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while(std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes -
         * Each line always has 5 sections of data */
        for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree.
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct) {
    if(_root == nullptr){ //if tree is empty
        _root = new UNode();
        _root->getDTree()->insert(newAcct); //sets new root
        return true;
    }else{
        UNode *curr = _root;
        return traverseTreeInsert(curr,newAcct); //call the helper function to insert node into tree
    }
}

/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {
    if(_root == nullptr){ //if tree is empty
        return false;
    }else{
        UNode* curr = _root;
        UNode *node = traverseTreeRemove(curr,username); //gets node to remove
        UNode* parentNode = nullptr;
        if(_root != node){
            parentNode = getParentNode(_root,node); //gets parent node
        }
        if(node->getUsername() == username){ //if obtained node matches username
            DNode* placeHolder = nullptr;
            bool isRemoved = node->getDTree()->remove(disc,placeHolder); //removes DNode that matches disrimator
            removed = placeHolder;
            if(isRemoved == true){ //if DNode is removed
                if(node->getDTree()->getNumUsers() <= 0){ //removes UNode if its DTree is empty
                    if(node->_left != nullptr){ //if UNode has a left child
                        UNode* nodeX = retrieve(maxNode(node->_left)); //gets the largest left child
                        node->_dtree->operator=(*nodeX->_dtree); //swaps nodes
                        UNode* parentX = getParentNode(_root,nodeX);
                        if(nodeX->_left != nullptr){ //gets nodeX left child if exitst and replace nodex with its left child
                            UNode* leftChild = nodeX->_left;
                            if(parentX->_left == nodeX){ //updates the parent node's or _root's pointer
                                delete nodeX;
                                nodeX = nullptr;
                                parentX->_left = leftChild;
                            }else if(parentX->_right == nodeX){
                                delete nodeX;
                                nodeX = nullptr;
                                parentX->_right = leftChild;

                            }
                        }else{
                            if(parentX->_left == nodeX){
                                delete nodeX;
                                parentX->_left = nullptr;
                                nodeX = nullptr;
                            }else if(parentX->_right == nodeX){
                                delete nodeX;
                                parentX->_right = nullptr;
                                nodeX = nullptr;
                            }
                        }
                    }else if(node->_right!= nullptr){ //if UNode has a right child if left node does not exits
                        UNode* nodeX = retrieve(minNode(node->_right));
                        node->_dtree->operator=(*nodeX->_dtree);
                        UNode* parentX = getParentNode(_root,nodeX);
                        if(nodeX->_right != nullptr){ //gets nodeX right child if exitst and replace nodex with its left right
                            UNode* rightChild = nodeX->_right;
                            if(parentX->_left == nodeX){ //updates the parent node's or _root's pointer
                                delete nodeX;
                                nodeX = nullptr;
                                parentX->_left = rightChild;
                            }else if(parentX->_right == nodeX){
                                delete nodeX;
                                nodeX = nullptr;
                                parentX->_right = rightChild;

                            }
                        }else{
                            if(parentX->_left == nodeX){
                                delete nodeX;
                                parentX->_left = nullptr;
                                nodeX = nullptr;
                            }else if(parentX->_right == nodeX){
                                delete nodeX;
                                parentX->_right = nullptr;
                                nodeX = nullptr;
                            }
                        }

                    }else{ //if UNode has no childs
                        delete node; //deletes UNode and updates parent node's or _root's pointers
                        if(_root == node){
                            _root = nullptr;
                            node = nullptr;
                        }else if(parentNode->_left == node){
                            parentNode->_left = nullptr;
                            node = nullptr;
                        }else if(parentNode->_right == node) {
                            parentNode->_right = nullptr;
                            node = nullptr;
                        }
                    }
                }
                traverseAllHeight(_root); //updates height
                checkAllImbalance(_root); //check each node for imbalance
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
}

/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
    if(_root == nullptr){ //if tree is empty
        return nullptr;
    }
    UNode *curr = traverseTreeRetrive(_root, username); //uses helper function to obtain node with matching username
    if(curr == nullptr){ //if helper function finds no such node
        return nullptr;
    }
    if(curr->getUsername() == username){ //if helper function finds matching node
        return curr;
    }else{
        return nullptr;
    }
}

/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
    if(_root == nullptr){ //if tree is empty
        return nullptr;
    }
    UNode *curr = traverseTreeRetrive(_root, username); //uses helper function to obtain node with matching username
    if(curr == nullptr){ //if helper function finds no such node
        return nullptr;
    }
    if(curr->getUsername() == username){ //if helper function finds matching node
        DNode* dNode = curr->getDTree()->retrieve(disc); //retrive DNode
        if(dNode != nullptr && dNode->getDiscriminator() == disc){ //if DNode is found
            return dNode;
        }else{
            return nullptr;
        }
    }else{
        return nullptr;
    }
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
    if(retrieve(username) != nullptr){
        return retrieve(username)->getDTree()->getNumUsers(); //gets number of users of UNode's dtree.
    }else{
        return 0;
    }
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
    traverseTreeDelete(_root); //deletes all nodes in UTree
}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {
    traverseInOrder(_root); //traverse through all nodes in order to print them
}

/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
    node->_height = traverseHeight(node); //updates height of node
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {
    if(node == nullptr){ //if node is a nullptr
        return 0;
    }
    UNode *leftNode = node->_left;
    UNode *rightNode = node->_right;
    if (leftNode == nullptr && rightNode == nullptr) { //if node has no child nodes
        return 0;
    }else{
        return getBalanceFactor(node); //gets balance factor. (left height - right height)
    }
}

//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */

void UTree::rebalance(UNode*& node){
    UNode* parentNode = nullptr;
    UNode* oldNode = node;
    string oldUsername = node->getUsername();
    if(_root->getUsername() != node->getUsername()){
        parentNode = getParentNode(_root,oldNode); //get parent node
    }
    if(getBalanceFactor(node) > 1 && getBalanceFactor(node->_left) >= 0){ //right rotation
        rightRotate(node);
    }else if (getBalanceFactor(node) > 1  && getBalanceFactor(node->_left) <= -1){ //left right rotation
        leftRotate(node->_left);
        rightRotate(node);
    }else if (getBalanceFactor(node) < -1 && getBalanceFactor(node->_right) <= 0){ //left rotation
        leftRotate(node);
    }else if (getBalanceFactor(node) < -1 && getBalanceFactor(node->_right) >= 1){ //right left rotation
        rightRotate(node->_right);
        leftRotate(node);
    }
    traverseAllHeight(node); //updates node

    if(_root == oldNode){ //updates parent node's pointers
        _root = node;
    }else if(parentNode->_left == oldNode){
        parentNode->_left = node;
    }else if(parentNode->_right == oldNode){
        parentNode->_right = node;
    }
    traverseAllHeight(_root); //updates node
    checkAllImbalance(_root); //check each node for imbalance
}



/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
 /*
UNode* UTree::rebalance(UNode* node) {

}
  */
//----------------


//Helper Functions
bool UTree::traverseTreeInsert(UNode *curr, Account newAcct){
    if(newAcct.getUsername() == curr->getUsername()){ //attempts inserts node if usernames matches
        bool isInsert = curr->getDTree()->insert(newAcct);
        if(isInsert == true){ //updates height and check each node for imbalance
            traverseAllHeight(_root);
            checkAllImbalance(_root);
            return true;
        }else{
            return false;
        }
    }
    if(curr->_left == nullptr && curr->_right != nullptr){ //inserts node
        if(newAcct.getUsername() < curr->getUsername()){
            curr->_left = new UNode();
            curr->_left->getDTree()->insert(newAcct);
            traverseAllHeight(_root);
            checkAllImbalance(_root);
            return true;
        }else{
            return traverseTreeInsert(curr->_right, newAcct); //rescursive case
        }
    }
    if(curr->_left != nullptr && curr->_right == nullptr){ //inserts node
        if(newAcct.getUsername() > curr->getUsername()){
            curr->_right = new UNode();
            curr->_right->getDTree()->insert(newAcct);
            traverseAllHeight(_root);
            checkAllImbalance(_root);
            return true;
        }else{
            return traverseTreeInsert(curr->_left, newAcct); //rescursive case
        }
    }
    if(curr->_left == nullptr && curr->_right == nullptr){ //inserts node
        if(newAcct.getUsername() > curr->getUsername()){
            curr->_right = new UNode();
            curr->_right->getDTree()->insert(newAcct);
            traverseAllHeight(_root);
            checkAllImbalance(_root);
            return true;
        }else if(newAcct.getUsername() < curr->getUsername()){
            curr->_left = new UNode();
            curr->_left->getDTree()->insert(newAcct);
            traverseAllHeight(_root);
            checkAllImbalance(_root);
            return true;
        }else{
            return false;
        }
    }
    if(newAcct.getUsername() > curr->getUsername()){ //rescursive case
        return traverseTreeInsert(curr->_right, newAcct);
    }else{
        return traverseTreeInsert(curr->_left, newAcct);
    }
}

UNode* UTree::traverseTreeRemove(UNode* node, string username){ //helper function for remove
    if(node->getUsername() == username){ //returns node if usernames matches
        return node;
    }
    if(node->_left == nullptr && node->_right == nullptr){ //returns node if it has no childs
        return node;
    }
    if(node->_left != nullptr && node->_right == nullptr){ //recursive cases
        return traverseTreeRemove(node->_left, username);
    }
    if(node->_left == nullptr && node->_right != nullptr){ //recursive cases
        return traverseTreeRemove(node->_right, username);
    }
    if(username > node->getUsername()){ //recursive cases
        return traverseTreeRemove(node->_right, username);
    }else{
        return traverseTreeRemove(node->_left, username);
    }
}

string UTree::maxNode(UNode* node){
    if(node == nullptr){ //base case
        return "";
    }
    string maxVaule = node->getUsername();
    if(node->_right != nullptr){ //recursive cases
        maxVaule = max(maxVaule,maxNode(node->_right)); //gets max vaule
    }
    return maxVaule;
}

string UTree::minNode(UNode* node) {
    if(node == nullptr){ //base case
        return "";
    }
    string minVaule = node->getUsername();
    if(node->_left != nullptr){ //recursive cases
        minVaule = min(minVaule,minNode(node->_left)); //gets min vaule
    }
    return minVaule;
}

UNode* UTree::traverseTreeRetrive(UNode* node, string username){
    if(node == nullptr){ //base case
        return nullptr;
    }
    if(node->getUsername() == username){ //returns node if usernames matches
        return node;
    }
    if(node->_left == nullptr && node->_right == nullptr){ //returns node if it has no childs
        return node;
    }
    if(username > node->getUsername()){ //recursive cases
        return traverseTreeRetrive(node->_right, username);
    }else{
        return traverseTreeRetrive(node->_left, username);
    }
}

void UTree::traverseInOrder(UNode* node) const {
    if (node == nullptr){ //base case
        return;
    }
    traverseInOrder(node->_left); //recursive cases
    node->_dtree->printAccounts(); //prints the node's dtree accounts
    traverseInOrder(node->_right);
}

int UTree::traverseHeight(UNode* node){
    if (node == nullptr) //base case
        return -1;
    else {
        int leftHeight = traverseHeight(node->_left);
        int rightHeight = traverseHeight(node->_right);
        if (leftHeight > rightHeight){ //recursive cases by adding 1 height per node
            return leftHeight + 1;
        }else{
            return rightHeight + 1;
        }
    }
}

void UTree::traverseAllHeight(UNode* node) {
    if (node == nullptr){ //base case
        return;
    }
    traverseAllHeight(node->_left); //recursive cases
    node->_height = traverseHeight(node); //sets that node's height
    traverseAllHeight(node->_right);
}

void UTree::traverseTreeDelete(UNode* node){
    if(node == nullptr){ //base case
        return;
    }
    traverseTreeDelete(node->_left); //recursive cases
    traverseTreeDelete(node->_right);
    delete node; //deletes node
}

void UTree::checkAllImbalance(UNode* node){
    if (node == nullptr){ //base case
        return;
    }
    checkAllImbalance(node->_left); //recursive cases
    if(abs(checkImbalance(node)) > 1){ //calls rebalance if an imbalance exists
        rebalance(node);
    }
    checkAllImbalance(node->_right);
}

int UTree::getBalanceFactor(UNode *node){
    if(node == nullptr){ //if node is nullptr
        return 0;
    }else{
        UNode *leftNode = node->_left;
        UNode *rightNode = node->_right;
        if(leftNode == nullptr && rightNode == nullptr){ //if node has no childs
            return 0;
        }else if(leftNode != nullptr && rightNode == nullptr){ //if node has only a left node
            return node->getHeight();
        }else if(leftNode == nullptr && rightNode != nullptr){ //if node has only a right node
            return node->getHeight() * -1;
        }else{
            return (leftNode->getHeight() + 1) - (rightNode->getHeight() + 1); //returns left height minus right height
        }

    }
}

void UTree::rightRotate(UNode*& c){
    UNode* b = c->_left; //performs a right rotation
    UNode* childNode = b->_right;
    b->_right = c;
    c->_left = childNode; //moves child node of b
    c = b;
}
void UTree::leftRotate(UNode*& c) {
    UNode* b = c->_right; //performs a left rotation
    UNode* childNode = b->_left;
    b->_left = c;
    c->_right = childNode; //moves child node of b
    c = b;
}


UNode* UTree::getParentNode(UNode* curr, UNode* oldNode){
    if (curr->_left == nullptr && curr->_right == nullptr){ //returns nullptr if curr has no childs
        return nullptr;
    }
    if(curr->_left == oldNode || curr->_right == oldNode){ //returns curr if curr has only one child
        return curr;
    }
    if(curr->_left != nullptr && curr->_right == nullptr){ //recursive cases if curr has only a left child
        return getParentNode(curr->_left, oldNode);
    }
    if(curr->_left == nullptr && curr->_right != nullptr){ //recursive cases if curr has only a right child
        return getParentNode(curr->_right, oldNode);
    }
    if(oldNode->getUsername() > curr->getUsername()){ //recursive cases
        return getParentNode(curr->_right, oldNode);
    }else{
        return getParentNode(curr->_left, oldNode);
    }
}

