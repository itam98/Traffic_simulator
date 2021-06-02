

#include <QtWidgets>

#include "mainwindow.h"



MainWindow::MainWindow()
    : textEdit(new QPlainTextEdit)

{
    //setCentralWidget(textEdit);

    createActions();
    createStatusBar();


    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &MainWindow::commitData);
#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}



void MainWindow::closeEvent(QCloseEvent *event)

{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}



void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile(QString());
    }
}



void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}


bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}


void MainWindow::about()

{
   QMessageBox::about(this, tr("About"),
            tr("       <b>Projekt z przedmiotu PJC</b><br>       "
               "Wykonał: Mateusz Szymański "));
}


void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}



void MainWindow::createActions()
{

    //---Menu

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));  //górny pasek


    //new file
    QAction *newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);

    //fileToolBar->addAction(newAct);

    //open
    QAction *openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);


    //save
    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);

    //save as
    QAction *saveAsAct = fileMenu->addAction(tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);

    // Help->About
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &MainWindow::about);



    //-----ToolBar
    QToolBar *fileToolBar = addToolBar(tr("Add new element"));


    //dolny pasek
    const QIcon addRoadIcon = QIcon(":/images/road_icon.png");
    QAction *addRoadAct = new QAction(addRoadIcon, tr("Add new &road"), this);
    //connect(addRoadAct, &QAction::triggered, this, &MainWindow::open);    //add new road
    fileToolBar->addAction(addRoadAct);

    const QIcon addCrossroadIcon = QIcon(":/images/crossroad_icon.png");
    QAction *addCrossroadAct = new QAction(addCrossroadIcon, tr("Add new &crossroad"), this);
    //connect(addCrossroadAct, &QAction::triggered, this, &MainWindow::open);   //add new crossroad
    fileToolBar->addAction(addCrossroadAct);

    QDockWidget *dock = new QDockWidget(tr("Settings"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    addDockWidget(Qt::RightDockWidgetArea, dock);
    //viewMenu->addAction(dock->toggleViewAction());

}



void MainWindow::createStatusBar()
{
    //statusBar()->showMessage(tr("Otwarto Plik"));
}





bool MainWindow::maybeSave()

{
    if (!textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}


void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}



bool MainWindow::saveFile(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}



void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}



QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
        if (!maybeSave())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (textEdit->document()->isModified())
            save();
    }
}
#endif
