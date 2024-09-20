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

    // Make the window visible
    gtk_widget_show_all(window);

    // Start the GTK+ event loop
    gtk_main();

    return 0;
}
