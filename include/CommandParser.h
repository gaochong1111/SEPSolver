#if !defined(COMMAND_PARSER_)
#define COMMAND_PARSER_
/*******************************************
*  @file  CommandParser.h                  * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "Parser.h"

class Parser;

using SortTypeList = vector<SortType*>;
using SelectorDec = pair<string, string>;
using SelectorDecList = vector<pair<string, string>>;
using ConstructorDec = pair<string, SelectorDecList>;
using ConstructorDecList = vector<ConstructorDec>;

/*! @class CommandParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class CommandParser
{
public:
    CommandParser() {}
    virtual ~CommandParser() {}
    virtual void parse(Parser& parser) {}

protected:
    SortType* parseSortDecl(Parser& parser);
    void parseSortDeclList(Parser& parser, SortTypeList& st_list);
    void parseSelectorDecl(Parser& parser, SelectorDec& sel_dec);
    void parseSelectorDeclList(Parser& parser, SelectorDecList& sd_list);
    void parseConstructorDecl(Parser& parser, ConstructorDec& con_dec);
    void parseConstructorDeclList(Parser& parser, ConstructorDecList& cd_list);
};
#endif
