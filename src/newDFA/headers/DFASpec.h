//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H

#include <string>
#include "../../DFAInterface/Spec.h"
using namespace std;

class DFASpec : public Spec {
public:
    DFASpec();
    ~DFASpec();

    void setTempWord(const string&);
    void setContent(const string&);
    string* getTempWord() const;
    string* getContent() const ;

private:
    string* tempWord;   // 时序词
    string* content;    // 验证内容
};


#endif //RUNTIME_VERIFICATION_SYSTEM_DFASPEC_H
