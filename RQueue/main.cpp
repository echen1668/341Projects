#include <iostream>
#include <stdexcept>
#include "rqueue.h"
using namespace std;
// Priority functions compute an integer priority for a student. Internal
// computations may be floating point, but must return an integer.

const string names1[10] = {"Eric", "Allen", "Lamar", "Patrick", "Mike", "Luke", "Sam", "Barry", "Chad", "Ottis"}; //names
const string names2[10] = {"Charlie", "Ed", "Anthony", "Taylor", "David", "Ben", "Jerry", "Danny", "Randy", "Wally"}; //names
const int num[7] = {0,1,2,3,4,5,6}; //prioirty numbers

class Tester {
public:
    void testingInsert(RQueue& queue1);
    bool testingInsertRemove(RQueue& queue1);
    bool testingInsertRemoveOneNode(RQueue& queue1);
    bool testingMerging(RQueue& queue1, RQueue& queue2);
    bool testingMergingHostEmpty(RQueue& queue1, RQueue& queue2);
    bool testingMergingRhsEmpty(RQueue& queue1, RQueue& queue2);
    bool testingMergingDifferentPriorty(RQueue& queue1, RQueue& queue2);
    void testingMergingSelfMerging(RQueue& queue1);
    bool testingCopyConstructor(RQueue& queue1);
    bool testingCopyConstructorOneNode(RQueue& queue1);
    bool testingCopyConstructorZeroNode(RQueue& queue1);
    bool testingAssigmentOperator(RQueue& queue1);
    bool testingAssigmentOperatorOneNode(RQueue& queue1);
    bool testingAssigmentOperatorZeroNode(RQueue& queue1);
    bool testingAssigmentOperatorAssignedTwice(RQueue& queue1);
    void testingAssigmentOperatorSelfAssign(RQueue& queue1);
    bool testingChangePrioritization(RQueue& queue1);
    bool testingChangePrioritizationOneNode(RQueue& queue1);
    bool testingChangePrioritizationZeroNodes(RQueue& queue1);
    bool testingRemoveEmptyTree(RQueue& queue1);
    bool testingRemoveEmptyTreeExtraStep(RQueue& queue1);
    bool checkForHeapRule(RQueue& queue1);
    void testingEfficneyInsert(RQueue &queue1, int numTrials, int N);
    void testingEfficneyRemove(RQueue &queue1, int numTrials, int N);
    void traverseAssigment(Node* node, Node* node2, bool &assigment);
    void traverseCopy(Node* node, Node* node2, bool &assigment);
    void traverseHeap(RQueue* queue1,Node* node, bool &isHeap);
};

int priorityTest1(const Student &tudent);
int priorityTest2(const Student &tudent);
int priorityFn1(const Student &tudent);
int priorityFn2(const Student &student);

