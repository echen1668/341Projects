// CMSC 341 - Spring 2021 - Project 4
// driver.cpp
// Simple driver program for use with HashTable class
#include "hash.h"
#include <random>

// Using a fixed seed value generates always the same sequence
// of pseudorandom numbers, e.g. reproducing scientific experiments
// here it helps us with testing since the same sequence repeats
std::mt19937 generator(10);// 10 is the fixed seed value

const string names1[20] = {"Eric", "Allen", "Lamar", "Patrick", "Mike", "Luke", "Sam", "Barry", "Chad", "Ottis", "Charlie", "Ed", "Anthony", "Taylor", "David", "Ben", "Jerry", "Danny", "Randy", "Wally"}; //randomized names

// We distribute the pseudorandom numbers uniformaly within
// the range [1000,99999]
std::uniform_int_distribution<> distribution(1000, 99999);

// The hash function used by HashTable class
unsigned int hashCode(const string str);

// the function to generate random serial numbers
unsigned int vaccineSerial() {return distribution(generator);}

class Tester{ // Tester class to implement test functions
public:
    Tester(){}
    ~Tester(){}
    bool testingInsert(HashTable &hashTable1);
    bool testingInsertSameNode(HashTable &hashTable1);
    bool testingInsertSameNodeAfterDelete(HashTable &hashTable1);
    bool testingRemove(HashTable &hashTable1);
    bool testingRemoveInEmptyTable(HashTable &hashTable1);
    bool testingRemoveObjectNotInTable(HashTable &hashTable1);
    bool testingRemoveObjectNotInTableQuadratic(HashTable &hashTable1);
    bool testingLinearProbing(HashTable &hashTable1);
    bool testingLinearProbingDifferentNames(HashTable &hashTable1);
    bool testingQuadraticProbing(HashTable &hashTable1);
    bool testingQuadraticProbingDifferentNames(HashTable &hashTable1);
    bool testingReHashing(HashTable &hashTable1);
    bool testingReHashingDifferentNames(HashTable &hashTable1);
    bool testingReHashingDelete(HashTable &hashTable1);
    bool testingReHashingDeleteDifferentNames(HashTable &hashTable1);
    bool testingInsertRemove(HashTable &hashTable1);
    bool testingInsertRemoveQuadratic(HashTable &hashTable1);
    bool testingInsertRemoveDifferentNames(HashTable &hashTable1);
    bool testingInsertRemoveDifferentNamesQuadratic(HashTable &hashTable1);
    bool testingInsertRemoveOneObject(HashTable &hashTable1);
    bool testingInsertRemoveOneObjectQuadratic(HashTable &hashTable1);
    bool testingMinPrimes();
    bool testingMaxPrimes();
    bool testingMaxSize();
private:
    int getIndex(HashTable &hashTable1, Person person1); //helper function
};

