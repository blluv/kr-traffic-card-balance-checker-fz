#include "app.h"
#include <gui/gui.h>

#include "scenes/scene.h"

App* app_alloc() {
    App* app = malloc(sizeof(App));

    app->scene_manager = scene_manager_alloc(&app_scene_event_handlers, app);
    app->view_dispatcher = view_dispatcher_alloc();

    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, app_custom_callback);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, app_back_event_callback);

    app->widget = widget_alloc();
    view_dispatcher_add_view(
        app->view_dispatcher, AppViewWaitingText, widget_get_view(app->widget));

    app->dialog = dialog_ex_alloc();
    view_dispatcher_add_view(app->view_dispatcher, AppViewDialog, dialog_ex_get_view(app->dialog));

    return app;
}

void app_free(App* app) {
    furi_assert(app);
    view_dispatcher_remove_view(app->view_dispatcher, AppViewDialog);
    view_dispatcher_remove_view(app->view_dispatcher, AppViewWaitingText);
    view_dispatcher_free(app->view_dispatcher);

    scene_manager_free(app->scene_manager);

    dialog_ex_free(app->dialog);
    widget_free(app->widget);
    free(app);
}

bool app_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

bool app_back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

int32_t kr_traffic_card_balance_app(void* p) {
    UNUSED(p);
    App* app = app_alloc();

    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(app->scene_manager, AppSceneWaiting);
    view_dispatcher_run(app->view_dispatcher);

    app_free(app);

    return 0;
}
