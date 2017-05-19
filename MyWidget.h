#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QFileDialog>
#include <QListWidget>
#include <QLCDNumber>
#include <QTextEdit>
#include <QFile>

class MyWidget:public QWidget{
	Q_OBJECT
	public:
		MyWidget(void);
	private:
		QPushButton *button_openfile;//打开文件按钮
		QListWidget *listWidget;//文件列表
		QTextEdit *textEdit;
		QVBoxLayout *layout_v_left;
		QVBoxLayout *layout_v_right;
		QHBoxLayout *layout_h;
	public slots:
		void slot_button_openfile(void);
};

#endif
