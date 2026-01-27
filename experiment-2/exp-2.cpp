#include <bits/stdc++.h>
using namespace std;

struct Node{
    char data;
    int freq;
    Node *left, *right;
    
    Node(char data,int freq){
        this->left = this->right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare{
    bool operator()(Node*l,Node*r){
        return (l->freq > r->freq);
    }
};
                                                  
void storeCodes(struct Node* root, string str, map<char, string> &huffmanCode){
    if(!root) return;
    
    if(root->data != '$')
        huffmanCode[root->data] = str;
        
    storeCodes(root->left, str+"0", huffmanCode);
    storeCodes(root->right, str+"1", huffmanCode);
}

void decode(struct Node* root, string s){
    struct Node* curr = root;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == nullptr && curr->right == nullptr) {
            cout << curr->data;
            curr = root;
        }
    }
}

void Huffman(string text){
    map<char, int> freq;
    for (char c : text)
        freq[c]++;

    struct Node *left, *right, *top;
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (auto pair : freq)
        minHeap.push(new Node(pair.first, pair.second));
        
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new Node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    map<char, string> huffmanCode;
    storeCodes(minHeap.top(), "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    string encodedString = "";
    for (char c : text) {
        encodedString += huffmanCode[c];
    }

    cout << "\nEncoded String: " << encodedString << endl;

	cout << "Decoded String: ";
    decode(minHeap.top(), encodedString);
    cout << endl;
}



int main() {
    string text;
    cout << "Enter text: ";
    cin>>text;
    
    Huffman(text);

    return 0;
}