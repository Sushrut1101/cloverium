#include <gtk/gtk.h>
#include <gdk/gdk.h>

void open_startmenu() {
    system("build/menu"); 
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    /* Start menu opens when startmenu button is closed 
    but doesnt close when it's pressed for the second time */

    // Create a GtkWindow with no decorations
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    // Set window size
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 50);

    // Make the window the same width as the display
    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen);
    int height = gdk_screen_get_height(screen);
    gtk_window_resize(GTK_WINDOW(window), width, 50);

    // Move window to bottom of the screen
    gtk_window_move(GTK_WINDOW(window), 0, height - 50); 

    // Create a GtkFixed container to hold the image
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Set taskbar image
    GtkWidget *image1 = gtk_image_new_from_file("/home/anon/.comfy/panel.png");
    gtk_fixed_put(GTK_FIXED(fixed), image1, 0, 0);

    // Create the start menu button
    GtkWidget *startmenu_button = gtk_button_new();
    GtkWidget *image2 = gtk_image_new_from_file("assets/clover.png"); 
    gtk_button_set_image(GTK_BUTTON(startmenu_button), image2);
    gtk_fixed_put(GTK_FIXED(fixed), startmenu_button, 5, 0); // Move to the leftmost position
    g_signal_connect(startmenu_button, "clicked", G_CALLBACK(open_startmenu), NULL); 

    // Set the window as a top-level window (always on top)
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);

    // Show the window
    gtk_widget_show_all(window);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_main();

    return 0;
}
