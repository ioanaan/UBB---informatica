#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct HNode {
    int freq;
    unsigned char min_char; 
    int left, right; 
    char ch;
};

vector<HNode> nodes;

struct Cmp {
    bool operator()(int a, int b) {
        if (nodes[a].freq != nodes[b].freq)
            return nodes[a].freq > nodes[b].freq;
        return nodes[a].min_char > nodes[b].min_char;
    }
};

map<char, string> codes;

void buildCodes(int idx, const string& code) {
    if (nodes[idx].left == -1 && nodes[idx].right == -1) {

        codes[nodes[idx].ch] = code.empty() ? "0" : code;
        return;
    }
    buildCodes(nodes[idx].left, code + "0");
    buildCodes(nodes[idx].right, code + "1");
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string text;
    char c;
    while (fin.get(c)) text += c;
    fin.close();

    if (text.empty()) {
        fout << "0\n\n";
        fout.close();
        return 0;
    }

    map<char, int> freq;
    for (char ch : text) freq[ch]++;

    priority_queue<int, vector<int>, Cmp> pq;
    for (auto& p : freq) {
        HNode node;
        node.freq = p.second;
        node.ch = p.first;
        node.min_char = (unsigned char)p.first;
        node.left = node.right = -1;
        nodes.push_back(node);
        pq.push((int)nodes.size() - 1);
    }

    while (pq.size() > 1) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();

        HNode z;
        z.freq = nodes[x].freq + nodes[y].freq;
        z.min_char = min(nodes[x].min_char, nodes[y].min_char);
        z.left = x;
        z.right = y;
        z.ch = 0;
        nodes.push_back(z);
        pq.push((int)nodes.size() - 1);
    }

    int root = pq.top();
    buildCodes(root, "");

    fout << freq.size() << "\n";
    for (auto& p : freq)
        fout << p.first << " " << p.second << "\n";

    for (char ch : text) fout << codes[ch];
    fout << "\n";

    fout.close();
    return 0;
}