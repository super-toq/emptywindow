/*
 * toq 2025, LICENCE MIT
 *
 *
 */

#include <adwaita.h>

static void
on_activate (AdwApplication *app, gpointer user_data) //Callback-Funktion wird aufgerufen wenn Anw. aktiviert wird
{
    // libadwaita will hier eine GtkApplication
    AdwApplicationWindow *win =
        ADW_APPLICATION_WINDOW (adw_application_window_new (GTK_APPLICATION (app))); //Adwaita-Fenster wird erstellt

    gtk_window_set_title (GTK_WINDOW (win), "Leeres Fenster"); // Fenstertitel
    gtk_window_set_default_size (GTK_WINDOW (win), 640, 360);  // Standard-Fenstergröße
    gtk_window_present (GTK_WINDOW (win));                     // Fenster anzeigen lassen
}

/* ---------------------------------------------------------------------------
 * Anwendungshauptteil, main()
 * --------------------------------------------------------------------------- */
int
main (int argc, char **argv)
{
    g_autoptr (AdwApplication) app =  // Instanz erstellen, mit App-ID und Default-Flags
        adw_application_new ("free.toq.emptywindow", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL); // Signal mit on_activate verbinden

    return g_application_run (G_APPLICATION (app), argc, argv); // g_application_run startet Anw. u. wartet auf Ereignis
}
