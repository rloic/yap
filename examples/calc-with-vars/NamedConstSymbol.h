/*
 * MIT License
 *
 * Copyright (c) 2018 insa.4if.hexanome_kalate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include <YAP/YAP.h>

#include <map>


template<typename Type, YAP::Symbol::Id ValueId, char DebugName = '\0'>
class NamedConstSymbol : public YAP::Symbol {
public:
    static Ptr Create(std::string const& name) {
        return Ptr(new NamedConstSymbol(name));
    }

    Type GetValue() {
        return GetSetValue();
    }

    void SetValue(Type value) {
        GetSetValue(true, value);
    }

protected:
    explicit NamedConstSymbol(std::string name)
            : Symbol(ValueId),
              mName{std::move(name)}
    {}

    void print(std::ostream &os) const override {
        os << DebugName << "(name=" << mName << ")";
    }

    Type GetSetValue(bool set = false, Type value = {}) {
        static std::map<std::string, Type> values;
        if (set) {
            values[mName] = std::move(value);
            return value;
        } else {
            if (values.find(mName) == values.end()) {
                using namespace YAP::Colors;
                std::cout << bold << red << "[Critical] " << reset
                          << red << "Must be defined: " << reset
                          << cyan << mName << reset
                          << std::endl;
                exit(1);
            }
            return values[mName];
        }
    }

private:
    std::string mName;
};
