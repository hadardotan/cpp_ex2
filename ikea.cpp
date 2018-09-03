//
// Created by Visitor on 9/1/2018.
//

#include "ikea.h"



/**
 * global variables
 */

std::vector<IkeaItem*> ikeaItems; // <item, quantity>

/**
 * helper functions
 */


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



IkeaItem createItem(std::vector<std::pair<std::string, std::string>> currentItem);

/**
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
void addItem(const std::string fileName)
{
    std::string currentLine;
    IkeaItem ikeaItem;
    IkeaItem* existItem;
    std::ifstream  inputFile(fileName);
    bool itemExist = false;

    std::vector<std::pair<std::string, std::string>> currentItem;

    if (inputFile.is_open())
    {
        int lineIndex = 0;
        while(std::getline(inputFile, currentLine))
        {
            if (currentLine == END_OF_ITEM)
            {
                //create item object
                if (currentItem.size() < 4)
                {
                    std::cout << "illegal item fields\n";
                    inputFile.close();
                    return;
                }
                if (itemExist)
                {
                    //

                }
                ikeaItem = createItem(currentItem);
                if (ikeaItem.getItemName() == "")
                {
                    std::cout << "illegal item fields\n";
                    inputFile.close();
                    return;
                }
                ikeaItems.push_back(&ikeaItem);
                lineIndex = 0;
                currentItem.clear();
            }
            else
            {
                std::pair<std::string, std::string> splitLine = splitLineByColon(currentLine);

                // check existance of mandatory fields
                if (lineIndex < MIN_NUM_OF_ITEM_LINES)
                {

                    if (splitLine.first != paramNames[lineIndex])
                    {
                        std::cout << "illegal line param\n";
                        //return to menu
                        inputFile.close();
                        return;

                    }
                    if (lineIndex == 0 )
                    { //check if item exist
                        existItem = findExistItem(splitLine.second);
                        if (existItem != nullptr) //means item exist - update quantity
                        {
                            itemExist = true;
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

IkeaItem createItem(std::vector<std::pair<std::string, std::string>> currentItem)
{

    //create mandatory first
    IkeaItem mandatory(trim(currentItem[0].second), trim(currentItem[1].second), trim(currentItem[3].second), trim(currentItem[2].second));
    std::string firstAdditional, secondAdditional;
    firstAdditional = trim(currentItem[4].first);

    if ( firstAdditional == "Weight" && currentItem.size() == 5)
    {
        return FabricItem(mandatory, trim(currentItem[4].second));
    }
    else if (firstAdditional == "Calories" && currentItem.size() == 5)
    {
        return CandyItem(mandatory, trim(currentItem[4].second));
    }
    else if(firstAdditional == "Dimensions")
    {
        secondAdditional = trim(currentItem[5].first);
        if ( secondAdditional == "Material" && currentItem.size() == 7)
        {
            if (trim(currentItem[6].first) == "Color")
            {
                return BigFurnitureItem(mandatory, trim(currentItem[4].second), trim(currentItem[5].second),
                                                                                    trim(currentItem[6].second));
            }
        }
        else if( secondAdditional == "Capacity" &&currentItem.size() == 6)
        {
            return KitchenItem(mandatory, trim(currentItem[4].second), trim(currentItem[5].second));
        }
    }
    else if(firstAdditional == "Author" && currentItem.size() == 7)
    {
        if (trim(currentItem[5].first) == "Year of publication")
        {
            if (trim(currentItem[6].first) == "Length")
            {
                return LeisureItem(mandatory, trim(currentItem[4].second),
                                                   trim(currentItem[5].second), trim(currentItem[6].second));
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
std::string getItemByCatalogNumber(int catalogNumber);


/**
 * finds ikea item by item name.
 * @param itemName
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByName(std::string itemName);



/**
 * comperator for ikea item by categorical number of item
 * @param left
 * @param right
 * @return
 */
bool compareByCategoricalOrder(const IkeaItem &left, const IkeaItem &right)
{

    return left.getCatalogNumber() < right.getCatalogNumber();

}

/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by categorical number
 */
std::string getItemsByCategoricalOrder(std::vector<IkeaItem> &items);



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

                std::string fileName;
                std::cin >> fileName;
                addItem(fileName);


                return 0;

            case FIND_ITEM_BY_CAT_NUM:
                return 0;

            case FIND_ITEM_BY_NAME:
                return 0;

            case PRINT_STOCK_BY_CAT_NUM:
                return 0;

            case PRINT_STOCK_BY_NAME:
                return 0;

            case SELL_ITEM:
                return 0;

            case EXIT:
                showMenu = false;

        }

    }

    return 0;








}