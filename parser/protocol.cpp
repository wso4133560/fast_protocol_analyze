#include "protocol.h"
#include "script_manager.h"
#include "parser.h"

Protocol::~Protocol()
{
    for (auto &it : m_fields)
    {
        delete it.second;
    }

    for (auto &it : m_allIntBase)
    {
        delete it;
    }
}

void Protocol::push_int_param(struct IntInfo* intInfo)
{
    IntBase* intBase = NULL;

    if (intInfo->field)
    {
        intBase = new FieldIntValue(intInfo->field);
    }
    else
    {
        intBase = new IntValue(intInfo->value);
    }

    m_intBaseStack.push_back(intBase);
    m_allIntBase.push_back(intBase);
}

void Protocol::merge_params(int actionOp)
{
    IntBase* leftInt = m_intBaseStack.back();
    m_intBaseStack.pop_back();
    IntBase* rightInt = m_intBaseStack.back();
    m_intBaseStack.pop_back();

    IntBase* intBase = NULL;
    switch (actionOp)
    {
        case ADD:
            intBase = new AddSubInt(leftInt, 0, rightInt);
            break;
        case SUB:
            intBase = new AddSubInt(leftInt, 1, rightInt);
            break;
        case MUL:
            intBase = new MultiDivInt(leftInt, 0, rightInt);
            break;
        case DIV:
            intBase = new MultiDivInt(leftInt, 1, rightInt);
            break;
    }

    m_intBaseStack.push_back(intBase);
    m_allIntBase.push_back(intBase);
}

void Protocol::push_field_action(int action)
{
    if (DECODE == action)
    {
        m_fieldAction.push_back(DECODE_ACTION);
    }
    else if(GONE == action)
    {
        m_fieldAction.push_back(GONE_ACTION);
    }
}

void Protocol::set_field_actions(char* field_name)
{
    std::string fieldName(field_name);
    auto findIt = m_fields.find(fieldName);
    if (m_fields.end() == findIt)
    {
        perror("set_field_actions errors field name");
        exit(-1);
    }

    findIt->second->actions.assign(m_fieldAction.begin(), m_fieldAction.end());
    m_fieldAction.clear();
}

void Protocol::set_logic_expr(int op)
{
    IntBase* leftInt = m_intBaseStack.back();
    m_intBaseStack.pop_back();
    IntBase* rightInt = m_intBaseStack.back();
    m_intBaseStack.pop_back();

    IntBase* intBase = NULL;
    switch (op)
    {
        case AND:
            intBase = new AndOrInt(leftInt, 0, rightInt);
            break;
        case OR:
            intBase = new AndOrInt(leftInt, 1, rightInt);
            break;
        case EQ:
        case NEQ:
        case GT:
        case GTE:
        case LT:
        case LTE:
            intBase = new CompareInt(leftInt, op, rightInt);
            break;
    }

    m_intBaseStack.push_back(intBase);
    m_allIntBase.push_back(intBase);
}
