#include <unordered_map>
#include<iostream>
using namespace std;

class Node
{
public:
    int key, value;
    Node *next, *prev;
    Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList
{
private:
    Node *head, *tail;

public:
    DoublyLinkedList()
    {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    void addtoFront(Node *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToFront(Node *node)
    {
        removeNode(node);
        addtoFront(node);
    }

    Node *removeLast()
    {
        Node *last = tail->prev;
        if (last == head)
            return nullptr;
        removeNode(last);
        return last;
    }

    ~DoublyLinkedList()
    {
        Node *curr = head;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

class LRUCache
{
private:
    int capacity;
    unordered_map<int, Node *> cache;
    DoublyLinkedList dll;

public:
    LRUCache(int cap) : capacity(capacity) {}

    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1; // not found
        // Move the accessed node to the front of the list (Found)
        Node *node = cache[key];
        dll.moveToFront(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (cache.find(key) != cache.end())
        {
            Node *node = cache[key];
            dll.moveToFront(node);
            node->value = value; // Update the value
        }
        else
        {
            if (cache.size() >= capacity)
            {
                Node *last = dll.removeLast();
                if (last)
                {
                    cache.erase(last->key); // Remove from cache
                    delete last;            // Free memory
                }
            }
            Node *node = new Node(key, value);
            dll.addtoFront(node);
            cache[key] = node;
        }
    }

    ~LRUCache()
    {
        for (auto &pair : cache)
        {
            delete pair.second; // Free memory for each node in the cache
        }
    }
};

int main()
{
    LRUCache cache(2); // capacity 2

    cache.put(1, 1);
    cache.put(2, 2);
    cout<< "get(1): " << cache.get(1) << "\n"; // returns 1

    cache.put(3, 3);                            // evicts key 2
    cout << "get(2): " << cache.get(2) << "\n"; // returns -1 (not found)

    cache.put(4, 4);                            // evicts key 1
    cout << "get(1): " << cache.get(1) << "\n"; // returns -1 (not found)
    cout << "get(3): " << cache.get(3) << "\n"; // returns 3
    cout << "get(4): " << cache.get(4) << "\n"; // returns 4

    return 0;
}