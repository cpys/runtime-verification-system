//
// Created by yingzi on 2017/5/9.
//

/*
 * 此类负责将xml文件转换成DFA
 */

#ifndef RUNTIME_VERIFICATION_SYSTEM_XMLPARSER_H
#define RUNTIME_VERIFICATION_SYSTEM_XMLPARSER_H

#include <string>
//#include "../DFA/Module.h"
#include "tinyxml2.h"

class XmlParser {
private:
    //Module module;  // DFA模型
    std::string filename;    // xml文件

public:
    bool setFileName(std::string filename);  // 设置xml文件名
    bool parseXml();    // 解析文件生成模型
};


#endif //RUNTIME_VERIFICATION_SYSTEM_XMLPARSER_H
