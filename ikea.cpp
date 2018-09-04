//
// Created by Visitor on 9/1/2018.
//

#include <memory>
#include <sstream>
#include "ikea.h"



/**
 * global variables
 */

std::vector<IkeaItem*> ikeaItems; // <item, quantity>

/**
 * helper functions
 */


/**
 * checks if string is numeric
 * @param str
 * @return
 */
bool isNumericString(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;



}


std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}


// todo - create enum of item names

/**
 * splits a line by colon <field> : <value>
 * @param line
 * @return
 */
std::pair<std::string, std::string> splitLineByColon(std::string line)
{

    std::string param, value;
    std::string::size_type pos = line.find(':');
    if(line.npos != pos)
    {

        param = line.substr(pos + 1);
        value = line.substr(0, pos);
    }
    return std::make_pair(param, value);

    //todo - else illegal line

};


/**
 * check if item exist in current ikeaItems according to catalog number
 * @param catalogNumber
 * @return
 */
IkeaItem* findExistItem(const std::string &catalogNumber)
{

    for (auto &ikeaItem : ikeaItems) {

        if (ikeaItem->getCatalogNumber() == catalogNumber)
        {
            return ikeaItem;
        }

    }
    return nullptr;
}

/**
 * validate exist ikeaItem has the same values as current imported ikea item
 * @param exist
 * @param current
 * @return
 */
//bool validateExist(IkeaItem* exist, std::vector<std::pair<std::string, std::string>> current)
//{
//
//    //first validate mandatory
//    if (exist->getCatalogNumber() != current[0].second || exist->getItemName() != current[1].second || exist->getPrice() != current[3].second)
//    {
//        return false;
//    }
//
//    std::string existType = exist->getItemType();
//
//    if (existType == "FabricItem")
//    {
//
//
//
//    }
//    else if (existType == )
//
//
//
//
//}



IkeaItem* createItem(std::vector<std::pair<std::string, std::string>> currentItem, string currentItemString);

/**
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
void addItem(const std::string fileName)
{
    string currentLine;
    IkeaItem* ikeaItem;
    IkeaItem* existItem;
    std::ifstream  inputFile("/cs/usr/hadar.dotan/Documents/cpp_ex2/items.txt");
    string currentItemString = "";
    bool itemExist = false;

    std::vector<std::pair<std::string, std::string>> currentItem;

    if (inputFile.is_open())
    {

        int lineIndex = 0;
        while(std::getline(inputFile, currentLine))
        {

            if (lineIndex > 7) //too many params
            {

                std::cout << "illegal item fields\n";
                inputFile.close();
                return;
            }

            else if (currentLine == END_OF_ITEM)
            {
                currentItemString += currentLine+"\n";
                //create item object
                if (currentItem.size() < 4)
                {

                    std::cout << "illegal item fields\n";
                    inputFile.close();
                    return;
                }
                ikeaItem = createItem(currentItem, currentItemString);
                if (ikeaItem == nullptr)
                {
                    std::cout << "illegal item fields\n";
                    inputFile.close();
                    return;
                }
                currentItemString = "";
                ikeaItems.push_back(ikeaItem);
                lineIndex = 0;
                currentItem.clear();
            }
            else
            {
                currentItemString += currentLine+"\n";
                std::pair<std::string, std::string> splitLine = splitLineByColon(currentLine);

                // check existance of mandatory fields
                if (lineIndex < MIN_NUM_OF_ITEM_LINES)
                {

                    if (splitLine.second != paramNames[lineIndex])
                    {
                        std::cout << "illegal line param\n";
                        //return to menu
                        inputFile.close();
                        return;

                    }
                    if (lineIndex == 0 )
                    { //check if item exist
                        existItem = findExistItem(splitLine.first);
                        if (existItem != nullptr) //means item exist - update quantity
                        {
                            itemExist = true;
                        }
                    }

                    if (lineIndex == 1 && itemExist)
                    {
                        if (existItem->getItemName() != trim(splitLine.first))
                        {

                            std::cout << "Exist item with the same categorical number but with different item name\n";
                        }
                    }
                }

                currentItem.push_back(splitLine);

                lineIndex++;

            }

        }

        inputFile.close();
    }


}

bool isDouble(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}


bool is3D(string s);

IkeaItem* createItem(std::vector<std::pair<std::string, std::string>> currentItem, string currentItemString)
{

    //create mandatory first
    IkeaItem* item;

    std::string firstAdditional, secondAdditional;
    firstAdditional = trim(currentItem[4].second);

    if ( firstAdditional == "Weight" && currentItem.size() == 5)
    {
        // validate weight is double
        if (!isDouble(trim(currentItem[4].first)))
        {
            return nullptr;
        }
        item = new FabricItem(trim(currentItem[0].first), trim(currentItem[1].first), trim(currentItem[3].first),
                              trim(currentItem[2].first),currentItemString, trim(currentItem[4].first));
        return item;
    }
    else if (firstAdditional == "Calories" && currentItem.size() == 5)
    {
        //validate calories is double
        if (!isDouble(trim(currentItem[4].first)))
        {
            return nullptr;
        }
        item = new CandyItem(trim(currentItem[0].first), trim(currentItem[1].first), trim(currentItem[3].first),
                             trim(currentItem[2].first), currentItemString, trim(currentItem[4].first));
        return item;
    }
    else if(firstAdditional == "Dimensions")
    {
        // validate dimension is 3 doubles
        if (!is3D(trim(currentItem[4].first)))
        {
            return nullptr;
        }
        secondAdditional = trim(currentItem[5].second);
        if ( secondAdditional == "Material" && currentItem.size() == 7)
        {
            if (trim(currentItem[6].second) == "Color")
            {
                item = new BigFurnitureItem(trim(currentItem[0].first), trim(currentItem[1].first),
                                            trim(currentItem[3].first), trim(currentItem[2].first), currentItemString,
                                            trim(currentItem[4].first), trim(currentItem[5].first),
                                            trim(currentItem[6].first));
                return item;
            }
        }
        else if( secondAdditional == "Capacity" &&currentItem.size() == 6)
        {
            // validate capacity is double
            if (!isDouble(trim(currentItem[5].first)))
            {
                return nullptr;
            }

            item = new KitchenItem(trim(currentItem[0].first), trim(currentItem[1].first),
                                   trim(currentItem[3].first), trim(currentItem[2].first),
                                   currentItemString, trim(currentItem[4].first), trim(currentItem[5].first));
            return item;
        }
    }
    else if(firstAdditional == "Author" && currentItem.size() == 7)
    {
        if (trim(currentItem[5].second) == "Year of publication")
        {

            if (trim(currentItem[6].second) == "Length")
            {

                if (!(isNumericString(trim(currentItem[5].first))) || !(isNumericString(trim(currentItem[6].first))))
                {

                    return nullptr;
                }
                item = new LeisureItem(trim(currentItem[0].first), trim(currentItem[1].first),
                                            trim(currentItem[3].first), trim(currentItem[2].first), currentItemString,
                                            trim(currentItem[4].first), trim(currentItem[5].first),
                                            trim(currentItem[6].first));

                return item;
            }
        }
    }

    //case nothing was returned , return illegal empty item
    return nullptr;
}

bool is3D(string s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    int i = 0;
    for(std::string s; iss >> s; )
    {
        result.push_back(s);
        i++;
    }
    if (i != 3)
    {
        return false;
    }
    for(auto& str: result)
    {
        if(!isDouble(str))
        {
            return false;
        }

    }
    return true;

}



/**
 * finds ikea item by catalog number.
 * @param catalogNumber
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByCatalogNumber(std::string catalogNumber)
{
    if (!isNumericString(catalogNumber))
    {
        return std::string("Illegal catalog number\n");
    }

    for (auto &ikeaItem : ikeaItems) {

        if (ikeaItem->getCatalogNumber() == catalogNumber) {

            return ikeaItem->getInputString();
        }
    }
    return std::string("Item not found\n");
}



/**
 * finds ikea item by item name.
 * @param itemName
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByName(std::string itemName)
{
    for (auto &ikeaItem : ikeaItems) {

        if (ikeaItem->getItemName() == itemName) {



            return ikeaItem->getInputString();
        }
    }
    return std::string("Item not found\n");

}



/**
 * comperator for ikea item by categorical number of item
 * @param left
 * @param right
 * @return
 */
