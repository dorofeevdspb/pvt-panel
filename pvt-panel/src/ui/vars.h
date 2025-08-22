#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

typedef enum {
    UserRole_Guest = 0,
    UserRole_Member = 1,
    UserRole_Admin = 2
} UserRole;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_USER_IDX = 0,
    FLOW_GLOBAL_VARIABLE_USER_NAMES = 1,
    FLOW_GLOBAL_VARIABLE_USERS = 2
};

// Native global variables



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/