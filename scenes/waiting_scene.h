#ifndef WAITING_SCENE_H
#define WAITING_SCENE_H

#include <gui/scene_manager.h>
#include <lib/nfc/nfc.h>
#include <lib/nfc/protocols/nfc_generic_event.h>

void waiting_scene_on_enter(void* context);
void waiting_scene_on_exit(void* context);
bool waiting_scene_on_event(void* context, SceneManagerEvent event);

NfcCommand waiting_scene_nfc_poller_callback(NfcGenericEvent event, void* context);

#endif