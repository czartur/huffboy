#include <iostream>
#include "Node.h"
using namespace std;

bool operator<(const Node &n1, const Node &n2){
        return (n1.m_freq > n2.m_freq);
}
bool operator==(const Node &n1, const Node &n2){
        return ((n1.m_freq == n2.m_freq) && (n1.m_data == n2.m_data));
}
void Node::show(){ cout << "(" << m_data << ", " << m_freq << ")" << endl; }
void Node::amoeba(){ m_freq = left->m_freq + right->m_freq; }