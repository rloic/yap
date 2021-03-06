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
class NamedVariableSymbol : public YAP::Symbol {
public:
    static Ptr Create(std::string const& name) {
        return Ptr(new NamedVariableSymbol(name));
    }

    Type GetValue() const {
        static std::map<std::string, Type> values;

        // Ask for the variable value, once
        auto found = values.find(mName);
        if (found == values.end()) {
            std::cout << "Enter the value of <" << mName << ">: ";
            Type value{};
            std::cin >> value;
            values[mName] = value;
        }

        return values[mName];
    }

protected:
    explicit NamedVariableSymbol(std::string name) : Symbol(ValueId), mName{std::move(name)} {}

    void print(std::ostream &os) const override {
        os << DebugName << "(name=" << mName << ")";
    }

private:
    std::string mName;
};
