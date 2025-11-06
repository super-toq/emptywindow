/*
 * toq 2025, LICENCE MIT
 *
 *
 */

#include <adwaita.h>

static void
on_activate (AdwApplication *app, gpointer user_data)
{
    // libadwaita will hier ein GtkApplication
    AdwApplicationWindow *win =
        ADW_APPLICATION_WINDOW (adw_application_window_new (GTK_APPLICATION (app)));

    gtk_window_set_title (GTK_WINDOW (win), "Leeres Fenster");
    gtk_window_set_default_size (GTK_WINDOW (win), 640, 360);
    gtk_window_present (GTK_WINDOW (win));
}

int
main (int argc, char **argv)
{
    g_autoptr (AdwApplication) app =
        adw_application_new ("free.toq.emptywindow", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

    return g_application_run (G_APPLICATION (app), argc, argv);
}
