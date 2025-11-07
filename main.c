/*
 * toq 2025, LICENSE: MIT
 *
 * gcc $(pkg-config --cflags gtk4 libadwaita-1) -o window main.c $(pkg-config --libs gtk4 libadwaita-1) 
 */

#include <adwaita.h>


static void on_button_clicked (GtkButton *button, gpointer)
{
    g_print ("Button clicked\n");
}
/* -------------------------------------------------------------------------------- */
/* ---------- Callback-Funktion wird aufgerufen wenn Anw. aktiviert wird ---------- */
static void
on_activate (AdwApplication *app, gpointer)
{
    /* ----- Adwaita-Fenster wird erstellt und als "win" gespeichert -------------------------- */
    AdwApplicationWindow *win = ADW_APPLICATION_WINDOW (adw_application_window_new (GTK_APPLICATION (app))); 

    gtk_window_set_title (GTK_WINDOW(win), "empty window");   // Fenstertitel
    gtk_window_set_default_size (GTK_WINDOW(win), 640, 400);  // Standard-Fenstergröße
    gtk_window_present (GTK_WINDOW(win));                     // Fenster anzeigen lassen

    /* ----- ToolbarView (als Root‑Widget) erstellt und als Inhalt des Fensters festgelegt ---- */
    AdwToolbarView *toolbar_view = ADW_TOOLBAR_VIEW (adw_toolbar_view_new ());
    adw_application_window_set_content (win, GTK_WIDGET (toolbar_view));

    /* ----- HeaderBar mit TitelWidget erstellt und dem ToolbarView hinzugefügt -------------- */
    AdwHeaderBar *header = ADW_HEADER_BAR (adw_header_bar_new());
    adw_header_bar_set_title_widget (header, gtk_label_new("My First Window"));
    adw_toolbar_view_add_top_bar (toolbar_view, GTK_WIDGET (header));

    /* ---- Haupt‑Box erstellen ------------------------------------------------------------- */
    GtkBox *box = GTK_BOX (gtk_box_new (GTK_ORIENTATION_VERTICAL, 12));
    gtk_widget_set_margin_top    (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_bottom (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_start  (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_end    (GTK_WIDGET (box), 20);
    gtk_widget_set_hexpand (GTK_WIDGET (box), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (box), TRUE);

    /* ----- Text-Label erstellen  ----- */
    GtkWidget *label = gtk_label_new("~ libadwaita ~");
    gtk_widget_set_halign (label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (label, GTK_ALIGN_CENTER);

    /* ----- Label als Inhalt zur hinzufügen ----- */ 
    gtk_box_append (box, label);
    //adw_toolbar_view_set_content (toolbar_view, label);

    /* ----- Schaltfläche erzeugen ----- */
    GtkWidget *first_btn = gtk_button_new_with_label("button");
    gtk_widget_set_halign(first_btn, GTK_ALIGN_CENTER);
    g_signal_connect(first_btn, "clicked", G_CALLBACK(on_button_clicked), app); // Funktion auslösen

    /* ----- Schaltfläche der Box hinzufügen ----- */
    gtk_box_append(box, first_btn);

    /* -----  Box zur ToolbarView hinzufügen ------------ */
    adw_toolbar_view_set_content(toolbar_view, GTK_WIDGET(box));

    /* ----- Fenster desktop‑konform anzeigen lassen ----- */
    gtk_window_present(GTK_WINDOW(win));

}

/* ---------------------------------------------------------------------------
 * Anwendungshauptteil, main()
 * --------------------------------------------------------------------------- */
int main (int argc, char **argv)
{
    g_autoptr (AdwApplication) app =                        // Instanz erstellen, mit App-ID und Default-Flags
        adw_application_new ("free.toq.window", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL); // Signal mit on_activate verbinden

    return g_application_run (G_APPLICATION (app), argc, argv); // g_application_run startet Anw. u. wartet auf Ereignis
}