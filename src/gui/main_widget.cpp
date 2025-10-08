#include "main_widget.hpp"

#include <iostream>

#include "ui_main_widget.h"

main_widget::main_widget (QWidget *parent) :
    QWidget(parent), ui(new Ui::main_widget) {
    ui->setupUi(this);
    setWindowTitle("Docusaurus文档排序");
    setupTree();
}

main_widget::~main_widget () {
    delete ui;
}

/**
 * @brief 初始化树
 */
void main_widget::setupTree () const {
    ui->mainTree->setHeaderLabel("目录结构");
    ui->mainTree->setDragEnabled(true);
    ui->mainTree->setAcceptDrops(true);
    ui->mainTree->setDropIndicatorShown(true);
    ui->mainTree->setDragDropMode(QAbstractItemView::InternalMove);
    ui->mainTree->header()->setStyleSheet(
        "QHeaderView::section {border-bottom: 1px solid #c0c0c0;}"
    );
}

/**
 * @brief 点击读取按钮，读取文档
 */
void main_widget::on_readButton_clicked () {
    // 前置处理
    ui->mainTree->clear();
    const QString folderText = ui->folderPath->text();
    const QDir folder(folderText);
    if (!folder.exists() || (folder.dirName() != "docs")) {
        ui->folderPath->setText("路径错误");
        return;
    }
    // 基本流程
    manger = StructManger(folder);
    manger.readStruct(ui->mainTree);
}

/**
 * @brief 点击写入按钮，重构树状结构到文件
 */
void main_widget::on_pushButton_clicked () {
    // 前置处理
    if (!manger.getPath().exists())
        return;
}
