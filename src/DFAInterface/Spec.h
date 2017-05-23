//
// Created by yingzi on 2017/5/22.
//

#ifndef RUNTIME_VERIFICATION_SYSTEM_SPEC_H
#define RUNTIME_VERIFICATION_SYSTEM_SPEC_H

#include <string>
using std::string;

class Spec {
public:
    Spec() = default;
    virtual ~Spec() = default;

    /*
     * 添加时序词
     * @param 时序词
     */
    virtual void setTempWord(const string&) = 0;

    /*
     * 添加验证内容
     * @param 验证内容
     */
    virtual void setContent(const string&) = 0;

    /*
    * 获取时序词
    * @return 时序词
    */
    virtual string* getTempWord() const = 0;

    /*
     * 获取验证内容
     * @return 验证内容
     */
    virtual string* getContent() const = 0;
};

#endif //RUNTIME_VERIFICATION_SYSTEM_SPEC_H
