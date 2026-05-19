#include <iostream>
#include <unordered_map>
using namespace std;

// Node for Doubly Linked List
class Node {
public:
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v) {
        key = k;
        value = v;
        prev = next = NULL;
    }
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;

    Node* head;
    Node* tail;

    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void deleteNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(0, 0);
        tail = new Node(0, 0);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            int val = node->value;

            cache.erase(key);
            deleteNode(node);
            addNode(node);
            cache[key] = head->next;

            return val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* existing = cache[key];
            cache.erase(key);
            deleteNode(existing);
        }

        if (cache.size() == capacity) {
            Node* lru = tail->prev;
            cache.erase(lru->key);
            deleteNode(lru);
        }

        Node* newNode = new Node(key, value);
        addNode(newNode);
        cache[key] = head->next;
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << cache.get(1) << endl; // 10

    cache.put(3, 30); // evicts key 2

    cout << cache.get(2) << endl; // -1

    return 0;
}
