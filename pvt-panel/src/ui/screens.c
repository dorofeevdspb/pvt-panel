#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_transfer_to_mode_status_(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_choose_mode_settings_preset_mode(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_variable_mode_settings_arrow_back_button_(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 12, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // transfer to mode status 
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.transfer_to_mode_status_ = obj;
            lv_obj_set_pos(obj, 205, 178);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_transfer_to_mode_status_, LV_EVENT_ALL, flowState);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 113, 113);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Mode\nSelection");
                }
            }
        }
        {
            // P_current
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.p_current = obj;
            lv_obj_set_pos(obj, 28, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "200");
        }
        {
            // SUMM_Time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.summ_time = obj;
            lv_obj_set_pos(obj, 160, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "4:40");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_choose_mode_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.choose_mode_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Mode Status
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mode_status = obj;
            lv_obj_set_pos(obj, 56, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Mode Status");
        }
        {
            // Alarm attention
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.alarm_attention = obj;
            lv_obj_set_pos(obj, 19, 27);
            lv_obj_set_size(obj, 18, 14);
            lv_led_set_color(obj, lv_color_hex(0xffc74428));
            lv_led_set_brightness(obj, 255);
        }
        {
            // current mode
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.current_mode = obj;
            lv_obj_set_pos(obj, 28, 79);
            lv_obj_set_size(obj, 56, 41);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_SCROLLED);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_SCROLLED);
                    lv_label_set_text(obj, "Current\nP1");
                }
            }
        }
        {
            // preset mode
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.preset_mode = obj;
            lv_obj_set_pos(obj, 114, 80);
            lv_obj_set_size(obj, 56, 41);
            lv_obj_add_event_cb(obj, event_handler_cb_choose_mode_settings_preset_mode, LV_EVENT_ALL, flowState);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Preset\nP2");
                }
            }
        }
        {
            // Timer
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.timer = obj;
            lv_obj_set_pos(obj, 225, 80);
            lv_obj_set_size(obj, 65, 41);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time");
                }
            }
        }
        {
            // Battery Indicator
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_indicator = obj;
            lv_obj_set_pos(obj, 280, 25);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // Sound indicator
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sound_indicator = obj;
            lv_obj_set_pos(obj, 257, 25);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // history journal button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.history_journal_button = obj;
            lv_obj_set_pos(obj, 267, 205);
            lv_obj_set_size(obj, 23, 20);
            add_style_carrie(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // history button
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.history_button = obj;
                    lv_obj_set_pos(obj, 4, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_choose_mode_settings();
}

void tick_screen_choose_mode_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
}

void create_screen_variable_mode_settings() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.variable_mode_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Variable mode settings page
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.variable_mode_settings_page = obj;
            lv_obj_set_pos(obj, 57, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Variable Mode settings");
        }
        {
            // Title Vacuum
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.title_vacuum = obj;
            lv_obj_set_pos(obj, 17, 31);
            lv_obj_set_size(obj, 138, 17);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Vacuum mmhg
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.vacuum_mmhg = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Vacuum, mmHg");
                }
            }
        }
        {
            // max P
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.max_p = obj;
            lv_obj_set_pos(obj, 33, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "max");
        }
        {
            // min P
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.min_p = obj;
            lv_obj_set_pos(obj, 109, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "min");
        }
        {
            // Title Time
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.title_time = obj;
            lv_obj_set_pos(obj, 176, 31);
            lv_obj_set_size(obj, 131, 16);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_carrie(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Time minutes
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_minutes = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time, minutes");
                }
            }
        }
        {
            // roller vacuum max
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_vacuum_max = obj;
            lv_obj_set_pos(obj, 17, 81);
            lv_obj_set_size(obj, 63, 125);
            lv_roller_set_options(obj, "199\n200\n201", LV_ROLLER_MODE_NORMAL);
            lv_roller_set_selected(obj, 1, LV_ANIM_OFF);
            lv_obj_set_style_transform_scale_x(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_scale_y(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // roller vacuum min
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_vacuum_min = obj;
            lv_obj_set_pos(obj, 92, 81);
            lv_obj_set_size(obj, 63, 125);
            lv_roller_set_options(obj, "49\n50\n51", LV_ROLLER_MODE_NORMAL);
            lv_roller_set_selected(obj, 1, LV_ANIM_OFF);
            lv_obj_set_style_transform_scale_x(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_scale_y(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // roller time max
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_time_max = obj;
            lv_obj_set_pos(obj, 176, 81);
            lv_obj_set_size(obj, 60, 125);
            lv_roller_set_options(obj, "11\n10\n9", LV_ROLLER_MODE_NORMAL);
            lv_roller_set_selected(obj, 1, LV_ANIM_OFF);
            lv_obj_set_style_transform_scale_x(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_scale_y(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // roller time min
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_time_min = obj;
            lv_obj_set_pos(obj, 245, 81);
            lv_obj_set_size(obj, 62, 125);
            lv_roller_set_options(obj, "3\n4\n5", LV_ROLLER_MODE_NORMAL);
            lv_roller_set_selected(obj, 1, LV_ANIM_OFF);
            lv_obj_set_style_transform_scale_x(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_scale_y(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff90d9f5), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // arrow back button 
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.arrow_back_button_ = obj;
            lv_obj_set_pos(obj, 17, 218);
            lv_obj_set_size(obj, 63, 18);
            lv_obj_add_event_cb(obj, event_handler_cb_variable_mode_settings_arrow_back_button_, LV_EVENT_ALL, flowState);
            add_style_carrie(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_EDITED);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Arrow back
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.arrow_back = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // Check mark button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.check_mark_button = obj;
            lv_obj_set_pos(obj, 248, 218);
            lv_obj_set_size(obj, 59, 18);
            add_style_carrie(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_EDITED);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // button Check mark
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button_check_mark = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // max P_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.max_p_1 = obj;
            lv_obj_set_pos(obj, 191, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "max");
        }
        {
            // min P_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.min_p_1 = obj;
            lv_obj_set_pos(obj, 257, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "min");
        }
    }
    
    tick_screen_variable_mode_settings();
}

void tick_screen_variable_mode_settings() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}

void create_screen_info() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.info = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    
    tick_screen_info();
}

void tick_screen_info() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}

void create_screen_load() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.load = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 71, 79);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MEDTECHNICS LLC");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 63, 140);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "www.medtechnics.ru");
        }
    }
    
    tick_screen_load();
}

void tick_screen_load() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Main", "Choose Mode settings", "Variable mode settings", "Info", "load" };
static const char *object_names[] = { "main", "choose_mode_settings", "variable_mode_settings", "info", "load", "transfer_to_mode_status_", "preset_mode", "arrow_back_button_", "obj0", "p_current", "summ_time", "mode_status", "alarm_attention", "current_mode", "obj1", "timer", "obj2", "battery_indicator", "sound_indicator", "history_journal_button", "history_button", "variable_mode_settings_page", "title_vacuum", "vacuum_mmhg", "max_p", "min_p", "title_time", "time_minutes", "roller_vacuum_max", "roller_vacuum_min", "roller_time_max", "roller_time_min", "arrow_back", "check_mark_button", "button_check_mark", "max_p_1", "min_p_1", "obj3", "obj4" };
static const char *style_names[] = { "carrie" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_choose_mode_settings,
    tick_screen_variable_mode_settings,
    tick_screen_info,
    tick_screen_load,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_choose_mode_settings();
    create_screen_variable_mode_settings();
    create_screen_info();
    create_screen_load();
}
