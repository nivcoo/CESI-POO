#include "OrderTab.h"

#include <QtWidgets>


OrderTab::OrderTab(QWidget *parent)
        : QWidget(parent)
{
    auto descriptionLabel = new QLabel(tr("Eius populus ab incunabulis primis ad usque pueritiae tempus extremum, quod annis circumcluditur fere trecentis, circummurana pertulit bella, deinde aetatem ingressus adultam post multiplices bellorum aerumnas Alpes transcendit et fretum, in iuvenem erectus et virum ex omni plaga quam orbis ambit inmensus, reportavit laureas et triumphos, iamque vergens in senium et nomine solo aliquotiens vincens ad tranquilliora vitae discessit."));
    descriptionLabel->setWordWrap(true);
    auto addButton = new QPushButton(tr("Add"));

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);
    setLayout(mainLayout);


}

