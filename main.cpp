#include <iostream>
#include <sstream>
#include <fstream>
#include "tree.h"
using namespace std;
void PrintMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Ввод новой строки для записи в дерево\n";
    std::cout << "2. Ввод строки для удаления из дерева\n";
    std::cout << "3. Поиск строки в дереве\n";
    std::cout << "4. Очистить дерево\n";
    std::cout << "5. Записать строки из input.txt в дерево\n";
    std::cout << "6. Вывести дерево на экран\n";
    std::cout << "7. Выход\n";
}

int main() {
    std::string s = "abc";
    RBTree<std::string> *tree = new RBTree<std::string>(s);

    while (true) {
        PrintMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string str;
                std::cout << "Введите строку для записи в дерево: ";
                std::cin.ignore(); // Очистка буфера
                std::getline(std::cin, str); // Считываем всю строку
                std::istringstream iss(str);
                std::vector<std::string> wordsVector;
                // Разделяем строку и добавляем слова в вектор
                std::string word;
                while (iss >> word) {
                    if(word[word.size()-1]=='.'||
                            word[word.size()-1]==','||
                            word[word.size()-1]=='!'||
                            word[word.size()-1]=='?'||
                            word[word.size()-1]==':'||
                            word[word.size()-1]==';'){
                        word.erase(word.end()-1);
                    }
                    wordsVector.push_back(word);
                }
                for(auto e: wordsVector){
                    tree->Insert(e);
                }
                cout<<"Слова из строки успешно добавлены. \n";
                break;
            }
            case 2: {
                std::string str;
                std::cout << "Введите строку для удаления из дерева: ";
                std::cin.ignore(); // Очистка буфера
                std::getline(std::cin, str); // Считываем всю строку
                if(tree->Remove(str))
                    cout<<"Слово успешно удалено \n"<<endl;
                else
                    cout<<"Слово не найдено \n"<<endl;
                break;
            }
            case 3: {
                std::string str;
                std::cout << "Введите строку для поиска: ";
                std::cin.ignore(); // Очистка буфера
                std::getline(std::cin, str); // Считываем всю строку
                if (tree->Search(str)) {
                    std::cout << "Строка найдена в дереве.\n";
                } else {
                    std::cout << "Строка не найдена в дереве.\n";
                }
                break;
            }
            case 4: {
                tree->Clear();
                std::cout << "Дерево очищено.\n";
                break;
            }
            case 5: {
                std::ifstream inputFile("input.txt");
                if (inputFile.is_open()) {
                    std::string line;
                    while (std::getline(inputFile, line)) {
                        std::istringstream iss(line);
                        std::vector<std::string> wordsVector;
                        std::string word;
                        while (iss >> word) {
                            if(word[word.size()-1]=='.'||
                               word[word.size()-1]==','||
                               word[word.size()-1]=='!'||
                               word[word.size()-1]=='?'||
                               word[word.size()-1]==':'||
                               word[word.size()-1]==';'){
                                word.erase(word.end()-1);
                            }
                            wordsVector.push_back(word);
                        }
                        for (const auto &e : wordsVector) {
                            tree->Insert(e);
                        }
                    }
                    inputFile.close();
                    std::cout << "Строки из input.txt добавлены в дерево.\n";
                } else {
                    std::cout << "Не удалось открыть файл input.txt.\n";
                }
                break;
            }
            case 6: {
                tree->PrintAll(tree->Root());
                break;
            }
            case 7: {
                delete tree;
                std::cout << "Программа завершена.\n";
                return 0;
            }
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }

    return 0;
}
