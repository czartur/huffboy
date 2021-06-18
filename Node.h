#ifndef NODE_H
#define NODE_H

class Node{
public:
    int m_id; //0 ~ 255 (ascii table characters) 256~(2*#dif.char -1) (artifical nodes)
    int m_freq;
    Node* left;
    Node* right; 
    Node (int id='@', int freq=0)
    : m_id(id), m_freq(freq), left(nullptr), right(nullptr){}
    friend bool operator<(const Node &n1, const Node &n2); //inverse comparison
    friend bool operator==(const Node &n1, const Node &n2);
    void show();
    void alter_ego(int jeff_bezos); //fill artificial nodes
};

#endif