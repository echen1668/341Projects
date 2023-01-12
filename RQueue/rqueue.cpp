// CMSC 341 - Spring 2021 - Project 3
// RQueue:

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
    _heap = nullptr; //sets heap to nullptr as it starts as an empty tree
    _size = 0; //sets size to 0
    priority = priFn; //sets priority
}

RQueue::~RQueue()
{
    clear(); //calls clear to delete tree
}

RQueue::RQueue(const RQueue& rhs)
{
    _heap = traverseInOrderCopyConstructor(rhs._heap); //calls helper function to copy rhs into this tree
    _size = rhs._size; //sets size
    priority = rhs.priority; //sets priority
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
    if(&rhs != this){
        clear(); //clears previous tree
        _heap = traverseInOrderAssigmentOperator(rhs._heap); //calls helper function to copy rhs into this tree
        _size = rhs._size; //sets size
        priority = rhs.priority; //sets priority
        return *this;
    }else{
        cout << "Cannot Self Assign" << endl; //if self assign occurs
        return *this;
    }
}

void RQueue::insertStudent(const Student& input) {
    if(_heap == nullptr){ //if tree is empty
        _heap = new Node(input); //sets heap/root
        _size = updateSize(_heap); //updates size
    }else{
        mergeHelper(_heap,new Node(input)); //calls helper merge function to insert new node
        _size = updateSize(_heap); //updates size
    }
}

Student RQueue::getNextStudent() {
    if(_heap == nullptr){ //if tree is empty, it will throw an expection
        throw std::domain_error("Heap is empty");
    }else{
        Student removed = _heap->getStudent(); //sets removed to root node with highest priority
        Node* leftNode = _heap->_left; //gets left subtree
        Node* rightNode = _heap->_right; //gets right subtree
        delete _heap; //removes root
        _heap = nullptr;
        _size--; //updates size
        if(leftNode == nullptr && rightNode == nullptr){ //resets the heap/root and returns removed node
            return removed;
        }
        if(leftNode != nullptr && rightNode == nullptr){ //if there is only a left node
            _heap = leftNode;
            return removed;
        }
        if(leftNode == nullptr && rightNode != nullptr){ //if there is only a right node
            _heap = rightNode;
            return removed;
        }
        if(priority(leftNode->getStudent()) < priority(rightNode->getStudent())){
            _heap = leftNode;
            mergeHelper(leftNode,rightNode);
        }else{
            _heap = rightNode;
            mergeHelper(rightNode,leftNode);
        }
        return removed;
    }
}


void RQueue::mergeWithQueue(RQueue& rhs) {
    if(&rhs != this){
        if(priority != rhs.priority){ //if priority for both trees are different, a domain error will be thrown
            throw std::domain_error("Priorities are different");
        }else{
            mergeHelper(_heap,rhs._heap); //calls helper function to merge trees
            _size = updateSize(_heap); //updates size
            rhs._size = 0; //deletes rhs node
            rhs._heap = nullptr;
        }
    }else{
        cout << "Cannot self-merge" << endl;
    }
}

void RQueue::clear() {
    traverseTreeDelete(_heap); //calls helper function to delete every node
    _heap = nullptr; //sets all member variables
    _size = 0;
    priority = nullptr;
}

int RQueue::numStudents() const
{
    return _size; //returns size, the number of students
}

void RQueue::printStudentQueue() const {
    traverseInOrderPrint(_heap); //calls helper function to print all nodes in preorder traversal
}

prifn_t RQueue::getPriorityFn() const {
    return priority; //return priority
}

void RQueue::setPriorityFn(prifn_t priFn) {
    priority = priFn; //resets priority
    Student** nodeArray;
    nodeArray = new Student*[_size]; //array to store the nodes in order
    int size = _size; //gets old size
    int index = 0;
    arrayTreeConvert(_heap,nodeArray,index); //converts tree into an array
    traverseTreeDelete(_heap);
    _heap = nullptr;
    sortArray(nodeArray,size); //sorts array in asending order by priority
    for(int i = 0; i < size; i++){
        insertStudent(*nodeArray[i]); //inserts node based on new priority
    }
    for(int i = 0; i < size; i++){ //deletes the array
        delete nodeArray[i];
        nodeArray[i] = nullptr;
    }
    delete [] nodeArray;
}

