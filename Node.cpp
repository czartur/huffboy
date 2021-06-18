#include <iostream>
#include "Node.h"
using namespace std;

bool operator<(const Node &n1, const Node &n2){
        return (n1.m_freq > n2.m_freq);
}
bool operator==(const Node &n1, const Node &n2){
        return ((n1.m_freq == n2.m_freq) && (n1.m_id == n2.m_id));
}
void Node::show(){ cout << "(" << m_id << ", " << m_freq << ")" << endl; }
void Node::alter_ego(int jeff_bezos){ 
        m_id = jeff_bezos;
        m_freq = left->m_freq + right->m_freq;
}