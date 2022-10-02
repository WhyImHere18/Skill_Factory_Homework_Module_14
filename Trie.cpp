#include "Trie.h"

// Возвращает новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память под новый узел
    TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым указателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе, если ключ явлется префиксом узла дерева, 
// помечает в качестве листового т.е. конец слова
void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение относительно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возвращает true если ключ есть в дереве, иначе false
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

// Возвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, std::string key, int depth = 0)
{
    // Если дерево пустое
    if (!root)
        return nullptr;
    // Если дошли до конца ключа
    if (depth == key.size()) {
        // Этот узел больше не конец слова
        // поэтому снимаем метку
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        // Если ключ не является префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Пока не дошли до конца ключа или определили, 
    // что его нет в дереве, рекурсивно вызываем для ребенка
    // соответствующего символа
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    // возвращаем новый корень
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
