#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    cout << " ---------- Testing Linked List ---------- " << endl;
    cout << endl;
    LinkedList<int> list;

    list.addHead(1);
    list.addHead(2);
    list.addHead(3);
    list.addHead(4);
    list.addHead(5);

    cout << "Print fowards: " << endl;
    list.printForward();
    // 5 4 3 2 1
    cout << endl;
    
    cout << "Print Backwards: " << endl;
    list.printReverse();
    // 1 2 3 4 5
    cout << endl;

    list.removeHead();
    list.removeHead();
    list.removeTail();

    cout << "Print fowards: (After edits) " << endl;
    list.printForward();
    // 3 2
    cout << endl;

    LinkedList<int> nList;
    nList = list;

    cout << "Print fowards: (Copy ass) " << endl;
    // 3 2
    list.printForward();
    cout << endl;

    nList = move(list);

    cout << "Print fowards: (Move ass) " << endl;
    cout << endl;

    nList.printForward();
    cout << "Should be empty -> " << endl;
    list.printForward();

    cout << "LINKED LIST TEST DONEEE :)))))) " << endl;
    cout << endl;
    cout << " ---------- Testing ABS STACK ---------- " << endl;  
    cout << endl;
    ABS<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);

    cout << "Stack size: " << stack.getSize() << endl;
    cout << "Peek top: " << stack.peek() << endl;

    cout << "POP 2: " << endl;

    cout << "1: " << stack.pop() << endl;
    cout << "2: " << stack.pop() << endl;

    cout << "Popping EVERYTHING!!!!!!" << endl;
    while (stack.getSize() > 0) {
        cout << "POP: " << stack.pop() << endl;
    }

    cout << "Stack size: " << stack.getSize() << "(pls be 0)" << endl;

    cout << endl;

    cout << "ABS DONE!" << endl;

    cout << " ---------- Testing LLS ---------- " << endl;
    cout << endl;

    LLS<int> lls;
    lls.push(12);
    lls.push(11);
    lls.push(2025);
    lls.push(123456789);

    cout << "Peek: " << lls.peek() << " / (should be 12345...)" << endl;
    cout << "Pop: " << lls.pop() << " / (should be 12345...)" << endl;
    cout << "Size: " << lls.getSize() << " / (should be 3)" << endl;
    
    lls.pop();
    lls.push(13);
    lls.push(14);

    cout << endl;
    lls.printForward();
    cout << "Should be: 14, 13, 11, 12" << endl;

    lls.printReverse();
    cout << "Should be: 12, 11, 13, 14" << endl;

    cout << endl;

    cout << "LLS TESTING DONE :)))" << endl;
 
    cout << " ---------- Testing LLQ ---------- " << endl;
    cout << endl;

    LLQ<int> q;

    cout << "enq stuff!!!!" << endl;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    cout << "Print ->: " << endl;
    q.printForward();
    cout << "Should be: 1,2,3,4,5" << endl;
    cout << endl;

    cout << "Print <-: " << endl;
    q.printReverse();
    cout << "Should be: 5,4,3,2,1" << endl;
    cout << endl;

    cout << "Peek front: " << q.peek() << " (should be 1)" << endl;
    cout << "dq one: " << q.dequeue() << " (should be 1)" << endl;
    cout << "Peek again: " << q.peek() << " (should be 2)" << endl;
    cout << "q size: " << q.getSize() << " (should be 4)" << endl;

    cout<<"TESTING FOE LLQ DONE :O" << endl;

    cout << endl;

    cout << " ---------- Testing LLDQ ---------- " << endl;
    cout << endl;

    LLDQ<int> dq;

    cout << "enq stuff!!!!" << endl;
    dq.pushFront(1);
    dq.pushFront(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);

    cout << "Print ->: " << endl;
    dq.printForward();
    cout << "Should be: 2,1,3,4,5" << endl;
    cout << endl;

    cout << "Print <-: " << endl;
    dq.printReverse();
    cout << "Should be: 5,4,3,1,2" << endl;
    cout << endl;

    cout << "Front: " << dq.front() << " (should be 2)" << endl;
    cout << "PopFront: " << dq.popFront() << " (should be 2)" << endl;
    cout << "PopBack: " << dq.popBack() << " (should be 5)" << endl;
    cout << "Back: " << dq.back() << " (should be 4)" << endl;

    cout<<"TESTING LLDQ COMPLETE!!!!!!!" << endl;

    cout << endl;

    cout << " ---------- Testing ABQ ---------- " << endl;
    cout << endl;

    ABQ<int> q1;

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);

    cout << "q ->:" << endl;
    q1.printForward();
    cout << "Should be 1 2 3 4 5" << endl;

    q1.printReverse();
    cout << "Should be 5 4 3 2 1" << endl;

    cout << "Peek front: " << q1.peek() << " (should be 1)" << endl;
    cout << "dq: " << q1.dequeue() << " (should be 1)" << endl;
    cout << "dq: " << q1.dequeue() << " (should be 2)" << endl;

    cout<<"should test more, but itll be ok" << endl;

    cout << " ---------- Testing ABDQ ---------- " << endl;
    cout << endl;

    ABDQ<int> d2;

    d2.pushBack(1);
    d2.pushBack(2);
    d2.pushBack(3);

    cout << "front: " << d2.front() << "------ back: " << d2.back() << endl;

    for(int i = 4; i <= 10; i++){
        d2.pushBack(i);
    }

    cout << "after push back:\n" << endl;
    cout << "front: " << d2.front() << " back: " << d2.back() << endl;
    cout << "size: " << d2.getSize() << endl;

    cout << "ALL TEST FINALLY DONE T-T" << endl;

    return 0;

}



#endif