#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/treeviewcolumn.h>
#include "GtkTorrentTreeView.hpp"
#include <Application.hpp>

GtkTorrentTreeView::GtkTorrentTreeView()
{
	m_liststore = Gtk::ListStore::create(m_cols);
	this->set_model(m_liststore);
	this->setupColumns();
}

void GtkTorrentTreeView::setupColumns()
{
    Gtk::TreeViewColumn *col = Gtk::manage(new Gtk::TreeViewColumn());
	this->append_column(*col);

	GtkTorrentCellRenderer *cell = Gtk::manage(new GtkTorrentCellRenderer());
    col->pack_start(*cell);

    col->add_attribute(*cell, "name", 0);
    col->add_attribute(*cell, "percent-text", 1);
    col->add_attribute(*cell, "seeders", 2);

	for (auto &c : this->get_columns()) {
		c->set_sizing(Gtk::TreeViewColumnSizing::TREE_VIEW_COLUMN_FIXED);
		c->set_clickable();
		c->set_resizable();
		c->set_reorderable();
	}
}

void GtkTorrentTreeView::addCell(shared_ptr<Torrent> &t)
{
	if (t == NULL)
		return;

	Gtk::TreeModel::Row row = *(m_liststore->append());
	row[m_cols.m_col_name] = t->getHandle().name();
	row[m_cols.m_col_percent] = t->getTotalProgress();
	row[m_cols.m_col_percent_text] = t->getTextState();
	row[m_cols.m_col_seeders] = t->getTotalSeeders();
	row[m_cols.m_col_leechers] = t->getTotalLeechers();
}

void GtkTorrentTreeView::updateCells()
{
	unsigned int i = 0;

	for (auto &c : m_liststore->children()) {
		shared_ptr<Torrent> t = Application::getSingleton()->getCore()->getTorrents()[i];

		c[m_cols.m_col_percent] = t->getTotalProgress();
		c[m_cols.m_col_seeders] = t->getTotalSeeders();
		c[m_cols.m_col_percent_text] = t->getTextState();
		c[m_cols.m_col_leechers] = t->getTotalLeechers();
		c[m_cols.m_col_dl_speed] = t->getTextDownloadRate();
		
		// TODO: Handle with events

		//m_cells[i]->property_text() = t->getTextState();

		++i;
	}
}

GtkTorrentCellRenderer::GtkTorrentCellRenderer() :
  Glib::ObjectBase(typeid(GtkTorrentCellRenderer)),
  Gtk::CellRenderer(),
  m_name(*this, "name"),
  m_percent_text(*this, "percent-text"),
  m_seeders(*this, "seeders"),
  m_leechers(*this, "leechers"),
  m_percent(*this, "percent"),
  m_empty(*this, "empty")
{
  text_renderer = Glib::RefPtr<Gtk::CellRendererText>(new Gtk::CellRendererText());
  progress_renderer = Glib::RefPtr<Gtk::CellRendererProgress>(new Gtk::CellRendererProgress());
  icon_renderer = Glib::RefPtr<Gtk::CellRendererPixbuf>(new Gtk::CellRendererPixbuf());
}

void GtkTorrentCellRenderer::render(const Cairo::RefPtr<::Cairo::Context >& cr,
                                    Gtk::Widget& widget, const Gdk::Rectangle& background_area,
                                    const Gdk::Rectangle& cell_area, Gtk::CellRendererState flags)
{
  //text_renderer->property_text().set_value(name().get_value());
  text_renderer->render(cr, widget,  background_area, cell_area, flags);
}

Glib::PropertyProxy<Glib::ustring>
GtkTorrentCellRenderer::property_name()
{
  return m_name.get_proxy();
}

Glib::PropertyProxy<Glib::ustring>
GtkTorrentCellRenderer::property_percent_text()
{
    return m_percent_text.get_proxy();
}

Glib::PropertyProxy<unsigned int>
GtkTorrentCellRenderer::property_seeders()
{
    return m_seeders.get_proxy();
}

Glib::PropertyProxy<unsigned int>
GtkTorrentCellRenderer::property_leechers()
{
    return m_leechers.get_proxy();
}

Glib::PropertyProxy<unsigned int>
GtkTorrentCellRenderer::property_percent()
{
    return m_percent.get_proxy();
}

Glib::PropertyProxy<unsigned int>
GtkTorrentCellRenderer::property_empty()
{
    return m_empty.get_proxy();
}
