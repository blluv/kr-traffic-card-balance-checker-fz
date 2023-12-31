#include "result_scene.h"
#include "app.h"

void result_scene_on_enter(void* context) {
    App* app = context;

    DialogEx* dialog = app->dialog;

    dialog_ex_set_context(dialog, app);
    dialog_ex_set_left_button_text(dialog, NULL);
    dialog_ex_set_right_button_text(dialog, NULL);
    dialog_ex_set_center_button_text(dialog, "OK");
    dialog_ex_set_header(dialog, "TMONEY CARD", 128 / 2, 20, AlignCenter, AlignCenter);
    snprintf(&app->text[0], sizeof(app->text), "%ld", app->balance);
    dialog_ex_set_text(dialog, app->text, 128 / 2, 35, AlignCenter, AlignCenter);
    dialog_ex_set_result_callback(dialog, result_scene_dialog_callback);

    view_dispatcher_switch_to_view(app->view_dispatcher, AppViewDialog);
}

void result_scene_on_exit(void* context) {
    UNUSED(context);
}

bool result_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == DialogExResultCenter) {
            return scene_manager_previous_scene(app->scene_manager);
        }
    }
    return false;
}

void result_scene_dialog_callback(DialogExResult result, void* context) {
    App* app = context;

    view_dispatcher_send_custom_event(app->view_dispatcher, result);
}
