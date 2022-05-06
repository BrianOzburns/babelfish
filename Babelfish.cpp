#include <iostream>
using namespace std;

const size_t DICT_SIZE = 10067;

class dict{
    private:

        class dictEntry{
            public:
                // word[0] is the translation, word[1] is the foreign word
                // std::pair<std::string, std::string> word;
                std::string translated_word;
                std::string foreign_word;
                // dictEntry* next_word = nullptr;
                std::shared_ptr<dictEntry> next_entry;

                // dictEntry(std::string x, std::string y){ word = std::make_pair(x, y); next_entry = nullptr; }
                // dictEntry(){ word = std::make_pair("", ""); next_entry = nullptr; }
                dictEntry(){ translated_word = ""; foreign_word = ""; next_entry = nullptr; }
        };

        std::shared_ptr<dictEntry> dictionary[DICT_SIZE] = {nullptr};

        int findHash(std::string s);

    public:
        void addWord(std::string translation, std::string to_add);
        std::string getTranslation(std::string s); 
        void print_dict();
        std::string lookUp(std::string s);
        // void print_all();
        // ~dict();
};

int dict::findHash(std:: string s){
    int hash = 0;
    for(size_t i = 0; i < s.size(); i++){
        hash += s[i] * s[i] * i;
    }
    return hash%DICT_SIZE;
}

void dict::addWord(std:: string translation, std::string to_add){
    int hash = findHash(to_add);
    
    // std::pair<std::string, std::string> entry = std::make_pair(translation, to_add);
    // std::cout << entry.first << " " << entry.second << std::endl;
    std::shared_ptr<dictEntry> new_entry = std::make_shared<dictEntry>();
    // dictEntry* new_entry = new dictEntry;
    // std::cout << new_entry->word.first << std::endl;
    new_entry->next_entry = nullptr;
    new_entry->translated_word = translation;
    new_entry->foreign_word = to_add;
    
    if (dictionary[hash] == nullptr){
        dictionary[hash] = new_entry;
    }
    else{
        // dictEntry* temp = dictionary[hash];
        std::shared_ptr<dictEntry> temp = dictionary[hash];
        while(temp){
            if(temp->foreign_word == new_entry->foreign_word){
                temp = nullptr;
                break;
            }
            temp = temp->next_entry;
        }
        if(temp != nullptr){
            temp->next_entry = new_entry;
        }
    }
}

void dict::print_dict(){
    for(size_t i = 0; i < DICT_SIZE; i++){
        if(dictionary[i]){
            std::shared_ptr<dictEntry> temp = dictionary[i];
            while(temp){
                std::cout << dictionary[i]->translated_word << " " << dictionary[i]->foreign_word << std::endl;
                temp = temp->next_entry;
            }
        }
    }
}

std::string dict::lookUp(std::string s){
    int hash = findHash(s);
    std::shared_ptr<dictEntry> temp = dictionary[hash];
    while(temp){
        if (temp->foreign_word == s){
            return temp->translated_word;
        }
        temp = temp->next_entry;
    }
    return "eh";
}
/**
void dict::print_all(){
    for(size_t i = 0; i < DICT_SIZE; i++){
        if(dictionary[i] == nullptr){
            std::cout << "nullptr ";
        }
    }
}
**/
/**
dict::~dict(){
    for(size_t i = 0; i < DICT_SIZE; i++){
        if (sizeof(dictionary[i]) == 0){
            continue;
        }
        dictEntry* to_delete = dictionary[i];
        while(to_delete->next_word != nullptr){
            dictEntry* next = to_delete->next_word;
            delete to_delete;
        }
    }
}
**/

int main(){
    dict d;
    std::string toAdd = "";
    std::string translation = "";
    std::string line;
    
    while(std::getline(std::cin, line) && line.size() != 0){
        std::string translation = line.substr(0,line.find(" "));
        std::string to_add = line.substr(line.find(" ")+1);
        
        d.addWord(translation, to_add);
    }
    // d.print_dict();
    while(std::getline(std::cin, line) && line.size() != 0){
        std::string w = d.lookUp(line);
        std::cout << w << std::endl;
    }
    
    return 0;
}