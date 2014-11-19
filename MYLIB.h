//
//  DANLIB.h
//
//  Created by Daniel Henderson on 2/11/14.
//  CSUF
//  CPSC 131 Section 02 - Data Structures
//  Prof. M. Ahmadnia
//  Spring 2014
//
//  Copyright (c) 2014 Deep Bondi.  The MIT License (MIT).
//


#ifndef __BST_TREE__
#define __BST_TREE__

#include <iomanip>
using namespace std;

enum TRAVERSE_ORDER_ { PREORDER_, INORDER_, POSTORDER_, NOPREF_ };
enum CHILD_COUNT_ { LEAF_, ONE_, TWO_, ANY_ };
enum STYLE_ { FULL_, NAME_ONLY_ };

class bst_tree {
public:
    struct user_record {
        int ID_number; // key field
        string Name; // Customer Name
        int Balance; // Customer balance ( whole dollars only )
    };
    
private:
    struct NODE {
        user_record info;
        NODE *left;
        NODE *right;
    };
    
    NODE* root;
    
    // For searches, a "best match" only counts from the beginning of the string.
    // The number of matching letters, from the beginning, gives the bestKeyMatchLength
    int bestKeyMatchLength = 0;
    // a pointer to the best match is saved at the end of a search.
    NODE* bestKeyMatch;
    
    // Each object has a current style with which records will display.
    // Some methods set this value before displaying info,
    // like the leaf display and other "short" info displays.
    STYLE_ currentDisplayStyle = FULL_;
    
    void insert(NODE* &r, user_record x){
        if (r == NULL) {
            r = new(NODE);
            r->info.ID_number = x.ID_number;
            r->info.Name = x.Name;
            r->info.Balance = x.Balance;
            r->left = r->right = NULL;
        }
        if ( x.ID_number < r->info.ID_number) {
            insert(r->left, x);
        }
        if (x.ID_number > r->info.ID_number) {
            insert(r->right, x);
        }
    }
    
    void DisplayInorder(NODE* r, CHILD_COUNT_ c=ANY_){ // (LC)(P)(RC)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            DisplayInorder(r->left, c);
            if ( c == ANY_ ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
            DisplayInorder(r->right, c);
        }
    }
    
    void DisplayPreorder(NODE* r, CHILD_COUNT_ c=ANY_){ // (P)(LC)(RC)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            if ( c == ANY_ ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
            DisplayPreorder(r->left, c);
            DisplayPreorder(r->right, c);
        }
    }
    
    void DisplayPostorder(NODE* r, CHILD_COUNT_ c=ANY_){ // (LC)(RC)(P)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            DisplayPostorder(r->left, c);
            DisplayPostorder(r->right, c);
            if ( c == ANY_ ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
        }
    }
    
    void DisplayNode(NODE* n){
        if (currentDisplayStyle == FULL_) {
            cout  << "  " << left << setw(5) << n->info.ID_number  << left << setw(7) << n->info.Name  << right << setw(9) << n->info.Balance << endl;
            
        } else if ( currentDisplayStyle == NAME_ONLY_ ) {
            cout  << n->info.ID_number << "  ";
        } else {
            cout << n->info.Name << endl;
        }
    }
    
    void DisplayHeading(){
        cout << "ID       Name     Balance  " << endl;
        cout << "---------------------------" << endl;
    }
    
    void searchOnKey( NODE* p, int s){
        // must catch null pointers
        // before trying to access data of node
        if ( p == NULL) {
            cout << endl << "No match to key \"" << s << "\"" << endl;
            
            return;
        }
        
        // since pointer points to node,
        // ok to check members of node
        if ( s == p->info.ID_number) {
            DisplayNodeInfo( p );
        }
        if ( s < p->info.ID_number) {
            searchOnKey(p->left, s);
        }
        if ( s > p->info.ID_number) {
            searchOnKey(p->right, s);
        }
    }
    
    
    void DisplayNodeInfo( NODE* n){
        cout << endl << "Info: " << n->info.ID_number << " : " << n->info.Name << " : " << n->info.Balance << endl;
    }
    
    
