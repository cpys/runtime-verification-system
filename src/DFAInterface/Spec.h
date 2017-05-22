//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_SPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_SPEC_H

#include <string>
using std::string;

class Spec {
public:
    Spec();
    virtual ~Spec();

    /*
     * 添加时序词
     * @param 时序词
     */
    virtual void setTempWord(const string&);

    /*
     * 添加验证内容
     * @param 验证内容
     */
    virtual void setContent(const string&);

    /*
    * 获取时序词
    * @return 时序词
    */
    virtual string* getTempWord();

    /*
     * 获取验证内容
     * @return 验证内容
     */
    virtual string* getContent();
};

#endif //RUNTIME_VERIFICATION_SYSTEM_SPEC_H
