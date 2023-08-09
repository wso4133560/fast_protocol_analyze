#pragma once
#include "parser.h"
#include "script_manager.h"
#include "template.h"
#include "protocol.h"
#include <unordered_map>
#include <vector>


class ScriptManager : public Singleton<ScriptManager> {
public:
    void DestroyPro()
    {
        for (auto &it : m_proMap)
            delete it.second;
    }

    void SetProName(char* data)
    {
        m_currPro = new Protocol(data);
        m_proMap[data] = m_currPro;
    }

    void push_int_param(struct IntInfo* intInfo)
    {
        m_currPro->push_int_param(intInfo);
    }

    void merge_params(int actionOp)
    {
        m_currPro->merge_params(actionOp);
    }

    void set_byte_field(char* name, char* show_name)
    {
        m_currPro->set_byte_field(name, show_name);
    }

    void push_field_action(int action)
    {
        m_currPro->push_field_action(action);
    }

    void set_field_actions(char* field_name)
    {
        m_currPro->set_field_actions(field_name);
    }

    void set_logic_expr(int op)
    {
        m_currPro->set_logic_expr(op);
    }

    void set_if_action()
    {
        m_currPro->set_if_action();
    }

private:
    std::unordered_map<std::string, Protocol*>          m_proMap;
    Protocol*                                           m_currPro;
};

void set_pro_name(char* data)
{
    ScriptManager::getInstance().SetProName(data);
}

void push_int_param(struct IntInfo* intInfo)
{
    ScriptManager::getInstance().push_int_param(intInfo);
}

void merge_params(int actionOp)
{
    ScriptManager::getInstance().merge_params(actionOp);
}

void set_byte_field(char* name, char* show_name)
{
    ScriptManager::getInstance().set_byte_field(name, show_name);
}

void push_field_action(int action)
{
    ScriptManager::getInstance().push_field_action(action);
}

void set_field_actions(char* field_name)
{
    ScriptManager::getInstance().set_field_actions(field_name);
}

void set_logic_expr(int op)
{
    ScriptManager::getInstance().set_logic_expr(op);
}

void set_if_action()
{
    ScriptManager::getInstance().set_if_action();
}
