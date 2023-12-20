#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::map<std::string, int> animalsYears = {
    {"Крыса", 1960},
    {"Бык", 1961},
    {"Тигр", 1962},
    {"Кролик", 1963},
    {"Дракон", 1964},
    {"Змея", 1965},
    {"Лошадь", 1966},
    {"Коза", 1967},
    {"Обезьяна", 1968},
    {"Петух", 1969},
    {"Собака", 1970},
    {"Кабан", 1971}
};

std::string getAnimal(int year) {
    std::string animal;
    for (const auto& entry : animalsYears) {
        const std::string& key = entry.first;
        int animalYear = entry.second;

        if (year > animalYear) {
            int number = animalYear;
            while (number < year) {
                number += 12;
                if (number == year) {
                    animal = key;
                }
            }
        } else if (year < animalYear) {
            int number = animalYear;
            while (number > year) {
                number -= 12;
                if (number == year) {
                    animal = key;
                }
            }
        } else if (year == animalYear) {
            animal = key;
        }
    }
    return animal;
}

void MainWindow::on_getAnimalBut_clicked()
{


    QDate userDate = ui->date->date();
    QString date = userDate.toString("dd.MM.yyyy");
    // Преобразование QString в строку (std::string)
    std::string dateString = date.toStdString();

    // Извлечение года из строки
    int year = std::stoi(dateString.substr(dateString.find_last_of('.') + 1));

    // Получение животного для года
    std::string animal = getAnimal(year);
    QString animalQString = QString::fromStdString(animal);

    ui->resultLabel->setText(animalQString);
}


void MainWindow::on_getAnimalYearBut_clicked()
{

    QDate userDate = ui->date->date();
    QString date = userDate.toString("dd.MM.yyyy");
    // Преобразование QString в строку (std::string)
    std::string dateString = date.toStdString();

    // Извлечение года из строки
    int year = std::stoi(dateString.substr(dateString.find_last_of('.') + 1));

    // Получение текущего года
    int currentYear = QDate::currentDate().year();

    // Получение животного для года рождения и текущего года
    std::string animal = getAnimal(year);
    std::string currentYearAnimal = getAnimal(currentYear);

    // Получение номеров животных для сравнения
    int birthAnimalNumber = animalsYears[animal];
    int currentAnimalNumber = animalsYears[currentYearAnimal];

    int futureYear;

    if (currentAnimalNumber > birthAnimalNumber) {
        futureYear = currentYear + 12 - (currentAnimalNumber - birthAnimalNumber);
    } else if (currentAnimalNumber < birthAnimalNumber) {
        futureYear = currentYear + (birthAnimalNumber - currentAnimalNumber);
    } else {
        futureYear = currentYear + 12;
    }

    QString futureYearString = QString::number(futureYear);

     ui->resultLabel->setText(futureYearString);
}

