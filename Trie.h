#pragma once

#include <string>
#include <iostream>
#include <vector>

#define ALPHABET_SIZE 26
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, std::string);
bool search(TrieNode*, std::string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode* root, std::string key, int depth);
std::vector<std::string> findWords(TrieNode* root, int ch);
