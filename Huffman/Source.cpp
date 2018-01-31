#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include <iomanip>
using namespace std;

int ch[28];
float prob[28];


typedef struct node {
	int name;
	float prob;
	bool flag = false;
	string value = "";
	struct node *left;
	struct node *right;
	struct node *dad;
} Node;

void ComputeProb(int);
void ComputeEntropy(int);
Node* FindMinProb(vector<Node> &, int);

void ArraySort(vector<Node> &node, int size) {
	Node temp;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (node[i].prob > node[j].prob) {
				temp = node[j];
				node[j] = node[i];
				node[i] = temp;
			}
		}
	}
}

void CreateTree(vector<Node> &node, int size) {
	Node *min1 = &node[0], *min2 = &node[0];
	for (int i = 0; i < size; i++) {
		min1 = FindMinProb(node, size);
		min2 = FindMinProb(node, size);
		Node parenaNode;
		parenaNode.name = i;
		parenaNode.prob = min1->prob + min2->prob;
		parenaNode.left = min1;
		parenaNode.right = min2;
		parenaNode.dad = NULL;
		node.push_back(parenaNode);
		min1->dad = &node[node.size() - 1];
		min2->dad = &node[node.size() - 1];
		//	cout << "parenaNode:" << min1->dad << endl;
	}
}

Node* FindMinProb(vector<Node> &node, int size) {
	float probTemp = 1;
	Node *min = &node[0];
	for (int i = 0; i < node.size(); i++) {
		if (node[i].flag)
			continue;
		else {
			if (node[i].prob < probTemp) {
				probTemp = node[i].prob;
				min = &node[i];
				//	cout << "min" << min << endl;
			}
		}
	}
	min->flag = true;
	return min;
}

void ComputeHuffmanCode(Node &myNode) {
	if (myNode.left != NULL) {
		myNode.left->value = myNode.value + "0";
		ComputeHuffmanCode(*myNode.left);
	}
	if (myNode.right != NULL) {
		myNode.right->value = myNode.value + "1";
		ComputeHuffmanCode(*myNode.right);
	}
}

void PrintAns(vector<Node> &node) {
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {

			if (node[j].name == i) {
				if (i == 26)
					cout << "CR:" << ch[i] << "\t\t" << "P(CR):" << node[j].prob << "\t\t" << "Code:" << node[j].value << endl;
				else if (i == 27)
					cout << "SP:" << ch[i] << "\t\t" << "P(SP):" << node[j].prob << "\t\t" << "Code:" << node[j].value << endl;
				else if (node[j].prob == 0)
					cout << (char)('a' + i) << ":" << ch[i] << "\t\t" << "P(" << (char)('a' + i) << "):" << node[j].prob << "\t\t\t" << "Code:" << node[j].value << endl;
				else
					cout << (char)('a' + i) << ":" << ch[i] << "\t\t" << "P(" << (char)('a' + i) << "):" << node[j].prob << "\t\t" << "Code:" << node[j].value << endl;
				break;
			}
		}
	}
}


int main() {
	int count = 0;
	fstream fin;
	fin.open("santaclaus.txt", ios::in);
	if (!fin) {
		cout << "ÀÉ®×Åª¨ú¥¢±Ñ" << endl;
	}
	else {
		char temp;
		while (fin.get(temp)) {	////////ÅªÀÉ
			if (temp == '\n')
				ch[26]++;
			else if ((int)temp == 32)
				ch[27]++;
			else {
				ch[temp - 'a']++;
			}
			count++;
		}
		/******* Problem3 *******/
		ComputeProb(count);
		ComputeEntropy(count);
		/******* Problem4 *******/
		//Node mynode[28];
		vector<Node> myNode;
		for (int i = 0; i<28; i++) {
			Node mynode;
			mynode.name = i;
			mynode.prob = prob[i];
			mynode.left = NULL;
			mynode.right = NULL;
			mynode.dad = NULL;
			myNode.push_back(mynode);
		}
		myNode.reserve(60);
		ArraySort(myNode, myNode.size());
		CreateTree(myNode, myNode.size() - 1);
		ComputeHuffmanCode(myNode[myNode.size() - 1]);


		PrintAns(myNode);
	}

	system("PAUSE");
	return 0;
}


void ComputeProb(int count) {
	for (int i = 0; i<28; i++) {
		prob[i] = (float)ch[i] / count;
		//if (i == 26)
		//	cout << "CR:" << ch[i] << "\tP(CR):" << prob[i] << endl;
		//else if (i == 27)
		//	cout << "SP:" << ch[i] << "\tP(SP):" << prob[i] << endl;
		//else{
		//	cout << (char)(i + 'a') << ":" << ch[i] << "\tP(" << (char)(i + 'a') << "):" << prob[i] << endl;
		//}
	}
}

void ComputeEntropy(int count) {
	float entropy = 0;
	for (int i = 0; i<28; i++) {
		if (prob[i] == 0) {
			//	cout << "Entropy = 0" << endl;

		}
		else {
			//	cout << (char)(i + 'a') << "  Entropy = " << prob[i] * (log(1 / prob[i]) / log(2)) << endl;
			entropy = entropy + (prob[i] * (log(1 / prob[i]) / log(2)));
		}
	}
	cout << "Entropy = " << entropy << " bits/symble" << endl;
}
