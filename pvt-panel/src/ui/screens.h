#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *choose_mode_settings;
    lv_obj_t *variable_mode_settings;
    lv_obj_t *transfer_to_mode_status_;
    lv_obj_t *preset_mode;
    lv_obj_t *arrow_back_button_;
    lv_obj_t *obj0;
    lv_obj_t *mode_status;
    lv_obj_t *alarm_attention;
    lv_obj_t *current_mode;
    lv_obj_t *obj1;
    lv_obj_t *timer;
    lv_obj_t *obj2;
    lv_obj_t *battery_indicator;
    lv_obj_t *sound_indicator;
    lv_obj_t *history_journal_button;
    lv_obj_t *history_button;
    lv_obj_t *variable_mode_settings_page;
    lv_obj_t *title_vacuum;
    lv_obj_t *vacuum_mmhg;
    lv_obj_t *max_p;
    lv_obj_t *min_p;
    lv_obj_t *title_time;
    lv_obj_t *time_minutes;
    lv_obj_t *roller_vacuum_max;
    lv_obj_t *roller_vacuum_min;
    lv_obj_t *roller_time_max;
    lv_obj_t *roller_time_min;
    lv_obj_t *arrow_back;
    lv_obj_t *check_mark_button;
    lv_obj_t *button_check_mark;
    lv_obj_t *max_p_1;
    lv_obj_t *min_p_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CHOOSE_MODE_SETTINGS = 2,
    SCREEN_ID_VARIABLE_MODE_SETTINGS = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_choose_mode_settings();
void tick_screen_choose_mode_settings();

void create_screen_variable_mode_settings();
void tick_screen_variable_mode_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/