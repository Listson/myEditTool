#include "MyWidget.h"
MyWidget::MyWidget(void){
	button_openfile = new QPushButton("打开文件");
	button_newfile	= new QPushButton("新建");
	button_save = new QPushButton("保存");
	button_saveas = new QPushButton("另存为");
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
	layout_v_left->addWidget(button_newfile);
	layout_v_left->addWidget(button_save);
	layout_v_left->addWidget(button_saveas);
	layout_v_left->addWidget(listWidget);
	layout_v_right->addWidget(tabWidget);

	layout_h = new QHBoxLayout;
	layout_h->addLayout(layout_v_left);
	layout_h->addLayout(layout_v_right);
	setLayout(layout_h);	
	connect(button_openfile, SIGNAL(clicked()), this, SLOT(slot_button_openfile()));
	connect(button_newfile, SIGNAL(clicked()), this, SLOT(slot_newFile()));
	connect(button_save, SIGNAL(clicked()), this, SLOT(slot_save()));
	connect(button_saveas, SIGNAL(clicked()), this, SLOT(slot_saveAs()));
	connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slot_tabCloseRequested(int)));
	connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_iteDoubleClicked(QListWidgetItem*)));
}
void MyWidget::slot_button_openfile(void){
	listWidget->clear();
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
	textEdit = new MyTextEdit;
	textEdit->setMinimumSize(500,500);
	textEdit->setAcceptRichText(true);
	textEdit->setText(content);
	textEdit->setCurrentFilePath(filepath);
	//将文本框设置到分页中(标签窗体)
	int index = tabWidget->addTab(textEdit, filename);
	tabWidget->setCurrentIndex(index);
}
void MyWidget::slot_tabCloseRequested(int index){
	//获取标签页对象,用于释放
	textEdit = (MyTextEdit*)tabWidget->widget(index);
	//将一个标签从标签栏中移出,切记标签页自己不会清除,需要手动释放
	tabWidget->removeTab(index);
	//释放标签页
	delete textEdit;
}
//传入文件路径,和保存文件内容的QString
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
int number=0;
void MyWidget::slot_newFile()//创建新文件操作
{
	QString filename = QString("未命名-%1").arg(number++);
	//创建一个文本框
	textEdit = new MyTextEdit;
	textEdit->setIsNewFile(true);//新创建的文件
	textEdit->setMinimumSize(500,500);
	textEdit->setAcceptRichText(true);
	//将文本框设置到分页中(标签窗体)
	int index = tabWidget->addTab(textEdit, filename);
	tabWidget->setCurrentIndex(index);
}
bool MyWidget::slot_save()//保存操作:1.保存修改 2.保存新创建的文件
{
	if(tabWidget->count()>0){
		//获取当前前的tab page
		textEdit = (MyTextEdit *)tabWidget->currentWidget();
		if(textEdit->getIsNewFile()){
			//如果是新创建的文件则调用另存为的函数
			slot_saveAs();
		}
		else{//不是新创建的文件则判断文件内容有没有被修改
			if(isNeedToSave(textEdit)){
				saveFile(textEdit->getCurrentFilePath());//如果修改了文件内容则保存文件
			}
		}
		return true;
	}
	return false;

}
bool MyWidget::slot_saveAs()//另存操作
{
	if(tabWidget->count()>0){
		QString filepath = QFileDialog::getSaveFileName(this, "另存为", "/");
		if(filepath.isEmpty())
			return false;
		else
			return saveFile(filepath);
	}
	return false;
}
bool MyWidget::isNeedToSave(MyTextEdit *textEdit)//是否需要保存(文件内容是否更改)
{
	//如果文本被修改
	if(textEdit->document()->isModified())
		return true;
	return false;
}
//这里为什么不能用字符串的引用
bool MyWidget::saveFile(QString filepath)//保存文件(将文件写入磁盘)
{
	//获取当前前的tab page
	textEdit = (MyTextEdit *)tabWidget->currentWidget();
	QFile file(filepath);
	if (file.open(QFile::WriteOnly | QIODevice::Truncate)) {
		QTextStream out(&file);
		out << textEdit->toPlainText();
	}
	textEdit->setIsNewFile(false);
	textEdit->setCurrentFilePath(filepath);
	int currentIndex = tabWidget->currentIndex();
	//修改标签名字
	tabWidget->setTabText(currentIndex, filepath.mid(filepath.lastIndexOf("/")+1));
	return true;
}



