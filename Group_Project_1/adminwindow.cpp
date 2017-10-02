#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "windowholder.h"
#include <QSqlQueryModel>
/*! \fn adminWindow::adminWindow
 * \param parent*/
adminWindow::adminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);


    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;

    query.prepare("SELECT * FROM College_Souvenirs");

    query.exec();

    model->setQuery(query);

    ui->SouvenirListTableView->setModel(model);
    ui->SouvenirListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SouvenirListTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SouvenirListTableView->show();

    QSqlQueryModel* otherModel = new QSqlQueryModel;
    QSqlQuery otherQuery;

    otherQuery.clear();
    otherQuery.prepare("SELECT * FROM College_Campus_Distances");
    otherQuery.exec();

    otherModel->setQuery(otherQuery);

    ui->collegeTableView->setModel(otherModel);
    ui->collegeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->collegeTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->collegeTableView->show();


    ui->rightGroupBoxDelete->hide();
    ui->leftGroupBoxAdd->hide();
    ui->bottomGroupBoxModify->hide();


    ui->priceLineEdit->setReadOnly(true);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    palette->setColor(QPalette::Text,Qt::black);
    ui->priceLineEdit->setPalette(*palette);

}

/*! \fn adminWindow::~adminWindow */
adminWindow::~adminWindow()
{
    delete ui;
}

/*! \fn adminWindow::on_backToLoginButton_clicked*/
void adminWindow::on_backToLoginButton_clicked()
{
    windowHolder* WH = windowHolder::getInstance();
    WH->AdminWindowHide();
    WH->LoginWindowShow();
}

void adminWindow::on_backToLoginButton_2_clicked()
{
    windowHolder* WH = windowHolder::getInstance();
    WH->AdminWindowHide();
    WH->LoginWindowShow();
}

void adminWindow::on_addSouvenirButton_clicked()
{
    ui->leftGroupBoxAdd->show();
    ui->rightGroupBoxDelete->hide();
    ui->bottomGroupBoxModify->hide();
    this->populateAddSouvenirCB();
}

void adminWindow::hideGroupBoxes()
{
    ui->leftGroupBoxAdd->hide();
    ui->rightGroupBoxDelete->hide();
    ui->bottomGroupBoxModify->hide();
}

void adminWindow::populateAddSouvenirCB()
{
    ui->addSouvenirSchoolNameComboBox->clear();
    QVector<college*> collegesList;
    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");

    if (query.exec("SELECT * FROM College_Campus_Distances"))
    {
        while(query.next())
        {
            collegesList.push_back(new college(query.value(0).toString(), query.value(1).toString(), false, query.value(2).toInt()));
        }
    }
    QVector<QString> dropDownVector;
    dropDownVector.push_back("Select A School");
    bool found = false;
    for(int i = 0; i < collegesList.size(); i++)
    {
        for(int j = 0; j < dropDownVector.size(); j++)
        {
            if(collegesList[i]->startingCollege == dropDownVector[j])
            {
                found = true;
            }
        }
        if(!found)
        {
            dropDownVector.push_back(collegesList[i]->startingCollege);
        }
        found = false;
    }


    for(int i = 0; i < dropDownVector.size(); i++)
    {
        ui->addSouvenirSchoolNameComboBox->addItem(dropDownVector[i]);
    }

}

void adminWindow::populateSchoolNameDeleteDB()
{
    ui->schoolNameDeleteComboBox->clear();
    QVector<college*> collegesList;
    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");

    if (query.exec("SELECT * FROM College_Campus_Distances"))
    {
        while(query.next())
        {
            collegesList.push_back(new college(query.value(0).toString(), query.value(1).toString(), false, query.value(2).toInt()));
        }
    }
    QVector<QString> dropDownVector;
    dropDownVector.push_back("Select A School");
    bool found = false;
    for(int i = 0; i < collegesList.size(); i++)
    {
        for(int j = 0; j < dropDownVector.size(); j++)
        {
            if(collegesList[i]->startingCollege == dropDownVector[j])
            {
                found = true;
            }
        }
        if(!found)
        {
            dropDownVector.push_back(collegesList[i]->startingCollege);
        }
        found = false;
    }


    for(int i = 0; i < dropDownVector.size(); i++)
    {
        ui->schoolNameDeleteComboBox->addItem(dropDownVector[i]);
    }

}

void adminWindow::on_deleteSouvenirButton_clicked()
{
    ui->leftGroupBoxAdd->hide();
    ui->rightGroupBoxDelete->show();
    ui->bottomGroupBoxModify->hide();
    this->populateSchoolNameDeleteDB();
}

void adminWindow::on_modifySouvenirButton_clicked()
{
    ui->leftGroupBoxAdd->hide();
    ui->rightGroupBoxDelete->hide();
    ui->bottomGroupBoxModify->show();

}

void adminWindow::on_schoolNameDeleteComboBox_currentIndexChanged(int index)
{
    QSqlQuery query;
    QVector<souvenir*> souvenirList;
}
