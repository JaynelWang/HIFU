#include "DioPortUI.h"

DioPortUI::DioPortUI(QWidget *parent, Qt::WFlags flags, int index, quint8 state, QString* images)
	: QWidget(parent, flags)
{
	this->key = index;
	this->state = state;
	this->images = images;
	this->mask = 0;
	this->isEditable = false;

	QSize size(340, 40);
	this->setFixedSize(size);

	this->layout = new QHBoxLayout(this);
	this->layout->setContentsMargins(1, 1, 1, 1);
	this->layout->setSpacing(1);

	this->portNum = new QLineEdit(this);
	QSize sizePortNum(23, 23);
	this->portNum->setFixedSize(sizePortNum);
	this->portNum->setAlignment(Qt::AlignHCenter);
	this->portNum->setReadOnly(true);
	this->portNum->setText(QString("%1").arg(key));
	this->layout->addWidget(this->portNum);

	this->buttonGroup = new QButtonGroup();
	QSize sizeButton(30, 30);

	this->group1 = new QGroupBox(this);
	QSize sizeGroup1(130, 35);
	this->group1->setFixedSize(sizeGroup1);
	this->layout1 = new QHBoxLayout(this->group1);
	this->layout1->setContentsMargins(1, 1, 1, 1);
	this->layout1->setSpacing(1);

	this->group2 = new QGroupBox(this);
	QSize sizeGroup2(130, 35);
	this->group2->setFixedSize(sizeGroup2);
	this->layout2 = new QHBoxLayout(this->group2);
	this->layout2->setContentsMargins(1, 1, 1, 1);
	this->layout2->setSpacing(1);

	for ( int i = 0; i < 4; i++) {
		buttons[i] = new QPushButton(this->group1);
		buttons[i]->setFixedSize(sizeButton);
		buttons[i]->setFlat(true);
		buttons[i]->setStyleSheet(images[(state >> 7- i) & 0x1]);
		this->layout1->addWidget(buttons[i]);
		this->buttonGroup->addButton(buttons[i], i);

		buttons[i + 4] = new QPushButton(this->group2);
		buttons[i + 4]->setFixedSize(sizeButton);
		buttons[i + 4]->setFlat(true);
		buttons[i + 4]->setStyleSheet(images[(state >> 3 -i) & 0x1]);
		this->layout2->addWidget(buttons[i + 4]);
		this->buttonGroup->addButton(buttons[i + 4], i + 4);
	}
	this->buttonGroup->setExclusive(false);

	this->layout->addWidget(this->group1);
	this->layout->addWidget(this->group2);

	this->portValue = new QLineEdit(this);
	QSize sizePortValue(23, 23);
	this->portValue->setFixedSize(sizePortValue);
	this->portValue->setAlignment(Qt::AlignHCenter);
	this->portValue->setReadOnly(true);
	this->layout->addWidget(this->portValue);

	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(ButtonClicked(int)));
}

DioPortUI::~DioPortUI()
{
	for (int i = 0; i < 8; i++) {
		if (buttons[i] != NULL) {
			delete buttons[i];
			buttons[i] = NULL;
		}
	}

	if (this->buttonGroup != NULL) {
		delete buttonGroup;
		this->buttonGroup = NULL;
	}

	if (this->layout1 != NULL) {
		delete layout1;
		this->layout1 = NULL;
	}

	if (this->layout2 != NULL) {
		delete layout;
		this->layout2 = NULL;
	}

	if (this->group1 != NULL) {
		delete group1;
		this->group1 = NULL;
	}

	if (this->group2 != NULL) {
		delete group2;
		this->group2 = NULL;
	}

	if (this->portNum != NULL) {
		delete portNum;
		this->portNum = NULL;
	}

	if (this->portValue != NULL) {
		delete portValue;
		this->portValue = NULL;
	}

	if (this->layout != NULL) {
		this->layout = NULL;
	}
}

int DioPortUI::getKey() {
	return this->key;
}

quint8 DioPortUI::getMask() {
	return this->mask;
}

void DioPortUI::setMask(quint8 value) {
	this->mask = value;
}

quint8 DioPortUI::getState() {
	return this->state;
}

void DioPortUI::setState(quint8 state) {
	this->state = state;
	Refresh();
}

bool DioPortUI::getIsEditable() {
	return this->isEditable;
}

void DioPortUI::setIsEditable(bool value) {
	this->isEditable = value;
}

void DioPortUI::Refresh() {
	this->portNum->setText(QString("%1").arg(this->key));

	int bitValue = 0;
	for (int i = 7; i >= 0; i--) {
		bitValue = (state >> (7 - i)) & 0x1;
		this->buttons[i]->setStyleSheet(images[bitValue]);		
	}
	
	portValue->setText(QString::number(state | 0xFFFFFF00, 16).toUpper().right(2));
}

void DioPortUI::JudgeDirection(quint8 portDirection) {
	int bitValue = 0;
	this->mask = portDirection;
	
	for(int i = 7; i >= 0; i--){
		bitValue = (portDirection >> 7 - i) & 0x1;
		if(bitValue == 0){
			this->buttons[i]->setStyleSheet(images[2]);
			this->buttons[i]->setEnabled(false);
		} else {
			this->buttons[i]->setEnabled(true);
		}
	}

	this->portValue->setText(QString::number((mask & state) | 0xFFFFFF00, 16).toUpper().right(2));
}

void DioPortUI::ButtonClicked(int id) {
	if (this->isEditable) {
		if ((mask >> 7 - id & 0x1) == 1) {
			if ((state >> 7 - id & 0x1) == 1) {
				state = (quint8) (state & ~(0x1 << 7 - id));
				this->buttons[id]->setStyleSheet(images[0]);

			} else {
				state = (quint8) (state | (0x1 << 7 - id));
				this->buttons[id]->setStyleSheet(images[1]);
			}
			this->portValue->setText(QString::number(state | 0xFFFFFF00, 16).toUpper().right(2));
		}

		emit stateChanged(this);
	}
}
