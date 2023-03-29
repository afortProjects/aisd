#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

#define AMOUNT_OF_BLOCKS_IN_BLOCK_LIST 8

struct BlockListNode;
struct SectionNode;
struct SelectorListNode;
struct AttributeListNode;
template<typename T> class DoubleLinkedList;



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

        bool operator==(const char* arr) {
            return strcmp(buffer, arr) == 0;
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
            newString.buffer[this->size + 1] = '\0';

            if (buffer != nullptr)
                delete[] buffer;
        
            this->size = newString.size;
            this->buffer = new char[this->size + 1];
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

            if (buffer != nullptr)
                delete[] buffer;

            this->size = newString.size;
            this->buffer = new char[newString.size + 1];
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
        if (amountOfBlocks == 0) {
            headNode = nextBlockListNode;
            headNode->next = NULL;
            headNode->prev = NULL;
            amountOfBlocks++;

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

void getCSSInput(DoubleLinkedList<BlockListNode>& blockList) {
    char character;
    myString emptyStringToClear("");
    myString selectorInput = { "" };
    myString attributeInput = { "" };
    myString input = { "" };
    bool wasNewSectionDetected = false;
    while (cin >> character) {
        input += character;
        if (character == '{') {
            wasNewSectionDetected = true;
        }
        else if (character == '}') {
            BlockListNode* currentBlock = blockList.getLastNode();
            SectionNode currentSection = currentBlock->sections[currentBlock->currentAmountOfSections];
            DoubleLinkedList<SelectorListNode>* selectorList = new DoubleLinkedList<SelectorListNode>;
            DoubleLinkedList<AttributeListNode>* attributeList = new DoubleLinkedList<AttributeListNode>;
            myString temp("");
            myString emptyString = { "" };
            int counter = 0;

            if (currentBlock->currentAmountOfSections == 8) {
                BlockListNode* newBlockListNode = new BlockListNode;
                blockList.addNewBlockToList(newBlockListNode);
                currentBlock = blockList.getLastNode();
            }

            for (int i = 0; i < selectorInput.length(); i++) {
                //todo: add handling for example + in css
                if (selectorInput[i] == ',' || (i == selectorInput.length() - 1 && temp != emptyString)) {
                    if (selectorInput.length() - 1 == i) temp += selectorInput[i];
                    SelectorListNode* newNode = new SelectorListNode;
                    newNode->next = NULL;
                    newNode->prev = NULL;
                    newNode->name = temp;
                    selectorList->addNewBlockToList(newNode);
                    temp = emptyStringToClear;
                }
                else {
                    temp += selectorInput[i];
                }
            }
            temp = "";

            for (int i = 0; i < attributeInput.length(); i++) {
                //todo: add handling for example + in css
                if (attributeInput[i] == ';' || (i == attributeInput.length() - 1 && temp != emptyString)) {
                    if (i == attributeInput.length() - 1 && attributeInput[i] != ';') temp += attributeInput[i];
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
                            if (attributeInput[j] != ';')
                                isNameInputFinished == false ? name += attributeInput[j] : value += attributeInput[j];

                        }
                    }
                    counter = i;

                    newNode->name = name;
                    newNode->value = value;

                    attributeList->addNewBlockToList(newNode);
                    temp = "";

                }
                else {
                    temp += attributeInput[i];
                }
            }
            input = "";
            currentSection.attributeList = attributeList;
            currentSection.selectorList = selectorList;
            currentBlock->sections[currentBlock->currentAmountOfSections] = currentSection;
            currentBlock->currentAmountOfSections += 1;
            wasNewSectionDetected = false;
            selectorInput = "";
            attributeInput = "";
        }
        if (character != '}' && character != '{') {
            wasNewSectionDetected == false ? selectorInput += character : attributeInput += character;
        }
        if(input == "????") {
            break;
        }
    }
    //printOutSelectorsAndAttributes(&blockList);
    //printOutBlockList(&blockList);
}

