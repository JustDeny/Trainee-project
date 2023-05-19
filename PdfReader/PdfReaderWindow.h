#pragma once

#include <QtWidgets/QMainWindow>
#include "QtPdf/qpdfdocument.h"
#include "QtPdf/qpdfselection.h"
#include "QtPdfWidgets/QPdfView"
#include "qsplitter.h"
#include "ZoomSelector.h"
#include <memory>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include "AboutDialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QtPdf/qpdfpagenavigator.h>



class PdfReaderWindow : public QMainWindow
{
public:
    PdfReaderWindow(QWidget *parent = nullptr);
    ~PdfReaderWindow();
private:
    int init_width = 800;
    int init_height = 600;
    
    QPdfDocument* m_document;
    QWidget* central_widget;
    QSplitter* splitter;
    QPdfView* pdf_view_widget;
    QTabWidget* tab_widget;
    QToolBar* tool_bar;
    QMenuBar* menu_bar;
    ZoomSelector* m_zoomSelector;
    QSpinBox* m_pageSelector;
    QHBoxLayout* h_layout;
    QFileDialog* m_fileDialog = nullptr;

    //menu bar components
    QMenu* file;
    QMenu* view;
    QMenu* help;
    
    void setupUI();
public slots:
    void open(const QUrl& docLocation);

private slots:
    void bookmarkselected(const QModelIndex& index);
    void pageSelected(int page);
    
    // action handlers
    void on_actionopen_triggered();
    void on_actionabout_triggered();
    void on_actionzoom_in_triggered();
    void on_actionzoom_out_triggered();
    void on_actionprevious_page_triggered();
    void on_actionnext_page_triggered();
    void on_actioncontinuous_triggered();
};
