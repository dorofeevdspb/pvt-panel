#pragma once
// LVGL compatibility shims for EEZ-generated code against LVGL v9.x
// Do not include <lvgl.h> here; this header is force-included for all units.
// Provide forward declarations and lightweight overloads instead of macros.

#include <stdint.h>

// 1) Dropdown: LVGL 9 removed the anim parameter. Add a 3-arg C++ overload
// that forwards to the 2-arg C function. This does not affect C units.
#ifdef __cplusplus
extern "C" {
	struct _lv_obj_t;
	typedef struct _lv_obj_t lv_obj_t;
	void lv_dropdown_set_selected(lv_obj_t * obj, uint32_t sel_opt);
	lv_obj_t * lv_obj_create(lv_obj_t * parent);
}
static inline void lv_dropdown_set_selected(lv_obj_t * obj, uint32_t sel_opt, int /*anim_ignored*/) {
	lv_dropdown_set_selected(obj, sel_opt);
}
#endif

// 2) Lottie fallback: if the widget is disabled, map creation to base object.
// Works for both C and C++ (simple macro), but only when LV_USE_LOTTIE is off.
#if !(defined(LV_USE_LOTTIE) && (LV_USE_LOTTIE + 0))
#  ifndef lv_lottie_create
#    define lv_lottie_create(parent) lv_obj_create(parent)
#  endif
#endif