myString printOutAmmountOfSections(DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* temp = blockList.headNode;
    int counter = 0;
    if (temp != NULL) {
        while (temp != NULL) {
            counter += temp->currentAmountOfSections;
            temp = temp->next;
        }
    }
    char counterInChar = counter + '0';
    myString returnValue = { "? == " };
    returnValue += counterInChar;
    return returnValue;
}

bool checkIfThereAreTwoCommasInInput(myString str) {
    int counter = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',') counter++;
    }
    return counter == 2;
}

myString printOutAmountOfSelectorsOfSection(int index, DoubleLinkedList<BlockListNode>& blockList) {
    SectionNode desiredSection = blockList.headNode->sections[index];
    SelectorListNode* temp = desiredSection.selectorList->headNode;
    int counter = 0;

    if (temp != NULL) {
        while (temp != NULL) {
             counter++;
            temp = temp->next;
        }
    }
    char indexInChar = (index+1) + '0';
    char counterInChar = counter + '0';
    if (counter != 0) {
        myString returnValue = { "" };
        returnValue += indexInChar;
        returnValue += { ",S,? == " };
        returnValue += counterInChar;
        return returnValue;
    }
    return myString { "" };
}

myString printOutAmountOfAttributesOfSection(int index, DoubleLinkedList<BlockListNode>& blockList) {
    SectionNode desiredSection = blockList.headNode->sections[index];
    AttributeListNode* temp = desiredSection.attributeList->headNode;
    int counter = 0;
    myString emptyString = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
            counter++;
            temp = temp->next;
        }
    }
    char indexInChar = (index + 1) + '0';
    char counterInChar = counter + '0';
    if (counter != 0) {
        myString returnValue = { "" };
        returnValue += indexInChar;
        returnValue += { ",A,? == " };
        returnValue += counterInChar;
        return returnValue;
    }
    return myString{ "" };
}


myString printOutNSelectorOfSection(int selectorIndex, int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    SectionNode desiredSection = blockList.headNode->sections[sectionIndex];
    SelectorListNode* temp = desiredSection.selectorList->headNode;
    int counter = 0;
    if (temp != NULL) {
        while (temp != NULL && counter != selectorIndex) {
            temp = temp->next;
            counter++;
        }
    }
    char sectionIndexInChar = (sectionIndex + 1) + '0';
    char selectorIndexInChar = (selectorIndex + 1)+ '0';
    if (counter == selectorIndex) {
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",S," };
        returnValue += selectorIndexInChar;
        returnValue += {" == "};
        returnValue += temp->name;
        return returnValue;
    }
    return myString{ "" };
}

int main() {
    DoubleLinkedList<BlockListNode> blockList;
    char character;
    myString input = { "" };
    myString output = { "" };

    getCSSInput(blockList);
    while (cin >> character) {
        input += character;
        if (input == "????") cout << "Sekcja komend" << "\n";
        else if (input == "****") {
            getCSSInput(blockList);
            input = "";
        }
        else if (input == "?") {
            output += printOutAmmountOfSections(blockList);
            output += "\n";
            input = "";
        }
        else if (checkIfThereAreTwoCommasInInput(input) && input.length() == 5) {
            int sectionIndex = input[0] - '0' - 1;
            if (input[2] == 'S') {
                if (isdigit(input[0]) && isdigit(input[4])) {
                    int selectorIndex = input[4] - '0' - 1;
                    output += printOutNSelectorOfSection(selectorIndex, sectionIndex, blockList);
                }
                else {
                    output += printOutAmountOfSelectorsOfSection(sectionIndex, blockList);
                }
            }
            if (input[2] == 'A') {
                output += printOutAmountOfAttributesOfSection(sectionIndex, blockList);
            }
            output += "\n";
            input = "";
        }
    }
    cout << output;
    return 0;
}