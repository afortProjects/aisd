#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

#define AMOUNT_OF_BLOCKS_IN_BLOCK_LIST 8

struct BlockListNode;
struct SectionNode;
struct SelectorListNode;
struct AttributeListNode;
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

    myString(myString&& stringObject) noexcept
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
        stringObject.size = 0;
    }


    myString& operator=(const myString& stringObject)
    {
        size = stringObject.size;
        buffer = new char[size + 1];
        strcpy(buffer, stringObject.buffer);
        return *this;
    }

    myString& operator=(myString&& stringObject) noexcept
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
        stringObject.size = 0;
        return *this;
    }

    bool operator!=(myString& stringObject2) {
        return strcmp(buffer, stringObject2.buffer);
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
        strcat(newString.buffer, stringToConcatenate.buffer);
        return newString;
    }

    myString& operator+=(const char& character)
    {
        myString newString;
        newString.size = this->size + 1;
        newString.buffer = new char[newString.size + 1];

        strcpy(newString.buffer, this->buffer);
        newString.buffer[this->size] = character;

        this->size = newString.size;

        strcpy(this->buffer, newString.buffer);
        return *this;
    }

    myString& operator+=(const myString& stringToConcatenate)
    {
        myString newString;
        newString.size = this->size + stringToConcatenate.size;
        newString.buffer = new char[newString.size + 1];
        strcpy(newString.buffer, this->buffer);
        strcat(newString.buffer, stringToConcatenate.buffer);

        this->size = newString.size;
        strcpy(this->buffer, newString.buffer);
        return *this;

    }

    char operator[](const int index) {
        return this->buffer[index];
    }

    unsigned int length() {
        return this->size;
    }
    const char* str() const {
        return this->buffer;
    }

    friend ostream& operator<<(std::ostream& cout, const myString& obj) {
        cout << obj.str() << endl;
        return cout;
    }

    ~myString() {
        if (buffer != nullptr) {
            delete [] buffer;
            size = 0;
        }
    }
};

template<typename T> class DoubleLinkedList;

struct SectionNode {
    DoubleLinkedList<SelectorListNode>* selectorList = NULL;
    DoubleLinkedList<AttributeListNode>* attributeList = NULL;
    int counter = 0;
};

struct BlockListNode {
    BlockListNode* prev = NULL;
    BlockListNode* next = NULL;
    SectionNode* sections = new SectionNode[AMOUNT_OF_BLOCKS_IN_BLOCK_LIST];
    int currentAmountOfSections = 0;
};


struct SelectorListNode {
    SelectorListNode* prev = nullptr;
    SelectorListNode* next = nullptr;
    myString name = { "" };
};


struct AttributeListNode {
    AttributeListNode* prev;
    AttributeListNode* next;
    myString name = { "" };
    myString value = { "" };
};



