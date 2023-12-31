#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include <stdbool.h>
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>

void result_scene_on_enter(void* context);
void result_scene_on_exit(void* context);
bool result_scene_on_event(void* context, SceneManagerEvent event);
void result_scene_dialog_callback(DialogExResult result, void* context);

#endif