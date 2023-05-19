#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class AboutDialog:public QDialog
{
	Q_OBJECT
private:
	QVBoxLayout* layout;
public:
	explicit AboutDialog(QWidget* parent = nullptr);
};

