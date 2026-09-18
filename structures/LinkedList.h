#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct LLNode
{
    int data;
    LLNode *next;

    LLNode(int data, LLNode *next = nullptr) : data(data), next(next) {}
};

class LinkedList
{
private:
    LLNode *head;
    int count;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList()
    {
        LLNode *current = head;
        while (current != nullptr)
        {
            LLNode *next = current->next;
            delete current;
            current = next;
        }
    }

    // Insere na cabeça — O(1)
    void insert(int data)
    {
        head = new LLNode(data, head);
        count++;
    }

    // Verifica se contém um valor — O(n)
    bool contains(int data) const
    {
        LLNode *current = head;
        while (current != nullptr)
        {
            if (current->data == data)
                return true;
            current = current->next;
        }
        return false;
    }

    int size() const { return count; }

    // =========
    //  Iterador
    // =========
    class Iterator
    {
    private:
        LLNode *current;

    public:
        Iterator(LLNode *node) : current(node) {}

        int operator*() const { return current->data; }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif
