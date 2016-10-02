#include <pebble.h>

//Call in values
static Window *window;
static TextLayer *main_layer, *header_layer;
int coin;

static void update_text() {
  coin = rand();
  
  static char coin_flip[18];
  
  if (coin%2 == 0) {
    snprintf(coin_flip, sizeof(coin_flip), "Heads");
    text_layer_set_text(main_layer, coin_flip);
  }
  else {
    snprintf(coin_flip, sizeof(coin_flip), "Tails");
    text_layer_set_text(main_layer, coin_flip);
  }

}

static void increment_click_handler(ClickRecognizerRef recognizer, void *context) {
  update_text();
}
static void click_config_provider(void *context) { 
  window_single_click_subscribe(BUTTON_ID_UP, increment_click_handler);
}





static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  header_layer = header_layer_create();

  update_text();
}

static void main_window_unload(Window *window) {

}



//Init and Deinit
static void init() {
  window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  window_stack_push(s_main_window, true);
}

static void deinit() {

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}