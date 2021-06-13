#ifndef NODE_H
#define NODE_H

class Node{
public:
    char m_data;
    int m_freq;
    Node* left;
    Node* right; 
    Node (int data='@', int freq=0)
    : m_data(data), m_freq(freq), left(nullptr), right(nullptr){}
    friend bool operator<(const Node &n1, const Node &n2); //inverse comparison
    friend bool operator==(const Node &n1, const Node &n2);
    void show();
    void amoeba(); //children sum
};

#endif