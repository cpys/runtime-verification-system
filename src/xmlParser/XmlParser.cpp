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

    XMLElement* model = xmlDocument.FirstChildElement();
    if (model == NULL || strcmp(model->Value(), "mxGraphModel") != 0) return false;

    XMLElement* root = model->FirstChildElement();
    if (root == NULL || strcmp(root->Value(), "root") != 0) return false;

    XMLElement* cell = root->FirstChildElement();

    do {
        if (cell == NULL || strcmp(cell->Value(), "mxCell") != 0) return false;

        // 解析cell
        if (cell->Attribute("vertex")) {
            if (strcmp(cell->Attribute("parent"), "1") == 0) {
                // 处理结点
                string node_value = cell->Attribute("value");
                cout << "结点" << cell->Attribute("id") << ", 值" << node_value << endl;
            }
            else if (cell->Attribute("parent")) {
                // 处理边上的转移条件
                string tran_value = cell->Attribute("value");
                int parent_edge = stoi(cell->Attribute("parent"));
                cout << "转移条件" << tran_value << ", 在边" << parent_edge << "上" << endl;
            }
        }
        else if (cell->Attribute("edge")) {
            // 处理边
            int source, target;

            if (cell->Attribute("source")) {
                source = stoi(cell->Attribute("source"));
            }
            else source = 0;

            if (cell->Attribute("target")) {
                target = stoi(cell->Attribute("target"));
            }
            else target = 0;

            cout << "边" << cell->Attribute("id") << ", 从结点" << source << "到" << target << endl;
        }

        cell = cell->NextSiblingElement();
    } while (cell != NULL);

    return true;
}