int main(){

    // We use this temp array to store some data points for later use
    int tempSerials[50] = {0};
    int secondIndex = 0;
    // create a hash table with the size 101, and the hash function hashCode
    HashTable aTable(101,hashCode);
    int temp = 0;
    // we insert 50 Person objects with the same key, person's name is the key
    for (int i=0;i<50;i++){
        temp = vaccineSerial();// generates a random number
        if (i%3 == 0){//this saves 17 numbers from the generated numbers for later use
            tempSerials[secondIndex] = temp;
            cout << temp << " was saved for later use." << endl;
            secondIndex++;
        }
        // print the random numbers which are inserted
        cout << "Insertion # " << i << " => " << temp << endl;
        aTable.insert(Person("John", temp));
    }
    cout << "Message: dump after 50 insertions in a table with 101 buckets:" << endl;
    aTable.dump();

    // We insert a data point to change the load factor, this should initiate a rehash
    temp = vaccineSerial();
    cout << "Insertion # 51" << " => " << temp << endl;
    aTable.insert(Person("John", temp));
    cout << "Message: dump after 51st insertion, the rehash should have happended to a table with 211 buckets:" << endl;
    aTable.dump();

    // Now we remove some data points which were saved in tempSerials array
    // Deleting 13 data points changes the deleteRatio, it should initiate a rehash
    for (int i = 0;i<14;i++)
        aTable.remove(Person("John", tempSerials[i]));
    cout << "Message: dump after 14 removes, a rehash should have happened to a table with 157 buckets," << endl;
    cout << "Message: after 13 removals the rehash happens, then the 14th removal will be tagged as DELETED in the new table." << endl;
    aTable.dump();
    cout << endl;

    Tester tester; //test class

    int size = 101;
    HashTable hashTableInsert(size,hashCode);
    //Testing Hash Table insertion
    cout << "Testing Hash Table insertion..." << endl;
    if(tester.testingInsert(hashTableInsert)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsert.dump();
    cout << endl;

    HashTable hashTableInsertSameNode(size,hashCode);
    //Testing Hash Table insertion with the same node
    cout << "Testing Hash Table insertion with the same node..." << endl;
    if(tester.testingInsertSameNode(hashTableInsertSameNode)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    HashTable hashTableInsertSameNodeAfterDelete(size,hashCode);
    //Testing Hash Table insertion with the same bucket after it is deleted
    cout << "Testing Hash Table insertion with the same bucket after it is deleted..." << endl;
    if(tester.testingInsertSameNodeAfterDelete(hashTableInsertSameNodeAfterDelete)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    HashTable hashTableRemove(size,hashCode);
    //Testing Hash Table removal
    cout << "Testing Hash Table removal..." << endl;
    if(tester.testingRemove(hashTableRemove)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableRemove.dump();
    cout << endl;

    HashTable hashTableRemoveEmptyTable(size,hashCode);
    //Testing Hash Table removal in an empty table
    cout << "Testing Hash Table removal in an empty table..." << endl;
    if(tester.testingRemoveInEmptyTable(hashTableRemoveEmptyTable)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    HashTable hashTableRemoveObjectNotInTable(size,hashCode);
    //Testing Hash Table removal of object not in table
    cout << "Testing Hash Table removal of object not in table..." << endl;
    if(tester.testingRemoveObjectNotInTable(hashTableRemoveObjectNotInTable)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    HashTable hashTableRemoveObjectNotInTableQuadratic(size,hashCode);
    //Testing Hash Table removal of object not in table under quadratic probing
    cout << "Testing Hash Table removal of object not in table under quadratic probing..." << endl;
    if(tester.testingRemoveObjectNotInTableQuadratic(hashTableRemoveObjectNotInTableQuadratic)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    int size2 = 201;
    HashTable hashTableLinearProbing(size2,hashCode);
    //Testing Hash Table linear probling
    cout << "Testing Hash Table linear probling..." << endl;
    if(tester.testingLinearProbing(hashTableLinearProbing)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableLinearProbing.dump();
    cout << endl;

    HashTable hashTableLinearProbingDifferentNames(size2,hashCode);
    //Testing Hash Table linear probling with different names
    cout << "Testing Hash Table linear probling with different names..." << endl;
    if(tester.testingLinearProbingDifferentNames(hashTableLinearProbingDifferentNames)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableLinearProbingDifferentNames.dump();
    cout << endl;

    HashTable hashTableQuadraticProbing(size2,hashCode);
    //Testing Hash Table quadratic probling
    cout << "Testing Hash Table quadratic probling..." << endl;
    if(tester.testingQuadraticProbing(hashTableQuadraticProbing)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableQuadraticProbing.dump();
    cout << endl;

    HashTable hashTableQuadraticProbingDifferentNames(size2,hashCode);
    //Testing Hash Table quadratic probling with different names
    cout << "Testing Hash Table quadratic probling with different names..." << endl;
    if(tester.testingQuadraticProbingDifferentNames(hashTableQuadraticProbingDifferentNames)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableQuadraticProbingDifferentNames.dump();
    cout << endl;

    HashTable hashTableReHash(size,hashCode);
    //Testing Hash Table rehashing
    cout << "Testing Hash Table rehashing..." << endl;
    if(tester.testingReHashing(hashTableReHash)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableReHash.dump();
    cout << endl;

    HashTable hashTableReHashDifferentNames(size,hashCode);
    //Testing Hash Table rehashing with different names
    cout << "Testing Hash Table rehashing with different names..." << endl;
    if(tester.testingReHashingDifferentNames(hashTableReHashDifferentNames)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableReHashDifferentNames.dump();
    cout << endl;

    HashTable hashTableReHashDelete(size,hashCode);
    //Testing Hash Table rehashing after deleting nodes
    cout << "Testing Hash Table rehashing after deleting nodes..." << endl;
    if(tester.testingReHashingDelete(hashTableReHashDelete)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableReHashDelete.dump();
    cout << endl;

    HashTable hashTableReHashDeleteDifferentNames(size,hashCode);
    //Testing Hash Table rehashing after deleting nodes with different names
    cout << "Testing Hash Table rehashing after deleting nodes with different names..." << endl;
    if(tester.testingReHashingDeleteDifferentNames(hashTableReHashDeleteDifferentNames)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableReHashDeleteDifferentNames.dump();
    cout << endl;

    HashTable hashTableInsertRemove(size,hashCode);
    //Testing Hash Table insertng and removing elements
    cout << "Testing Hash Table insertng and removing elements.." << endl;
    if(tester.testingInsertRemove(hashTableInsertRemove)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertRemove.dump();
    cout << endl;

    HashTable hashTableInsertRemoveQuadratic(size,hashCode);
    //Testing Hash Table insertng and removing elements under quadratic probing
    cout << "Testing Hash Table insertng and removing elements under quadratic probing.." << endl;
    if(tester.testingInsertRemoveQuadratic(hashTableInsertRemoveQuadratic)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertRemoveQuadratic.dump();
    cout << endl;

    HashTable hashTableInsertRemoveDifferentNames(size,hashCode);
    //Testing Hash Table insertng and removing elements with different names
    cout << "Testing Hash Table insertng and removing elements with different names.." << endl;
    if(tester.testingInsertRemoveDifferentNames(hashTableInsertRemoveDifferentNames)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertRemoveDifferentNames.dump();
    cout << endl;

    HashTable hashTableInsertRemoveDifferentNamesQuadratic(size,hashCode);
    //Testing Hash Table insertng and removing elements with different names under quadratic probing
    cout << "Testing Hash Table insertng and removing elements with different names under quadratic probing.." << endl;
    if(tester.testingInsertRemoveDifferentNamesQuadratic(hashTableInsertRemoveDifferentNamesQuadratic)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertRemoveDifferentNamesQuadratic.dump();
    cout << endl;

    HashTable hashTableInsertOneObject(size,hashCode);
    //Testing Hash Table insertng and removing one elemet
    cout << "Testing Hash Table insertng and removing one elemet.." << endl;
    if(tester.testingInsertRemoveOneObject(hashTableInsertOneObject)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertOneObject.dump();
    cout << endl;

    HashTable hashTableInsertOneObjectQuadratic(size,hashCode);
    //Testing Hash Table insertng and removing one object under quadratic probing
    cout << "Testing Hash Table insertng and removing one object under quadratic probing.." << endl;
    if(tester.testingInsertRemoveOneObjectQuadratic(hashTableInsertOneObjectQuadratic)){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting Tree;" << endl;
    hashTableInsertOneObjectQuadratic.dump();
    cout << endl;

    //Testing creating Hash Table with MINPRIME
    cout << "Testing creating Hash Table with MINPRIME.." << endl;
    if(tester.testingMinPrimes()){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    //Testing creating Hash Table with MAXPRIME
    cout << "Testing creating Hash Table with MAXPRIME.." << endl;
    if(tester.testingMaxPrimes()){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;

    //Testing if table rehash when inserting elements inital size times
    cout << "Testing if table rehash when inserting elements inital size times.." << endl;
    if(tester.testingMaxSize()){
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << endl;


    return 0;
}

// The implementation of the hash function
// you can copy this function to your mytest.cpp file
unsigned int hashCode(const string str) {
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    for ( int i = 0 ; i < str.length(); i++)
        val = val * thirtyThree + str[i] ;
    return val ;
}

//test functions
bool Tester::testingInsert(HashTable &hashTable1){
    int temp = 0;
    for (int i=0;i<20;i++){ //will insert non-collison elements, each with a different name
        temp = vaccineSerial();// generates a random number
        Person person1(Person(names1[i], temp));
        int index = hashTable1.m_hash(person1.key()) % hashTable1.tableSize(); //calacuates the index person1 should be inserted in
        if(hashTable1.insert(person1) == false){ //test fails if insertion fails
            return false;
        }
        if(getIndex(hashTable1,person1) != index){ //test fails if index is not correct
            return false;
        }
    }
    return true;
}

bool Tester::testingInsertSameNode(HashTable &hashTable1){
    int temp = 0;
    for (int i=1;i<10;i++){
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
    }
    if(hashTable1.insert(Person("John", temp)) == false){ //test pass if insertion the same person (the last bucket inserted) fails
        return true;
    }else{
        return false;
    }
}

bool Tester::testingInsertSameNodeAfterDelete(HashTable &hashTable1){
    int temp = 0;
    for (int i=1;i<10;i++){
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
    }
    hashTable1.remove(Person("John", temp)); //removes the last bucket inserted
    if(hashTable1.insert(Person("John", temp)) == true){ //test pass if insertion the same person (the last bucket inserted) succeds
        return true;
    }else{
        return false;
    }
}

bool Tester::testingRemove(HashTable &hashTable1){
    int tempSerials[50] = {1}; //keeps array of serial numbers
    int secondIndex = 0;
    int temp = 0;
    for (int i=1;i<50;i++){
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    for (int i = 1;i<13;i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false){ //test fails if removal fails
            return false;
        }
    }
    if(hashTable1.m_numDeleted != 12){
        return false;
    }
    return true;
}

bool Tester::testingRemoveInEmptyTable(HashTable &hashTable1){
    int tempSerials[50] = {1};
    int secondIndex = 0;
    int temp = 0;
    for (int i=1;i<1;i++){ //will not insert anything
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    if(hashTable1.remove(Person("John", tempSerials[0])) == false){ //test pass if removal fails
        return true;
    }else{
        return false;
    }
}

bool Tester::testingRemoveObjectNotInTable(HashTable &hashTable1) {
    int tempSerials[50] = {1};
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 10; i++) {
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    tempSerials[12] = 999; //adds serial number that is not in table
    if (hashTable1.remove(Person("Mike", tempSerials[12])) == false) { //test pass if removal fails
        return true;
    } else {
        return false;
    }
}

bool Tester::testingRemoveObjectNotInTableQuadratic(HashTable &hashTable1){
    hashTable1.m_currentProb = QUADRATIC; //sets probing to quadratic
    int tempSerials[50] = {1};
    int secondIndex = 0;
    int temp = 0;
    for (int i=1;i<10;i++){
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    tempSerials[12] = 999; //adds serial number that is not in table
    if(hashTable1.remove(Person("Joe", tempSerials[12])) == false){ //test pass if removal fails
        return true;
    }else{
        return false;
    }
}

bool Tester::testingLinearProbing(HashTable &hashTable1){
    hashTable1.m_currentProb = LINEAR; //sets probing to linear
    int temp = 0;
    for (int i=1;i<51;i++) {
        temp = vaccineSerial();// generates a random number
        Person person1(Person("John", temp));
        int index = hashTable1.m_hash(person1.key()) % hashTable1.tableSize(); //calacuates the index person1 should be inserted in
        if(hashTable1.m_table[index].key() != "" && hashTable1.m_table[index].serial() != 0){ //if that index is empty, insert it in
            int i = 0;
            while(hashTable1.m_table[index].key() != ""){ //gets new index to insert
                index = (hashTable1.m_hash(person1.key()) + i) % hashTable1.tableSize();
                i++;
            }
        }
        if(hashTable1.insert(person1) == false){ //test fails if insertion fails
            return false;
        }
        if(getIndex(hashTable1,person1) != index){ //test fails if index is not correct
            return false;
        }
    }
    return true;
}

bool Tester::testingLinearProbingDifferentNames(HashTable &hashTable1){
    hashTable1.m_currentProb = LINEAR; //sets probing to linear
    int temp = 0;
    for (int i=1;i<51;i++) {
        temp = vaccineSerial();// generates a random number
        Person person1(Person(names1[rand()%20], temp));
        int index = hashTable1.m_hash(person1.key()) % hashTable1.tableSize(); //calacuates the index person1 should be inserted in
        if(hashTable1.m_table[index].key() != "" && hashTable1.m_table[index].serial() != 0){ //if that index is empty, insert it in
            int i = 0;
            while(hashTable1.m_table[index].key() != ""){ //gets new index to insert
                index = (hashTable1.m_hash(person1.key()) + i) % hashTable1.tableSize();
                i++;
            }
        }
        if(hashTable1.insert(person1) == false){ //test fails if insertion fails
            return false;
        }
        if(getIndex(hashTable1,person1) != index){ //test fails if index is not correct
            return false;
        }
    }
    return true;
}

bool Tester::testingQuadraticProbing(HashTable &hashTable1) {
    hashTable1.m_currentProb = QUADRATIC; //sets probing to quadratic
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        Person person1(Person("John", temp));
        int index = hashTable1.m_hash(person1.key()) %
                    hashTable1.tableSize(); //calacuates the index person1 should be inserted in
        if (hashTable1.m_table[index].key() != "" &&
            hashTable1.m_table[index].serial() != 0) { //if that index is empty, insert it in
            int i = 0;
            while (hashTable1.m_table[index].key() != "") { //gets new index to insert
                index = ((hashTable1.m_hash(person1.key()) % hashTable1.tableSize()) + (i * i)) %
                        hashTable1.tableSize();
                i++;
            }
        }
        if (hashTable1.insert(person1) == false) { //test fails if insertion fails
            return false;
        }
        if (getIndex(hashTable1, person1) != index) { //test fails if index is not correct
            return false;
        }
    }
    return true;
}

bool Tester::testingQuadraticProbingDifferentNames(HashTable &hashTable1){
    hashTable1.m_currentProb = QUADRATIC; //sets probing to quadratic
    int temp = 0;
    for (int i=1;i<51;i++) {
        temp = vaccineSerial();// generates a random number
        Person person1(Person(names1[rand()%20], temp));
        int index = hashTable1.m_hash(person1.key()) % hashTable1.tableSize(); //calacuates the index person1 should be inserted in
        if(hashTable1.m_table[index].key() != "" && hashTable1.m_table[index].serial() != 0){ //if that index is empty, insert it in
            int i = 0;
            while(hashTable1.m_table[index].key() != ""){ //gets new index to insert
                index = ((hashTable1.m_hash(person1.key()) % hashTable1.tableSize()) + (i*i)) % hashTable1.tableSize();
                i++;
            }
        }
        if(hashTable1.insert(person1) == false){ //test fails if insertion fails
            return false;
        }
        if(getIndex(hashTable1,person1) != index){ //test fails if index is not correct
            return false;
        }
    }
    return true;
}

bool Tester::testingReHashing(HashTable &hashTable1) {
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        if (hashTable1.insert(Person("John", temp)) == false) { //test fails if insertion fails
            return false;
        }
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    int newSize = hashTable1.findNextPrime(4 * (ceil(float(hashTable1.tableSize()) / 2.0) - hashTable1.m_numDeleted)); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after rehashing" << endl;
    for (int i = 51; i < 101; i++) {
        temp = vaccineSerial();// generates a random number
        if (hashTable1.insert(Person("John", temp)) == false) { //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after rehashing" << endl;
    if (hashTable1.tableSize() != newSize) { //test fails if size is not correct
        return false;
    }
    cout << "Second Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    newSize = hashTable1.findNextPrime(4 * (ceil((float(hashTable1.tableSize()) / 2.0) - hashTable1.m_numDeleted))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after second rehashing" << endl;
    for (int i = 101; i < 151; i++) {
        temp = vaccineSerial();// generates a random number
        if (hashTable1.insert(Person("John", temp)) == false) { //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after second rehashing" << endl;
    if (hashTable1.tableSize() != newSize) { //test fails if size is not correct
        return false;
    }
    return true;
}

bool Tester::testingReHashingDifferentNames(HashTable &hashTable1){
    int temp = 0;
    for (int i=1;i<51;i++){
        temp = vaccineSerial();// generates a random number
        if(hashTable1.insert(Person(names1[rand()%20], temp)) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    int newSize = hashTable1.findNextPrime(4*(ceil(float(hashTable1.tableSize())/2.0) - hashTable1.m_numDeleted)); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after rehashing" << endl;
    for (int i=51;i<101;i++){
        temp = vaccineSerial();// generates a random number
        if(hashTable1.insert(Person(names1[rand()%20], temp)) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after rehashing" << endl;
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    cout << "Second Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    newSize = hashTable1.findNextPrime(4*(ceil((float(hashTable1.tableSize())/2.0) - hashTable1.m_numDeleted))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after second rehashing" << endl;
    for (int i=101;i<151;i++){
        temp = vaccineSerial();// generates a random number
        if(hashTable1.insert(Person(names1[rand()%20], temp)) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after second rehashing" << endl;
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    return true;
}

bool Tester::testingReHashingDelete(HashTable &hashTable1){
    int tempSerials[51] = {1}; //array of serial number
    int secondIndex = 0;
    int temp = 0;
    for (int i=1;i<51;i++){
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp;
    }
    for (int i = 1;i<13;i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    int newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after rehashing" << endl;
    for (int i = 13;i<15;i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after rehashing" << endl;
    cout << "Second Tree;" << endl;
    hashTable1.dump(); //prints second tree
    if(hashTable1.tableSize() != newSize) { //test fails if size is not correct
        return false;
    }
    newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after second rehashing" << endl;
    for (int i = 15;i<30;i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after second rehashing" << endl;
    cout << "Third Tree;" << endl;
    hashTable1.dump(); //prints second tree
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after third rehashing" << endl;
    for (int i = 30;i<51;i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after third rehashing" << endl;
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    return true;
}

bool Tester::testingReHashingDeleteDifferentNames(HashTable &hashTable1){
    int tempSerials[51] = {1}; //array of serial number
    string tempName[51] = {""}; //array of string names
    int secondIndex = 0;
    int temp = 0;
    for (int i=1;i<51;i++){
        temp = vaccineSerial();// generates a random number
        string nameKey = names1[rand()%20];
        hashTable1.insert(Person(nameKey, temp));
        tempSerials[i] = temp;
        tempName[i] = nameKey;
    }
    for (int i = 1;i<13;i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump(); //prints inital tree
    int newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after rehashing" << endl;
    for (int i = 13;i<15;i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after rehashing" << endl;
    cout << "Second Tree;" << endl;
    hashTable1.dump(); //prints second tree
    if(hashTable1.tableSize() != newSize) { //test fails if size is not correct
        return false;
    }
    newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after second rehashing" << endl;
    for (int i = 15;i<30;i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after second rehashing" << endl;
    cout << "Third Tree;" << endl;
    hashTable1.dump(); //prints second tree
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    newSize = hashTable1.findNextPrime(4*(hashTable1.numEntries() - ceil(float(hashTable1.numEntries())*0.25))); //calacautes new size when rehasing occurs
    cout << "Size should  be " << newSize << " after third rehashing" << endl;
    for (int i = 30;i<51;i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    cout << "Size is " << hashTable1.tableSize() << " after third rehashing" << endl;
    if(hashTable1.tableSize() != newSize){ //test fails if size is not correct
        return false;
    }
    return true;
}

bool Tester::testingInsertRemove(HashTable &hashTable1) {
    int tempSerials[51] = {1}; //array of serial number
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 51; i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false) { //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0) { //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingInsertRemoveQuadratic(HashTable &hashTable1) {
    hashTable1.m_currentProb = QUADRATIC; //set to quadratic
    int tempSerials[51] = {1}; //array of serial number
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 51; i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false) { //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0) { //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingInsertRemoveDifferentNames(HashTable &hashTable1) {
    int tempSerials[51] = {1}; //array of serial number
    string tempName[51] = {""}; //array of string names
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        string nameKey = names1[rand()%20];
        hashTable1.insert(Person(nameKey, temp));
        tempSerials[i] = temp; //adds serial number to array
        tempName[i] = nameKey; //adds name to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 51; i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false){ //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0){ //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingInsertRemoveDifferentNamesQuadratic(HashTable &hashTable1) {
    hashTable1.m_currentProb = QUADRATIC; //set to quadratic
    int tempSerials[51] = {1}; //array of serial number
    string tempName[51] = {""}; //array of string names
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 51; i++) {
        temp = vaccineSerial();// generates a random number
        string nameKey = names1[rand() % 20];
        hashTable1.insert(Person(nameKey, temp));
        tempSerials[i] = temp; //adds serial number to array
        tempName[i] = nameKey; //adds name to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 51; i++) {
        if (hashTable1.remove(Person(tempName[i], tempSerials[i])) == false) { //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0) { //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingInsertRemoveOneObject(HashTable &hashTable1) {
    int tempSerials[51] = {1}; //array of serial number
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 2; i++) {
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 2; i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false) { //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0) { //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingInsertRemoveOneObjectQuadratic(HashTable &hashTable1){
    hashTable1.m_currentProb = QUADRATIC; //set to quadratic
    int tempSerials[51] = {1}; //array of serial number
    int secondIndex = 0;
    int temp = 0;
    for (int i = 1; i < 2; i++) {
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
        tempSerials[i] = temp; //adds serial number to array
    }
    cout << "Inital Tree;" << endl;
    hashTable1.dump();
    for (int i = 1; i < 2; i++) {
        if (hashTable1.remove(Person("John", tempSerials[i])) == false) { //test fails if insertion fails
            return false;
        }
    }
    if (hashTable1.numEntries() == 0) { //test fails if table is not empty
        return true;
    } else {
        return false;
    }
}

bool Tester::testingMinPrimes(){
    int size = 100; //size less than MINPRIME
    HashTable hashTable1(size,hashCode); //creates hash table
    if(!(hashTable1.tableSize() == MINPRIME && hashTable1.tableSize() > size)){ //checks if table size/capacity is not size, but MINPRIME
        return false;
    }
    int size2 = 101; //size equal to MINPRIME
    HashTable hashTable2(size2,hashCode); //creates hash table
    if(!(hashTable2.tableSize() == MINPRIME && hashTable2.tableSize() == size2)){ //checks if table size/capacity is MINPRIME
        return false;
    }
    int size3 = 102; //size greater than MINPRIME
    HashTable hashTable3(size3,hashCode); //creates hash table
    if(!(hashTable3.tableSize() > MINPRIME && hashTable3.tableSize() == hashTable3.findNextPrime(size3))){ //checks if table size/capacity is not MINPRIME, but size3
        return false;
    }
    return true;
}

bool Tester::testingMaxPrimes(){
    int size = 99992; //size greater than MAXPRIME
    HashTable hashTable1(size,hashCode); //creates hash table
    if(!(hashTable1.tableSize() == MAXPRIME && hashTable1.tableSize() < size)){ //checks if table size/capacity is not size, but MAXPRIME
        return false;
    }
    hashTable1.setProbingPolicy(QUADRATIC);
    int size2 = 99991; //size equal to MAXPRIME
    HashTable hashTable2(size2,hashCode); //creates hash table
    if(!(hashTable2.tableSize() == MAXPRIME && hashTable2.tableSize() == size2)) { //checks if table size/capacity is MAXPRIME
        return false;
    }
    int size3 = 99990; //size greater than MAXPRIME
    HashTable hashTable3(size3,hashCode); //creates hash table
    if(!(hashTable3.tableSize() <= MAXPRIME && hashTable3.tableSize() == hashTable3.findNextPrime(size3))) { //checks if table size/capacity is not MAXPRIME, but size3
        return false;
    }
    return true;
}

bool Tester::testingMaxSize(){
    int size = 101; //size less than MINPRIME
    HashTable hashTable1(size,hashCode); //creates hash table
    cout << "Inital size is " << hashTable1.tableSize() << endl;
    int temp = 0;
    for (int i = 0; i < (size + 2); i++) { //inserts a number of elements greater than to the inital size
        temp = vaccineSerial();// generates a random number
        hashTable1.insert(Person("John", temp));
    }
    cout << "Final size is " << hashTable1.tableSize() << endl;
    if(hashTable1.tableSize() > size){ //checks if table rehashed
        return true;
    }else{
        return false;
    }
}

//helper function
int Tester::getIndex(HashTable &hashTable1, Person person1){
    for(int i = 0; i < hashTable1.m_capacity; i++){
        if(hashTable1.m_table[i].key() == person1.key() && hashTable1.m_table[i].serial() == person1.serial()){
            return i; //returns the index of the person passed in the function
        }
    }
    return -1; //if person passed in the function not found in the table
}