#include <iostream>
#include <queue>
#include <string>
#include <map>
#include "Node.h"
using namespace std;

void buildTree(Node **head, priority_queue <Node> &pq){
    while(pq.size() > 1){
        Node* novo = new Node;
        novo->right = new Node;
        novo->left = new Node; 
        *(novo->right) = pq.top(); pq.pop();
        *(novo->left) = pq.top(); pq.pop();
        novo->amoeba();
        pq.push(*novo);
        *head = novo;
    }
}

void pre_traversal(Node* root, FILE* fp, map<char, string> &table, string& cur){
	if(root == nullptr) return;
    fprintf(fp, "%d %c ", root->m_freq, root->m_data);
    if(root->left==nullptr && root->right==nullptr) table[root->m_data] = cur;
    cur+='0';
	pre_traversal(root->left, fp, table, cur);
    cur[cur.size()-1]='1';
	pre_traversal(root->right, fp, table, cur);
    cur.pop_back();
}

void sim_traversal(Node* root, FILE* fp){
	if(root == nullptr) return;
	sim_traversal(root->left, fp);
    fprintf(fp, "%d %c ", root->m_freq, root->m_data);
	sim_traversal(root->right, fp);
} 

int main() {
	FILE *input = fopen("input.txt", "r");
	FILE *huf = fopen("arvhuf.txt", "w");
	FILE *texto = fopen("texto.txt", "w");
	if(!input || !huf || !texto) {
		cout << "Problema na arbetura dos arquivos..." << endl;
		return 1;
	}
	priority_queue<Node> pq;
	Node* head = nullptr; 
	char caractere;

	//get frequency of each char from 'input.txt'
	map <char, int> frequencia;
	while ((caractere = fgetc(input)) != EOF) frequencia[caractere]++;
	for (auto p : frequencia) { //add to priority queue
		pq.push(Node(p.first, p.second));
	}
	buildTree(&head, pq);

    //generate 'arvhuf.txt' and encoding map
    string binaryPath;
	map<char, string> encoding;
    pre_traversal(head, huf, encoding, binaryPath);
    sim_traversal(head, huf);

	//translate 'input.txt' using encoding map
	rewind(input);
	while((caractere = fgetc(input)) != EOF){
		for(auto b: encoding[caractere]) fputc(b, texto);  
	}

	//debugging
	//for(auto p: frequencia) cout <<"caractere: " << p.first << " frequencia: " << p.second << endl;
	//for(auto p: encoding) cout << "caractere: " << p.first << " path: " << p.second << endl;

	fclose(input);
	fclose(huf);
	fclose(texto);
	return 0;
}