template<typename T> class DoubleLinkedList {
public:
    T* headNode = nullptr;
    int amountOfBlocks = 0;
    bool wasHeadNodeSet = false;
public:
    //TODO: Write destructor
    DoubleLinkedList() {
        T* head = new T;
        head->prev = NULL;
        head->next = NULL;
        wasHeadNodeSet = false;
        headNode = head;
    }


    int length() {
        return amountOfBlocks;
    }

    void addNewBlockToList(T* nextBlockListNode) {
        //Checking if first place in list is available
        if (!wasHeadNodeSet) {
            nextBlockListNode->next = NULL;
            nextBlockListNode->prev = NULL;

            headNode = nextBlockListNode;
            wasHeadNodeSet = true;
        }
        else {
            T* last = headNode;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = nextBlockListNode;
            nextBlockListNode->prev = last;
            amountOfBlocks++;
        }

    }

    T* getLastNode() {
        T* last = headNode;
        while (last->next != NULL) {
            last = last->next;
        }
        return last;
    }

 

    friend ostream& operator<<(ostream& cout, T list) {
        T* temp = list.headNode;
        if (temp != NULL) {
            cout << "The list contains: ";
            while (temp != NULL) {
                cout << temp->currentAmountOfSections << " ";
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


template <class T> void printOutBlockList(T* blockList) {
    BlockListNode* temp = blockList->headNode;
    if (temp != NULL) {
        cout << "The list contains: ";
        while (temp != NULL) {
            cout << temp->currentAmountOfSections << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    else {
        cout << "The list is empty.\n";

    }
}

template <class T> void printAttributeList(T* attributeList) {
    AttributeListNode* temp = attributeList->headNode;
    myString output = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
                output = output + temp->name;
                output = output + ":";
                output = output + temp->value;
                output = output + " ";
                temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
    cout << "Attributes: " << output << endl;
}

template <class T> void printSelectorList(T* selectorList) {
    SelectorListNode* temp = selectorList->headNode;
    myString output = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
            output = output + temp->name;
            output = output + " ";
            temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
    cout << "Selectors: " << output << endl;
}

template<class T> void printOutSelectorsAndAttributes(T* blockList) {
    BlockListNode* temp = blockList->headNode;
    if (temp != NULL) {
        while (temp != NULL) {
            for (int i = 0; i < temp->currentAmountOfSections; i++) {
                if (temp->sections[i].attributeList->headNode != nullptr && temp->sections[i].selectorList->headNode != nullptr) {
                    printSelectorList(temp->sections[i].selectorList);
                    printAttributeList(temp->sections[i].attributeList);

                }
            }
            temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
}

int main() {
    char character;
    myString emptyStringToClear("");
    myString selectorInput = { "" };
    myString attributeInput = { "" };
    bool wasNewSectionDetected = false;
    DoubleLinkedList<BlockListNode> blockList;
    while (cin >> character) {
        if (character == '{') {
            wasNewSectionDetected = true;
        }
        else if (character == '}') {
            BlockListNode* currentBlock = blockList.getLastNode();
            if (currentBlock->currentAmountOfSections == 8) {
                //We need to create new block
                BlockListNode* newBlockListNode = new BlockListNode;
                blockList.addNewBlockToList(newBlockListNode);
                currentBlock = blockList.getLastNode();
            }
            SectionNode currentSection = currentBlock->sections[currentBlock->currentAmountOfSections];
            //Create new selector, attribute list, and fill it with data
            DoubleLinkedList<SelectorListNode>* selectorList = new DoubleLinkedList<SelectorListNode>;

            myString temp("");
            myString emptyString = { "" };

            for (int i = 0; i < selectorInput.length(); i++) {
                //todo: add handling for example + in css
                if (selectorInput[i] == ',' || (i == selectorInput.length() - 1 && temp != emptyString)) {
                    if (selectorInput.length() - 1 == i) temp = temp + selectorInput[i];
                    SelectorListNode* newNode = new SelectorListNode;
                    newNode->next = NULL;
                    newNode->prev = NULL;
                    newNode->name = temp;
                    selectorList->addNewBlockToList(newNode);
                    temp = emptyStringToClear;
                }
                else {
                    temp = temp + selectorInput[i];
                }
            }
            temp = emptyStringToClear;

            DoubleLinkedList<AttributeListNode>* attributeList = new DoubleLinkedList<AttributeListNode>;
            int counter = 0;
            for (int i = 0; i < attributeInput.length(); i++) {
                //todo: add handling for example + in css
                if (attributeInput[i] == ';' || (i == attributeInput.length() -1 && temp != emptyString)) {
                    if (i == attributeInput.length() - 1 && attributeInput[i] != ';') temp = temp + attributeInput[i];
                    AttributeListNode* newNode = new AttributeListNode;
                    newNode->next = NULL;
                    newNode->prev = NULL;
                    myString name = { "" };
                    myString value = { "" };
                    bool isNameInputFinished = false;
                    for (int j = counter; j < i; j++) {
                        if (attributeInput[j] == ':') {
                            isNameInputFinished = true;
                        }
                        else {
                            if(attributeInput[j] != ';')
                                isNameInputFinished == false ? name = name + attributeInput[j] : value = value + attributeInput[j];

                        }
                    }
                    counter = i;

                    newNode->name = name;
                    newNode->value = value;

                    attributeList->addNewBlockToList(newNode);
                    temp = emptyStringToClear;

                }
                else {
                    temp = temp + attributeInput[i];
                }
            }
            
            currentSection.attributeList = attributeList;
            currentSection.selectorList = selectorList;
            currentBlock->sections[currentBlock->currentAmountOfSections] = currentSection;
            currentBlock->currentAmountOfSections++;
            wasNewSectionDetected = false;
            selectorInput = { "" };
            attributeInput = { "" };
        }
        if (character != '}' && character != '{') {
            wasNewSectionDetected == false ? selectorInput = selectorInput + character : attributeInput = attributeInput + character;
        } 
    }
     printOutSelectorsAndAttributes(&blockList);

    return 0;
}