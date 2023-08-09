#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>

enum FieldType {
    BIT_FIELD,
    BYTE_FIELD,
};

enum FieldAction {
    DECODE_ACTION,
    GONE_ACTION,
};

class IntBase
{
public:
	virtual ~IntBase() {}
	virtual void DoAction() = 0;
    int intType;
};

class FieldIntValue : public IntBase
{
public:
    FieldIntValue(std::string name)
        : m_name(name) {intType = 0;}

    virtual void DoAction()
    {
    }

    std::string m_name;
};

class IntValue : public IntBase
{
public:
    IntValue(int value)
        : m_value(value) {intType = 1;}

    virtual void DoAction()
    {
    }

    uint64_t m_value;
};

class MultiDivInt : public IntBase
{
public:
    MultiDivInt(IntBase* leftInt, int op, IntBase* rightInt)
    : m_leftInt(leftInt)
    , m_op(op)
    , m_rightInt(rightInt)
    {}

    virtual void DoAction()
    {
    }

    IntBase* m_leftInt;
    uint8_t  m_op;
	IntBase* m_rightInt;
};

class AddSubInt : public IntBase
{
public:
    AddSubInt(IntBase* leftInt, int op, IntBase* rightInt)
    : m_leftInt(leftInt)
    , m_op(m_op)
    , m_rightInt(rightInt)
    {}

    virtual void DoAction()
    {
    }

private:
    IntBase* m_leftInt;
    uint8_t  m_op;
	IntBase* m_rightInt;
};

class AndOrInt : public IntBase
{
public:
    AndOrInt(IntBase* leftInt, uint8_t op, IntBase* rightInt)
    : m_leftInt(leftInt)
    , m_op(m_op)
    , m_rightInt(rightInt)
    {}

    virtual void DoAction()
    {
    }

    IntBase* m_leftInt;
    uint8_t  m_op;
	IntBase* m_rightInt;
};

class CompareInt : public IntBase
{
public:
    CompareInt(IntBase* leftInt, int op, IntBase* rightInt)
    : m_leftInt(leftInt)
    , m_op(m_op)
    , m_rightInt(rightInt)
    {}

    virtual void DoAction()
    {
    }

    IntBase* m_leftInt;
    int  m_op;
	IntBase* m_rightInt;
};

class Field {
public:
    virtual void DoAction() = 0;

    std::string                         fieldName;
    std::string                         showName;
    std::vector<FieldAction>            actions;

    std::string                         content;
    FieldType                           fieldType;
};

class ByteField : public Field {
public:
    ByteField(char* name, char* show_name, IntBase* intBase)
    {
        fieldType = BYTE_FIELD;
        fieldName = name;
        showName = show_name;
        m_fieldLen = intBase;
    }

    // change it to llvm ir
    void DoAction()
    {
    }
private:
    IntBase* m_fieldLen;
};

class Protocol {
public:
    Protocol(char* data) 
    : m_proName(data) {}

    ~Protocol();

    void SetProName(char* data)
    {
        m_proName = data;
    }

    void SetByteField()
    {

    }

    void push_int_param(struct IntInfo* intInfo);

    void merge_params(int actionOp);

    void set_byte_field(char* name, char* show_name)
    {
        auto findIt = m_fields.find(std::string(name));
        if (findIt != m_fields.end())
        {
            perror("repeat field name");
            return exit(-1);
        }

        IntBase* intBase = m_intBaseStack.back();
        m_intBaseStack.pop_back();

        ByteField* byteField = new ByteField(name, show_name, intBase);
        m_fields[std::string(name)] = byteField;
    }

    void push_field_action(int action);

    void set_field_actions(char* field_name);

    void set_logic_expr(int op);

    void set_if_action()
    {
        IntBase* intBase = m_intBaseStack.back();
        m_intBaseStack.pop_back();
        intBase->DoAction();
    }

private:
    std::string                                             m_proName;                      // protocol name
    std::unordered_map<std::string, Field*>                 m_fields;                       // fields map
    std::vector<IntBase*>                                   m_intBaseStack;
    std::vector<FieldAction>                                m_fieldAction;
    std::vector<IntBase*>                                   m_allIntBase;
};