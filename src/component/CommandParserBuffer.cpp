/*******************************************
*  @file  CommandParserBuffer.cpp          * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "component/CommandParserBuffer.h"

CommandParserBuffer::CommandParserBuffer() {
    m_buffer["SetLogicParser"] = new SetLogicParser();
    m_buffer["CommandParser"] = new CommandParser(); 
    m_buffer["DeclSortParser"] = new DeclSortParser(); 
    m_buffer["DeclDatatypesParser"] = new DeclDatatypesParser(); 

}

DeclDatatypesParser* CommandParserBuffer::getDeclDatatypesParser() {
    return dynamic_cast<DeclDatatypesParser*>(m_buffer["DeclDatatypesParser"]);
}

DeclSortParser* CommandParserBuffer::getDeclSortParser() {
    return dynamic_cast<DeclSortParser*>(m_buffer["DeclSortParser"]);
}

CommandParser* CommandParserBuffer::getCommandParser() {
    return m_buffer["CommandParser"];
}

SetLogicParser* CommandParserBuffer::getSetLogicParser() {
    return dynamic_cast<SetLogicParser*>(m_buffer["SetLogicParser"]);
}

CommandParserBuffer::~CommandParserBuffer() {
    for (auto item : m_buffer) {
        delete item.second;
    }
}