public:
    bst_tree() {
        root = NULL;
    }
    
    
    void insert(user_record m){
        insert(root, m);
    }
    
    void DisplayInorder(){
        DisplayHeading();
        DisplayInorder(root);
    }
    
    
    void DisplayLeafNodes(TRAVERSE_ORDER_ travorder){
        currentDisplayStyle = NAME_ONLY_;
        cout << endl << "Leaves of the tree are: " << endl;
        switch (travorder) {
            case PREORDER_:
            {
                DisplayPreorder(root, LEAF_);
                break;
            }
            case POSTORDER_:
            {
                DisplayPostorder(root, LEAF_);
                break;
            }
            default:
            {
                DisplayInorder(root, LEAF_);
                break;
            }
        }
        cout << endl;
    }
    
    void DisplayDoubleChildNodes(TRAVERSE_ORDER_ travorder){
        currentDisplayStyle = NAME_ONLY_;
        cout << endl << "Parents with two children are: " << endl;
        switch (travorder) {
            case PREORDER_:
            {
                DisplayPreorder(root, TWO_);
                break;
            }
            case POSTORDER_:
            {
                DisplayPostorder(root, TWO_);
                break;
            }
            default:
            {
                DisplayInorder(root, TWO_);
                break;
            }
        }
        cout << endl;
    }
    
    void DisplaySingleChildNodes(TRAVERSE_ORDER_ travorder){
        currentDisplayStyle = NAME_ONLY_;
        cout << endl << "Parents with only one child are: " << endl;
        switch (travorder) {
            case PREORDER_:
            {
                DisplayPreorder(root, ONE_);
                break;
            }
            case POSTORDER_:
            {
                DisplayPostorder(root, ONE_);
                break;
            }
            default:
            {
                DisplayInorder(root, ONE_);
                break;
            }
        }
        cout << endl;
    }
    
    
    void searchKey(int s){
        
        searchOnKey( root, s);
    }
    
    
};

#endif // __BST_TREE__






#ifndef __TREE__
#define __TREE__

#include <iomanip>
using namespace std;

enum TRAVERSE_ORDER { PREORDER, INORDER, POSTORDER, NOPREF };
enum CHILD_COUNT { LEAF, ONE, TWO, ANY };
enum STYLE { FULL, NAME_ONLY };

class tree {
public:
    struct MONTH {
        string MonthName; // key field
        int MonthDays;
    };
    
private:
    struct NODE {
        string month_Name;
        int month_Days;
        NODE *left;
        NODE *right;
    };
    
    NODE* root;
    
    // For searches, a "best match" only counts from the beginning of the string.
    // The number of matching letters, from the beginning, gives the bestKeyMatchLength
    int bestKeyMatchLength = 0;
    // a pointer to the best match is saved at the end of a search.
    NODE* bestKeyMatch;
    
    // Each object has a current style with which records will display.
    // Some methods set this value before displaying info,
    // like the leaf display and other "short" info displays.
    STYLE currentDisplayStyle = FULL;

    void insert(NODE* &r, MONTH x){
        if (r == NULL) {
            r = new(NODE);
            r->month_Name = x.MonthName;
            r->month_Days = x.MonthDays;
            r->left = r->right = NULL;
        }
        if ( x.MonthName < r->month_Name) {
            insert(r->left, x);
        }
        if (x.MonthName > r->month_Name) {
            insert(r->right, x);
        }
    }

    void DisplayInorder(NODE* r, CHILD_COUNT c=ANY){ // (LC)(P)(RC)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            DisplayInorder(r->left, c);
            if ( c == ANY ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
            DisplayInorder(r->right, c);
        }
    }
    
