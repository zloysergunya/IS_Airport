#include "mainwidget.h"

#include "config.h"
#include "window_registration.h"
#include "window_authorization.h"
#include "window_workwidget.h"

#include <QFile>
#include <QVBoxLayout>

#include <QDebug>
#include "user.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_currentWidget(nullptr)
{
    setWindowTitle(Config::nameApplication);
    if (!QFile(Config::fileUsers).exists()) {
        m_currentWidget = new Window_Registration(Window_Registration::Admin, this);
        connect(m_currentWidget, SIGNAL(openAuthorization()),
                this, SLOT(slotOpenAuthorization()));
    }
    else {
        m_currentWidget = new Window_Authorization(this);
        connect(m_currentWidget, SIGNAL(openRegistration()),
                this, SLOT(slotOpenRegistration()));
        connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
                this, SLOT(slotOpenWorkWidget(User*)));
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0); // Делаем нулевые границы
    layout->addWidget(m_currentWidget);
    setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete m_currentWidget;
}

void MainWidget::slotOpenAuthorization()
{
    delete m_currentWidget;
    m_currentWidget = new Window_Authorization(this);
    connect(m_currentWidget, SIGNAL(openRegistration()),
            this, SLOT(slotOpenRegistration()));
    connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
            this, SLOT(slotOpenWorkWidget(User*)));
    layout()->addWidget(m_currentWidget);
}

void MainWidget::slotOpenRegistration()
{
    delete m_currentWidget;
    m_currentWidget = new Window_Registration(Window_Registration::Passenger, this);
    connect(m_currentWidget, SIGNAL(openAuthorization()),
            this, SLOT(slotOpenAuthorization()));
    layout()->addWidget(m_currentWidget);
}

void MainWidget::slotOpenWorkWidget(User *user)
{
    delete m_currentWidget;
    m_currentWidget = new Window_WorkWidget(*user, this);
    connect(m_currentWidget, SIGNAL(changeUser()),
            this, SLOT(slotOpenAuthorization()));
    layout()->addWidget(m_currentWidget);
}

