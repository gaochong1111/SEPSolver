#if !defined(TOKEN_SCANNER_FACTORY_)
#define TOKEN_SCANNER_FACTORY_
/*******************************************
*  @file  TokenScannerFactory              *
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-8                     *
*                                          *
*******************************************/

#include "TokenScanner.h"
#include "scanner/LeftParenScanner.h"
#include "scanner/RightParenScanner.h"
#include "scanner/CommentScanner.h"
#include "scanner/KeywordScanner.h"
#include "scanner/NumberLiteralScanner.h"
#include "scanner/StringLiteralScanner.h"
#include "scanner/SymbolScanner.h"

/*! @class TokenScannerFactory
 *  @brief Brief class description
 *
 *  Detailed description
 */
class TokenScannerFactory
{
public:
    TokenScannerFactory() {}
    virtual ~TokenScannerFactory() {}
    TokenScanner* getTokenScanner(char sign);

};

#endif
