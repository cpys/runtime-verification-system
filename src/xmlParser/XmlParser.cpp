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
    XMLError xmlError = xmlDocument.LoadFile(filename.c_str());
    if (xmlError != XML_SUCCESS) {
        cerr << "Cannot open file " << filename << endl;
        return false;
    }

    XMLElement* model = xmlDocument.FirstChildElement();
    if (model == NULL || strcmp(model->Value(), "mxGraphModel") != 0) return false;

    XMLElement* root = model->FirstChildElement();
    if (root == NULL || strcmp(root->Value(), "root") != 0) return false;

    XMLElement* cell = root->FirstChildElement();

    // 先解析结点
    do {
        if (cell == NULL || strcmp(cell->Value(), "mxCell") != 0) return false;

        if (cell->Attribute("vertex") && strcmp(cell->Attribute("parent"), "1") == 0) {
            // 处理结点
            string node_value = cell->Attribute("value");
            int cell_id = stoi(cell->Attribute("id"));
            cout << "结点" << cell_id << ", 值" << node_value << endl;

            // 将状态添加到模型中
//            State state(node_value);
//            int state_id = this->module.addState(state);
            int state_id = this->module.addState(node_value);

            // 更新结点id与状态id的对应表
            this->cell_id_to_state_id[cell_id] = state_id;
            this->state_id_to_cell_id[state_id] = cell_id;
        }

        cell = cell->NextSiblingElement();
    } while (cell != NULL);

    // 再处理边
    cell = root->FirstChildElement();
    do {
        if (cell == NULL || strcmp(cell->Value(), "mxCell") != 0) return false;

        if (cell->Attribute("edge")) {
            // 处理边
            int source, target, cell_id;

            cell_id = stoi(cell->Attribute("id"));

            if (cell->Attribute("source")) {
                source = stoi(cell->Attribute("source"));
            }
            else source = 0;

            if (cell->Attribute("target")) {
                target = stoi(cell->Attribute("target"));
            }
            else target = 0;

            cout << "边" << cell_id << ", 从结点" << source << "到" << target << endl;

            int state_from = this->cell_id_to_state_id[source];
            int state_to = this->cell_id_to_state_id[target];
            Tran tran(state_from, state_to);
            this->cell_id_to_tran[cell_id] = tran;
        }

        cell = cell->NextSiblingElement();
    } while (cell != NULL);

    // 最后处理边上的转移条件
    cell = root->FirstChildElement();
    do {
        if (cell == NULL || strcmp(cell->Value(), "mxCell") != 0) return false;

        if (cell->Attribute("vertex") && strcmp(cell->Attribute("parent"), "1") != 0) {
            // 处理边上的转移条件
            string tran_value = cell->Attribute("value");
            int parent_edge = stoi(cell->Attribute("parent"));
            cout << "转移条件" << tran_value << ", 在边" << parent_edge << "上" << endl;

            Tran tran = this->cell_id_to_tran[parent_edge];
//            tran.addCondition(tran_value);
//            this->module.addTran(tran);
            this->module.addTran(tran.getStateFrom(), tran.getStateTo(), tran_value);
        }

        cell = cell->NextSiblingElement();
    } while (cell != NULL);

    return true;
}