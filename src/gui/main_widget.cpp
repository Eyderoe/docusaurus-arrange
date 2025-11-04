#include "main_widget.hpp"


main_widget::main_widget (QWidget *parent) :
    QWidget(parent), ui(new Ui::main_widget) {
    ui->setupUi(this);
    const QSettings settings;
    ui->folderPath->setText(settings.value("docs_path", "").toString());
    ui->licenseButton->setCheckable(false);
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
    ui->mainTree->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->mainTree->setDragDropMode(QAbstractItemView::InternalMove);
    ui->mainTree->header()->setStyleSheet(
        "QHeaderView::section {border-bottom: 1px solid #c0c0c0;}"
    );
}

/**
 * @brief 点击读取按钮，读取文档
 */
void main_widget::on_readButton_clicked () {
    QSettings settings;
    // 前置处理
    ui->mainTree->clear();
    QString folderText = ui->folderPath->text();
    if (QDir(folderText).dirName() != "docs")
        folderText = folderText + QDir::separator() + "docs";
    const QDir folder(folderText);
    if (!folder.exists() || (folder.dirName() != "docs")) {
        ui->folderPath->setText("路径错误");
        settings.setValue("docs_path", "");
        return;
    }
    settings.setValue("docs_path", QDir(folderText).absolutePath());
    // 基本流程
    manger = StructManager(folder);
    manger.readStruct(ui->mainTree);
}

/**
 * @brief 点击写入按钮，重构树状结构到文件
 */
void main_widget::on_writeButton_clicked () {
    int loc{};
    for (int i = 0; i < ui->mainTree->topLevelItemCount(); ++i) {
        loc += 10;
        const Node *child = dynamic_cast<Node*>(ui->mainTree->topLevelItem(i));
        if (loc != child->sidebarLoc) {
            if (child->isFolder)
                writeFolderConfig(child->baseDir, loc);
            else
                writeFileConfig(child->baseDir, loc);
        }
        if (child->isFolder)
            traverseWrite(child);
    }
    on_readButton_clicked();
}

/**
 * @brief 点击许可按钮，弹出许可窗口
 */
void main_widget::on_licenseButton_clicked () {
    license_dialog dialog(this);
    dialog.exec();
}
