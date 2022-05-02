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
                dictEntry* next_entry;

                // dictEntry(std::string x, std::string y){ word = std::make_pair(x, y); next_entry = nullptr; }
                // dictEntry(){ word = std::make_pair("", ""); next_entry = nullptr; }
                dictEntry(){ translated_word = ""; foreign_word = ""; next_entry = nullptr; }
        };

        dictEntry* dictionary[DICT_SIZE] = {nullptr};

        int findHash(std::string s);

    public:
        void addWord(std::string translation, std::string to_add);
        std::string getTranslation(std::string s); 
        void print_dict();
        std::string lookUp(std::string s);
        void getInput();
        ~dict();
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
    dictEntry* new_entry = new dictEntry;
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
        dictEntry* temp = dictionary[hash];
        // bool word_exists_already = false;
        if(temp->foreign_word == new_entry->foreign_word){
            // word_exists_already = true;
            return;
        }
        while(temp->next_entry){
            if(temp->next_entry->foreign_word == new_entry->foreign_word){
                // word_exists_already = true;
                return;
            }
            temp = temp->next_entry;
        }
        // if(!word_exists_already){
            // temp->next_entry = new_entry;
        // }
        temp->next_entry = new_entry;
    }
}

void dict::print_dict(){
    for(size_t i = 0; i < DICT_SIZE; i++){
        if(dictionary[i]){
            dictEntry* temp = dictionary[i];
            while(temp){
                std::cout << dictionary[i]->translated_word << " " << dictionary[i]->foreign_word << std::endl;
                temp = temp->next_entry;
            }
        }
    }
}

std::string dict::lookUp(std::string s){
    int hash = findHash(s);
    dictEntry* temp = dictionary[hash];
    while(temp){
        if (temp->foreign_word == s){
            return temp->translated_word;
        }
        temp = temp->next_entry;
    }
    return "eh";
}

void dict::getInput(){
    std::string line;
    std::string l;
    while(std::getline(std::cin, line) && line.size() != 0){
        std::string translation = line.substr(0,line.find(" "));
        std::string to_add = line.substr(line.find(" ")+1);
        
        this->addWord(translation, to_add);
    }
    line = "";
    while(std::getline(std::cin, l) && l.size() != 0){
        line += l + ' ';
    }
    std::string word = "";
    std::string w = "";
    size_t i = 0;

    while(line[i] != ' ' && i < line.size()){
        word += line[i];
        i += 1;
    }
    w = this->lookUp(word);
    std::cout << w;
    i += 1;
    while(i < line.size()){
        while(line[i] != ' '){
            word += line[i];
            i += 1;
        }
        i += 1;
        w = this->lookUp(word);
        std::cout << std::endl << w;
        word = "";
    }

    /**
    while(i < line.size()){
        while(line[i] != ' '){
            word += line[i];
            i += 1;
        }
        i += 1;
        std::string w = this->lookUp(word);
        std::cout << w << std::endl;
        word = "";
    }
    **/
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

dict::~dict(){
    for(size_t i = 0; i < DICT_SIZE; i++){
        dictEntry* to_delete = dictionary[i];
        while(to_delete){
            dictEntry* next = to_delete->next_entry;
            delete to_delete;
            to_delete = next;
        }
    }
}

int main(){
    dict d;
    
    d.getInput();
    /**
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
    **/
    return 0;
}
