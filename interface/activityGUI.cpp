#include "activityGUI.h"
#include <iostream>


void ActivityGUI::initGUI() {
    auto* mainLayout = new QHBoxLayout{};
    setLayout(mainLayout);

    auto* leftLayout = new QVBoxLayout{};
    auto* rightLayout = new QVBoxLayout{};
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    leftLayout->addWidget(tblV);

    tblV->resizeColumnsToContents();
    tblV->resizeRowsToContents();

    auto* formLayout = new QFormLayout{};
    formLayout->addRow("Title", titleTxt);
    formLayout->addRow("Description", descriptionTxt);
    formLayout->addRow("Type", typeTxt);
    formLayout->addRow("Duration", durationTxt);
    rightLayout->addLayout(formLayout);

    auto* buttonLayout = new QVBoxLayout{};

    const auto &report = serv.serviceTypeReport();
    for(auto &type: report){
        auto btn = new QPushButton{QString::fromStdString(type.first)};
        buttonLayout->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, [type](){
            QMessageBox::information(nullptr, "Info", QString::fromStdString(to_string(type.second)));
        });
    }

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(modifyBtn);
    //buttonLayout->addWidget(new QPushButton{"&Print all"});
    //buttonLayout->addWidget(new QPushButton{"&Search"});
    buttonLayout->addWidget(sortByTitleBtn);
    buttonLayout->addWidget(sortByDescriptionBtn);
    buttonLayout->addWidget(sortByTypeAndDurationBtn);
    buttonLayout->addWidget(undoBtn);

    rightLayout->addLayout(abuttonLayout);
    rightLayout->addLayout(buttonLayout);

    auto* filterFormLayout = new QFormLayout;
    filterFormLayout->addRow("Type", filterTypeTxt);
    rightLayout->addLayout(filterFormLayout);

    auto* filterButtonLayout = new QVBoxLayout;
    filterButtonLayout->addWidget(filterByTypeBtn);
    rightLayout->addLayout(filterButtonLayout);


    auto* currentFormLayout = new QFormLayout;
    currentFormLayout->addRow("Title", currentTitleTxt);
    currentFormLayout->addRow("Number", currentGenerationsTxt);
    rightLayout->addLayout(currentFormLayout);

    auto* currentButtonLayout = new QVBoxLayout;
    currentButtonLayout->addWidget(addCurrentBtn);
    currentButtonLayout->addWidget(deleteCurrentBtn);
    currentButtonLayout->addWidget(generateCurrentBtn);
    currentButtonLayout->addWidget(currentActivitiesBtn);
    currentButtonLayout->addWidget(readCurrentBtn);

    rightLayout->addLayout(currentButtonLayout);

}

void CurrentActivitiesGUI::initGUI() {
    auto* mainLayout = new QHBoxLayout{};
    setLayout(mainLayout);

    auto* leftLayout = new QVBoxLayout{};
    auto* rightLayout = new QVBoxLayout{};
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    leftLayout->addWidget(currentListWidget);

    auto* currentformLayout = new QFormLayout{};
    currentformLayout->addRow("Title", currentTitleTxt);
    rightLayout->addLayout(currentformLayout);

    mainLayout->addWidget(currentListWidget);

    QStringList currentListHeader;
    currentListHeader << "Title" << "Description" << "Type" << "Duration";
    this->currentListWidget->setHorizontalHeaderLabels(currentListHeader);

    currentListWidget->resizeColumnsToContents();
    currentListWidget->resizeRowsToContents();

    auto* buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(addCurrentBtn);
    buttonLayout->addWidget(deleteCurrentBtn);
    buttonLayout->addWidget(generateCurrentBtn);
    currentformLayout->addRow("Number", currentGenerationsTxt);
    currentformLayout->addRow("Filename", filenameTxt);
    buttonLayout->addWidget(exportCurrentBtn1);
    buttonLayout->addWidget(exportCurrentBtn2);

    mainLayout->addLayout(buttonLayout);
}

void ActivityGUI::loadData(const vector<Activity>& activities) {
    model->setActivities(activities);
}

void CurrentActivitiesGUI::loadData() {
    currentListWidget->clearContents();
    auto currents = serv.serviceGetAllCurrentActivities();
    int i = 0;
    for(auto &current: currents){
        currentListWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(current.getTitle())));
        currentListWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(current.getDescription())));
        currentListWidget->setItem(i,2, new QTableWidgetItem(QString::fromStdString(current.getType())));
        currentListWidget->setItem(i,3, new QTableWidgetItem(QString::fromStdString(to_string(current.getDuration()))));
        i++;
    }
}

