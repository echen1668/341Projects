#include <stdexcept>
#include <iostream>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
//the following is your tester class, you add your test functions in this class
//you declare and implement the Tester class in your mytest.cpp file
class Tester;
//forward declaration, BufferList will be a friend of Buffer class
class BufferList;
class Buffer{
public:
    friend class Grader;//Grader will have access to private members of Buffer
    friend class Tester;//Tester will have access to private members of Buffer
    friend class BufferList;//BufferList will have access to private members of Buffer
    Buffer(int capacity);       //constructor
    ~Buffer();                  //destructor
    Buffer(const Buffer & rhs); //copy constructor
    const Buffer & operator=(const Buffer & rhs);// overloaded assignment operator
    void enqueue(int data); // inserts at the end
    int dequeue();          // removes from start
    void clear();           // deallocate memory
    bool empty();           // returns true if buffer holds no items
    bool full();            // returns true if no space left in buffer
    int count();            // returns number of items currently held in the buffer
    int capacity();         // returns maximum number of items this buffer can hold
    void dump();            // prints out the contents, for debugging purposes

private:
    int *m_buffer ;         // pointer to dynamically allocated array for buffer
    int m_capacity ;        // length of the allocated space pointed by m_buffer
    int m_count ;           // current number of items in the buffer
    int m_start ;           // index of the first (oldest) item in the buffer
    int m_end ;             // index of the last (newest) item in the buffer
    Buffer* m_next;         // pointer to the next buffer in a linked list

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
};


class Grader;//this class is for grading purposes, no need to do anything
//the following is your tester class, you add your test functions in this class
//you declare and implement the Tester class in your mytest.cpp file
class Tester;
const int DEFAULT_MIN_CAPACITY = 10;
const int MAX_FACTOR = 16;
const int INCREASE_FACTOR = 2;
class BufferList{
public:
    friend class Grader;//Grader will have access to private members of BufferList
    friend class Tester;//Tester will have access to private members of BufferList
    BufferList(int minBufCapacity);     //constructor
    ~BufferList();                      //destructor
    BufferList(const BufferList & rhs); //copy constructor
    const BufferList & operator=(const BufferList & rhs);// overloaded assignment operator
    void enqueue(const int & data);         //add data
    int dequeue();                                  //remove data
    void clear();           //clear all data, deallocate all memory
    void dump();            //prints out the contents, for debugging purposes

private:
    Buffer * m_cursor;      //the cursor is the rear of list and its next points to front of list
    int m_listSize;         //this is the size of linked list, i.e. number of nodes in the list
    int m_minBufCapacity;   //the min size for circular buffers in the list

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
};

class Tester{
public:
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount); //tests buffer by adding and removing a certain number of items
    void BufferDequeue(int dataCount); //tests dequeue
    bool BufferEnqueueFull(int size); //tests full buffer
    bool BufferDequeueEmpty(int size); //tests empty buffer
    bool BufferEnqueueDequeueLessThanOne(int size); //test buffer if a size less than 1 is passed
    bool BufferCopyConstructor(const Buffer &buffer); //tests copy constructer
    bool BufferCopyConstructorDiffrentData(const Buffer &buffer); //test tests copy constructer deep copy
    bool BufferAssigmentOperator(const Buffer &buffer); //tests assigment operator
    bool BufferAssigmentOperatorDiffrentData(const Buffer &buffer); //tests assigment operator deep copy
    void BufferAssigmentOperatorSelfAssign(); //test self assigment
    bool BufListEnqueueDequeue(BufferList &buffer, int dataCount); //test bufferlist by adding and removing a certain number of items
    bool BufListDequeueEmpty(int size); //test empty bufferlist
    void BufListDequeue(int bufferSize, int dataCount); //tests dequeue on buffer list
    bool BufListCopyConstructor(const BufferList &buffer); //tests copy constructer
    bool BufListCopyConstructorDiffrentData(const BufferList &buffer); //test tests copy constructer deep copy
    bool BufListAssigmentOperator(const BufferList &buffer); //tests assigment operator deep copy
    bool BufListAssigmentOperatorDiffrentData(const BufferList &buffer); //tests assigment operator deep copy
    void BufListAssigmentOperatorSelfAssign(); //test self assigment
    void BufListEnqueuePerformance(int numTrials, int N); //tests time interstion on enqueue
    void BufListDequeuePerformance(int numTrials, int N);
    void measureInsertionTimeBufListCopyConstructor(int numTrials, int N); //tests time on copy constructor
    void measureInsertionTime(int numTrials, int N);
};


