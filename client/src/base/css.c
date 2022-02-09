#include "client.h"

void Css_include_auth(GtkWidget *authorization_layout, GtkWidget *image, GtkWidget *button_log, GtkWidget *button_reg, GtkWidget *forg_password,
                   GtkWidget *label_login, GtkWidget *label_password, GtkWidget *label_cookiechat, GtkWidget *label_authorization){
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector

  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(authorization_layout);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "box_authorization");

  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(authorization_log_pass.login);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "entry_login");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(authorization_log_pass.password);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "entry_password");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(image);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "image");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(button_log);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "button_log");

  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(button_reg);
  gtk_style_context_add_provider(context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6, "button_reg");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(forg_password);
  gtk_style_context_add_provider(context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7, "forg_password");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(label_login);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "label_login");

  GtkStyleContext *context9;  
  context9 = gtk_widget_get_style_context(label_password);
  gtk_style_context_add_provider(context9, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context9, "label_password");

  GtkStyleContext *context10;  
  context10 = gtk_widget_get_style_context(label_cookiechat);
  gtk_style_context_add_provider(context10, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context10, "label_cookiechat");

  GtkStyleContext *context11;  
  context11 = gtk_widget_get_style_context(label_authorization);
  gtk_style_context_add_provider(context11, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context11, "label_authorization");

  GtkStyleContext *context12;  
  context12 = gtk_widget_get_style_context(authorization_log_pass.Error_message);
  gtk_style_context_add_provider(context12, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context12, "label_error_auth");
}

void Css_include_reg(GtkWidget *label_login, GtkWidget *label_password, GtkWidget *label_repeat_password, GtkWidget *label_nickname, GtkWidget *label_secret_word, GtkWidget *label_registration, GtkWidget *apply_btn) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(label_login);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "label_login");

  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(label_password);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "label_password");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(label_repeat_password);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "label_repeat_password");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(label_nickname);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "label_nickname");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(label_secret_word);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "label_secret_word");

  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(label_registration);
  gtk_style_context_add_provider(context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6, "label_registration");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(apply_btn);
  gtk_style_context_add_provider(context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7, "apply_btn");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(widgets_registration.entry_login);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "entry_login");

  GtkStyleContext *context9;
  context9 = gtk_widget_get_style_context(widgets_registration.entry_password);
  gtk_style_context_add_provider(context9, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context9, "entry_password");

  GtkStyleContext *context10;
  context10 = gtk_widget_get_style_context(widgets_registration.entry_repeat_password);
  gtk_style_context_add_provider(context10, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context10, "entry_repeat_password");

  GtkStyleContext *context11;
  context11 = gtk_widget_get_style_context(widgets_registration.entry_nickname);
  gtk_style_context_add_provider(context11, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context11, "entry_nickname");

  GtkStyleContext *context12;
  context12 = gtk_widget_get_style_context(widgets_registration.entry_secret_word);
  gtk_style_context_add_provider(context12, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context12, "entry_secret_word");

  GtkStyleContext *context13;
  context13 = gtk_widget_get_style_context(widgets_registration.label_error_login);
  gtk_style_context_add_provider(context13, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context13, "label_error_login");

  GtkStyleContext *context14;
  context14 = gtk_widget_get_style_context(widgets_registration.label_error_secret_word);
  gtk_style_context_add_provider(context14, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context14, "label_error_sw");

  GtkStyleContext *context15;
  context15 = gtk_widget_get_style_context(widgets_registration.label_error_password);
  gtk_style_context_add_provider(context15, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context15, "label_error_password");

   GtkStyleContext *context16;
  context16 = gtk_widget_get_style_context(widgets_registration.label_error_repeat_password);
  gtk_style_context_add_provider(context16, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context16, "label_error_repeat_password");

  GtkStyleContext *context17;
  context17 = gtk_widget_get_style_context(widgets_registration.label_error_nickname);
  gtk_style_context_add_provider(context17, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context17, "label_error_nickname");
}

