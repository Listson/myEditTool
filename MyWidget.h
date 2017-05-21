#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QFileDialog>
#include <QListWidget>
#include <QLCDNumber>
#include <QFile>
#include <QDir>
#include <QTabWidget>
#include <QMessageBox>
#include <QTextStream>
#include "MyTextEdit.h"
#include <QString>

class MyWidget:public QWidget{
	Q_OBJECT
	public:
		MyWidget(void);
		bool readFile(const QString &filepath, QString &content);
		bool isNeedToSave(MyTextEdit *textEdit);//是否需要保存(文件内容是否更改)
		bool saveFile(QString filepath);//保存文件(将文件写入磁盘)
	private:
		QString dirpath;
		QPushButton *button_openfile;//打开文件按钮
		QPushButton *button_newfile;//新建文件按钮
		QPushButton *button_save;//保存文件按钮
		QPushButton *button_saveas;//另存文件按钮

		QListWidget *listWidget;//文件列表
		MyTextEdit *textEdit;
		QTabWidget *tabWidget;
		QVBoxLayout *layout_v_left;
		QVBoxLayout *layout_v_right;
		QHBoxLayout *layout_h;
	public slots:
		void slot_button_openfile(void);
		void slot_iteDoubleClicked(QListWidgetItem *listWidgetItem);
		void slot_tabCloseRequested(int index);
		void slot_newFile();//创建新文件操作
		bool slot_save();//保存操作:1.保存修改 2.保存新创建的文件
		bool slot_saveAs();//另存操作
};

#endif