    void DisplayPreorder(NODE* r, CHILD_COUNT c=ANY){ // (P)(LC)(RC)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            if ( c == ANY ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
            DisplayPreorder(r->left, c);
            DisplayPreorder(r->right, c);
        }
    }
    
    void DisplayPostorder(NODE* r, CHILD_COUNT c=ANY){ // (LC)(RC)(P)
        if (r != NULL) {
            int countOfChildren = 0;
            if (r->left != NULL) countOfChildren++;
            if (r->right != NULL) countOfChildren++;
            DisplayPostorder(r->left, c);
            DisplayPostorder(r->right, c);
            if ( c == ANY ){
                DisplayNode( r );
            } else if ( countOfChildren == c ){
                DisplayNode( r );
            }
        }
    }
    
    void DisplayNode(NODE* n){
        if (currentDisplayStyle == FULL) {
            cout  << "  " << left << setw(14) << n->month_Name << n->month_Days << endl;

        } else if ( currentDisplayStyle == NAME_ONLY ) {
            cout  << n->month_Name << "  ";
        } else {
            cout << n->month_Name << endl;
        }
    }
    
    void DisplayHeading(){
        cout << "Month name    No. Days" << endl;
        cout << "----------------------" << endl;
    }
    
    void searchOnName( NODE* p, string s){
        // must catch null pointers
        // before trying to access data of node
        if ( p == NULL) {
            cout << endl << "No match to string \"" << s << "\"" << endl;
            if (bestKeyMatch != NULL) {
                cout << "Best matching string is \"" << bestKeyMatch->month_Name << "\"" << endl;
            }
            
            return;
        }
        
        // since pointer points to node,
        // ok to check members of node
        if ( s == p->month_Name) {
            DisplayNodeInfo( p );
        }
        if ( s < p->month_Name) {
            int matchLen = compareKey(p, s);
            if ( matchLen > bestKeyMatchLength ) {
                bestKeyMatchLength = matchLen;
                bestKeyMatch = p;
            }
            searchOnName(p->left, s);
        }
        if ( s > p->month_Name) {
            int matchLen = compareKey(p, s);
            if ( matchLen > bestKeyMatchLength ) {
                bestKeyMatchLength = matchLen;
                bestKeyMatch = p;
            }
            searchOnName(p->right, s);
        }
    }
    
    int compareKey(NODE* n, string s){
        int compareMatch = 0;
        int counter = 0;
        int s_length = static_cast<int>(s.length());
        int n_data_length = static_cast<int>(n->month_Name.length());
        
        int shortest = s_length < n_data_length ? s_length : n_data_length;
        int longest = s_length > n_data_length ? s_length : n_data_length;
        while (compareMatch < shortest && counter < shortest && ( s[counter] == n->month_Name[counter] ) ) {
            compareMatch++;
            counter++;
        }
        
        // return -1 if exact match
        if ( compareMatch == longest ) {
            compareMatch = -1;
        }
        return compareMatch;
    }
    
    void DisplayNodeInfo( NODE* n){
        cout << endl << "There are " << n->month_Days << " days in the month of " << n->month_Name << endl;
    }

    
public:
    tree() {
        root = NULL;
    }
    
    
    void insert(MONTH m){
        insert(root, m);
    }
    
    void DisplayInorder(){
        DisplayHeading();
        DisplayInorder(root);
    }
    
    
    void DisplayLeafNodes(TRAVERSE_ORDER travorder){
        currentDisplayStyle = NAME_ONLY;
        cout << endl << "Leaves of the tree are: " << endl;
        switch (travorder) {
            case PREORDER:
            {
                DisplayPreorder(root, LEAF);
                break;
            }
            case POSTORDER:
            {
                DisplayPostorder(root, LEAF);
                break;
            }
            default:
            {
                DisplayInorder(root, LEAF);
                break;
            }
        }
        cout << endl;
    }
    
    void DisplayDoubleChildNodes(TRAVERSE_ORDER travorder){
        currentDisplayStyle = NAME_ONLY;
        cout << endl << "Parents with two children are: " << endl;
        switch (travorder) {
            case PREORDER:
            {
                DisplayPreorder(root, TWO);
                break;
            }
            case POSTORDER:
            {
                DisplayPostorder(root, TWO);
                break;
            }
            default:
            {
                DisplayInorder(root, TWO);
                break;
            }
        }
        cout << endl;
    }
    
    void DisplaySingleChildNodes(TRAVERSE_ORDER travorder){
        currentDisplayStyle = NAME_ONLY;
        cout << endl << "Parents with only one child are: " << endl;
        switch (travorder) {
            case PREORDER:
            {
                DisplayPreorder(root, ONE);
                break;
            }
            case POSTORDER:
            {
                DisplayPostorder(root, ONE);
                break;
            }
            default:
            {
                DisplayInorder(root, ONE);
                break;
            }
        }
        cout << endl;
    }
    

    void searchName(string s){
        bestKeyMatch = NULL;
        bestKeyMatchLength = 0;
        
       searchOnName( root, s);
   }
    
    
};

#endif // __TREE__


#ifndef __QUEUEPK__
#define __QUEUEPK__

#include <iostream>
using namespace std;

enum findTypes { MIN, MAX };

template <class T>
class queuepk {
private:
    struct node {
        T info;
        node *next;
    };
    node *front, *rear;
    
public:
    queuepk() { front = NULL; rear = NULL; }
    // -- add a node at the rear of the queue
    void pushq( T x) {
        node* p;
        p = new(node);
        p->info = x;
        p->next = NULL;
        
        if (front == NULL) {
            front = p;
            rear = p;
        } else {
            rear->next = p;
            rear = p;
        }
    }
    