void Css_include_SW(GtkWidget *authorization_layout, GtkWidget *label_login, GtkWidget *label_secret_word, GtkWidget *label_recovery, GtkWidget *apply_btn) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(label_login);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "label_login");
  
  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(label_secret_word);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "label_secret_word");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(label_recovery);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "label_recovery");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(apply_btn);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "apply_btn");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(widgets_forgot_password.entry_login);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "entry_login");

  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(widgets_forgot_password.entry_secret_word);
  gtk_style_context_add_provider(context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6, "entry_secret_word");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(widgets_forgot_password.label_error_login);
  gtk_style_context_add_provider(context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7, "label_error_login");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(widgets_forgot_password.label_error_SW);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "label_error_sw");

  GtkStyleContext *context9;
  context9 = gtk_widget_get_style_context(authorization_layout);
  gtk_style_context_add_provider(context9, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context9, "box_authorization");

}

void Css_include_change_password(GtkWidget *label_password, GtkWidget *label_repeat_password, GtkWidget *create_new_pass, GtkWidget *apply_btn) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(label_password);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "label_password");
  
  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(label_repeat_password);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "label_repeat_password");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(create_new_pass);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "create_new_pass");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(apply_btn);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "apply_btn");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(widgets_forgot_password.entry_password);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "entry_password");

  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(widgets_forgot_password.entry_repeat_password);
  gtk_style_context_add_provider(context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6, "entry_repeat_password");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(widgets_forgot_password.label_error_password);
  gtk_style_context_add_provider(context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7, "label_error_password");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(widgets_forgot_password.label_error_repeat_password);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "label_error_repeat_password");
}

void css_include_window_chat(GtkWidget *bottom_panel2, GtkWidget *bottom_entry) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(bottom_panel2);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "bottom_panel2");

  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(bottom_entry);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "bottom_entry");
}

void css_include_window_left(GtkWidget *bottom_panel, GtkWidget *bottom_button1, GtkWidget *bottom_button2, GtkWidget *bottom_button3, GtkWidget *top_searching) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(bottom_panel);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "bottom_panel");
  
  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(bottom_button1);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "bottom_button1");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(bottom_button2);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "bottom_button2");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(bottom_button3);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "bottom_button3");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(top_searching);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "top_searching");
}

void css_include_start_window_chat(GtkWidget *start_message, GtkWidget *chat_box) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(start_message);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "start_message");

   GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(chat_box);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "start_chat_layout");

}

void css_include_window_setting(GtkWidget *save_changes, GtkWidget *label_setting, GtkWidget *label_nickname, GtkWidget *entry_nickname, GtkWidget *label_login, GtkWidget *entry_login, 
      GtkWidget *button_change_password, GtkWidget *button_change_avatar, GtkWidget *button_log_outs) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(label_setting);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "label_setting");
  
  GtkStyleContext *context2;
  context2 = gtk_widget_get_style_context(label_nickname);
  gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context2, "label_nickname");

  GtkStyleContext *context3;
  context3 = gtk_widget_get_style_context(entry_nickname);
  gtk_style_context_add_provider(context3, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context3, "entry_nickname");

  GtkStyleContext *context4;
  context4 = gtk_widget_get_style_context(label_login);
  gtk_style_context_add_provider(context4, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context4, "label_login");

  GtkStyleContext *context5;
  context5 = gtk_widget_get_style_context(entry_login);
  gtk_style_context_add_provider(context5, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context5, "entry_login");

  GtkStyleContext *context6;
  context6 = gtk_widget_get_style_context(button_change_password);
  gtk_style_context_add_provider(context6, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context6, "button_change_password");

  GtkStyleContext *context7;
  context7 = gtk_widget_get_style_context(button_change_avatar);
  gtk_style_context_add_provider(context7, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context7, "button_change_avatar");

  GtkStyleContext *context8;
  context8 = gtk_widget_get_style_context(button_log_outs);
  gtk_style_context_add_provider(context8, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context8, "button_log_outs");

  GtkStyleContext *context9;
  context9 = gtk_widget_get_style_context(save_changes);
  gtk_style_context_add_provider(context9, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context9, "save_changes");

  GtkStyleContext *context10;
  context10 = gtk_widget_get_style_context(widgets_registration.label_error_nickname);
  gtk_style_context_add_provider(context10, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context10, "label_error_nickname");

  GtkStyleContext *context11;
  context11 = gtk_widget_get_style_context(widgets_registration.label_error_login);
  gtk_style_context_add_provider(context11, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context11, "label_error_login");
}

void css_button_contacts(GtkWidget *contact_button) {
  //css link
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "client/src/theme.css", NULL);

  //css add selector
  GtkStyleContext *context1;
  context1 = gtk_widget_get_style_context(contact_button);
  gtk_style_context_add_provider(context1, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_style_context_add_class(context1, "contact_button");
}
