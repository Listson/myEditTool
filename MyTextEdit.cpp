#include "MyTextEdit.h"
MyTextEdit::MyTextEdit(){
	this->isNewFile = false;//默认不是新文件
}
void MyTextEdit::setIsNewFile(bool isNewFile){
	this->isNewFile = isNewFile;
}
bool MyTextEdit::getIsNewFile(){
	return this->isNewFile;
}
void MyTextEdit::setCurrentFilePath(QString &currentFilePath){
	this->currentFilePath = currentFilePath;
}
QString MyTextEdit::getCurrentFilePath(){
	return this->currentFilePath;
}