// for debugging
void RQueue::dump() const
{
    if (_size == 0) {
        cout << "Empty skew heap.\n" ;
    } else {
        dump(_heap);
        cout << endl;
    }
}

// for debugging
void RQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->_left);
        cout << priority(pos->_student) << ":" << pos->_student.getName();
        dump(pos->_right);
        cout << ")";
    }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
    sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
         << ", year: " << student.getYear() << ", major: " << student.getMajorStr()
         << ", group: " << student.getGroupStr();
    return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getStudent();
    return sout;
}


//Helper functions
void RQueue::traverseTreeDelete(Node* node){
    if(node == nullptr){ //base case
        return;
    }
    traverseTreeDelete(node->_left); //recursive cases
    traverseTreeDelete(node->_right);
    delete node; //delete node
    node = nullptr;
}

Node* RQueue::traverseInOrderAssigmentOperator(Node* rhsNode){
    if(rhsNode == nullptr){ //base case
        return nullptr;
    }
    Node *node = new Node(rhsNode->_student); //copies node from rhs to this tree's node
    node->_left = traverseInOrderAssigmentOperator(rhsNode->_left); //recursive cases
    node->_right = traverseInOrderAssigmentOperator(rhsNode->_right);
    return node;
}

Node* RQueue::traverseInOrderCopyConstructor(Node* rhsNode){
    if(rhsNode == nullptr){ //base case
        return nullptr;
    }
    Node *node = new Node(rhsNode->_student); //copies node from rhs to this tree's node
    node->_left = traverseInOrderCopyConstructor(rhsNode->_left); //recursive cases
    node->_right = traverseInOrderCopyConstructor(rhsNode->_right);
    return node;
}

void RQueue::traverseInOrderPrint(Node* node) const {
    if(node == nullptr){ //base case
        return;
    }
    cout << "[" << priority(node->getStudent()) << "] " << node->getStudent() << endl; //prints node
    traverseInOrderPrint(node->_left); //recursive cases
    traverseInOrderPrint(node->_right);
}

void RQueue::mergeHelper(Node*& node, Node* rhsNode){
    if(node == nullptr && rhsNode == nullptr){ //base case
        return;
    }
    if(node != nullptr && rhsNode == nullptr){ //base case
        return;
    }
    if(node == nullptr && rhsNode != nullptr){ //sets empty node to rhs node
        node = rhsNode;
        return;
    }
    if(priority(node->_student) <= priority(rhsNode->_student)){ //keeps going down the tree until rhs node priority is less than node priority
        mergeHelper(node->_right,rhsNode);
    }else if(priority(node->_student) > priority(rhsNode->_student)){ //swaps node
        Node *temp = node;
        node = rhsNode;
        mergeHelper(node->_right,temp); //keeps going down the tree until rhs node priority is less than node priority
    }
    Node *temp2 = node->_right; //rotates left and right subtrees
    node->_right = node->_left;
    node->_left = temp2;

}

int RQueue::updateSize(Node* node) {
    if (node == nullptr) { //base case
        return 0;
    }
    return updateSize(node->_left) + 1 + updateSize(node->_right); //recursive cases by adding 1 per node
}

void RQueue::arrayTreeConvert(Node* node, Student** nodeArray, int &index){
    if(node == nullptr){ //base case
        return;
    }
    arrayTreeConvert(node->_left, nodeArray, index); //recursive cases
    //Student(string name, int priority, int year, int major, int group)
    nodeArray[index] = new Student(node->getStudent().getName(),node->getStudent().getPriority(),node->getStudent().getYear(),node->getStudent().getMajor(),node->getStudent().getGroup());//copies student from node into array
    index++; //increases index
    arrayTreeConvert(node->_right, nodeArray, index);
}

void RQueue::sortArray(Student**& nodeArray, int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(priority(*nodeArray[j]) < priority(*nodeArray[i])){ //sorts array into an asending order based on priority
                Student* temp = nodeArray[i];
                nodeArray[i] = nodeArray[j];
                nodeArray[j] = temp;
            }
        }
    }
}
