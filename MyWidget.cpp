#include "MyWidget.h"
MyWidget::MyWidget(void){
	button_openfile = new QPushButton("打开文件");
	listWidget = new QListWidget;
	listWidget->setMaximumWidth(150);
	listWidget->setMinimumWidth(150);
	textEdit = new QTextEdit;
	textEdit->setMinimumSize(500,500);
	textEdit->setAcceptRichText(true);
	layout_v_left = new QVBoxLayout;
	layout_v_right = new QVBoxLayout;
	layout_v_left->addWidget(button_openfile);
	layout_v_left->addWidget(listWidget);
	layout_v_right = new QVBoxLayout;
	layout_v_right->addWidget(textEdit);

	QFile file("MyWidget.cpp");
	QString text;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		text.append(line);
	}
	textEdit->setText(text);


	layout_h = new QHBoxLayout;
	layout_h->addLayout(layout_v_left);
	layout_h->addLayout(layout_v_right);
	setLayout(layout_h);	
}
void MyWidget::slot_button_openfile(void){
	
}
