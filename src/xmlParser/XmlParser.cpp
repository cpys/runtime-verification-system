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

    // 先循环一遍，处理结点、边、验证逻辑
    do {
        if (cell == NULL) return false;
        if (strcmp(cell->Value(), "mxCell") == 0) {
            // 边、结点、转移关系
            if (cell->Attribute("vertex") && strcmp(cell->Attribute("parent"), "1") == 0) {
                // 处理结点
                string state_string = cell->Attribute("value");
                int cell_id = stoi(cell->Attribute("id"));
                cout << "结点" << cell_id << ": " << state_string << endl;

                // 将状态添加到模型中
                int state_id = this->module.addState(state_string);

                // 更新结点id与状态id的对应表
                this->cell_id_to_state_id[cell_id] = state_id;
                this->state_id_to_cell_id[state_id] = cell_id;
            }
            else if (cell->Attribute("edge")) {
                // 处理边
                int cell_id = stoi(cell->Attribute("id"));

                int source, target;
                if (cell->Attribute("source")) {
                    source = stoi(cell->Attribute("source"));
                }
                else source = 0;

                if (cell->Attribute("target")) {
                    target = stoi(cell->Attribute("target"));
                }
                else target = 0;

                cout << "边" << cell_id << ", 从结点" << source << "到" << target << endl;

                // 将边暂存在类中
                int state_from = this->cell_id_to_state_id[source];
                int state_to = this->cell_id_to_state_id[target];
                Tran tran(state_from, state_to);
                this->cell_id_to_tran[cell_id] = tran;
            }
        }
        else if (strcmp(cell->Value(), "UserObject") == 0) {
            // 验证逻辑

        }

        cell = cell->NextSiblingElement();
    } while(cell != NULL);

    // 再循环一遍，处理转移关系，将其附加到边上
    cell = root->FirstChildElement();
    do {
        if (cell == NULL) return false;

        if (strcmp(cell->Value(), "mxCell") == 0 && cell->Attribute("vertex") && strcmp(cell->Attribute("parent"), "1") != 0) {
            // 处理边上的转移条件
            string tran_value = cell->Attribute("value");
            int parent_edge = stoi(cell->Attribute("parent"));
            cout << "转移条件" << tran_value << ", 在边" << parent_edge << "上" << endl;

            Tran tran = this->cell_id_to_tran[parent_edge];
            this->module.addTran(tran.getStateFrom(), tran.getStateTo(), tran_value);
        }

        cell = cell->NextSiblingElement();
    } while (cell != NULL);

    return true;
}