#pragma once
#include <stdint.h>
// set script protocal name
#ifdef __cplusplus
extern "C" {
#endif

struct IntInfo {
    char*           field;
    uint64_t        value;
};

void set_pro_name(char* data);
void set_byte_field(char* name, char* show_name);
void push_int_param(struct IntInfo* intInfo);
void merge_params(int actionOp);
void push_field_action(int action);
void set_field_actions(char* field_name);
void set_logic_expr(int op);
void set_if_action();
#ifdef __cplusplus
}
#endif

