//
// Created by Visitor on 9/1/2018.
//

#include "ikea.h"







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
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
bool addItem(std::string fileName)
{
    std::string currentLine;
    std::ifstream  inputFile(fileName);
    if (inputFile.is_open())
    {
        int lineIndex = 0;
        while(std::getline(inputFile, currentLine))
        {
            if (currentLine == END_OF_ITEM)
            {
                lineIndex = 0;
            }
            else
            {
                std::pair<std::string, std::string> splitLine = splitLineByColon(currentLine);

                // mandatory fields
                if (lineIndex < MIN_NUM_OF_ITEM_LINES)
                {
                    if (splitLine.first != paramNames[lineIndex])
                    {
                        std::cout << "illegal line param\n";
                    }
                    lineIndex++;
                }

                // additional fields



            }









        }

        inputFile.close();
    }


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

    std::vector<IkeaItem, double> ikeaItems; // <item, quantity>

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
                if (addItem(fileName))
                {

                }

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