void CurrentActivitiesGUI::initConnect() {
    serv.addObserver(this);
    QObject::connect(addCurrentBtn, &QPushButton::clicked, [&](){
        auto title = currentTitleTxt->text().toStdString();
        try {
            serv.serviceAddCurrentActivity(title);
            auto list = serv.serviceGetAllCurrentActivities();
            int i=0;
            for(const auto& activity: list){
                currentListWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(activity.getTitle())));
                currentListWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(activity.getDescription())));
                currentListWidget->setItem(i,2, new QTableWidgetItem(QString::fromStdString(activity.getType())));
                currentListWidget->setItem(i,3, new QTableWidgetItem(QString::fromStdString(to_string(activity.getDuration()))));
                i++;
            }
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }

    });

    QObject::connect(deleteCurrentBtn, &QPushButton::clicked, [&](){
        try {
            serv.serviceDeleteCurrentActivities();
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(generateCurrentBtn, &QPushButton::clicked, [&](){
        auto nr = currentGenerationsTxt->text().toInt();
        try {
            serv.serviceGenerateCurrentActivities(nr);
            auto list = serv.serviceGetAllCurrentActivities();
            int i=0;
            for(const auto& activity: list){
                currentListWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(activity.getTitle())));
                currentListWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(activity.getDescription())));
                currentListWidget->setItem(i,2, new QTableWidgetItem(QString::fromStdString(activity.getType())));
                currentListWidget->setItem(i,3, new QTableWidgetItem(QString::fromStdString(to_string(activity.getDuration()))));
                i++;
            }
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(exportCurrentBtn1, &QPushButton::clicked, [&](){
        auto filename = filenameTxt->text().toStdString();
        try {
            serv.serviceExportCurrentActivitiesToHTML(filename);
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(exportCurrentBtn2, &QPushButton::clicked, [&](){
        auto filename = filenameTxt->text().toStdString();
        try {
            serv.serviceExportCurrentActivitiesToCVS(filename);
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

}

void CurrentActivitiesGUI::update() {
    loadData();
}

void ActivityGUI::initConnect() {
    serv.addObserver(this);
    //add btn
    QObject::connect(addBtn, &QPushButton::clicked, [this](){
        auto title = titleTxt->text().toStdString();
        auto description = descriptionTxt->text().toStdString();
        auto type = typeTxt->text().toStdString();
        auto duration = durationTxt->text().toInt();
        try {
            serv.serviceAdd(title, description, type, duration);
            loadData(serv.serviceGetAll());

        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //select from list
    QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
            titleTxt->setText("");
            descriptionTxt->setText("");
            typeTxt->setText("");
            durationTxt->setText("");
            return;
        }
        int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = tblV->model()->index(selRow, 0);
        auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
        titleTxt->setText(cel0Value);
        auto cel1Index = tblV->model()->index(selRow, 1);
        auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
        descriptionTxt->setText(cel1Value);
        auto cel2Index = tblV->model()->index(selRow, 2);
        auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
        typeTxt->setText(cel2Value);
        auto cel3Index = tblV->model()->index(selRow, 3);
        auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
        durationTxt->setText(cel3Value);
    });

    //modify btn
    QObject::connect(modifyBtn, &QPushButton::clicked, [&](){
        auto title = titleTxt->text().toStdString();
        auto description = descriptionTxt->text().toStdString();
        auto type = typeTxt->text().toStdString();
        auto duration = durationTxt->text().toInt();
        try {
            serv.serviceModify(title, description, type, duration);
            loadData(serv.serviceGetAll());
        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //delete btn
    QObject::connect(deleteBtn, &QPushButton::clicked, [&](){
        auto title = titleTxt->text().toStdString();
        auto description = descriptionTxt->text().toStdString();
        auto type = typeTxt->text().toStdString();
        auto duration = durationTxt->text().toInt();
        try {
            serv.serviceDelete(title, description, type, duration);
            loadData(serv.serviceGetAll());
        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //filter btn
    QObject::connect(filterByTypeBtn, &QPushButton::clicked, [&](){
        auto type = filterTypeTxt->text().toStdString();
        try {
            auto list = serv.serviceGetFilteredByType(type);
            loadData(list);
        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //undo
    QObject::connect(undoBtn, &QPushButton::clicked, [&](){
        try {
            serv.serviceUndo();
            loadData(serv.serviceGetAll());
        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //sort page button
    QObject::connect(sortByTitleBtn, &QPushButton::clicked, [&](){
        try {
            auto list = serv.serviceSortedByTitle();
            loadData(list);

        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });
    QObject::connect(sortByDescriptionBtn, &QPushButton::clicked, [&](){
        try {
            auto list = serv.serviceSortedByDescription();
            loadData(list);

        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });
    QObject::connect(sortByTypeAndDurationBtn, &QPushButton::clicked, [&](){
        try {
            auto list = serv.serviceSortedByTypeAndDuration();
            loadData(list);

        } catch (Exception &exception) {
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(addCurrentBtn, &QPushButton::clicked, [&](){
        auto title = currentTitleTxt->text().toStdString();
        try {
            serv.serviceAddCurrentActivity(title);
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }

    });

    QObject::connect(deleteCurrentBtn, &QPushButton::clicked, [&](){
        try {
            serv.serviceDeleteCurrentActivities();
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(generateCurrentBtn, &QPushButton::clicked, [&](){
        auto nr = currentGenerationsTxt->text().toInt();
        try {
            serv.serviceGenerateCurrentActivities(nr);
        }catch (Exception &exception){
            QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.getMessage()));
        }
    });

    //current activities page
    QObject::connect(currentActivitiesBtn, &QPushButton::clicked, [&](){
        auto currentWidow = new CurrentActivitiesGUI(serv);
        currentWidow->show();
    });

    QObject::connect(readCurrentBtn, &QPushButton::clicked, [&](){
        auto currentWidow = new readActivitiesGUI(serv);
        currentWidow->show();
    });

}

void ActivityGUI::update() {
    loadData(serv.serviceGetAll());
}


void readActivitiesGUI::update() {
    repaint();
}

void readActivitiesGUI::paintEvent(QPaintEvent *ev){
    QPainter p(this);
    int x = 10;
    for(const auto& a: serv.serviceGetAllCurrentActivities()){
        p.drawEllipse(x, 0, a.getDuration(), a.getDuration());
        x += 20;
    }

}
