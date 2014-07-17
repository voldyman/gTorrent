#pragma once

#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <glibmm/property.h>
#include <core/Torrent.hpp>

// Gtk Torrent Columns Section

class GtkTorrentColumns : public Gtk::TreeModel::ColumnRecord
{
public:
	GtkTorrentColumns()
	{
		add(m_col_name);
		add(m_col_seeders);
		add(m_col_leechers);
		add(m_col_dl_speed);
		add(m_col_percent);
		add(m_col_percent_text);
	}
	
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<unsigned int> m_col_seeders;
	Gtk::TreeModelColumn<unsigned int> m_col_leechers;
	Gtk::TreeModelColumn<unsigned int> m_col_percent;
	Gtk::TreeModelColumn<Glib::ustring> m_col_percent_text;
	Gtk::TreeModelColumn<unsigned int> m_col_empty;
	Gtk::TreeModelColumn<Glib::ustring> m_col_dl_speed;
};

// Gtk Torrent Tree View Cell Renderer

class GtkTorrentCellRenderer : public Gtk::CellRenderer
{
  private:
    Glib::RefPtr<Gtk::CellRendererText> text_renderer;
    Glib::RefPtr<Gtk::CellRendererProgress> progress_renderer;
    Glib::RefPtr<Gtk::CellRendererPixbuf> icon_renderer;

    Glib::Property<Glib::ustring> m_name;
    Glib::Property<Glib::ustring> m_percent_text;
    Glib::Property<unsigned int> m_seeders;
    Glib::Property<unsigned int> m_leechers;
    Glib::Property<unsigned int> m_percent;
    Glib::Property<unsigned int> m_empty;

  public:
    GtkTorrentCellRenderer();

    unsigned int Padding;

    Glib::PropertyProxy<Glib::ustring> property_name();
    Glib::PropertyProxy<Glib::ustring> property_percent_text();
    Glib::PropertyProxy<unsigned int> property_seeders();
    Glib::PropertyProxy<unsigned int> property_leechers();
    Glib::PropertyProxy<unsigned int> property_percent();
    Glib::PropertyProxy<unsigned int> property_empty();

    void render(const Cairo::RefPtr<::Cairo::Context>& cr,
                Gtk::Widget& widget, const Gdk::Rectangle& background_area,
                const Gdk::Rectangle& cell_area, Gtk::CellRendererState flags);
};

// Gtk Torrent Tree View Section

class GtkTorrentTreeView : public Gtk::TreeView
{
private:
	GtkTorrentColumns m_cols;
	Glib::RefPtr<Gtk::ListStore> m_liststore;
	void setupColumns();
	
public:
	GtkTorrentTreeView();

	void addCell(shared_ptr<Torrent> &t);
	void updateCells();
};

