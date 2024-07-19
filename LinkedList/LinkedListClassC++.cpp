/*
LinkedListClassC++.cpp

Benjamin Alexander

7/17/2024

Assignment: This application provides a doubly linked circular list for the below problem:
Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Copyright (c) 2024 Benjamin Alexander. All rights reserved.
*/

class Node{
    public:
        int data;
        Node* next;
        Node* previous;

        Node(int x)
        {
            data = x;
            next = NULL;
            previous = NULL;
        }
};

class MyLinkedList {
private :
    Node* head;
    Node* tail;
    int size;
public:
    MyLinkedList() {
        head = NULL;
        tail = NULL;
        size = -1;
    }
    
    int get(int index) {
        Node* current = head; 
        if(size < 0)
            return -1;

        if(index == 0)
        {
            cout << "found " << current->data << " at index " << index << "\n\n";
            return (current->data);  
        }

        if(current->next == NULL)
            return -1;

        current = current->next; 
        int count = 1; 
        
        while (current != head) { 
            if (count == index) 
            {
                cout << "found " << current->data << " at index " << index << "\n\n";
                return (current->data); 
            }
            count++; 
            current = current->next; 
        }
        
        return -1;  
    }
    
    void push_front(int val) {
        Node* newNode = new Node(val);

        newNode->next = head;
        newNode->previous = tail;

        if(head == NULL) //if lsit is empty
            tail = newNode;
        else //else set tail next to the new head
        {
            tail->next = newNode;
            head->previous = newNode;
        }
        
        head = newNode;//set head to new head
        size++;
        cout << "added  " << val << " at front \n";
        PrintList();
    }
    
    void 3push_back(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        newNode->previous = tail;

        if(head == NULL) //if list is empty
            head = newNode;
        else //else set tail next to the new head
        {
            tail->next = newNode;
            head->previous = newNode;
        }
        
        tail = newNode;//set head to new head  
        size++;
        cout << "added  " << val << " at tail \n";
        PrintList();
    }
    
    void addAtIndex(int index, int val) {
        if(index == 0)//if num is less than head
        {
            push_front(val);
        }
        else if (index == size+1)//if num is greater than tail
        {
            push_back(val);
        }
        else if(index < size+1)
        {
            Node* newNode = new Node(val);//create new node
            newNode->next = head;//set next to head

            cout << "\n\n head = "<< head->data << "\n\n"; 

            for(int i = 0; i < index; i++)
            {
                newNode->next = newNode->next->next;
            }
            newNode->previous = newNode->next->previous;//we found the correct insert point, set previous to next previous
            newNode->previous->next = newNode;//finally remember to resolve the previous and next nodes, to point to this new node
            newNode->next->previous = newNode;
            size++;
            cout << "added  " << val << " at index "  << index << "\n";
            PrintList();
        }
    }

    void pop_back()
    {
        Node* t = tail;   
        
        if(t->next == NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            tail->previous->next = head;
            head->previous = tail->previous;
            tail = tail->previous;
        }
        cout << "removed  " << t->data << " at tail \n";

        delete(t);
        size--;
        PrintList();
    }

    void pop_front()
    {
        Node* t = head; 
        
        if(t->next == NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head->next->previous = tail;
            tail->next = head->next;
            head = head->next;
        }
        cout << "removed  " << t->data << " at front \n";

        delete(t);
        size--;
        PrintList();
    }
    
    void deleteAtIndex(int index) {
        if(index == 0)
        {
            pop_front();
        }
        else if (index == size)
        {
            pop_back();
        }
        else if(index < size)
        {
            Node* t = head;
            for(int i = 0; i < index; i++)
            {
                t = t->next;
            }
            if(t->next == t->previous)
            {
                t->next->next = NULL;
                t->previous->previous = NULL;
                head = t->next;
                tail = t->next;
            }
            else
            {
                t->next->previous = t->previous;
                t->previous->next = t->next;
            }
        
            cout << "delete " << t->data << " at index " << index << "\n";
            delete(t);
            size--;
            PrintList();
        }
    }

    void PrintList()
    {
        cout << "size = " << size << ", ";
        if(size < 0)
        {
            return;
        }
        cout << head->data<< " ";//since list is circular, print head, then move to next value
        struct Node *ptr = head->next;
        
        while(ptr != head && ptr != NULL)//look back to head and print all values
        {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << "\n";
    }

    void PrintListBackward()
    {
        if(size < 0)
        {
            return;
        }
        if(head->previous != NULL)
        {
            cout << head->previous->data<< " ";//since list iis circular, print previous, then move to next value
            struct Node *ptr = head->previous->previous;
            while(ptr != head->previous && ptr != NULL)//look back to previous and print all values
            {
                cout << ptr->data << " ";
                ptr = ptr->previous;
            }
        }
        else
        {
            cout << head->data<< " ";//since list is circular, print head, then move to next value 
        }
        cout << "\n";
    }
};

int main()
{
	MyLinkedList myLinkedList = new MyLinkedList();
	myLinkedList.addAtHead(1);
	myLinkedList.addAtTail(3);
	myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
	myLinkedList.get(1);              // return 2
	myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
	myLinkedList.get(1);              // return 3
	return 0;
}