int main() {

    Tester tester;
    int bufferSize = 1000;
    Buffer buffer(bufferSize);

    //testing insertion/removal for 1 data item
    cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
    if (tester.BufferEnqueueDequeue(buffer, 1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for no data items
    cout << "\nTest case: Buffer class: Inserting/removing 0 data item:\n";
    if (tester.BufferEnqueueDequeue(buffer, 0)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for negative data items
    cout << "\nTest case: Buffer class: Inserting/removing negative data item:\n";
    if (tester.BufferEnqueueDequeue(buffer, -10)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for half data size
    cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize/2)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for full data size
    cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }

    //testing insertion in a full buffer
    cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
    if (tester.BufferEnqueueFull(1000)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }

    //testing removal in a empty buffer
    cout << "\nTest case: Buffer class: Throwing exception while removing in empty buffer:\n";
    if (tester.BufferDequeueEmpty(1000)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing creating a Buffer with size 0
    cout << "\nTest case: Buffer class: creating a Buffer with size 0:\n";
    if (tester.BufferEnqueueDequeueLessThanOne(0)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing creating a Buffer with size -10
    cout << "\nTest case: Buffer class: creating a Buffer with size -10:\n";
    if (tester.BufferEnqueueDequeueLessThanOne(-10)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing FIFO with dequeue function
    cout << "\nTest case: Buffer class: FIFO with dequeue function:\n";
    tester.BufferDequeue(10);

    //testing copy constructor for Buffer
    Buffer b1a(10);
    for (int i=0;i<b1a.capacity();i++){ //adds elements with random number between 1 to 100
        b1a.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: Buffer class: Copy Constructor for Buffer:\n";
    if (tester.BufferCopyConstructor(b1a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing copy constructor for Buffer at size 1
    Buffer b1b(1);
    for (int i=0;i<b1b.capacity();i++){ //adds elements
        b1b.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: Buffer class: Copy Constructor for Buffer at size 1:\n";
    if (tester.BufferCopyConstructor(b1b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing copy constructor for Buffer at size 0
    Buffer b1c(0);
    for (int i=0;i<b1c.capacity();i++){ //adds elements
        b1c.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: Buffer class: Copy Constructor for Buffer at size 0:\n";
    if (tester.BufferCopyConstructor(b1c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    Buffer b1d(-10);
    for (int i=0;i<b1d.capacity();i++){ //adds elements
        b1d.enqueue(rand() % 100 + 1);
    }
    //testing copy constructor for Buffer at size -10
    cout << "\nTest case: Buffer class: Copy Constructor for Buffer at size -10:\n";
    if (tester.BufferCopyConstructor(b1d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer
    cout << "\nTest case: Buffer class: Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer:\n";
    if (tester.BufferCopyConstructorDiffrentData(b1a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size 1
    cout << "\nTest case: Buffer class: Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size 1:\n";
    if (tester.BufferCopyConstructorDiffrentData(b1b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size 0
    cout << "\nTest case: Buffer class: Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size 0:\n";
    if (tester.BufferCopyConstructorDiffrentData(b1c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size -10
    cout << "\nTest case: Buffer class: Deep Copy for Copy Constructor for Buffer by changing element in the copied buffer at size -10:\n";
    if (tester.BufferCopyConstructorDiffrentData(b1d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for Buffer
    cout << "\nTest case: Buffer class: Assigment Operator for Buffer:\n";
    if (tester.BufferAssigmentOperator(b1a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator  for Buffer at size 1
    cout << "\nTest case: Buffer class: Assigment Operator for Buffer at size 1:\n";
    if (tester.BufferAssigmentOperator(b1b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator  for Buffer at size 0
    cout << "\nTest case: Buffer class: Assigment Operator for Buffer at size 0:\n";
    if (tester.BufferAssigmentOperator(b1c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for Buffer at size -10
    cout << "\nTest case: Buffer class: Assigment Operatorfor Buffer at size -10:\n";
    if (tester.BufferAssigmentOperator(b1d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer
    cout << "\nTest case: Buffer class: Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer:\n";
    if (tester.BufferAssigmentOperatorDiffrentData(b1a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size 1
    cout << "\nTest case: Buffer class: Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size 1:\n";
    if (tester.BufferAssigmentOperatorDiffrentData(b1b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size 0
    cout << "\nTest case: Buffer class: Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size 0:\n";
    if (tester.BufferAssigmentOperatorDiffrentData(b1c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size -10
    cout << "\nTest case: Buffer class: Deep Copy for Assigment Operator for Buffer by changing element in the copied buffer at size -10:\n";
    if (tester.BufferAssigmentOperatorDiffrentData(b1d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing Self Assignment for Assigment Operator
    cout << "\nTest case: Buffer class: Self Assignment for Assigment Operator, should print out 'Cannot self assign':\n";
    tester.BufferAssigmentOperatorSelfAssign();

    int bufferListSize = 1000;
    BufferList bufferList2(bufferListSize);
    //testing insertion/removal for 1 data item
    cout << "\nTest case: BufferList class: Inserting/removing 1 data item:\n";
    if (tester.BufListEnqueueDequeue(bufferList2,1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for no data items
    cout << "\nTest case: BufferList class: Inserting/removing 0 data item:\n";
    if (tester.BufListEnqueueDequeue(bufferList2,0)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for negative data items
    cout << "\nTest case: BufferList class: Inserting/removing negative data item:\n";
    if (tester.BufListEnqueueDequeue(bufferList2,-10)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for a data size equal to the size of the initial buffer
    cout << "\nTest case: BufferList class: Inserting/removing a data size equal to the size of the initial buffer:\n";
    if (tester.BufListEnqueueDequeue(bufferList2,bufferListSize)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing insertion/removal for a data size greater than the size of the initial buffer
    cout << "\nTest case: BufferList class: Inserting/removing a data size greater than the size of the initial buffer:\n";
    if (tester.BufListEnqueueDequeue(bufferList2,10000)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing removal in a empty buffer
    cout << "\nTest case: BufferList class: Throwing exception while removing in empty buffer:\n";
    if (tester.BufListDequeueEmpty(1000)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing FIFO with dequeue function
    cout << "\nTest case: BufferList class: FIFO with dequeue function:\n";
    tester.BufListDequeue(10,20);

    //testing copy constructor for BufferList
    BufferList b2a(10);
    for (int i=0;i<10;i++){ //adds elements with random number between 1 to 100
        b2a.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: BufferList class: Copy Constructor for BufferList:\n";
    if (tester.BufListCopyConstructor(b2a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing copy constructor for BufferList when size exceeds mininum capacity
    BufferList b2a1(10);
    for (int i=0;i<20;i++){ //adds elements with random number between 1 to 100
        b2a1.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: BufferList class: Copy Constructor for BufferList:\n";
    if (tester.BufListCopyConstructor(b2a1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing copy constructor for BufferList at size 1
    BufferList b2b(1);
    for (int i=0;i<1;i++){ //adds elements
        b2b.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: BufferList class: Copy Constructor for BufferList at size 1:\n";
    if (tester.BufListCopyConstructor(b2b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing copy constructor for BufferList at size 0
    BufferList b2c(0);
    for (int i=0;i<0;i++){ //adds elements
        b2c.enqueue(rand() % 100 + 1);
    }
    cout << "\nTest case: BufferList class: Copy Constructor for BufferList at size 0:\n";
    if (tester.BufListCopyConstructor(b2c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    BufferList b2d(-10);
    for (int i=0;i<-10;i++){ //adds elements
        b2d.enqueue(rand() % 100 + 1);
    }
    //testing copy constructor for BufferList at size -10
    cout << "\nTest case: BufferList class: Copy Constructor for BufferList at size -10:\n";
    if (tester.BufListCopyConstructor(b2d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing the deep copy copy constructor for BufferList by changing elements
    cout << "\nTest case: BufferList class: Copy Constructor deep copy for BufferList:\n";
    if (tester.BufListCopyConstructorDiffrentData(b2a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy copy constructor for BufferList when size exceeds mininum capacity
    cout << "\nTest case: BufferList class: Copy Constructor deep copy for BufferList:\n";
    if (tester.BufListCopyConstructorDiffrentData(b2a1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy copy constructor for BufferList at size 1
    cout << "\nTest case: BufferList class: Copy Constructor deep copy for BufferList at size 1:\n";
    if (tester.BufListCopyConstructorDiffrentData(b2b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy copy constructor for BufferList at size 0
    cout << "\nTest case: BufferList class: Copy Constructor deep copy for BufferList at size 0:\n";
    if (tester.BufListCopyConstructorDiffrentData(b2c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy copy constructor for BufferList at size -10
    cout << "\nTest case: BufferList class: Copy Constructor deep copy for BufferList at size -10:\n";
    if (tester.BufListCopyConstructorDiffrentData(b2d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for BufferList
    cout << "\nTest case: BufferList class: Assigment Operator for BufferList:\n";
    if (tester.BufListAssigmentOperator(b2a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for BufferList when size exceeds mininum capacity
    cout << "\nTest case: BufferList class: Assigment Operator for BufferList:\n";
    if (tester.BufListAssigmentOperator(b2a1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for BufferList at size 1
    cout << "\nTest case: BufferList class: Assigment Operator for BufferList at size 1:\n";
    if (tester.BufListAssigmentOperator(b2b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for BufferList at size 0
    cout << "\nTest case: BufferList class: Assigment Operator for BufferList at size 0:\n";
    if (tester.BufListAssigmentOperator(b2c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing assigment operator for BufferList at size -10
    cout << "\nTest case: BufferList class: Assigment Operator for BufferList at size -10:\n";
    if (tester.BufListAssigmentOperator(b2d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing the deep copy assigment operator for BufferList by changing elements
    cout << "\nTest case: BufferList class: Assigment Operator deep copy for BufferList:\n";
    if (tester.BufListAssigmentOperatorDiffrentData(b2a)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy assigment operator for BufferList when size exceeds mininum capacity
    cout << "\nTest case: BufferList class: Assigment Operator deep copy for BufferList:\n";
    if (tester.BufListAssigmentOperatorDiffrentData(b2a1)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy assigment operator for BufferList at size 1
    cout << "\nTest case: BufferList class: Assigment Operator deep copy for BufferList at size 1:\n";
    if (tester.BufListAssigmentOperatorDiffrentData(b2b)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy assigment operator for BufferList at size 0
    cout << "\nTest case: BufferList class: Assigment Operator deep copy for BufferList at size 0:\n";
    if (tester.BufListAssigmentOperatorDiffrentData(b2c)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }
    //testing deep copy assigment operator for BufferList at size -10
    cout << "\nTest case: BufferList class: Assigment Operator deep copy for BufferList at size -10:\n";
    if (tester.BufListAssigmentOperatorDiffrentData(b2d)){
        cout << "\tTest passed!\n";
    }else{
        cout << "\tTest failed!\n";
    }

    //testing Self Assignment for Assigment Operator of BufferList
    cout << "\nTest case: BufferList class: Self Assignment for Assigment Operator, should print out 'Cannot self assign':\n";
    tester.BufListAssigmentOperatorSelfAssign();

    //Measuring the efficiency of insertion functionality for BufferList enqueue
    cout << "\nMeasuring the efficiency of insertion for BufferList enqueue functionality:" << endl;
    int A = 5;//number of trials
    int B = 10000;//original input size
    tester.BufListEnqueuePerformance(A, B);
    cout << endl;

    //Measuring the efficiency of insertion functionality for BufferList dequeue
    cout << "\nMeasuring the efficiency of insertion for BufferList dequeue functionality:" << endl;
    int C = 5;//number of trials
    int D = 10000;//original input size
    tester.BufListDequeuePerformance(C, D);
    cout << endl;

    //Measuring the efficiency of insertion functionality for copy constructor
    cout << "\nMeasuring the efficiency of insertion functionality for copy constructor:" << endl;
    int A2 = 5;//number of trials
    int B2 = 1000000;//original input size
    tester.measureInsertionTimeBufListCopyConstructor(A2, B2);

    //Measuring the efficiency of insertion functionality
    cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
    int M = 5;//number of trials
    int N = 1000;//original input size
    tester.measureInsertionTime(M, N);

    //print out an example of a bufferlist
    int newBufferListSize = 5;
    int newBufferListDataSize = 40;
    BufferList newBufferList(newBufferListSize);
    for(int i = 0; i < newBufferListDataSize; i++){
        newBufferList.enqueue(rand() % 100 + 1);
    }
    cout << "Here is an example of a linked list:" << endl;
    newBufferList.dump();


    return 0;

}

//Functions for buffer.cpp
Buffer::Buffer(int capacity){
    if(capacity > 0){ //sets up inital vaules if capacity is greater than 0
        m_capacity = capacity;
        m_buffer = new int[capacity]; //creates new buffer
        m_start = 0;
        m_end = 0;
        m_count = 0;
    }else{
        m_capacity = 0; //if capacity is less than 1
        m_buffer = nullptr;
        m_count = 0;
        m_start = 0;
        m_end = 0;
    }
}

void Buffer::clear(){
    delete [] m_buffer; //deletes buffer
    m_buffer = nullptr; //resets all vaules
    m_capacity = 0;
    m_start = 0;
    m_end = 0;
    m_count = 0;

}

Buffer::~Buffer(){
    clear();
}

int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

bool Buffer::full(){
    if(count()==capacity()){ //if array if fill
        return true;
    }else{ //if array is not full
        return false;
    }
}

bool Buffer::empty(){
    if(count()==0){ //if array is empty
        return true;
    }else{ //if array is not empty
        return false;
    }
}

void Buffer::enqueue(int data){
    if(full()){
        throw std::overflow_error("Buffer is full"); //throws error expection if buffer is full
    }else{
        if(empty()){ //if array is empty
            m_buffer[0] = data; //sets first index to data
            m_start = 0;
            m_end = 0;
            m_count++;
        }else{
            //cout << "2nd Else is hit" << endl;
            int newIndex = m_end + 1; //data goes at the end of the array. Space after m_end
            if(newIndex >= m_capacity){ //if index goes over the end of the array
                newIndex = 0; //goes to the beginning of the list
            }
            m_buffer[newIndex] = data;
            m_end = newIndex; //updates m_end
            m_count++;
        }
    }
}

int Buffer::dequeue(){
    if(empty()){
        throw std::underflow_error("Buffer is empty"); //throws error expection if buffer is empty
    }else{
        int newIndex = m_start + 1; //updates m_start
        int oldInt = m_buffer[m_start];
        m_buffer[m_start] = 0; //removes data from old m_start
        if(newIndex >= m_capacity){ //if index goes over the end of the array
            newIndex = 0; //goes to the beginning of the list
        }
        m_start = newIndex;
        m_count--;
        return oldInt;
    }
}

Buffer::Buffer(const Buffer & rhs){
    if(rhs.m_capacity > 0){
        m_capacity = rhs.m_capacity; //sets capacity and array size
        m_buffer = new int[rhs.m_capacity];
        m_start = rhs.m_start; //sets start and end
        m_end = rhs.m_end;
        m_count = rhs.m_count;
        int counter = m_start;
        while(counter != m_end){
            m_buffer[counter] = rhs.m_buffer[counter];
            counter ++;
            if(counter == m_capacity){ //if counter reaches the end of the array
                counter = 0;
            }
        }
        m_buffer[m_end] =  rhs.m_buffer[m_end];
    }else{ //if rhs capacity is less than 1
        m_capacity = 0;
        m_buffer = nullptr;
        m_count = 0;
        m_start = 0;
        m_end = 0;
    }
}

const Buffer & Buffer::operator=(const Buffer & rhs){
    if(this != &rhs){ //checks for self assigment
        clear(); //clears previous data
        if(rhs.m_capacity > 0){
            m_capacity = rhs.m_capacity; //sets capacity and array size
            m_buffer = new int[rhs.m_capacity];
            m_start = rhs.m_start; //sets start and end
            m_end = rhs.m_end;
            m_count = rhs.m_count;
            int counter = m_start;
            while(counter != m_end){
                m_buffer[counter] = rhs.m_buffer[counter];
                counter++;
                if(counter == m_capacity){ //if counter reaches the end of the array
                    counter = 0;
                }
            }
            m_buffer[m_end] =  rhs.m_buffer[m_end];
        }else{
            m_capacity = 0;
            m_buffer = nullptr;
            m_count = 0;
            m_start = 0;
            m_end = 0;
        }
        return *this; //returns puzzle
    }else{
        cout << "Cannot self assign" << endl;
        return rhs; //returns puzzle
    }
}

void Buffer::dump(){
    int start = m_start;
    int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}

//Functions for bufferlist.cpp
BufferList::BufferList(int minBufCapacity){
    if(minBufCapacity > 0){ //if min capacity is greater than 0
        m_minBufCapacity = minBufCapacity; //sets capacity
        m_listSize = 1; //inintailize members vaules
        m_cursor = new Buffer(m_minBufCapacity); //creates first node in cursor and points to itself.
        m_cursor->m_next = m_cursor;

    }else{ //if min capacity is less than 1, assigns default capacity
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
        m_listSize = 1;
        m_cursor = new Buffer(m_minBufCapacity);
        m_cursor->m_next = m_cursor;
    }
}
BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    Buffer* curr = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        Buffer* temp = curr->m_next;
        delete curr;
        curr = temp;
    }
    m_cursor = nullptr;
    m_listSize = 0;
    m_minBufCapacity = 0;
}

void BufferList::enqueue(const int& data) {
    try{
        m_cursor->enqueue(data); //adds data to newest buffer
    }
    catch(overflow_error &e){ //if current buffer is full
        int newSize = INCREASE_FACTOR * m_cursor->capacity(); //creates new buffer/node with new size
        if(newSize > MAX_FACTOR* m_minBufCapacity){ //if newSize reaches maxinum capacity
            newSize = m_minBufCapacity;
        }
        Buffer *temp = new Buffer(newSize);
        temp->m_next = m_cursor->m_next; //sets new node pointer to beginning of the list which is current node->m_next
        m_cursor->m_next = temp; //updates m_cursor->m_next
        m_cursor = temp; //updates m_cursor
        m_listSize++; //increments listSize
        m_cursor->enqueue(data); //adds new data
    }
}

int BufferList::dequeue() {
    try{
        int oldData = m_cursor->m_next->dequeue(); //removes data from oldest buffer
        if(m_cursor->m_next->empty() == true && m_listSize > 1){ //if the buffer is empty after dequeue
            Buffer *temp = m_cursor->m_next;
            m_cursor->m_next = temp->m_next; //sets current node pointer to the next node after the oldest empty node
            delete temp; //removes oldest empty buffer
            m_listSize--; //decrements listSize
        }
        return oldData;
    }
    catch(underflow_error &e){ //if current buffer is full
        if(m_listSize > 1){ //if there is more than one node in the linked list
            Buffer *temp = m_cursor->m_next;
            m_cursor->m_next = temp->m_next; //sets current node pointer to the next node after the oldest empty node
            delete temp; //removes oldest empty buffer
            m_listSize--; //decrements listSize
            int oldData = m_cursor->m_next->dequeue(); //removes data from oldest buffer
            return oldData;
        }else{
            //cout << "There is only on node left in the linked list" << endl;
            throw std::underflow_error("There is only on node left in the linked list");
        }
    }
}

BufferList::BufferList(const BufferList & rhs){
    if(rhs.m_minBufCapacity > 0){ //if min capacity is greater than 0
        m_minBufCapacity = rhs.m_minBufCapacity; //sets the capacity
        m_listSize = rhs.m_listSize; //inintailize members
        Buffer* curr = rhs.m_cursor->m_next; //set curr at the beginning of the rhs list
        Buffer* start; //points to the oldest buffer/beginning of the list
        Buffer* newList;//points to the newest buffer/end of the list
        Buffer* temp = new Buffer(*curr); //copys from the rhs, calls the Buffer copy constructor
        curr = curr->m_next; //moves to the next node
        start = temp; //sets the first node
        newList = temp; //updates newList
        for(int i = 1; i < m_listSize; i++){ //traverse through rhs list
            Buffer* temp = new Buffer(*curr); //copys node
            curr = curr->m_next;
            Buffer* prev = newList; //gets previous node
            prev->m_next = temp; //inserts the copied node into the end of the new linked list
            newList = temp; //sets new cursor
        }
        m_cursor = newList; //creates new cursor
        m_cursor->m_next = start; //sets new beginning of the list

    }else{ //if min capacity is less than 1, assigns default capacity
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
        m_listSize = 1;
        m_cursor = new Buffer(m_minBufCapacity);
        m_cursor->m_next = m_cursor;
    }
}

const BufferList & BufferList::operator=(const BufferList & rhs){
    if(this != &rhs){ //checks for self assigment
        clear(); //clears previous data
        if(rhs.m_minBufCapacity > 0){ //if min capacity is greater than 0
            m_minBufCapacity = rhs.m_minBufCapacity; //sets the capacity
            m_listSize = rhs.m_listSize; //inintailize members
            Buffer* curr = rhs.m_cursor->m_next; //set curr at the beginning of the rhs list
            Buffer* start; //points to the oldest buffer/beginning of the list
            Buffer* newList;//points to the newest buffer/end of the list
            Buffer* temp = new Buffer(*curr); //copys from the rhs, calls the Buffer copy constructor
            curr = curr->m_next; //moves to the next node
            start = temp; //sets the first node
            newList = temp; //updates newList
            for(int i = 1; i < m_listSize; i++){ //traverse through rhs list
                Buffer* temp = new Buffer(*curr); //copys node
                curr = curr->m_next;
                Buffer* prev = newList; //gets previous node
                prev->m_next = temp; //inserts the copied node into the end of the new linked list
                newList = temp; //sets new cursor
            }
            m_cursor = newList; //creates new cursor
            m_cursor->m_next = start; //sets new beginning of the list
        }else{ //if min capacity is less than 1, assigns default capacity
            m_minBufCapacity = DEFAULT_MIN_CAPACITY;
            m_listSize = 1;
            m_cursor = new Buffer(m_minBufCapacity);
            m_cursor->m_next = m_cursor;
        }
        return *this; //returns puzzle
    }else{
        cout << "Cannot self assign" << endl;
        return rhs; //returns puzzle
    }
}
void BufferList::dump(){
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}

//Test Functions
bool Tester::BufferEnqueueDequeue(Buffer &buffer, int dataCount){
    int count = 0;
    for (int i=0;i<dataCount;i++) { //adds elements
        buffer.enqueue(i);
        count++;
    }
    cout << count << " elements are enqueued" << endl;
    count = 0;
    for (int i=0;i<dataCount;i++){ //removes elements
        buffer.dequeue();
        count++;
    }
    cout << count << " elements are dequeued" << endl;
    if(buffer.empty()){ //checks if all elements are removed
        return true;
    }else{
        return false;
    }
}

void Tester::BufferDequeue(int dataCount){
    Buffer buffer(dataCount);
    for (int i=0;i<dataCount;i++){ //adds elements with random number
        buffer.enqueue(rand() % 100 + 1);
    }
    buffer.dump(); //prints out buffer
    cout << "_______________________________________" << endl;
    for (int i=0;i<dataCount;i++){ //removes elements
        cout << buffer.dequeue() << " "; //should print out all elements in the same order as they went in. (Should match order seen printed by dump())
    }
    cout << endl;
}

bool Tester::BufferEnqueueDequeueLessThanOne(int size){
    Buffer b1(size); //tests if a size less than 1 result in an empty buffer at 0
    if(b1.empty() && b1.m_capacity == 0 && b1.m_count == 0){ //if buffer is empty and capacity and count are 0, return true
        return true;
    }else{
        return false;
    }
}

bool Tester::BufferEnqueueFull(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++)
        aBuffer.enqueue(i);
    try{
        //trying to insert in a full buffer
        aBuffer.enqueue(size+1);
    }
    catch(overflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester::BufferDequeueEmpty(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++){ //adds elements
        aBuffer.enqueue(i);
    }
    for (int i=0;i<size;i++){ //removes elements
        aBuffer.dequeue();
    }
    try{
        //trying to remove at empty buffer
        aBuffer.dequeue();
    }
    catch(underflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester::BufferCopyConstructor(const Buffer &buffer){
    bool address = false; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    Buffer b2(buffer);
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_capacity == 0 && b2.m_capacity == 0){ //if capacity is zero for both
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        size = true;
        address = true;
        data = true;
    }else{
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        if(buffer.m_capacity == b2.m_capacity){ //checks capacities
            size = true;
        }
        cout << "Addresses are " << buffer.m_buffer << " and " << b2.m_buffer << endl;
        if(buffer.m_buffer != b2.m_buffer){ //checks addresses
            address = true;
        }
        int counter = buffer.m_start;
        while(counter != buffer.m_end){ //checks data in buffer
            if(buffer.m_buffer[counter] != b2.m_buffer[counter]){
                data = false;
            }
            counter++;
            if(counter == buffer.m_capacity){ //if counter reaches the end of the array
                counter = 0;
            }
        }
        if(buffer.m_buffer[buffer.m_end] != b2.m_buffer[buffer.m_end]){ //checks m_end index
            data = false; //should find that different element at index 0
        }
        int start = buffer.m_start;
        int end = buffer.m_end;
        int count = 0;
        cout << "Buffer size: " << buffer.m_capacity << " : ";
        if (buffer.m_capacity != 0){
            while(count < buffer.m_count){
                cout << buffer.m_buffer[start] << "[" << start << "]" << " ";
                start = (start + 1) % buffer.m_capacity;
                count++;
            }
            cout << endl;
        }
    }
    if(data == true && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::BufferCopyConstructorDiffrentData(const Buffer &buffer){
    bool address = false; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    Buffer b2(buffer);
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_capacity == 0 && b2.m_capacity == 0){ //if capacity is zero for both
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        size = true;
        address = true;
        data = false;
    }else{
        if(b2.m_buffer[buffer.m_start] != 10){ //changes first elements in buffer
            buffer.m_buffer[buffer.m_start] = 10;
        }else{
            buffer.m_buffer[buffer.m_start] = 5;
        }
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        if(buffer.m_capacity == b2.m_capacity){ //checks capacities
            size = true;
        }
        cout << "Addresses are " << buffer.m_buffer << " and " << b2.m_buffer << endl;
        if(buffer.m_buffer != b2.m_buffer){ //checks addresses
            address = true;
        }
        int counter = buffer.m_start;
        while(counter != buffer.m_end){ //checks data in buffer
            if(buffer.m_buffer[counter] != b2.m_buffer[counter]){
                data = false; //should find that different element at index 0
            }
            counter++;
            if(counter == buffer.m_capacity){ //if counter reaches the end of the array
                counter = 0;
            }
        }
        if(buffer.m_buffer[buffer.m_end] != b2.m_buffer[buffer.m_end]){ //checks m_end index
            data = false; //should find that different element at index 0
        }
        int start = buffer.m_start;
        int end = buffer.m_end;
        int count = 0;
        cout << "Buffer size: " << buffer.m_capacity << " : ";
        if (buffer.m_capacity != 0){
            while(count < buffer.m_count){
                cout << buffer.m_buffer[start] << "[" << start << "]" << " ";
                start = (start + 1) % buffer.m_capacity;
                count++;
            }
            cout << endl;
        }
    }
    if(data == false && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::BufferAssigmentOperator(const Buffer &buffer){
    bool address = false; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    Buffer b2 = buffer;
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_capacity == 0 && b2.m_capacity == 0){ //if capacity is zero for both
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        size = true;
        address = true;
        data = true;
    }else{
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        if(buffer.m_capacity == b2.m_capacity){ //checks capacities
            size = true;
        }
        cout << "Addresses are " << buffer.m_buffer << " and " << b2.m_buffer << endl;
        if(buffer.m_buffer != b2.m_buffer){ //checks addresses
            address = true;
        }
        int counter = buffer.m_start;
        while(counter != buffer.m_end){ //checks data in buffer
            if(buffer.m_buffer[counter] != b2.m_buffer[counter]){
                data = false;
            }
            counter++;
            if(counter == buffer.m_capacity){ //if counter reaches the end of the array
                counter = 0;
            }
        }
        if(buffer.m_buffer[buffer.m_end] != b2.m_buffer[buffer.m_end]){ //checks m_end index
            data = false; //should find that different element at index 0
        }
        int start = buffer.m_start;
        int end = buffer.m_end;
        int count = 0;
        cout << "Buffer size: " << buffer.m_capacity << " : ";
        if (buffer.m_capacity != 0){
            while(count < buffer.m_count){
                cout << buffer.m_buffer[start] << "[" << start << "]" << " ";
                start = (start + 1) % buffer.m_capacity;
                count++;
            }
            cout << endl;
        }
    }
    if(data == true && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::BufferAssigmentOperatorDiffrentData(const Buffer &buffer){
    bool address = false; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    Buffer b2 = buffer;
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_capacity == 0 && b2.m_capacity == 0){ //if capacity is zero for both
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        size = true;
        address = true;
        data = false;
    }else{
        if(b2.m_buffer[buffer.m_start] != 10){ //changes first elements in buffer
            buffer.m_buffer[buffer.m_start] = 10;
        }else{
            buffer.m_buffer[buffer.m_start] = 5;
        }
        cout << "Sizes are " << buffer.m_capacity << " and " << b2.m_capacity << endl;
        if(buffer.m_capacity == b2.m_capacity){ //checks capacities
            size = true;
        }
        cout << "Addresses are " << buffer.m_buffer << " and " << b2.m_buffer << endl;
        if(buffer.m_buffer != b2.m_buffer){ //checks addresses
            address = true;
        }
        int counter = buffer.m_start;
        while(counter != buffer.m_end){ //checks data in buffer
            if(buffer.m_buffer[counter] != b2.m_buffer[counter]){
                data = false; //should find that different element at index 0
            }
            counter++;
            if(counter == buffer.m_capacity){ //if counter reaches the end of the array
                counter = 0;
            }
        }
        if(buffer.m_buffer[buffer.m_end] != b2.m_buffer[buffer.m_end]){ //checks m_end index
            data = false; //should find that different element at index 0
        }
        int start = buffer.m_start;
        int end = buffer.m_end;
        int count = 0;
        cout << "Buffer size: " << buffer.m_capacity << " : ";
        if (buffer.m_capacity != 0){
            while(count < buffer.m_count){
                cout << buffer.m_buffer[start] << "[" << start << "]" << " ";
                start = (start + 1) % buffer.m_capacity;
                count++;
            }
            cout << endl;
        }
    }
    if(data == false && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

void Tester::BufferAssigmentOperatorSelfAssign(){
    Buffer buffer1(10); //selfs assigns buffer, should print "Cannot self assign"
    buffer1 = buffer1;
}

bool Tester::BufListEnqueueDequeue(BufferList &buffer, int dataCount){
    int count = 0;
    for (int i=0;i<dataCount;i++){ //adds elements
        buffer.enqueue(i);
        count++;
    }
    cout << count << " elements are enqueued" << endl;
    count = 0;
    for (int i=0;i<dataCount;i++){ //removes elements
        buffer.dequeue();
        count++;
    }
    cout << count << " elements are dequeued" << endl;
    if(buffer.m_cursor->empty()){ //checks if all elements are removed
        return true;
    }else{
        return false;
    }

}

bool Tester::BufListDequeueEmpty(int size){
    BufferList aBuffer(size);
    for (int i=0;i<size;i++){ //adds elements
        aBuffer.enqueue(i);
    }
    for (int i=0;i<size;i++){ //removes elements
        aBuffer.dequeue();
    }
    try{
        //trying to remove at empty buffer
        aBuffer.dequeue();
    }
    catch(underflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

void Tester::BufListDequeue(int bufferSize, int dataCount){
    BufferList bufferList1(bufferSize);
    for (int i=0;i<dataCount;i++){ //adds elements with random number
        bufferList1.enqueue(rand() % 100 + 1);
    }
    bufferList1.dump(); //prints out bufferlist
    cout << "_______________________________________" << endl;
    for (int i=0;i<dataCount;i++){ //removes elements
        cout << bufferList1.dequeue() << " "; //should print out all elements in the same order as they went in. (Should match order seen printed by dump())
    }
    cout << endl;
}

bool Tester::BufListCopyConstructor(const BufferList &buffer){
    bool address = true; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    BufferList b2(buffer);
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_cursor->empty() == true && b2.m_cursor->empty() == true){ //if capacity is zero for both
        cout << "Both BufferLists are empty" << endl;
        size = true;
        address = true;
    }else{
        if(buffer.m_minBufCapacity == b2.m_minBufCapacity && buffer.m_listSize == b2.m_listSize){ //checks capacities and size
            cout << "List Sizes are " << buffer.m_listSize << " and " << b2.m_listSize << endl;
            size = true;
        }
        Buffer* temp = buffer.m_cursor->m_next;
        Buffer* temp2 = b2.m_cursor->m_next;
        for(int i=0;i<buffer.m_listSize;i++){
            if(temp != temp2){ //checks addresses
                cout << "Address are " << temp << " and " << temp2 << endl;
            }else{
                cout << "Address are " << temp << " and " << temp2 << endl;
                address = false; //if addresses are the same, then set address to false
            }
            int counter = temp->m_start;
            while(counter != temp->m_end){ //checks data in buffer
                if(temp->m_buffer[counter] != temp2->m_buffer[counter]){
                    data = false;
                }
                counter++;
                if(counter == temp->m_capacity){ //if counter reaches the end of the array
                    counter = 0;
                }
            }
            if(temp->m_buffer[temp->m_end] != temp2->m_buffer[temp2->m_end]){ //checks m_end index (only if such on exists)
                data = false; //should find that different element at index 0
            }
            temp = temp->m_next;
            temp2 = temp2->m_next;
        }
        Buffer* tempPrint = buffer.m_cursor->m_next; //prints out buffer
        for(int i=0;i<buffer.m_listSize;i++){
            int start = tempPrint->m_start;
            int end = tempPrint->m_end;
            int count = 0;
            cout << "Buffer size: " << tempPrint->m_capacity << " : ";
            if (tempPrint->m_capacity != 0){
                while(count < tempPrint->m_count){
                    cout << tempPrint->m_buffer[start] << "[" << start << "]" << " ";
                    start = (start + 1) % tempPrint->m_capacity;
                    count++;
                }
                cout << endl;
            }
            tempPrint = tempPrint->m_next;
        }
    }
    if(data == true && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::BufListCopyConstructorDiffrentData(const BufferList &buffer){
    bool address = true; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    BufferList b2(buffer);
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_cursor->empty() == true && b2.m_cursor->empty() == true){ //if capacity is zero for both
        cout << "Both BufferLists are empty" << endl;
        size = true;
        address = true;
        data = false;
    }else{
        if(b2.m_cursor->m_next->m_buffer[b2.m_cursor->m_next->m_start] != 10){ //changes first elements in buffer
            buffer.m_cursor->m_next->m_buffer[buffer.m_cursor->m_next->m_start] = 10;
        }else{
            buffer.m_cursor->m_next->m_buffer[buffer.m_cursor->m_next->m_start] = 5;
        }
        if(buffer.m_minBufCapacity == b2.m_minBufCapacity && buffer.m_listSize == b2.m_listSize){ //checks capacities and size
            cout << "List Sizes are " << buffer.m_listSize << " and " << b2.m_listSize << endl;
            size = true;
        }
        Buffer* temp = buffer.m_cursor->m_next;
        Buffer* temp2 = b2.m_cursor->m_next;
        for(int i=0;i<buffer.m_listSize;i++){
            if(temp != temp2){ //checks addresses
                cout << "Address are " << temp << " and " << temp2 << endl;
            }else{
                cout << "Address are " << temp << " and " << temp2 << endl;
                address = false; //if addresses are the same, then set address to false
            }
            int counter = temp->m_start;
            while(counter != temp->m_end){ //checks data in buffer
                if(temp->m_buffer[counter] != temp2->m_buffer[counter]){
                    data = false;
                }
                counter++;
                if(counter == temp->m_capacity){ //if counter reaches the end of the array
                    counter = 0;
                }
            }
            if(temp->m_buffer[temp->m_end] != temp2->m_buffer[temp2->m_end]){ //checks m_end index (only if such on exists)
                data = false; //should find that different element at index 0
            }
            temp = temp->m_next;
            temp2 = temp2->m_next;
        }
        Buffer* tempPrint = buffer.m_cursor->m_next; //prints out buffer
        for(int i=0;i<buffer.m_listSize;i++){
            int start = tempPrint->m_start;
            int end = tempPrint->m_end;
            int count = 0;
            cout << "Buffer size: " << tempPrint->m_capacity << " : ";
            if (tempPrint->m_capacity != 0){
                while(count < tempPrint->m_count){
                    cout << tempPrint->m_buffer[start] << "[" << start << "]" << " ";
                    start = (start + 1) % tempPrint->m_capacity;
                    count++;
                }
                cout << endl;
            }
            tempPrint = tempPrint->m_next;
        }
    }
    if(data == false && size == true && address == true){
        return true;
    }else{
        return false;
    }
}


bool Tester::BufListAssigmentOperator(const BufferList &buffer){
    bool address = true; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    BufferList b2 = buffer;
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_cursor->empty() == true && b2.m_cursor->empty() == true){ //if capacity is zero for both
        cout << "Both BufferLists are empty" << endl;
        size = true;
        address = true;
    }else{
        if(buffer.m_minBufCapacity == b2.m_minBufCapacity && buffer.m_listSize == b2.m_listSize){ //checks capacities and size
            cout << "List Sizes are " << buffer.m_listSize << " and " << b2.m_listSize << endl;
            size = true;
        }
        Buffer* temp = buffer.m_cursor->m_next;
        Buffer* temp2 = b2.m_cursor->m_next;
        for(int i=0;i<buffer.m_listSize;i++){
            if(temp != temp2){ //checks addresses
                cout << "Address are " << temp << " and " << temp2 << endl;
            }else{
                cout << "Address are " << temp << " and " << temp2 << endl;
                address = false; //if addresses are the same, then set address to false
            }
            int counter = temp->m_start;
            while(counter != temp->m_end){ //checks data in buffer
                if(temp->m_buffer[counter] != temp2->m_buffer[counter]){
                    data = false;
                }
                counter++;
                if(counter == temp->m_capacity){ //if counter reaches the end of the array
                    counter = 0;
                }
            }
            if(temp->empty() == false){
                if(temp->m_buffer[temp->m_end] != temp2->m_buffer[temp2->m_end]){ //checks m_end index (only if such on exists)
                    data = false; //should find that different element at index 0
                }
            }
            temp = temp->m_next;
            temp2 = temp2->m_next;
        }
        Buffer* tempPrint = buffer.m_cursor->m_next; //prints out buffer
        for(int i=0;i<buffer.m_listSize;i++){
            int start = tempPrint->m_start;
            int end = tempPrint->m_end;
            int count = 0;
            cout << "Buffer size: " << tempPrint->m_capacity << " : ";
            if (tempPrint->m_capacity != 0){
                while(count < tempPrint->m_count){
                    cout << tempPrint->m_buffer[start] << "[" << start << "]" << " ";
                    start = (start + 1) % tempPrint->m_capacity;
                    count++;
                }
                cout << endl;
            }
            tempPrint = tempPrint->m_next;
        }
    }
    if(data == true && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

bool Tester::BufListAssigmentOperatorDiffrentData(const BufferList &buffer){
    bool address = true; //sees if addresses are different
    bool size = false; //sees if capacities are the same
    bool data = true; //sees if data are the same
    BufferList b2 = buffer;
    b2.dump(); //Will prints out buffer for both buffer and b2
    cout << "_____________________________" << endl;
    if(buffer.m_cursor->empty() == true && b2.m_cursor->empty() == true){ //if capacity is zero for both
        cout << "Both BufferLists are empty" << endl;
        size = true;
        address = true;
        data = false;
    }else{
        if(b2.m_cursor->m_next->m_buffer[b2.m_cursor->m_next->m_start] != 10){ //changes first elements in buffer
            buffer.m_cursor->m_next->m_buffer[buffer.m_cursor->m_next->m_start] = 10;
        }else{
            buffer.m_cursor->m_next->m_buffer[buffer.m_cursor->m_next->m_start] = 5;
        }
        if(buffer.m_minBufCapacity == b2.m_minBufCapacity && buffer.m_listSize == b2.m_listSize){ //checks capacities and size
            cout << "List Sizes are " << buffer.m_listSize << " and " << b2.m_listSize << endl;
            size = true;
        }
        Buffer* temp = buffer.m_cursor->m_next;
        Buffer* temp2 = b2.m_cursor->m_next;
        for(int i=0;i<buffer.m_listSize;i++){
            if(temp != temp2){ //checks addresses
                cout << "Address are " << temp << " and " << temp2 << endl;
            }else{
                cout << "Address are " << temp << " and " << temp2 << endl;
                address = false; //if addresses are the same, then set address to false
            }
            int counter = temp->m_start;
            while(counter != temp->m_end){ //checks data in buffer
                if(temp->m_buffer[counter] != temp2->m_buffer[counter]){
                    data = false;
                }
                counter++;
                if(counter == temp->m_capacity){ //if counter reaches the end of the array
                    counter = 0;
                }
            }
            if(temp->m_buffer[temp->m_end] != temp2->m_buffer[temp2->m_end]){ //checks m_end index (only if such on exists)
                data = false; //should find that different element at index 0
            }
            temp = temp->m_next;
            temp2 = temp2->m_next;
        }
        Buffer* tempPrint = buffer.m_cursor->m_next; //prints out buffer
        for(int i=0;i<buffer.m_listSize;i++){
            int start = tempPrint->m_start;
            int end = tempPrint->m_end;
            int count = 0;
            cout << "Buffer size: " << tempPrint->m_capacity << " : ";
            if (tempPrint->m_capacity != 0){
                while(count < tempPrint->m_count){
                    cout << tempPrint->m_buffer[start] << "[" << start << "]" << " ";
                    start = (start + 1) % tempPrint->m_capacity;
                    count++;
                }
                cout << endl;
            }
            tempPrint = tempPrint->m_next;
        }
    }
    if(data == false && size == true && address == true){
        return true;
    }else{
        return false;
    }
}

void Tester::BufListAssigmentOperatorSelfAssign(){
    BufferList bufferlist1(10); //selfs assigns buffer, should print "Cannot self assign"
    bufferlist1 = bufferlist1;
}

void Tester::BufListEnqueuePerformance(int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        BufferList buffer1(N);
        start = clock();
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            buffer1.enqueue(rand() % 100 + 1);
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}

void Tester::BufListDequeuePerformance(int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        BufferList buffer1(N);
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            buffer1.enqueue(rand() % 100 + 1);
        }
        start = clock();
        for(int i = 0; i < N; i++){ //the algorithm to be analyzed for efficiency
            buffer1.dequeue();
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}

void Tester::measureInsertionTimeBufListCopyConstructor(int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        BufferList buffer1(N);
        start = clock();
        BufferList buffer2(buffer1);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}

void Tester::measureInsertionTime(int numTrials, int N){
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials-1;k++)
    {
        start = clock();
        BufferList p1(N);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N * N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}
