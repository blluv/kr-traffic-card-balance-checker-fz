#include "scene.h"

#include "waiting_scene.h"
#include "result_scene.h"

void (*const app_scene_on_enter_handlers[])(void*) = {
    waiting_scene_on_enter,
    result_scene_on_enter,
};

void (*const app_scene_on_exit_handlers[])(void*) = {
    waiting_scene_on_exit,
    result_scene_on_exit,
};

bool (*const app_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    waiting_scene_on_event,
    result_scene_on_event,
};

const SceneManagerHandlers app_scene_event_handlers = {
    .on_enter_handlers = app_scene_on_enter_handlers,
    .on_exit_handlers = app_scene_on_exit_handlers,
    .on_event_handlers = app_scene_on_event_handlers,
    .scene_num = AppSceneNum,
};
