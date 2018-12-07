#if !defined(TYPES_)
#define TYPES_

#include <vector>
#include <map>
#include <string>

#include "component/FuncType.h"
#include "component/SortType.h"
#include "component/Var.h"

using std::vector;
using std::map;
using std::string;

using SyntaxErrorTable = vector<string>;

// LogicParser.h
using LogicInfo = map<string, string>;
using TheoryInfo = map<string, string>;
using Theories = vector<string>;

// Parser.h
using SortTable = map<string, SortType>; 
using FuncTable = map<string, FuncType>;
using VarStack = vector<Var>;
using ScopeMarkStack = vector<int>;



#endif
