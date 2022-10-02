// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include "Trie.h"

int main()
{
    // Define root node
    TrieNode* root = getNewNode();

    // Fill tree
    insert(root, "cat");
    insert(root, "call");
    insert(root, "cult");
    insert(root, "run");
    insert(root, "rule");

    // Enter first letter
    std::cout << "Enter a letter: ";
    char c = 0;
    std::cin >> c;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Check if first letter exists in the vocabular defined in the tree (root node has children with this prefix)
    // a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

    while (!root->children[c - 'a'])
    {
        std::cout << "The vocabulary is poor and does not contain any word starting this letter. Try another letter..." << std::endl;
        std::cout << "Enter a letter: ";
        std::cin >> c;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // There is root's child with entered prefix. Therefore, set this child as root node and try to find all words in the tree containing this prefix.
    //root = root->children[c - 'a'];

    std::string word = std::string(1, c);
    std::vector<std::string> words;

    while (!root->isEndOfWord)
    {
        int ch = 0;
        words = findWords(root, c);
        for (std::string i : words)
        {
            std::cout << "Do you mean " << i << "? (Press 'right arrow' to confirm, press 'down arrow' to refuse)";
            ch = std::getchar();
            while (ch != 77 && ch != 80)
            {
                switch (ch)
                {
                case 77:
                    std::cout << i << std::endl;
                    break;
                case 80:
                    break;
                default:
                    std::cout << "Wrong operation. Press 'right arrow' to confirm, press 'down arrow' to refuse:";
                    break;
                }
            }
        }
        std::cout << "Enter next letter: ";
        std::cin >> c;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        word.push_back(c);
        root = root->children[c - 'a'];
    }

    //insert(root, "c");
    //insert(root, "r");

    //insert(root->children[2], "a");
    //insert(root->children[2], "u");
    //insert(root->children[17], "u");

    //insert(root->children[2]->children[0], "t");
    //insert(root->children[2]->children[20], "l");

    //insert(root->children[2]->children[20]->children[11], "t");

    //insert(root->children[17]->children[20], "n");
    //insert(root->children[17]->children[20], "t");

    //insert(root->children[2]->children[0], "l");
    //insert(root->children[2]->children[0]->children[11], "l");

    return 0;
}