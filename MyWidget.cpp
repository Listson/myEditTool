#include "MyWidget.h"
MyWidget::MyWidget(void){
	button_openfile = new QPushButton("打开文件");
	listWidget = new QListWidget;
	listWidget->setMaximumWidth(150);
	listWidget->setMinimumWidth(150);
	tabWidget = new QTabWidget;
	tabWidget->setTabsClosable(true);//设置关闭按钮
	tabWidget->setMinimumSize(500,500);
	tabWidget->setMovable(true);//标签栏里的标签是否可以移动
	layout_v_left = new QVBoxLayout;
	layout_v_right = new QVBoxLayout;
	layout_v_left->addWidget(button_openfile);
	layout_v_left->addWidget(listWidget);
	layout_v_right->addWidget(tabWidget);

	layout_h = new QHBoxLayout;
	layout_h->addLayout(layout_v_left);
	layout_h->addLayout(layout_v_right);
	setLayout(layout_h);	
	connect(button_openfile, SIGNAL(clicked()), this, SLOT(slot_button_openfile()));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_tabCloseRequested(int)));
	connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_iteDoubleClicked(QListWidgetItem*)));
}
void MyWidget::slot_button_openfile(void){
	dirpath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
	QDir dir;
	dir.cd(dirpath);
	//QStringList filters;
	//filters << "*.cpp" << "*.c" << "*.h"<<".txt";
	//dir.setNameFilters(filters);
	for(unsigned int i=0; i<dir.count(); i++){
		if(dir[i].compare(".")==0 || dir[i].compare("..")==0)
			continue;
		listWidget->addItem(dir[i]);
	}
}
void MyWidget::slot_iteDoubleClicked(QListWidgetItem *listWidgetItem){
	QString filename = listWidgetItem->text();
	QString filepath;
	filepath.append(dirpath).append("/").append(filename);
	QString content;
	//读取文件内容
	readFile(filepath, content);
	//创建一个文本框
	textEdit = new QTextEdit;
	textEdit->setMinimumSize(500,500);
	textEdit->setAcceptRichText(true);
	textEdit->setText(content);
	//将文本框设置到分页中(标签窗体)
	int index = tabWidget->addTab(textEdit, filename);
	tabWidget->setCurrentIndex(index);
}
void MyWidget::slot_tabCloseRequested(int index){
	//获取标签页对象,用于释放
	textEdit = (QTextEdit*)tabWidget->widget(index);
	//将一个标签从标签栏中移出,切记标签页自己不会清除,需要手动释放
	tabWidget->removeTab(index);
	//释放标签页
	delete textEdit;
}
bool MyWidget::readFile(const QString &filepath, QString &content){
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
		//QMessageBox ::information(NULL, NULL, "open file error");
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		content.append(line);
	}
	return true;
}



