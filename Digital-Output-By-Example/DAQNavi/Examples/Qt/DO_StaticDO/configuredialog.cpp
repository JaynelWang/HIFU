#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>

ConfigureDialog::ConfigureDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
	
	Initailization();
}

ConfigureDialog::~ConfigureDialog()
{
	
}

void ConfigureDialog::Initailization()
{
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
    ICollection<DeviceTreeNode> *supportedDevices = instantDoCtrl -> getSupportedDevices();

	if (supportedDevices->getCount() == 0)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	} else {
		for (int i = 0; i < supportedDevices->getCount(); i++) {
			DeviceTreeNode const &node = supportedDevices->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);	
	}
	instantDoCtrl->Dispose();
	supportedDevices->Dispose();
}

void ConfigureDialog::CheckError(ErrorCode errorCode)
{
	if (errorCode != Success) {
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

	std::wstring description = ui.cmbDevice->currentText().toStdWString();
	DeviceInformation selected(description.c_str());
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();

	ErrorCode errorCode = instantDoCtrl->setSelectedDevice(selected);
	if (errorCode != Success) {
		QString str;
		QString des = QString::fromStdWString(description);
		str.sprintf("Error:the error code is 0x%x\nThe %s is busy or not exit in computer now.\nSelect other device please!", errorCode, des.toUtf8().data());
		QMessageBox::information(this, "Warning Information", str);
		return;
	}

	configure.deviceName = ui.cmbDevice->currentText();

	instantDoCtrl->Dispose();
	this->accept();
}

void ConfigureDialog::ButtonCancelClicked()
{
	this->reject();
}
