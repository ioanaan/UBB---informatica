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

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int N;
    fin >> N;
    fin.ignore(1000, '\n');

    map<char, int> freq;
    for (int i = 0; i < N; i++) {
        string line;
        getline(fin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        char ch = line[0];
        int fr = stoi(line.substr(2));
        freq[ch] = fr;
    }

    string bits;
    getline(fin, bits);
    if (!bits.empty() && bits.back() == '\r') bits.pop_back();
    fin.close();

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

    if (nodes[root].left == -1 && nodes[root].right == -1) {
        for (char b : bits) fout << nodes[root].ch;
        fout.close();
        return 0;
    }

    int cur = root;
    for (char b : bits) {
        cur = (b == '0') ? nodes[cur].left : nodes[cur].right;

        if (nodes[cur].left == -1 && nodes[cur].right == -1) {
            fout << nodes[cur].ch;
            cur = root;
        }
    }

    fout.close();
    return 0;
}