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
#include <QDir>
#include <QTabWidget>
#include <QMessageBox>

class MyWidget:public QWidget{
	Q_OBJECT
	public:
		MyWidget(void);
		bool readFile(const QString &filepath, QString &content);
	private:
		QString dirpath;
		QPushButton *button_openfile;//打开文件按钮
		QListWidget *listWidget;//文件列表
		QTextEdit *textEdit;
		QTabWidget *tabWidget;
		QVBoxLayout *layout_v_left;
		QVBoxLayout *layout_v_right;
		QHBoxLayout *layout_h;
	public slots:
		void slot_button_openfile(void);
		void slot_iteDoubleClicked(QListWidgetItem *listWidgetItem);
		void slot_tabCloseRequested(int index);
};

#endif
