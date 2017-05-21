#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H
#include <QTextEdit>
class MyTextEdit:public QTextEdit{
	public:
		MyTextEdit();
		void setIsNewFile(bool isNewFile);
		bool getIsNewFile();
		void setCurrentFilePath(QString &currentFilePath);
		QString getCurrentFilePath();
	private:
		bool isNewFile;//是否是新建文件true:是 false:不是
		QString currentFilePath;//保存当前文本框文件的路径
};

#endif