int main() {
    Tester tester; //tester class

    RQueue queueInsert(priorityTest1);
    //Testing RQueue insertion
    cout << "Testing RQueue insertion..." << endl;
    tester.testingInsert(queueInsert);
    cout << "Resulting RQueue:" << endl;
    queueInsert.dump();
    cout << endl;

    RQueue queueInsertRemove(priorityTest1);
    //Testing RQueue insertion and removal
    cout << "Testing RQueue insertion and removal...";
    if(tester.testingInsertRemove(queueInsertRemove)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueInsertRemoveOneNode(priorityTest1);
    //Testing RQueue insertion and removal for one node
    cout << "Testing RQueue insertion and removal for one node...";
    if(tester.testingInsertRemoveOneNode(queueInsertRemoveOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueMerge1(priorityTest1);
    RQueue queueMerge2(priorityTest1);
    //Testing RQueue merging
    cout << "Testing RQueue merging...";
    if(tester.testingMerging(queueMerge1,queueMerge2)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueMerge1Host(priorityTest1);
    RQueue queueMerge2Host(priorityTest1);
    //Testing RQueue merging when host tree is empty.
    cout << "Testing RQueue merging when host tree is empty...";
    if(tester.testingMergingHostEmpty(queueMerge1Host,queueMerge2Host)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueMerge1Rhs(priorityTest1);
    RQueue queueMerge2Rhs(priorityTest1);
    //Testing RQueue merging when rhs tree is empty.
    cout << "Testing RQueue merging when rhs tree is empty...";
    if(tester.testingMergingRhsEmpty(queueMerge1Rhs,queueMerge2Rhs)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueMergeDifferent1(priorityTest1);
    RQueue queueMergeDifferent2(priorityTest2);
    //Testing RQueue merging with different priorities
    cout << "Testing RQueue merging with different priorities...";
    if(tester.testingMergingDifferentPriorty(queueMergeDifferent1,queueMergeDifferent2)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting RQueue:" << endl;
    queueMergeDifferent1.dump();
    cout << endl;

    RQueue queueMergeSelfMerge(priorityTest1);
    //Testing RQueue self merging should print out "Cannot self-merge"
    cout << "Testing RQueue self merging should print out \"Cannot self-merge\"..." << endl;
    tester.testingMergingSelfMerging(queueMergeSelfMerge);
    cout << endl;

    RQueue queueCopyConstructor(priorityTest1);
    //Testing RQueue copy constructor
    cout << "Testing RQueue copy constructor...";
    if(tester.testingCopyConstructor(queueCopyConstructor)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueCopyConstructorOneNode(priorityTest1);
    //Testing RQueue copy constructor with only one node
    cout << "Testing RQueue copy constructor with only one node...";
    if(tester.testingCopyConstructorOneNode(queueCopyConstructorOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueCopyConstructorZeroNode(priorityTest1);
    //Testing RQueue copy constructor with zero nodes
    cout << "Testing RQueue copy constructor with zero nodes...";
    if(tester.testingCopyConstructorZeroNode(queueCopyConstructorZeroNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueAssigmentOperator(priorityTest1);
    //Testing RQueue assigment operator
    cout << "Testing RQueue assigment operator...";
    if(tester.testingAssigmentOperator(queueAssigmentOperator)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueAssigmentOperatorOneNode(priorityTest1);
    //Testing RQueue assigment operator with only one node
    cout << "Testing RQueue assigment operator with only one node...";
    if(tester.testingAssigmentOperatorOneNode(queueAssigmentOperatorOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueAssigmentOperatorZeroNode(priorityTest1);
    //Testing RQueue assigment operator with zero nodes
    cout << "Testing RQueue assigment operator with zero nodes...";
    if(tester.testingAssigmentOperatorZeroNode(queueAssigmentOperatorZeroNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueAssigmentOperatorAssignedTwice(priorityTest1);
    //Testing RQueue assigment operator assigned twice
    cout << "Testing RQueue assigment operator assigned twice...";
    if(tester.testingAssigmentOperatorAssignedTwice(queueAssigmentOperatorAssignedTwice)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueAssigmentOperatorSelfAssign(priorityTest1);
    //Testing RQueue assigment operator self assignment
    cout << "Testing RQueue assigment operator self assignment should print out \"Cannot self-assign\"...";
    tester.testingAssigmentOperatorSelfAssign(queueAssigmentOperatorSelfAssign); //should print out "Cannot self-assign"
    cout << endl;

    RQueue queueChangePriority(priorityTest1);
    //Testing RQueue changing priority
    cout << "Testing RQueue changing priority...";
    if(tester.testingChangePrioritization(queueChangePriority)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueChangePriorityOneNode(priorityTest1);
    //Testing RQueue changing priority with only one node
    cout << "Testing RQueue changing priority with only one node...";
    if(tester.testingChangePrioritizationOneNode(queueChangePriorityOneNode)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueChangePriorityZeroNodes(priorityTest1);
    //Testing RQueue changing priority with an empty heap
    cout << "Testing RQueue changing priority an empty heap...";
    if(tester.testingChangePrioritizationZeroNodes(queueChangePriorityZeroNodes)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueRemoveEmptyTree(priorityTest1);
    //Testing RQueue remove an empty tree
    cout << "Testing RQueue remove an empty tree...";
    if(tester.testingRemoveEmptyTree(queueRemoveEmptyTree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueRemoveEmptyTreeExtraStep(priorityTest1);
    //Testing RQueue remove an empty tree when it already removes that tree
    cout << "Testing RQueue remove an empty tree when it already removes that tree...";
    if(tester.testingRemoveEmptyTreeExtraStep(queueRemoveEmptyTreeExtraStep)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueCheckForHeap(priorityTest2);
    //Testing RQueue checking if tree follow heap rules
    cout << "Testing RQueue checking if tree follow heap rules..";
    cout << endl;
    if(tester.checkForHeapRule(queueCheckForHeap)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    RQueue queueInsertEfficency(priorityTest1);
    //Testing RQueue time efficeny on insertion
    cout << "Testing RQueue time efficeny on insertion..." << endl;
    int A = 5;//number of trials
    int B = 500;//original input size
    tester.testingEfficneyInsert(queueInsertEfficency,A,B);
    cout << endl;

    RQueue queueRemoveEfficency(priorityTest1);
    //Testing RQueue time efficeny on removal
    cout << "Testing RQueue time efficeny on removal..." << endl;
    int C = 5;//number of trials
    int D = 500;//original input size
    tester.testingEfficneyRemove(queueRemoveEfficency,C,D);
    cout << endl;

    RQueue queue1(priorityFn1);
    RQueue queue2(priorityFn1);

    // Create some test students and insert them into the queue
    //Student(string name, int priority, int year, int major, int group)
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);

    queue1.insertStudent(student3);
    queue1.insertStudent(student1);
    queue1.insertStudent(student2);
    queue1.insertStudent(student4);

    std::cout << "\nqueue1 dump after inserting 4 students (Nick, Sam, Liz, Eva):" << std::endl;
    queue1.dump();

    Student student5("John",6,3,2,1);
    Student student6("Mia",3,0,0,0);

    queue2.insertStudent(student5);
    queue2.insertStudent(student6);

    std::cout << "\nqueue2 dump after inserting 2 students (John, Mia):" << std::endl;
    queue2.dump();

    queue1.mergeWithQueue(queue2);

    std::cout << "\nqueue2 dump after merge:" << std::endl;
    queue2.dump();
    // Print the queue, change priority function, print again, change
    // again, print again.  Changing the priority function should cause
    // the heap to be rebuilt.

    std::cout << std::endl << "Contents of queue1 after merging with queue2:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after merging with queue2:\n";
    queue1.dump();
    cout << endl;
    RQueue queue3(queue1);
    std::cout << "\nDump queue3 after copying with queue1:\n";
    queue3.dump();



    queue1.setPriorityFn(priorityFn2);

    std::cout << std::endl << "Contents of queue1 after changing the priority function to priorityFn2:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
    queue1.dump();
    cout << endl;
    RQueue queue4 = queue1;
    std::cout << "\nDump queue4 after copying with queue1:\n";
    queue4.dump();

    queue1.setPriorityFn(priorityFn1);

    std::cout << std::endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
    queue1.dump();

    // Remove and print students in priority order

    std::cout << "\nFinal queue1 in priority order:\n";
    while (queue1.numStudents() > 0) {
        Student student = queue1.getNextStudent();
        std::cout << "[" << priorityFn1(student) << "] " << student << std::endl;
    }


    return 0;
}

int priorityTest1(const Student&student) {
    //priority is determined by an officer in registrar office
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    return student.getPriority();
}

int priorityTest2(const Student&student) {
    //priority value is determined based on some criteria
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    int priority = student.getYear() + student.getMajor() + student.getGroup();
    return priority;
}

int priorityFn1(const Student&student) {
    //priority value is determined based on some criteria
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    int priority = student.getYear() + student.getMajor() + student.getGroup();
    return priority;
}

int priorityFn2(const Student&student) {
    //priority is determined by an officer in registrar office
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    return student.getPriority();
}

//test functions
void Tester::testingInsert(RQueue &queue1){
    cout << endl;
    cout << "Tree at each insertion:" << endl;
    for(int i = 0; i < 10; i++){ //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        cout << "Inserting " << names1[i] << " with priority " << newStudent.getPriority() << endl;
        queue1.insertStudent(newStudent);
        queue1.dump();
    }
    cout << "Result from printStudentQueue" << endl;
    queue1.printStudentQueue(); //prints them
}

bool Tester::testingInsertRemove(RQueue &queue1){
    for(int i = 0; i < 10; i++){ //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Tree:" << endl;
    queue1.dump();
    while (queue1.numStudents() > 0){ //removes the 10 nodes
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
        queue1.dump();
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingInsertRemoveOneNode(RQueue &queue1){
    for(int i = 0; i < 1; i++){ //inserts only one node
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Tree:" << endl;
    queue1.dump();
    while (queue1.numStudents() > 0){ //removes the one node
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
        queue1.dump();
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingMerging(RQueue &queue1, RQueue &queue2){
    bool isHeap = true;
    for(int i = 0; i < 5; i++){ //inserts 10 nodes for the first queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "First Tree:" << endl;
    queue1.dump();
    for(int i = 0; i < 6; i++){ //inserts 10 nodes for the second queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names2[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue2.insertStudent(newStudent);
    }
    cout << "Second Tree:" << endl;
    queue2.dump();
    int size1 = queue1.numStudents();
    int size2 = queue2.numStudents();
    queue1.mergeWithQueue(queue2); //merges the two trees
    cout << "Resulting RQueue:" << endl;
    queue1.dump();
    if(queue1.numStudents() != (size1 + size2)) { //checks if the sum of the two sizes equal to new size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check for heap rule
    if (isHeap == false){ //returns true if heap rule is followed, false if not
        return false;
    }
    while (queue1.numStudents() > 0){ //removes the nodes in order
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingMergingHostEmpty(RQueue &queue1, RQueue &queue2){
    bool isHeap = true;
    for(int i = 0; i < 0; i++){ //no nodes will be inserted for host tree
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "First Tree:" << endl;
    queue1.dump(); //first tree should be empty
    for(int i = 0; i < 6; i++){ //inserts 10 nodes for the second queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names2[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue2.insertStudent(newStudent);
    }
    cout << "Second Tree:" << endl;
    queue2.dump();
    int size1 = queue1.numStudents();
    int size2 = queue2.numStudents();
    queue1.mergeWithQueue(queue2); //merges the two trees
    cout << "Resulting RQueue:" << endl;
    queue1.dump();
    if(queue1.numStudents() != (size1 + size2)) { //checks if the sum of the two sizes equal to new size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check for heap rule
    if (isHeap == false){ //returns true if heap rule is followed, false if not
        return false;
    }
    while (queue1.numStudents() > 0){ //removes the nodes in order
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingMergingRhsEmpty(RQueue &queue1, RQueue &queue2){
    bool isHeap = true;
    for(int i = 0; i < 5; i++){ //inserts 10 nodes for the first queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "First Tree:" << endl;
    queue1.dump();
    for(int i = 0; i < 0; i++){ //no nodes will be inserted for rhs tree
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names2[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue2.insertStudent(newStudent);
    }
    cout << "Second Tree:" << endl;
    queue2.dump(); //second tree should be empty
    int size1 = queue1.numStudents();
    int size2 = queue2.numStudents();
    queue1.mergeWithQueue(queue2); //merges the two trees
    cout << "Resulting RQueue:" << endl;
    queue1.dump();
    if(queue1.numStudents() != (size1 + size2)) { //checks if the sum of the two sizes equal to new size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check for heap rule
    if (isHeap == false){ //returns true if heap rule is followed, false if not
        return false;
    }
    while (queue1.numStudents() > 0){ //removes the nodes in order
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingMergingDifferentPriorty(RQueue &queue1, RQueue &queue2) {
    for (int i = 0; i < 5; i++) { //inserts 10 nodes for the first queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "First Tree:" << endl;
    queue1.dump();
    for (int i = 0; i < 6; i++) { //inserts 10 nodes for the second queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names2[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue2.insertStudent(newStudent);
    }
    cout << "Second Tree:" << endl;
    queue2.dump();
    try { //should throw an expection
        queue1.mergeWithQueue(queue2);
    }
    catch (domain_error &e) {
        //the exception that we expect
        cout << "Expection caught" << endl;
        return true;
    }
    catch (...) {
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

void Tester::testingMergingSelfMerging(RQueue& queue1){
    for (int i = 0; i < 5; i++) { //inserts 10 nodes for the first queue
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    queue1.mergeWithQueue(queue1); //attempts self merge, should print out "Cannot self merge"
}

bool Tester::testingCopyConstructor(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2(queue1); //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue1._heap == queue2._heap){ //check address
        return false;
    }
    traverseCopy(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingCopyConstructorOneNode(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 1; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2(queue1); //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue1._heap == queue2._heap){ //check address
        return false;
    }
    traverseCopy(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingCopyConstructorZeroNode(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 0; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2(queue1); //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    traverseCopy(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingAssigmentOperator(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2 = queue1; //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue1._heap == queue2._heap){ //check address
        return false;
    }
    traverseAssigment(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingAssigmentOperatorOneNode(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 1; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2 = queue1; //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue1._heap == queue2._heap){ //check address
        return false;
    }
    traverseAssigment(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingAssigmentOperatorZeroNode(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 0; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2 = queue1; //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    traverseAssigment(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingAssigmentOperatorAssignedTwice(RQueue &queue1){
    bool assigment = true; //true if a deep copy is made, else false
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    RQueue queue2 = queue1; //copies tree
    cout << "Copied Tree:" << endl;
    queue2.dump();
    if (queue1.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue1._heap == queue2._heap){ //check address
        return false;
    }
    traverseAssigment(queue1._heap,queue2._heap,assigment); //checks each node
    if(assigment == false){
        return false;
    }
    RQueue queue3(priorityTest1);
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names2[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue3.insertStudent(newStudent);
    }
    cout << "Second Inital Tree:" << endl;
    queue3.dump();
    queue2 = queue3; //copies tree again
    cout << "Second Copied Tree:" << endl;
    queue2.dump();
    if (queue3.numStudents() != queue2.numStudents()){ //check number of students
        return false;
    }
    if (queue3._heap == queue2._heap){ //check address
        return false;
    }
    traverseAssigment(queue3._heap,queue2._heap,assigment); //checks each node
    if(assigment == true){
        return true;
    }else{
        return false;
    }
}

void Tester::traverseAssigment(Node* node, Node* node2, bool &assigment){
    if (node == nullptr || node2 == nullptr) { //base cases
        return;
    }
    traverseAssigment(node->_left, node2->_left, assigment); //recursive cases
    if (node->getStudent().getName() != node2->getStudent().getName() || node->getStudent().getPriority() != node2->getStudent().getPriority() || node->getStudent().getYear() != node2->getStudent().getYear()) { //false if nodes are not the same
        assigment = false;
    }
    traverseAssigment(node->_right, node2->_right, assigment);
}

void Tester::traverseCopy(Node* node, Node* node2, bool &assigment) {
    if (node == nullptr || node2 == nullptr) { //base cases
        return;
    }
    traverseCopy(node->_left, node2->_left, assigment); //recursive cases
    if (node->getStudent().getName() != node2->getStudent().getName() || node->getStudent().getPriority() != node2->getStudent().getPriority() || node->getStudent().getYear() != node2->getStudent().getYear()) { //false if nodes are not the same
        assigment = false;
    }
    traverseCopy(node->_right, node2->_right, assigment);
}

void Tester::testingAssigmentOperatorSelfAssign(RQueue& queue1){
    cout << endl;
    queue1 = queue1; //Should print out cannot "Cannot Self-Assign"
}

bool Tester::testingChangePrioritization(RQueue& queue1){
    bool isHeap = true;
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    int size1 = queue1.numStudents(); //get first size
    queue1.setPriorityFn(priorityTest2); //change priority
    cout << "Final Tree:" << endl;
    queue1.dump();
    int size2 = queue1.numStudents(); //get second size
    if(size1 != size2){ //check size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check if heap follows min-heap rules
    if(isHeap == false){
        return false;
    }
    while(queue1.numStudents() > 0){ //removes the 10 nodes
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingChangePrioritizationOneNode(RQueue& queue1){
    bool isHeap = true;
    for (int i = 0; i < 1; i++) { //inserts only one node
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    int size1 = queue1.numStudents(); //get first size
    queue1.setPriorityFn(priorityTest2); //change priority
    cout << "Final Tree:" << endl;
    queue1.dump();
    int size2 = queue1.numStudents(); //get second size
    if(size1 != size2){ //check size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check if heap follows min-heap rules
    if(isHeap == false){
        return false;
    }
    while(queue1.numStudents() > 0){ //removes the only node
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingChangePrioritizationZeroNodes(RQueue& queue1){
    bool isHeap = true;
    for (int i = 0; i < 0; i++) { //no nodes will be inserted at all
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Inital Tree:" << endl;
    queue1.dump();
    int size1 = queue1.numStudents(); //get first size
    queue1.setPriorityFn(priorityTest2); //change priority
    cout << "Final Tree:" << endl;
    queue1.dump();
    int size2 = queue1.numStudents(); //get second size
    if(size1 != size2){ //check size
        return false;
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check if heap follows min-heap rules
    if(isHeap == false){
        return false;
    }
    while(queue1.numStudents() > 0){ //removes the only node
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
    }
    if(queue1.numStudents() == 0){
        return true;
    }else{
        return false;
    }
}

bool Tester::testingRemoveEmptyTree(RQueue& queue1){
    try { //should throw an expection
        queue1.getNextStudent();
    }
    catch (domain_error &e) {
        //the exception that we expect
        cout << endl;
        cout << "Expection caught" << endl;
        return true;
    }
    catch (...) {
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester::testingRemoveEmptyTreeExtraStep(RQueue& queue1){
    for (int i = 0; i < 5; i++) { //inserts 5 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    cout << endl;
    cout << "Tree:" << endl;
    queue1.dump();
    while(queue1.numStudents() > 0){ //removes 5 nodes
        Student student = queue1.getNextStudent();
        prifn_t treePriority = queue1.getPriorityFn();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
        queue1.dump();
    }
    try { //should throw an expection
        queue1.getNextStudent();
    }
    catch (domain_error &e) {
        //the exception that we expect
        cout << "Expection caught" << endl;
        return true;
    }
    catch (...) {
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester::checkForHeapRule(RQueue &queue1) {
    bool isHeap = true; //bool for if heap rule is followed
    for (int i = 0; i < 10; i++) { //inserts 10 nodes
        //Student(string name, int priority, int year, int major, int group)
        Student newStudent(names1[i],num[rand()%7],rand()%4,rand()%3,rand()%2);
        queue1.insertStudent(newStudent);
    }
    traverseHeap(&queue1,queue1._heap,isHeap); //check for heap rule
    if(isHeap == false) { //returns false if heap rule is not followed
        return false;
    }
    cout << "Resulting RQueue:" << endl;
    queue1.dump();
    while(queue1.numStudents() > 0 && isHeap == true){
        prifn_t treePriority = queue1.getPriorityFn();
        Student student = queue1.getNextStudent();
        std::cout << "[" << treePriority(student) << "] " << student << std::endl;
        traverseHeap(&queue1, queue1._heap, isHeap);
        if(isHeap == false) { //returns false if heap rule is not followed
            return false;
        }
    }
    if(isHeap == true){ //returns true if heap rule is followed, false if not
        return true;
    }else{
        return false;
    }
}

void Tester::traverseHeap(RQueue* queue1,Node* node, bool &isHeap){
    if(node == nullptr || (node->_left == nullptr && node->_right == nullptr)){ //base cases
        return;
    }
    traverseHeap(queue1, node->_left, isHeap); //recursive cases
    if(node->_left != nullptr && node->_right == nullptr){ //check if heap rule is followed or violated
        if(queue1->priority(node->getStudent()) > queue1->priority(node->_left->getStudent())){
            isHeap = false;
        }
    }else if(node->_left == nullptr && node->_right != nullptr){
        if(queue1->priority(node->getStudent()) > queue1->priority(node->_right->getStudent())){
            isHeap = false;
        }
    }else{
        if(queue1->priority(node->getStudent()) > queue1->priority(node->_left->getStudent()) || queue1->priority(node->getStudent()) > queue1->priority(node->_right->getStudent()) ){
            isHeap = false;
        }
    }
    traverseHeap(queue1, node->_right, isHeap); //recursive cases
}


void Tester::testingEfficneyInsert(RQueue &queue1, int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        start = clock();
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            Student newStudent("", 1, 1, 1, 1);
            queue1.insertStudent(newStudent);
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}

void Tester::testingEfficneyRemove(RQueue &queue1, int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            Student newStudent("", 1, 1, 1, 1);
            queue1.insertStudent(newStudent);
        }
        start = clock();
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            queue1.getNextStudent();
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Removing " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}