#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h> 

void open_browser() {
    system("chromium &"); 
}

void open_file_manager() {
    system("thunar &"); 
}

void open_terminal() {
    system("xfce4-terminal");
}

void open_screen_settings() {
    system("xfce4-display-settings"); 
}

void open_appearance_settings() {
    system("lxappearance &"); 
}

void open_set_wallpaper() {
    system("build/settings"); 
}

void open_settings() {
    system("build/settings"); 
}

void open_dmenu() {
    system("dmenu_run"); 
}
void open_shutdown() {
    system("systemctl poweroff"); 
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Panel");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 720);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    GtkWidget *image = gtk_image_new_from_file("/home/anon/.comfy/menubg.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    
    //GtkWidget *image2 = gtk_image_new_from_file("assets/user.png");
    //gtk_fixed_put(GTK_FIXED(fixed), image2, 456, 56);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 13, 10);

    GtkWidget *create_button(const gchar *label, const gchar *icon_path) {
        GtkWidget *button = gtk_button_new();
        GtkWidget *label_widget = gtk_label_new(label);
        GtkWidget *icon_widget = gtk_image_new_from_file(icon_path);
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(hbox), icon_widget, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label_widget, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(button), hbox);
        return button;
    }

    GtkWidget *button1 = create_button("Web Browser", "assets/firefox.png");
    GtkWidget *button2 = create_button("File Manager", "assets/folder.png");
    GtkWidget *button3 = create_button("Terminal", "assets/terminal.png");
    GtkWidget *button4 = create_button("Screen Settings", "assets/settings.png");
    GtkWidget *button5 = create_button("Set Wallpaper", "assets/settings.png");
    GtkWidget *button6 = create_button("Search", "assets/search.png");
    GtkWidget *button7 = create_button("Shut Down", "assets/power.png");

    gtk_widget_set_size_request(button1, 375, 60);
    gtk_widget_set_size_request(button2, 200, 60);
    gtk_widget_set_size_request(button3, 200, 60);
    gtk_widget_set_size_request(button4, 200, 60);
    gtk_widget_set_size_request(button5, 200, 60);
    gtk_widget_set_size_request(button6, 200, 40);
    gtk_widget_set_size_request(button7, 100, 40);

    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button6, FALSE, FALSE, 290); 

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), hbox, 450, 650); 
    gtk_box_pack_start(GTK_BOX(hbox), button7, FALSE, FALSE, 0); 

    g_signal_connect(button1, "clicked", G_CALLBACK(open_browser), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(open_file_manager), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(open_terminal), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(open_screen_settings), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(open_set_wallpaper), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(open_dmenu), NULL);
    g_signal_connect(button7, "clicked", G_CALLBACK(open_shutdown), NULL);

    gtk_widget_show_all(window);

    GdkScreen *screen = gdk_screen_get_default();
    int screen_width = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);

    // Position the window at the bottom left corner with a 50px margin
    gtk_window_move(GTK_WINDOW(window), 3, screen_height - 720 - 50);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_main();

    return 0;
}
