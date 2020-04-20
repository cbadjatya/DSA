#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode{
	vector<TrieNode*> children;
	bool isEnd = false;
};

TrieNode* makeNode(){
	TrieNode* node = new TrieNode();
	node->children = vector<TrieNode*> (26,NULL);
	return node;
}

void insert(TrieNode* root, string word, int i){
	if(i == word.size()){
		root->isEnd = true;
		return;
	}

	int index = word[i] - 'a';
	if(root->children[index] == NULL)
		root->children[index] = makeNode();

	insert(root->children[index],word,i+1);
}

TrieNode* makeTrie(vector<string>& words){
	TrieNode* root = makeNode();
	for(auto word : words){
		insert(root,word,0);
	}
	return root;
}

bool isEmpty(TrieNode* root){
	for(auto each : root->children){
		if(each != NULL) return false;
	}
	return true;
}

TrieNode* deleteWord(TrieNode* root, string word, int i=0){
	if(root == NULL) return NULL;

	if(i == word.size()){
		root->isEnd = false;

		if(isEmpty(root)){
			delete(root);
			root =  NULL;
		}

		return root;
	}

	int index = word[i] - 'a';
	root->children[index] = deleteWord(root->children[index],word,i+1);

	if(isEmpty(root) && root->isEnd != true){
		delete(root);
		root =  NULL;
	}
	return root;
}

bool check(TrieNode* root, string word, int i = 0){
	if(root == NULL) return false;

	int index = word[i]-'a';

	if(i == word.size()){
		return (root->isEnd);
	}
	
	return check(root->children[index], word, i+1);
}

void getSuggestions(TrieNode* root, string prefixString){

	if(root->isEnd){
		cout<<prefixString<<endl;
	}
	if(isEmpty(root)) return;

	for(int i=0;i<26;i++){
		if(root->children[i] != NULL){
			prefixString.push_back(97+i);
			getSuggestions(root->children[i],prefixString);
			prefixString.pop_back();
		}
	}
}

void printWords(TrieNode* root, string query){
	if (root==NULL){
		cout<<"NULL root\n";
		return;
	}
	TrieNode* curr = root;
	for(int i=0;i<query.length();i++){
		int index = query[i] - 'a';
		if(curr->children[index] == NULL){
			cout<<"prefix not present\n";
			return;
		}
		curr = curr->children[index];
	}

	getSuggestions(curr,query);
}

int main(){
	vector<string> words = {
		"apple","apply", "abby","ba", "ball", "bald", "baller", "baba", "waldo", "batman", "panther"
	};
	TrieNode* root = makeTrie(words);

	cout<<"is 'apple' present ? Ans: "<<check(root,"apple")<<"\n";

	root = deleteWord(root,"apple");

	cout<<"is 'apple' present now ? Ans: "<<check(root,"apple")<<"\n";

	cout<<"suggestions for 'bo' :\n";
	printWords(root,"bo");

	cout<<"suggestions for 'ba' :\n";
	printWords(root,"ba");

	cout<<"suggestions for 'waldo' :\n";
	printWords(root,"waldo");

	return 0;
}