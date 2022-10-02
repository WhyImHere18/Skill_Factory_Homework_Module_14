#include "Trie.h"

// ���������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ ��� ����� ����
    TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ����������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// �����, ���� ���� ������� ��������� ���� ������, 
// �������� � �������� ��������� �.�. ����� �����
void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � �������� ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ���� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false
bool search(struct TrieNode* root, std::string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, std::string key, int depth = 0)
{
    // ���� ������ ������
    if (!root)
        return nullptr;
    // ���� ����� �� ����� �����
    if (depth == key.size()) {
        // ���� ���� ������ �� ����� �����
        // ������� ������� �����
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� ����� ��� ����������, 
    // ��� ��� ��� � ������, ���������� �������� ��� �������
    // ���������������� �������
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // ���� � ����� ��� ��������� �����
    // (������ ������ ���� ��� �������� �������),
    // � �� �� ������������� ������ ������.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // ���������� ����� ������
    return root;
}

std::vector<std::string> findWords(TrieNode* root, int ch)
{
    char c = 0;
    std::vector<std::string> words;
    std::string word;
    word.push_back(ch);
    root = root->children[ch - 'a'];
    TrieNode* curr = root;
    bool again = false;

    int i = 0;
    while (i < ALPHABET_SIZE)
    {
        if (curr != nullptr && !curr->isEndOfWord)
        {
            while (curr->children[i])
            {
                c = 'a' + i;
                //std::cout << std::string(1, c);
                word.push_back(c);
                curr = curr->children[i];
                again = true;
                break;
                //findWords(root, word, words_);
            }
            if (again)
            {
                i = 0;
            }

            if (!again)
            {
                i++;
                continue;
            }
            
            again = false;
        }
        else {
            std::cout << word << std::endl;
            words.push_back(word);
            word = "";
            curr = root;
            continue;
        }
    }
    return words;

}
