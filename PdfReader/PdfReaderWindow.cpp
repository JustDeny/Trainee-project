#include "PdfReaderWindow.h"
#include <qmessagebox.h>
#include <iostream>

const qreal zoomMultiplier = qSqrt(2.0);

PdfReaderWindow::PdfReaderWindow(QWidget* parent)
    : QMainWindow(parent), m_document(new QPdfDocument(this)),
    central_widget(new QWidget(this)),
    splitter(new QSplitter(Qt::Horizontal, central_widget)),
    tool_bar(new QToolBar(this)),
    menu_bar(new QMenuBar(this)),
    m_zoomSelector(new ZoomSelector(this)),
    m_pageSelector(new QSpinBox(this)),
    tab_widget(new QTabWidget(this)),
    pdf_view_widget(new QPdfView()),
    h_layout(new QHBoxLayout(central_widget))
{
    resize(init_width, init_height);
    setCentralWidget(central_widget);
    central_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setupUI();
    pdf_view_widget->setDocument(m_document);
}

PdfReaderWindow::~PdfReaderWindow()
{
}

void PdfReaderWindow::setupUI()
{
    h_layout->addWidget(splitter); //kinda layout
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->resize(init_width, init_height);
    splitter->addWidget(tab_widget);
    splitter->addWidget(pdf_view_widget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    tab_widget->resize(257, 509);
    pdf_view_widget->resize(400, 519);

    //setting up menu bar
    menuBar()->setFixedHeight(27);
    file = menuBar()->addMenu("&File");
    QAction* open = new QAction("Open", file);
    QAction* quit = new QAction("Quit", file);
    file->addAction(open);
    file->addAction(quit);

    view = menuBar()->addMenu("&View");
    QAction* zoom_out = new QAction("Zoom Out", view);
    QAction* zoom_in = new QAction("Zoom In", view);
    QAction* prev_page = new QAction("Previous Page", view);
    QAction* next_page = new QAction("Next Page", view);

    QAction* continuous = new QAction("Continuous", view);
    view->addAction(zoom_in);
    view->addAction(zoom_out);
    view->addAction(prev_page);
    view->addAction(next_page);
    view->addAction(continuous);

    help = menuBar()->addMenu("&Help");
    QAction* about = new QAction("About", help);
    help->addAction(about);

    //connecting signals for menu bar
    connect(open, &QAction::triggered, this, &PdfReaderWindow::on_actionopen_triggered);
    connect(about, &QAction::triggered, this, &PdfReaderWindow::on_actionabout_triggered);
    connect(quit, &QAction::triggered, this, &QApplication::quit);


    //setting up toolbar
    tool_bar = addToolBar("main toolbar");
    tool_bar->setMovable(false);
    QAction* open_tool = tool_bar->addAction("Open File");
    open_tool->setIcon(QIcon("images/document-open.svgz"));
    tool_bar->addSeparator();
    QAction* zoom_out_tool = tool_bar->addAction("Zoom Out");
    zoom_out_tool->setIcon(QIcon("images/zoom-out.svgz"));
    tool_bar->addWidget(m_zoomSelector);
    QAction* zoom_in_tool = tool_bar->addAction("Zoom In");
    zoom_in_tool->setIcon(QIcon("images/zoom-in.svgz"));
    tool_bar->addSeparator();
    QAction* prev_page_tool = tool_bar->addAction("Previous Page");
    prev_page_tool->setIcon(QIcon("images/go-previous-view.svgz"));
    tool_bar->addWidget(m_pageSelector);
    QAction* next_page_tool = tool_bar->addAction("Next Page");
    next_page_tool->setIcon(QIcon("images/go-next-view.svgz"));


    //connecting signals for tool bar
    connect(open_tool, &QAction::triggered, this, &PdfReaderWindow::on_actionopen_triggered);
    connect(zoom_in_tool, &QAction::triggered, this, &PdfReaderWindow::on_actionzoom_in_triggered);
    connect(zoom_out_tool, &QAction::triggered, this, &PdfReaderWindow::on_actionzoom_out_triggered);
    connect(prev_page_tool, &QAction::triggered, this, &PdfReaderWindow::on_actionprevious_page_triggered);
    connect(next_page_tool, &QAction::triggered, this, &PdfReaderWindow::on_actionnext_page_triggered);

    //connecting signals for zoom selector
    connect(m_zoomSelector, &ZoomSelector::zoomModeChanged, pdf_view_widget, &QPdfView::setZoomMode);
    connect(m_zoomSelector, &ZoomSelector::zoomFactorChanged, pdf_view_widget, &QPdfView::setZoomFactor);
    m_zoomSelector->reset();
}

void PdfReaderWindow::open(const QUrl& docLocation)
{
    if (docLocation.isLocalFile()) {
        m_document->load(docLocation.toLocalFile());
        const auto documentTitle = m_document->metaData(QPdfDocument::MetaDataField::Title).toString();
        setWindowTitle(!documentTitle.isEmpty() ? documentTitle : QStringLiteral("PDF Viewer"));
        pageSelected(0);
        m_pageSelector->setMaximum(m_document->pageCount() - 1);
    }
    else {
        const QString message = tr("%1 is not a valid local file").arg(docLocation.toString());
        QMessageBox::critical(this, tr("Failed to open"), message);
    }

}

void PdfReaderWindow::bookmarkselected(const QModelIndex& index)
{
}

void PdfReaderWindow::pageSelected(int page)
{
    auto nav = pdf_view_widget->pageNavigator();
    nav->jump(page, {}, nav->currentZoom());
}

void PdfReaderWindow::on_actionopen_triggered()
{
    if (m_fileDialog == nullptr) {
        m_fileDialog = new QFileDialog(this, tr("Choose a PDF"),
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        m_fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
        m_fileDialog->setMimeTypeFilters({ "application/pdf" });
    }

    if (m_fileDialog->exec() == QDialog::Accepted) {
        const QUrl toOpen = m_fileDialog->selectedUrls().constFirst();
        if (toOpen.isValid())
            open(toOpen);
    }
}

void PdfReaderWindow::on_actionabout_triggered()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void PdfReaderWindow::on_actionzoom_in_triggered()
{
    pdf_view_widget->setZoomFactor(pdf_view_widget->zoomFactor() * zoomMultiplier);

}

void PdfReaderWindow::on_actionzoom_out_triggered()
{
    pdf_view_widget->setZoomFactor(pdf_view_widget->zoomFactor() / zoomMultiplier);
}

void PdfReaderWindow::on_actionprevious_page_triggered()
{
    auto nav = pdf_view_widget->pageNavigator();
    nav->jump(nav->currentPage() - 1, {}, nav->currentZoom());
}

void PdfReaderWindow::on_actionnext_page_triggered()
{
    auto nav = pdf_view_widget->pageNavigator();
    nav->jump(nav->currentPage() + 1, {}, nav->currentZoom());
}