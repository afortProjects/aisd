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
        strcpy(newString.buffer + this->size, stringToConcatenate.buffer);
        return newString;
    }

    void operator+=(const char& character)
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

    void operator+=(const myString& stringToConcatenate)
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

    friend ostream& operator<<(std::ostream& cout, const myString& obj) {
        cout << obj.str() << endl;
        return cout;
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
    if (temp != NULL) {
        cout << "The list contains: ";
        while (temp != NULL) {
            cout << temp->name << ":" << temp->value;
            temp = temp->next;
        }
        cout << endl;
    }
    else {
        cout << "The list is empty.\n";

    }
}

template <class T> void printSelectorList(T* selectorList) {
    SelectorListNode* temp = selectorList->headNode;
    if (temp != NULL) {
        cout << "The list contains: ";
        while (temp != NULL) {
            cout << temp->name;
            temp = temp->next;
        }
        cout << endl;
    }
    else {
        cout << "The list is empty.\n";

    }
}

template<class T> void printOutSelectorsAndAttributes(T* blockList) {
    BlockListNode* temp = blockList->headNode;
    if (temp != NULL) {
        cout << "The list contains: ";
        while (temp != NULL) {
            for (int i = 0; i < temp->currentAmountOfSections; i++) {
                if (temp->sections[i].attributeList->headNode != nullptr && temp->sections[i].selectorList->headNode != nullptr) {
                    printSelectorList(temp->sections[i].selectorList);
                    printAttributeList(temp->sections[i].attributeList);

                }
            }
            temp = temp->next;
        }
        cout << endl;
    }
    else {
        cout << "The list is empty.\n";

    }
}

template <class T> void setHeadNodesToNullValues(T* list) {
    list->headNode = NULL;
}

int main() {
    char character;
    myString selectorInput = { "" };
    myString attributeInput = { "" };
    bool wasNewSectionDetected = false;
    //Initialize blockList
    DoubleLinkedList<BlockListNode> blockList;
    while (cin >> character) {
        if (character == '{') {
            cout << "Wczytano {" << endl;
            wasNewSectionDetected = true;
        }
        else if (character == '}') {
            cout << "Wczytano }" << endl;
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
            setHeadNodesToNullValues(selectorList);
            
            cout << selectorList->wasHeadNodeSet << endl;
            myString temp = "";
            for (int i = 0; i < selectorInput.length(); i++) {
                //todo: add handling for example + in css
                if (selectorInput[i] == ',') {
                    SelectorListNode* newNode = new SelectorListNode;
                    newNode->next = NULL;
                    newNode->prev = NULL;

                    newNode->name = temp;
                    selectorList->addNewBlockToList(newNode);
                    cout << temp << endl;
                    temp = "";
                }
                else {
                    temp = temp + selectorInput[i];
                }
            }
            myString emptyString = { "" };
            cout << "s" << selectorInput;
            cout << "a" << attributeInput;
            if (temp != emptyString) {
                SelectorListNode* newNode = new SelectorListNode;
                newNode->next = NULL;
                newNode->prev = NULL;
                newNode->name = temp;
                selectorList->addNewBlockToList(newNode);
                cout << "qwe" << temp << endl;
            }
            temp = "";
            DoubleLinkedList<AttributeListNode>* attributeList = new DoubleLinkedList<AttributeListNode>;
            setHeadNodesToNullValues(attributeList);
            int counter = 0;
            for (int i = 0; i < attributeInput.length(); i++) {
                //todo: add handling for example + in css
                if (attributeInput[i] == ';') {
                    AttributeListNode* newNode = new AttributeListNode;
                    newNode->next = NULL;
                    newNode->prev = NULL;
                    myString name = "";
                    myString value = "";
                    bool isNameInputFinished = false;
                    for (int j = counter; j < i; j++) {
                        if (attributeInput[j] == ':') {
                            isNameInputFinished = true;
                            counter = j;
                        }
                        if (attributeInput[j] != ':') {
                            isNameInputFinished == false ? name += attributeInput[j] : value += attributeInput[j];

                        }
                    }

                    newNode->name = name;
                    newNode->value = value;

                    attributeList->addNewBlockToList(newNode);
                        temp = "";
                }
                else {
                    temp += attributeInput[i];
                }
            }
            if (temp != emptyString) {
                AttributeListNode* newNode = new AttributeListNode;
                newNode->next = NULL;
                newNode->prev = NULL;
                myString name = "";
                myString value = "";
                bool isNameInputFinished = false;
                for (int j = 0; j < temp.length(); j++) {
                    if (attributeInput[j] == ':') {
                        isNameInputFinished = true;
                    }
                    if (attributeInput[j] != ':') {
                        isNameInputFinished == false ? name += attributeInput[j] : value += attributeInput[j];

                    }
                }
                newNode->name = name;
                newNode->value = value;
                attributeList->addNewBlockToList(newNode);
                cout << "t2" << temp << endl;
            }
            currentSection.attributeList = attributeList;
            currentSection.selectorList = selectorList;
            currentBlock->sections[currentBlock->currentAmountOfSections] = currentSection;
            currentBlock->currentAmountOfSections++;
            wasNewSectionDetected = false;
            selectorInput = "";
            attributeInput = "";
        }
        if (character != '}' && character != '{') {
            wasNewSectionDetected == false ? selectorInput += character : attributeInput += character;
        }   
        //printAttributeList(blockList.getLastNode()->sections[0].attributeList);
        //printOutBlockList(&blockList);
    }
     printOutSelectorsAndAttributes(&blockList);
    //cout << blockList.getLastNode()->sections[0].attributeList->/*headNode*/;

    return 0;
}