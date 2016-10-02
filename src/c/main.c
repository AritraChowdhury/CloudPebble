#include <pebble.h>

//Call in values
static ActionBarLayer *action_bar;
static GBitmap *s_icon_plus;

static Window *main_window;
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

static void click_handler(ClickRecognizerRef recognizer, void *context) {
  update_text();
}
static void click_config_provider(void *context) { 
  window_single_click_subscribe(BUTTON_ID_SELECT, click_handler);
}



static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  
  action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, s_icon_plus);
  
  header_layer = text_layer_create(GRect(4, PBL_IF_RECT_ELSE(0, 30), 145, 60));
  text_layer_set_font(header_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_background_color(header_layer, GColorClear);
  text_layer_set_text(header_layer, "Coin Toss");
  text_layer_set_text_alignment(header_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
  layer_add_child(window_layer, text_layer_get_layer(header_layer));

  main_layer = text_layer_create(GRect(4, PBL_IF_RECT_ELSE(44, 60), 145, 60));
  text_layer_set_font(main_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_background_color(main_layer, GColorClear);
  text_layer_set_text_alignment(main_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
  layer_add_child(window_layer, text_layer_get_layer(main_layer));
  
  update_text();
}

static void main_window_unload(Window *window) {
  text_layer_destroy(header_layer);
  text_layer_destroy(main_layer);
}



//Init and Deinit
static void init() {
  s_icon_plus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_ICON_PLUS);
  
  main_window = window_create();
  
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  window_stack_push(main_window, true);
}

static void deinit() {
  window_destroy(main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}