    // test whether queue is empty or not
    bool Emptyq() {
        return (front == NULL) ? true : false;
    }
    
    // pop the first node
    T pop() {
        node *p = front;
        T x;
        x = front->info;
        front = front->next;
        delete (p);
        return x;
    }
    
    // find the minimum in queue
    T findminq(){
        node* found = NULL;
        node* h = front;
        node* t = NULL;
            found = front;
            while (h != NULL) {
                if (t != NULL) {
                    if (h->info < t->info) {
                        found = h;
                    }
                }
                t = h;
                h = t->next;
            }
        return found->info;
    }

    // find maximum in queue
    T findmaxq() {
        node* found = NULL;
        node* h = front;
        node* t = NULL;
        
            found = front;
            while (h != NULL) {
                if (t != NULL) {
                    if (h->info > t->info) {
                        found = h;
                    }
                }
                t = h;
                h = t->next;
            }
        return found->info;
    }
    
    // display all in queue
    void displyaAllq(){
        node* t = front;
        
    while(t != NULL && !this->Emptyq() ) {
        
        // int x = q.pop();
        cout << t->info << "-->";
        t = t->next;
    }
    cout << "NULL" << endl;
    }
    
}; // end class queuepk

#endif // defined(__QUEUEPK__)

#ifndef __STACKPK__
#define __STACKPK__
#include <iostream>
using namespace std;

template <class T>
class stackpk {
private:
    struct node {
        T info;
        node* next;
    };
    node *stack;
public:
    // constructor
    stackpk() { stack = NULL; }

    // add a node at the front of the list
    void pushs( T x ){
        node *p;
        p = new(node);
        p->info = x;
        p->next = NULL;
        if ( stack == NULL) {
            stack = p;
        } else {
            p->next = stack;
            stack = p;
        }
    }
    
    // test whether stack is empty or not
    bool Emptys() {
        return (stack == NULL) ? true : false;
    }
    
    // pop the first node
    T pop() {
        node *p = stack;
        T x;
        x = stack->info;
        stack = stack->next;
        delete p;
        return x;
    }
    
    // return sum of info in all nodes
    // node.info must respond to +
    T sum(){
        T total = 0;
        node* s = stack;
        while ( s != NULL) {
            total += s->info;
            s = s->next;
        }
        return total;
    }
    
    // return count of nodes in stack
    int nodecount(){
        int c = 0;
        node* s = stack;
        while ( s != NULL) {
            c += 1;
            s = s->next;
        }
        return c;
    }
    
    friend std::ostream& operator<<(std::ostream& os, stackpk &s){
        // string s = "";
        node* n = s.stack;
        while ( n != NULL) {
            os << static_cast<T>(n->info)  << "-->";
            n = n->next;
        }
        os << "NULL\n";
        return os;
    }
};

#endif // define __STACKPK__

#ifndef __ORDEREDLIST__
#define __ORDEREDLIST__

#include <iostream>
using namespace std;

template <class T>
class OrderedLinkedList {
private:
    struct NODE {
        T info;
        NODE *next;
    };
    NODE *list;
public:
    OrderedLinkedList() { list = NULL; }
    
    void Insert( T x ) {
        NODE *p = list, *q = list, *r;
        // create a new node
        r = new ( NODE );
        r->info = x;
        r->next = NULL;
        
        // find the insertion place
        while( p != NULL && p->info < x) {
            q = p;
            p = p-> next;
        }
        
        if ( p == list ) // x is the first info
        {
            list = r;
            r->next = p;
        } else if ( p == NULL) // x is the last info
        {
            q->next = r;
        } else // x is neither first nor last info
        {
            r->next = p;
            q->next = r;
        }
    }
    
    void display() {
        NODE *p = list;
        while (p != NULL) {
            cout << p->info << "-->";
            p = p->next;
        }
        cout << "NULL\n";
    }
    
    // return count of nodes in list
    int nodecount(){
        int c = 0;
        NODE* s = list;
        while ( s != NULL) {
            c += 1;
            s = s->next;
        }
        return c;
    }
    
    // return count of even nodes in list
    int evencount(){
        int c = 0;
        NODE* s = list;
        while ( s != NULL ) {
            if (s->info % 2 == 0) {
                c += 1;
            }
            s = s->next;
        }
        return c;
    }

    // return count of odd nodes in list
    int oddcount(){
        return (nodecount() - evencount());
    }
    
    //  find the average of info in all nodes
    float average(){
        NODE* l = list;
        int sum = 0.0;
        while ( l != NULL) {
            sum += l->info;
            l = l->next;
        }
        
        return (static_cast<float>(sum)/nodecount());
    }
    
