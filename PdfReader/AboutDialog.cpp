#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent):
	QDialog(parent), layout(new QVBoxLayout(this))
{
	QLabel* descriptionLabel = new QLabel("Trainee project: PDF Reader", this);
	layout->addWidget(descriptionLabel);
	setLayout(layout);
}
