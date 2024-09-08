//
// Created by bmaco on 28.05.2024.
//

#ifndef LAB6_7_MYTABLEMODEL_H
#define LAB6_7_MYTABLEMODEL_H

#include <QtWidgets>
#include "../domain/activity.h"

class MyTableModel: public QAbstractTableModel{
private:
    std::vector<Activity> activities;
public:
    explicit MyTableModel(const std::vector<Activity>& activities):activities(activities){};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return (int)activities.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        //qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
        if (role == Qt::DisplayRole) {
            Activity a = activities[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(a.getTitle());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(a.getDescription());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(a.getType());
            }
            else if (index.column() == 3) {
                return QString::number(a.getDuration());
            }
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override{
        if(orientation == Qt::Horizontal and role == Qt::DisplayRole){
            if (section == 0) {
                return QString::fromLocal8Bit("Title");
            }
            else if (section == 1) {
                return QString::fromLocal8Bit("Description");
            }
            else if (section == 2) {
                return QString::fromLocal8Bit("Type");
            }
            else if (section == 3) {
                return QString::fromLocal8Bit("Duration");
            }
        }
        return QVariant();
    }

    void setActivities(const vector<Activity>& activitiess) {
        activities = activitiess;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(this->rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
    }
};

#endif //LAB6_7_MYTABLEMODEL_H
