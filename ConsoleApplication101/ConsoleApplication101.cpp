#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    // Данные.
    T m_data;

    // Адрес следующего элемента списка.
    Node* m_next;

    // Адрес предыдущего элемента списка.
    Node* m_previous;

    Node(T data);

};

template <typename T>
Node<T>::Node(T data) :
    m_data(data),
    m_next(nullptr),
    m_previous(nullptr)
{
}

template <typename T>
class List
{

    // Голова.
    Node<T>* m_head;
    // Хвост.
    Node<T>* m_tail;

    // Количество элементов.
    unsigned int m_size;

public:

    List();
    List(const List& list);

    ~List();

    List& operator=(const List& right);

    // Добавление в начало списка.
    void AddHead(T data);

    // Добавление в конец списка.
    void AddTail(T data);

    void Assign(const List& list);

    // Вставка элемента в заданную позицию.
    void Insert(T data, unsigned int index);

    // Получить элемент списка по индексу.
    Node<T>* NodeAt(unsigned int index) const;

    // Печать списка, начиная с головы.
    void PrintHead() const;

    // Печать списка, начиная с хвоста.
    void PrintTail() const;

    // Удалить весь список.
    void RemoveAll();

    // Удаление элемента по индексу.
    void RemoveAt(unsigned int index);

    // Удаление головного элемента.
    void RemoveHead();

    // Удаление хвостового элемента.
    void RemoveTail();

    // Получение количества элементов, находящихся в списке.
    unsigned int GetSize() const;
};

template <typename T>
List<T>::List() : m_head(nullptr), m_tail(nullptr), m_size(0U)
{
}

template <typename T>
List<T>::List(const List& list) : m_head(nullptr), m_tail(nullptr), m_size(0U)
{
    Assign(list);
}

template <typename T>
List<T>::~List()
{
    RemoveAll();
}

template <typename T>
List<T>& List<T>::operator=(const List& right)
{
    if (this != &right)
    {
        Assign(right);
    }

    return *this;
}

template <typename T>
void List<T>::AddHead(T data)
{
    Node<T>* node = new Node<T>(data);

    if (m_size > 0U)
    {
        m_head->m_previous = node;
        node->m_next = m_head;
        m_head = node;
    }
    else
    {
        m_head = node;
        m_tail = node;
    }

    ++m_size;

}

template <typename T>
void List<T>::AddTail(T data)
{
    Node<T>* node = new Node<T>(data);

    if (m_size > 0U)
    {
        m_tail->m_next = node;
        node->m_previous = m_tail;
        m_tail = node;
    }
    else
    {
        m_head = node;
        m_tail = node;
    }

    ++m_size;
}

template <typename T>
void List<T>::Assign(const List& list)
{
    RemoveAll();

    Node<T>* node = list.m_head;

    while (node != nullptr)
    {
        AddTail(node->m_data);

        node = node->m_next;
    }
}

template <typename T>
unsigned int List<T>::GetSize() const
{
    return m_size;
}

template <typename T>
void List<T>::Insert(T data, unsigned int index)
{
    if (index < m_size)
    {
        if (index == 0U)
        {
            AddHead(data);
        }
        else if (index == m_size - 1U)
        {
            AddTail(data);
        }
        else
        {
            Node<T>* current = NodeAt(index);

            Node<T>* node = new Node<T>(data);

            node->m_previous = current->m_previous;
            node->m_next = current;

            current->m_previous->m_next = node;
            current->m_previous = node;

            ++m_size;
        }
    }
}

template <typename T>
Node<T>* List<T>::NodeAt(unsigned int index) const
{
    Node<T>* node = nullptr;

    if (index < m_size)
    {
        if (index < m_size / 2U)
        {
            node = m_head;

            unsigned int i = 0U;

            while (i < index)
            {
                node = node->m_next;
                i++;
            }
        }
        else
        {
            node = m_tail;

            unsigned int i = m_size - 1U;

            while (i > index)
            {
                node = node->m_previous;
                i--;
            }
        }
    }


    return node;
}

template <typename T>
void List<T>::PrintHead() const
{
    Node<T>* current = m_head;

    while (current != nullptr)
    {
        cout << current->m_data;

        current = current->m_next;
    }

    cout << endl;
}

template <typename T>
void List<T>::PrintTail() const
{
    Node<T>* current = m_tail;

    while (current != nullptr)
    {
        cout << current->m_data;

        current = current->m_previous;
    }

    cout << endl;
}

template <typename T>
void List<T>::RemoveAll()
{
    while (m_head != nullptr)
    {
        RemoveHead();
    }
}

template <typename T>
void List<T>::RemoveAt(unsigned int index)
{
    if (index < m_size)
    {
        if (index == 0U)
        {
            RemoveHead();
        }
        else if (index == m_size - 1U)
        {
            RemoveTail();
        }
        else
        {
            Node<T>* removeElement = NodeAt(index);

            removeElement->m_previous->m_next = removeElement->m_next;
            removeElement->m_next->m_previous = removeElement->m_previous;

            delete removeElement;

            --m_size;
        }
    }
}

template <typename T>
void List<T>::RemoveHead()
{
    if (m_head != nullptr)
    {
        Node<T>* node = m_head;

        m_head = m_head->m_next;

        if (m_head != nullptr)
        {
            m_head->m_previous = nullptr;
        }
        else
        {
            m_tail = nullptr;
        }

        delete node;

        --m_size;
    }
}

template <typename T>
void List<T>::RemoveTail()
{
    if (m_tail != nullptr)
    {
        Node<T>* node = m_tail;

        m_tail = m_tail->m_previous;

        if (m_tail != nullptr)
        {
            m_tail->m_next = nullptr;
        }
        else
        {
            m_head = nullptr;
        }

        delete node;

        --m_size;
    }
}

int main()
{
    List<int> list1;

    char szString[] = "Hello world!";
    cout << szString << endl;

    for (unsigned int i = 0U; i < strlen(szString); ++i)
    {
        list1.AddTail(szString[i]);
    }

    cout << endl << "First list" << endl;
    list1.PrintHead();

    List<int> list2 = list1;

    cout << endl << "Second list" << endl;
    list2.PrintHead();

    List<int> list3;
    list3 = list1;

    cout << endl << "Third list" << endl;
    list3.PrintHead();

    cout << endl << "First list" << endl;
    list1.PrintTail();

    list1.RemoveAt(2U);
    list1.PrintHead();

    list1.Insert('?', 0U);
    list1.Insert('?', 4U);
    list1.Insert('?', 4U);
    list1.PrintHead();

    return 0;
}