    // print values from all nodes in list
    friend std::ostream& operator<<(std::ostream& os, OrderedLinkedList &s){
        // string s = "";
        NODE* n = s.list;
        while ( n != NULL) {
            os << static_cast<T>(n->info)  << "-->";
            n = n->next;
        }
        os << "NULL\n";
        return os;
    }

};


#endif // define __ORDEREDLIST__




#ifndef __STACK__
#define __STACK__


// Stack class
// Implements basic stack functions:
//   push
//   pop
//   isEmpty - user must test,
//             no fail mechanism
//             if pop when empty
//   isFull  - user must test
//   clearStack - only sets top pointer
//                to zero, does not free
//                any objects in stack.
//   max - returns maximum allowed items
//         for object. maxSize is initiallized
//         by Stack constructor,
//         so maxSize varies for each
//         instance.

template<class T, int maxSize>
class Stack {
private:
    T a[maxSize];
    int top;
public:
    void clearStack();
    bool isEmpty();
    bool isFull();
    void push(T item);
    int max();
    T pop();

};

template<class T, int maxSize>
bool Stack<T, maxSize>::isEmpty() {
    return static_cast<bool>(top == 0);
}

template<class T, int maxSize>
bool Stack<T, maxSize>::isFull() {
    return static_cast<bool>(top == maxSize);
}

template<class T, int maxSize>
T Stack<T, maxSize>::pop() {
    return a[--top];
}

template<class T, int maxSize>
void Stack<T,maxSize>::push(T item){
    a[top++] = item;
}

// TODO: Clear stack of memory-using objects
//       when clearing stack, or decrement
//       use counts if objects have them.
template<class T, int maxSize>
void Stack<T,maxSize>::clearStack(){
    top = 0;
}

template<class T, int maxSize>
int Stack<T, maxSize>::max() {
    return maxSize;
}



#endif /* defined(__LINKEDLIST__) */

#ifndef __LINKEDLISTschool__
#define __LINKEDLISTschool__
//
// class LINKEDLIST
//       adds nodes to list.
//       Always adds to end of list
//       by searching for last node.
//       TODO: add "tail" pointer to
//             make it more efficient

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class LINKEDLIST {
private:
    struct NODE{
        int age;
        float gpa;
        NODE *next;
    };
    
    NODE *head;
    
    NODE* findLastNode() {
        NODE* last  = head;
        
        if ( last == NULL) {
            return head;
        }
        
        while (last->next != NULL) {
            last = last->next;
        }
        
        return last;
    }
    
    void assignValuesToNode(NODE* n, int a, float g){
        n->age = a;
        n->gpa = g;
    }
public:
    void addNode(int a, float g){
        NODE* last = findLastNode();
        if ( last == NULL) {
            head = new(NODE);
            assignValuesToNode(head, a, g);
            return;
        }
        last->next = new(NODE);
        last = last->next;
        assignValuesToNode(last, a, g);
    }
    
    void displayAllNodes(){
        NODE* n = head;
        cout << "AGE \tGPA" << endl;
        cout << "------------" << endl;
        if (head != NULL) {
            do {
                displayNode(n);
                n = n->next;
            }
            while (n != NULL);
            
        }
    }
    
    void displayNode(NODE* n){
        cout << n->age << "\t" << fixed << setprecision(2) << n->gpa << endl;
    }
    
    NODE* findNodeWithAge(int a){
        bool isFound = false; // flag if found
        NODE* found = head;
        
        while (found != NULL && !isFound) {
            if (found->age == a) {
                isFound = true;
            }
            else {
                found = found->next;
            }
        }
        return isFound ? found : NULL;
    }
    
    NODE* findNodeWithGPA(float g, float accuracy = 0.01 ){
        bool isFound = false; // flag if found
        NODE* found = head;
        
        while (head != NULL && !isFound){
            if(found->gpa >= (g - accuracy) && found->gpa <= ( g + accuracy)) {
                isFound = true;
            } else{
                found = found->next;
            }
        }
        return isFound ? found : NULL;
    }
    
    LINKEDLIST() {
        head = NULL;
    }
    
    ~LINKEDLIST() {
        NODE *n1, *n2;
        n1 = head;
        while (n1 != NULL) {
            n2 = n1->next;
            delete n1;
            n1 = n2;
        }
    }
    
    
    
};


#endif /* defined(__LINKEDLISTschool__) */



