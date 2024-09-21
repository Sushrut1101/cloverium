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

    // Create a box to hold the image and buttons
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Create the image widget
    GtkWidget *image = gtk_image_new_from_file("/home/anon/.comfy/menubg.png");

    // Add widgets to the box
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    // Add the box to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Make the window visible (this will trigger realization and size calculation)
    gtk_widget_show_all(window);

    // Get the screen
    GdkScreen *screen = gdk_screen_get_default();

    // Get the screen's width and height
    int screen_width = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);

    // Get the window's actual height after realization
    int window_height = gtk_widget_get_allocated_height(window);

    // Set the window position to the bottom left corner, adjusted for the 50px margin
    gtk_window_move(GTK_WINDOW(window), 0, screen_height - window_height - 50);

    // Start the GTK+ event loop
    gtk_main();

    return 0;
}
