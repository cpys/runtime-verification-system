//
// Created by yingzi on 2017/5/9.
//

#include <iostream>
#include "XmlParser.h"
using namespace std;

int main(int argc, char** argv) {

    XmlParser xmlParser;
    xmlParser.setFileName(argv[1]);
    xmlParser.parseXml();

    return 0;
}