// CMSC 341 - Spring 2021 - Project 4
// hash.cpp
// The implementation of the class HashTable
#include "hash.h"
#include "math.h"
HashTable::HashTable(unsigned size, hash_fn hash){
    m_hash = hash; //sets hash function
    m_capacity = size; //sets table size
    if(size < MINPRIME){ //if size is less than MINPRIME
        m_capacity = MINPRIME; //set table size to MINPRIME
    }
    if(size > MAXPRIME){ //if size is more than MAXPRIME
        m_capacity = MAXPRIME; //set table size to MAXPRIME
    }
    if(isPrime(m_capacity) == false){ //if table size is not a prime number
        m_capacity = findNextPrime(m_capacity);
    }
    m_table =  new Person[m_capacity]; //sets table size in Person array
    m_currentProb = LINEAR; //class starts as a linar probling.
    m_size = 0; //initalize sizes
    m_numDeleted = 0;
}

HashTable::~HashTable(){
    delete [] m_table; //deletes table
    m_table = nullptr; //sets table to nullptr
    m_hash = nullptr; //sets hash function to nullptr
    m_capacity = 0; //resets vaules
    m_size = 0;
    m_numDeleted = 0;
}

bool HashTable::insert(Person person){
    for(int i = 0; i < m_capacity; i++){ //checks to make sure that person does not already exitst in table
        if(m_table[i].key() == person.key() && m_table[i].serial() == person.serial()){
            return false; //returns false if person already exists in table
        }
    }
    if(m_size >= m_capacity || m_size >= MAXPRIME){ //if table is full
        return false;
    }
    int num = m_hash(person.key()); //gets number through hash function
    int index = num % m_capacity; //gets index through modding table size
    if(m_table[index].key() == "" && m_table[index].serial() == 0){ //if that index is empty, insert it in
        m_table[index] = person;
        m_size++; //updates size
        checkRHashInsert(); //checks if rehash is needed
        return true;
    }else{
        if(m_currentProb == LINEAR){ //if probe linear
            int i = 0;
            while(m_table[index].key() != ""){ //gets new index to insert
                index = (num + i) % m_capacity;
                i++;
            }
            m_table[index] = person;
            m_size++; //updates size
            checkRHashInsert(); //checks if rehash is needed
            return true;
        }else if(m_currentProb == QUADRATIC){ //if probe quadratic
            int i = 0;
            while(m_table[index].key() != ""){ //gets new index to insert
                index = ((num % m_capacity) + (i*i)) % m_capacity;
                i++;
            }
            m_table[index] = person;
            m_size++; //updates size
            checkRHashInsert(); //checks if rehash is needed
            return true;
        }
    }
    return false;
}

bool HashTable::remove(Person person){
    /*
    for(int i = 0; i < m_capacity; i++){
        if(m_table[i].key() == person.key() && m_table[i].serial() == person.serial()){ //if person is found, it's set to "DELETED"
            m_table[i].setKey("DELETED" );
            m_table[i].setSerial(0);
            m_numDeleted++; //updates number of deleted spaces
            checkRHashRemove(); //checks for rehash
            return true;
        }
    }
    return false; //if person is not found
     */
    if(m_currentProb == LINEAR){ //if probe linear
        int num = m_hash(person.key());
        int index = num % m_capacity; //gets index through modding table size
        int counter = 0;
        while(counter <= m_capacity){
            index = (num + counter) % m_capacity; //use linear probing
            if(m_table[index].key() == person.key() && m_table[index].serial() == person.serial()){ //if person is found, it's set to "DELETED"
                m_table[index].setKey("DELETED" );
                m_table[index].setSerial(0);
                m_numDeleted++; //updates number of deleted spaces
                checkRHashRemove(); //checks for rehash
                return true;
            }
            counter++;
        }
        return false; //if person is not found
    }else if(m_currentProb == QUADRATIC){ //if probe quadratic
        int num = m_hash(person.key());
        int index = num % m_capacity; //gets index through modding table size
        int counter = 0;
        while(counter <= m_capacity){ //use quadratic probing
            index = ((num % m_capacity) + (counter*counter)) % m_capacity;
            if(m_table[index].key() == person.key() && m_table[index].serial() == person.serial()){ //if person is found, it's set to "DELETED"
                m_table[index].setKey("DELETED" );
                m_table[index].setSerial(0);
                m_numDeleted++; //updates number of deleted spaces
                checkRHashRemove(); //checks for rehash
                return true;
            }
            counter++;
        }
        return false; //if person is not found
    }
    return false;//if person is not found
}

void HashTable::setProbingPolicy(probing prob){
    m_currentProb = prob; //sets probing policy to linar or quadratic
    int num = m_size - m_numDeleted;
    int newSize = findNextPrime(num * 4); //new size
    Person *newArray = new Person[num]; //array for non-deleted occupited spaces
    int index = 0;
    for(int i = 0; i < m_capacity; i++){
        if(m_table[i].key() != "DELETED" && m_table[i].key() != ""){ //inserts person in array if not deleted
            newArray[index] = m_table[i];
            index++;
        }
    }
    delete [] m_table; //removes old table
    m_table = new Person[newSize]; //creates new table with new size
    m_capacity = newSize;
    m_numDeleted = 0;
    m_size = 0;
    for(int i = 0; i < num; i++){ //re-inserts persons into new table from array
        insert(newArray[i]);
    }
    delete [] newArray; //deletes array
    newArray = nullptr;
}

float HashTable::lambda() const {
    return float(m_size)/float(m_capacity); //returns load factor which is the ratio of occiped buckets to table size
}

float HashTable::deletedRatio() const {
    return float(m_numDeleted)/float(m_size); //returns the ratio of deleted buckets to occiped buckets
}

void HashTable::dump() const {
    for (int i = 0; i < m_capacity; i++) {
        cout << "[" << i << "] : " << m_table[i] << endl;
    }
}

bool HashTable::isPrime(int number){
    // If number is prime this function returns true
    // otherwise it returns false
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we won't go beyond MAXPRIME
    //the smallest prime would be next after MINPRIME
    if (current < MINPRIME) current = MINPRIME;
    for (int i=current; i<MAXPRIME; i++) {
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

//Helper functions
void HashTable::checkRHashInsert(){
    if(lambda() > 0.5){ //if load factor is greater than 0.5
        if(m_currentProb == LINEAR){//changes probe
            setProbingPolicy(QUADRATIC);
        }else if (m_currentProb == QUADRATIC){
            setProbingPolicy(LINEAR);
        }
    }
}

void HashTable::checkRHashRemove(){
    if(deletedRatio() > 0.25){ // if the number of deleted buckets is more than 25 percent of the total number of occupied buckets
        if(m_currentProb == LINEAR){//changes probe
            setProbingPolicy(QUADRATIC);
        }else if (m_currentProb == QUADRATIC){
            setProbingPolicy(LINEAR);
        }
    }
}