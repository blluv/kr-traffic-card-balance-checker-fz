#include "app.h"
#include "scene.h"
#include "waiting_scene.h"
#include "card/tmoney.h"

void waiting_scene_on_enter(void* context) {
    App* app = context;

    widget_reset(app->widget);
    widget_add_string_element(app->widget, 64, 15, AlignCenter, AlignCenter, FontPrimary, "HELLO");

    view_dispatcher_switch_to_view(app->view_dispatcher, AppViewWaitingText);

    app->tx = bit_buffer_alloc(256);
    app->rx = bit_buffer_alloc(256);

    FURI_LOG_I("TC", "waiting_scene_on_enter");
    app->nfc = nfc_alloc();
    app->poller = nfc_poller_alloc(app->nfc, NfcProtocolIso14443_4a);
    nfc_poller_start(app->poller, waiting_scene_nfc_poller_callback, app);
}

void waiting_scene_on_exit(void* context) {
    App* app = context;
    widget_reset(app->widget);

    FURI_LOG_I("TC", "waiting_scene_on_exit");
    nfc_poller_stop(app->poller);
    nfc_poller_free(app->poller);
    nfc_free(app->nfc);
}

bool waiting_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == BalanceReadEvent) {
            scene_manager_next_scene(app->scene_manager, AppSceneResult);
            return true;
        }
    }
    return false;
}

NfcCommand waiting_scene_nfc_poller_callback(NfcGenericEvent event, void* context) {
    furi_assert(event.protocol == NfcProtocolIso14443_4a);

    App* app = context;
    Iso14443_4aPollerEvent* ev = event.event_data;

    if(ev->type == Iso14443_4aPollerEventTypeReady) {
        app->balance = tmoney(app);
        FURI_LOG_I("TC", "Balance: %ld", app->balance);
        view_dispatcher_send_custom_event(app->view_dispatcher, BalanceReadEvent);
        return NfcCommandStop;
    }

    return NfcCommandContinue;
}
