//
// Created by yingzi on 2017/5/9.
//

#include <iostream>
#include "XmlParser.h"
using namespace tinyxml2;
using namespace std;

bool XmlParser::setFileName(std::string filename) {
    this->filename = filename;
    return true;
}

bool XmlParser::parseXml() {
    XMLDocument xmlDocument;
    xmlDocument.LoadFile(filename.c_str());
    XMLNode* root = xmlDocument.FirstChild();
    cout << root->Value() << endl;

    XMLText* rootText = root->ToText();
    cout << rootText->Value() << endl;


    return true;
}