bool compareByCategoricalOrder(const IkeaItem* &left, const IkeaItem* &right)
{

    return left->getCatalogNumber() < right->getCatalogNumber();

}

/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by categorical number
 */
void getItemsByCategoricalOrder(std::vector<IkeaItem*> &items)
{
    std::sort (items.begin(), items.end(), compareByCategoricalOrder); //todo check
    for (auto pos=items.begin(); pos!=items.end(); ++pos) {
        std::cout << (*pos)->getInputString() ;
    }


}



/**
 * comperator for ikea item by categorical number of item
 * @param left
 * @param right
 * @return
 */
bool compareByItemName(const IkeaItem &left, const IkeaItem &right)
{

    return left.getItemName() < right.getItemName();

}


/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by item name alphabetically
 */
std::string getItemsByItemName(std::vector<IkeaItem> &items);



/**
 * sells an item
 * @param catalogNumber
 * @return
 */
bool sellItem(int catalogNumber);








int main()
{

    int userInput;
    bool showMenu = true;

    while (showMenu)
    {

        std::cout << STORE_MENU;
        std::cin >> userInput;

        while (std::cin.fail() || userInput > 7)
        {
            std::cout << STORE_MENU;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> userInput;
        }


        switch (userInput)
        {

            case INPUT_STOCK_FROM_FILE:
            {
                std::string fileName;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> fileName;
                addItem(fileName);
                break;
            }

            case FIND_ITEM_BY_CAT_NUM:
            {
                std::string catalogNumber;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> catalogNumber;
                std::cout << getItemByCatalogNumber(catalogNumber);
                //todo - check which error can happen?
                break;
            }

            case FIND_ITEM_BY_NAME:
            {
                std::string itemName;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::getline(std::cin, itemName);
                std::cout << getItemByName(itemName);
                break;
            }

            case PRINT_STOCK_BY_CAT_NUM:
                getItemsByCategoricalOrder(ikeaItems);
                break;

            case PRINT_STOCK_BY_NAME:
                break;

            case SELL_ITEM:
                break;

            case EXIT:
                showMenu = false;
                break;

            default:
                break;

        }

    }

    return 0;








}