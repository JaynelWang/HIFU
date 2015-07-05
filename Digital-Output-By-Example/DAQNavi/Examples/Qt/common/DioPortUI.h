#ifndef DIOPORTUI_H
#define DIOPORTUI_H

#include <QtGui>

class DioPortUI : public QWidget
{
	Q_OBJECT

public:
    DioPortUI(QWidget *parent = 0, Qt::WFlags flags = 0, int index = 0, quint8 state = 0, QString* images = 0);
	~DioPortUI();

	int getKey();
	quint8 getMask();
	void setMask(quint8 value);
	quint8 getState();
	void setState(quint8 state);
	bool getIsEditable();
	void setIsEditable(bool value);
	void Refresh();
	void JudgeDirection(quint8 portDirection);

signals:
	void stateChanged(QObject* sender);

private:
	QGroupBox* group1;
	QGroupBox* group2;
	QButtonGroup* buttonGroup;
	QPushButton* buttons[8];
	QHBoxLayout* layout1;
	QHBoxLayout* layout2;
	QHBoxLayout* layout;
	QLineEdit* portNum;
	QLineEdit* portValue;
	QString* images;

	int key;
	quint8 mask;
	quint8 state;
	bool isEditable;

private slots:
	void ButtonClicked(int id); 
};

#endif // DIOPORTUI_H
