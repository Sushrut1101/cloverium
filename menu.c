#include <gtk/gtk.h>
#include <gdk/gdk.h>

int main(int argc, char *argv[]) {
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Panel");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    // Set window size
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 720);

    // Create a fixed container
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Load an image and set it as a background
    GtkWidget *image = gtk_image_new_from_file("/home/anon/.comfy/menubg.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    // Create a vertical box to hold the buttons
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 13, 10); // Position the box at the top-left

    // Create the buttons
    GtkWidget *button1 = gtk_button_new_with_label("Button 1");
    GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    GtkWidget *button3 = gtk_button_new_with_label("Button 3");
    GtkWidget *button4 = gtk_button_new_with_label("Button 4");
    GtkWidget *button5 = gtk_button_new_with_label("Button 5");
    GtkWidget *button6 = gtk_button_new_with_label("Button 6");

    // Add the buttons to the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button6, FALSE, FALSE, 0);

    // Make the window visible
    gtk_widget_show_all(window);

    // Get the screen
    GdkScreen *screen = gdk_screen_get_default();

    // Get the screen's width and height
    int screen_width = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);

    // Set the window position to the bottom left corner, adjusted for the 50px margin
    gtk_window_move(GTK_WINDOW(window), 3, screen_height - 640 - 130);

    // Load CSS stylesheet
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Start the GTK+ event loop
    gtk_main();

    return 0;
}
