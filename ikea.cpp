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
 * clears cin
 */
void initCin()
{
    std::cin.clear();
    std::cin.ignore(256, '\n');
}



/**
 * checks if string is numeric
 * @param str
 * @return
 */
bool isNumericString(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;

}
/**
 * left trim
 * @param str
 * @param chars
 * @return
 */
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

/**
 * right trim
 * @param str
 * @param chars
 * @return
 */
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

/**
 * left and right trim
 * @param str
 * @param chars
 * @return
 */
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}


/**
 * splits a line by colon <field> : <value>
 * @param line
 * @return
 */
std::pair<std::string, std::string> splitLineByColon(std::string line)
{

    std::string param = "", value = "";
    std::string::size_type pos = line.find(':');

    if(line.npos != pos)
    {
        param = line.substr(pos + 1);
        value = line.substr(0, pos);
    }
    return std::make_pair(param, value);


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


IkeaItem* createItem(std::vector<std::pair<std::string, std::string>> currentItem, string currentItemString);

/**
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
void addItem(const std::string fileName="/cs/usr/hadar.dotan/Documents/cpp_ex2/items.txt")
{
    string currentLine;
    IkeaItem* ikeaItem;
    IkeaItem* existItem;
    std::ifstream  inputFile(fileName);
    string currentItemString = "";
    bool itemExist = false;
    std::vector<std::pair<std::string, std::string>> currentItem;
    if (inputFile.is_open())
    {
        int lineIndex = 0, productNo = 0;
        while(std::getline(inputFile, currentLine))
        {
            if (lineIndex > MAX_NUM_OF_ITEM_LINES) //too many params
            {
                std::cout << ILLEGAL_ITEM_FIELDS;
                inputFile.close();
                return;
            }
            else if (currentLine == END_OF_ITEM)
            {
                currentItemString += currentLine+"\n";
                //create item object
                if (currentItem.size() < MIN_NUM_OF_ITEM_LINES)
                {
                    std::cout << ILLEGAL_ITEM_FIELDS;
                    inputFile.close();
                    return;
                }

                if (itemExist)
                {
                    auto addQuantity = std::stod(currentItem[2].first);
                    existItem->updateQuantity(addQuantity);
                }
                else
                {
                    ikeaItem = createItem(currentItem, currentItemString);
                    if (ikeaItem == nullptr)
                    {
                        std::cout << ILLEGAL_ITEM_FIELDS;
                        inputFile.close();
                        return;
                    }
                    ikeaItems.push_back(ikeaItem);
                }

                currentItemString = "";
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
                        std::cout << ILLEGAL_LINE_PARAM;
                        //return to menu
                        inputFile.close();
                        return;

                    }
                    if (lineIndex == 0 )
                    {
                        productNo++;
                        existItem = findExistItem(trim(splitLine.first));
                        if (existItem != nullptr) //means item exist - update quantity
                        {
                            itemExist = true;
                        }
                    }

                    if (lineIndex == 1 && itemExist)
                    {
                        if (existItem->getItemName() != trim(splitLine.first))
                        {

                            std::cout << "product no. "+std::to_string(productNo)+" already in stock with different values\n";
                        }

                    }
                }

                currentItem.push_back(splitLine);
                lineIndex++;
            }
        }
        inputFile.close();
        return;
    }
    std::cout << ILLEGAL_PATH;
}

/**
 *
 * @param s
 * @return true if string is double, false otherwise
 */
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

/**
 *
 * @param s
 * @return true if string is 3 doubles seprated by spaces, false otherwise
 */
bool is3D(string s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    int i = 0;
    for(std::string s; iss >> s; )
    {
        result.push_back(s);
        i++;
    }
    if (i != FURNITURE_DIM)
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




IkeaItem* createItem(std::vector<std::pair<std::string, std::string>> currentItem, string currentItemString)
{

    //create mandatory first
    IkeaItem* item;

    std::string firstAdditional, secondAdditional;
    firstAdditional = trim(currentItem[4].second);

    if ( firstAdditional == WEIGHT && currentItem.size() == 5)
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
    else if (firstAdditional == CALORIES && currentItem.size() == 5)
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
    else if(firstAdditional == DIM)
    {
        // validate dimension is 3 doubles
        if (!is3D(trim(currentItem[4].first)))
        {
            return nullptr;
        }
        secondAdditional = trim(currentItem[5].second);
        if ( secondAdditional == MATERIAL && currentItem.size() == 7)
        {
            if (trim(currentItem[6].second) == COLOR)
            {
                item = new BigFurnitureItem(trim(currentItem[0].first), trim(currentItem[1].first),
                                            trim(currentItem[3].first), trim(currentItem[2].first), currentItemString,
                                            trim(currentItem[4].first), trim(currentItem[5].first),
                                            trim(currentItem[6].first));
                return item;
            }
        }
        else if( secondAdditional == CAPACITY &&currentItem.size() == 6)
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
    else if(firstAdditional == AUTHOR && currentItem.size() == 7)
    {
        if (trim(currentItem[5].second) == YEAR)
        {

            if (trim(currentItem[6].second) == LEN)
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





/**
 * finds ikea item by catalog number.
 * @param catalogNumber
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByCatalogNumber(std::string catalogNumber)
{
    if (!isNumericString(catalogNumber))
    {
        return std::string(ILLEGAL_CAT_NUM);
    }

    for (auto &ikeaItem : ikeaItems) {

        if (ikeaItem->getCatalogNumber() == catalogNumber) {

            return ikeaItem->getInputString();
        }
    }
    return std::string(ITEM_NOT_FOUND);
}



/**
 * finds ikea item by item name.
 * @param itemName
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByName(std::string itemName)
{
    for (auto &ikeaItem : ikeaItems)
    {
        if (ikeaItem->getItemName() == itemName)
        {
            return ikeaItem->getInputString();
        }
    }
    return std::string(ITEM_NOT_FOUND);

}



/**
 * comperator for ikea item by categorical number of item
 * @param left
 * @param right
 * @return
 */
bool compareByCategoricalOrder(IkeaItem* left, IkeaItem* right)
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
    std::sort (items.begin(), items.end(), compareByCategoricalOrder);
    for (auto pos=items.begin(); pos!=items.end(); ++pos)
    {
        std::cout << (*pos)->getInputString() ;
    }
}


/**
 * comperator for ikea item by categorical number of item
 * @param left
 * @param right
 * @return
 */
bool compareByItemName(IkeaItem* left, IkeaItem* right)
{
    return left->getItemName() < right->getItemName();
}

/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by item name alphabetically
 */
void getItemsByItemName(std::vector<IkeaItem*> &items)
{
    std::sort (items.begin(), items.end(), compareByItemName);
    for (auto pos = items.begin(); pos != items.end(); ++pos)
    {
        std::cout << (*pos)->getInputString() ;
    }
}

/**
 * sells an item
 * @param catalogNumber
 * @return
 */
string sellItem(string catalogNumber) {

    if (!isNumericString(catalogNumber)) {
        return std::string(ILLEGAL_CAT_NUM);

    }
    IkeaItem *item = findExistItem(catalogNumber);
    if (item == nullptr) {
        return std::string(ITEM_NOT_FOUND);
    }
    if (item->isPerUnit()) {
        std::cout << ENTER_UNIT;
    } else {
        std::cout << ENTER_QUANTITY;
    }
    std::string desiredQuantity;
    initCin();
    std::cin >> desiredQuantity;

    if ((item->isPerUnit() && isNumericString(desiredQuantity)) || (!item->isPerUnit() && isDouble(desiredQuantity)))
    {
        double subQuantity = std::stod(desiredQuantity);
        if (subQuantity > item->getQuantity()) {
            return std::string(NO_STOCK);
        }
        item->updateQuantity(-subQuantity);
        return item->getInputString();
    }
    return std::string(ILLEGAL_QUANTITY);
}



/**
 *
 * @return
 */
int main()
{
    int userInput;
    bool showMenu = true;
    while (showMenu)
    {

        std::cout << STORE_MENU;
        std::cin >> userInput;

        while (std::cin.fail() || userInput > MAX_MENU_BUTTON)
        {
            std::cout << STORE_MENU;
            initCin();
            std::cin >> userInput;
        }
        switch (userInput)
        {
            case INPUT_STOCK_FROM_FILE:
            {
                std::string fileName;
                initCin();
                std::cout << ENTER_PATH;
                std::cin >> fileName;
                addItem(fileName);
                break;
            }
            case FIND_ITEM_BY_CAT_NUM:
            {
                std::string catalogNumber;
                initCin();
                std::cout << ENTER_CAT_NUM;
                std::cin >> catalogNumber;
                std::cout << getItemByCatalogNumber(catalogNumber);
                break;
            }

            case FIND_ITEM_BY_NAME:
            {
                std::string itemName;
                initCin();
                std::cout << ENTER_ITEM_NAME;
                std::getline(std::cin, itemName);
                std::cout << getItemByName(itemName);
                break;
            }

            case PRINT_STOCK_BY_CAT_NUM:
            {
                getItemsByCategoricalOrder(ikeaItems);
                break;
            }

            case PRINT_STOCK_BY_NAME:
            {
                getItemsByItemName(ikeaItems);
                break;
            }

            case SELL_ITEM:
            {
                std::string catalogNumber;
                initCin();
                std::cin >> catalogNumber;
                std::cout<< sellItem(catalogNumber);
                break;
            }
            case EXIT:
                showMenu = false;
                break;

            default:
                break;

        }

    }

    return 0;








}