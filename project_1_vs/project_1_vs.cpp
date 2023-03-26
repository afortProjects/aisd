#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

#define AMOUNT_OF_BLOCKS_IN_BLOCK_LIST 8

struct BlockListNode;
struct SectionNode;
struct SelectorListNode;
struct AttributeListNode;
class BlockList;
class SelectorList;
class AttributeList;

struct BlockListNode {
    BlockListNode* prev = NULL;
    BlockListNode* next = NULL;
    SectionNode* blocks[AMOUNT_OF_BLOCKS_IN_BLOCK_LIST];
    int currentAmountOfBlocks = 0;
};

struct SectionNode {
    SelectorList* selectorList;
    AttributeList* attributeList;
    int counter;
};

struct SelectorListNode {
    SelectorListNode* prev;
    SelectorListNode* next;
    char* name;
};


struct AttributeListNode {
    AttributeListNode* prev;
    AttributeListNode* next;
    char* name;
    char* value;
};



class BlockList {
public:
    struct BlockListNode* headNode;
    struct BlockListNode* tailNode;
    int amountOfBlocks = 0;
public:
    BlockList(struct BlockListNode* head) {
        headNode = head;
    }

    int length() {
        return amountOfBlocks;
    }

    void addNewBlockToList(BlockListNode* nextBlockListNode) {
        struct BlockListNode* last = headNode;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = nextBlockListNode;
        nextBlockListNode->prev = last;
        amountOfBlocks++;
    }

    friend ostream& operator<<(ostream& cout, BlockList list) {
        BlockListNode* temp = list.headNode;
        if (temp != NULL) {
            cout << "The list contains: ";
            while (temp != NULL) {
                cout << temp->currentAmountOfBlocks << " ";
                temp = temp->next;
            }
            cout << endl;
        }
        else {
            cout << "The list is empty.\n";
        
        }
        return cout;
    }
};

class AttributeList {
public:
    AttributeListNode* headNode;
public:
    AttributeList() {
        headNode = NULL;
    }
};

class SelectorList {
public:
    SelectorListNode* headNode;
public:
    SelectorList() {
        headNode = NULL;
    }
};


class myString
{
private:
    char* buffer = nullptr;
    unsigned int size = 0;
public:
    myString() : buffer(nullptr), size(0) {};

    myString(const char* newBuffer) {
        size = strlen(newBuffer);
        buffer = new char[size + 1];
        strcpy(buffer, newBuffer);
    };

    myString(const myString& stringObject)
    {
        size = stringObject.size;
        buffer = new char[size + 1];
        strcpy(buffer, stringObject.buffer);
    }

    myString(myString&& stringObject)
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
    }

    myString& operator=(const myString& stringObject)
    {
        size = stringObject.size;
        buffer = new char[size + 1];
        strcpy(buffer, stringObject.buffer);
        return *this;
    }

    myString& operator=(myString&& stringObject)
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
        return *this;
    }

    myString operator+(const char& character)
    {
        myString newString;
        newString.size = this->size + 1;
        newString.buffer = new char[newString.size + 1];

        strcpy(newString.buffer, this->buffer);
        newString.buffer[this->size] = character;
        newString.buffer[this->size + 1] = '\0';

        return newString;
    }

    myString operator+(const myString& stringToConcatenate)
    {
        myString newString;
        newString.size = this->size + stringToConcatenate.size;
        newString.buffer = new char[newString.size + 1];
        strcpy(newString.buffer, this->buffer);
        strcpy(newString.buffer + this->size, stringToConcatenate.buffer);
        return newString;
    }

    myString operator+=(const char& character)
    {
        myString newString;
        newString.size = this->size + 1;
        newString.buffer = new char[newString.size + 1];

        strcpy(newString.buffer, this->buffer);
        newString.buffer[this->size] = character;
        newString.buffer[this->size + 1] = '\0';

        this->size = newString.size;
        strcpy(this->buffer, newString.buffer);
    }

    myString operator+=(const myString& stringToConcatenate)
    {
        myString newString;
        newString.size = this->size + stringToConcatenate.size;
        newString.buffer = new char[newString.size + 1];
        strcpy(newString.buffer, this->buffer);
        strcpy(newString.buffer + this->size, stringToConcatenate.buffer);

        this->size = newString.size;
        strcpy(this->buffer, newString.buffer);
    }

    char operator[](const int index) {
        return buffer[index];
    }

    unsigned int length() {
        return size;
    }
    const char* str() const {
        return buffer;
    }
    ~myString() {
        if (buffer != nullptr) {
            delete[] buffer;
        }
        size = 0;
    }

    friend ostream& operator<<(std::ostream& cout, const myString& obj) {
        cout << obj.str() << endl;
        return cout;
    }

};

int main() {
    char character;
    myString input = { "" };

    //Create new Block List
    //BlockListNode newBlockListNode;
    //newBlockListNode.currentAmountOfBlocks = 3;
    //BlockList blockList(&newBlockListNode);

    //BlockListNode newBlockListNode2;
    //newBlockListNode2.currentAmountOfBlocks = 5;
    //blockList.addNewBlockToList(&newBlockListNode2);
    //cout << blockList;
    //BlockListNode newBlockListNode2;
    //newBlockListNode2.currentAmountOfBlocks = 51;
    //blockList.addNewBlockToList(&newBlockListNode2);
    //BlockListNode newBlockListNode3;
    //newBlockListNode3.currentAmountOfBlocks = 522;
    //blockList.addNewBlockToList(&newBlockListNode3);

    // blockList.printListOfBlocks();
    // BlockListNode* temp = blockList.headNode;
    //         if(temp != NULL) {
    //             cout<<"The list contains: ";
    //             while(temp != NULL) {
    //                 cout<<temp->currentAmountOfBlocks<<" ";
    //                 temp = temp->next;
    //             }
    //             cout<<endl;
    //         } else {
    //             cout<<"The list is empty.\n";
    //         }

    //Initialize blockList
    BlockListNode firstBlockListNode;
    BlockList blockList(&firstBlockListNode);
     while (cin>>character) {
         if(character == '{') {
              //Input contains selectors
              if(blockList.length() == 8) {
                  //We need to create new block
                  BlockListNode newBlockListNode;
                  blockList.addNewBlockToList(&newBlockListNode);
              }

         }
         input += character;

     }
    return 0;
}