//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H

#include <string>
#include "../../DFAInterface/Spec.h"
#include "../../DFAInterface/State.h"
using namespace std;

class DFASpec : public Spec {
public:
    DFASpec();
    ~DFASpec();

    void setTempWord(const string&);
    void setContent(const string&);
    string* getTempWord() const;
    string* getContent() const ;

    bool verifyState(State*);

    string toString();

private:
    string* tempWord;   // 时序词
    string* content;    // 验证内容

    string* varName;    // 验证内容变量名
    string* varOperator;    // 验证内容运算符
    string* varValue;   // 验证内容变量值

    /*
     * 当content发生变化时更新具体的验证内容信息
     */
    void updateContentInfo();
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
