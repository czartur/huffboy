#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

void recoveryTree(vector<Node> &pre, vector<Node> &sim, int lp, int rp, int ls, int rs, Node** cur){

    Node* aux = new Node;
    *aux = pre[lp];
    aux->left = aux->right = nullptr;
    *cur = aux;

    //search for pre[lp] in sim 
    int i=ls;
    while(!(sim[i]==pre[lp])) i++; 

    //recurrence
    if(i!=ls) recoveryTree(pre, sim, lp+1, lp+i-ls, ls, i-1, &(aux->left));
    if(i!=rs) recoveryTree(pre, sim, lp+i-ls+1, rp, i+1, rs, &(aux->right));
}

char treeWalk(Node* cur, FILE* fcur){
    char c;
    if(cur->left == nullptr && cur->right == nullptr) return (char)cur->m_id;
    if((c=fgetc(fcur)) == EOF) return EOF;
    else if (c == '0') return treeWalk(cur->left, fcur);
    return  treeWalk(cur->right, fcur);
}

int main(){
    FILE* huf = fopen("arvhuf.txt", "r");
    FILE* texto = fopen("texto.hfm", "r");
    FILE* saida = fopen("saida.txt", "w");
    if(!huf || !texto || !saida){
        cout << "Problema na abertura dos arquivos..." << endl;
        return 1;
    }

    //get pre-order and sim-order from 'arvhuf.txt'
    fseek(huf, 0, SEEK_END);
    int tam = ftell(huf);
    rewind(huf);
    char lixo;
    int freq, id;
    vector<Node> pre, sim;
    while((fscanf(huf, "%d%c%d", &freq, &lixo, &id)) != EOF){
        //cout << caractere << numero << endl;
        if(ftell(huf)<=tam/2) pre.push_back(Node(id, freq));
        else sim.push_back(Node(id, freq));
    } 
    
    //recovery tree from pre-order and sim-order
    Node* head = nullptr;
    recoveryTree(pre, sim, 0, pre.size()-1, 0, sim.size()-1, &head);

    //translate 'texto.hfm' using tree
    char caractere;
    while((caractere = treeWalk(head, texto)) != EOF){
        fprintf(saida, "%c", caractere);
    }

    cout << "Prime Day 21 de Junho" << endl;

    fclose(huf);
    fclose(saida);
    fclose(texto);
    return 0;   
}