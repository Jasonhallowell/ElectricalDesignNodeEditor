#include "NumberDisplayDataModel.hpp"
#include <QGroupBox>
#include "DecimalData.hpp"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>

NumberDisplayDataModel::
NumberDisplayDataModel()
  : _label2(new QLabel())
{
    QGroupBox *echoGroup = new QGroupBox(tr("Echo"));
    QLabel *echoLabel = new QLabel(tr("Voltage:"));
    QLabel *echoLabel2 = new QLabel(tr("Current:"));
    QComboBox *echoComboBox = new QComboBox;
    //echoComboBox->addItem(tr("Normal"));
    //echoComboBox->addItem(tr("Password"));
    //echoComboBox->addItem(tr("PasswordEchoOnEdit"));
    //echoComboBox->addItem(tr("No Echo"));

    echoLineEdit = new QLineEdit;
    echoLineEdit->setPlaceholderText("Placeholder Text");
    echoLineEdit->setFocus();

    echoLineEdit2 = new QLineEdit;
    echoLineEdit2->setPlaceholderText("Placeholder Text");
    echoLineEdit2->setFocus();

    QGridLayout *echoLayout = new QGridLayout ();
        echoLayout->addWidget(echoLabel, 0, 0);
        //echoLayout->addWidget(echoComboBox, 0, 1);
        echoLayout->addWidget(echoLineEdit, 0, 1);
        echoLayout->addWidget(echoLabel2, 3, 0);
        echoLayout->addWidget(echoLineEdit2, 3, 1);
        _label2->setLayout(echoLayout);
}


unsigned int
NumberDisplayDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}


NodeDataType
NumberDisplayDataModel::
dataType(PortType, PortIndex) const
{
  return DecimalData().type();
}


std::shared_ptr<NodeData>
NumberDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}


void
NumberDisplayDataModel::
setInData(std::shared_ptr<NodeData> data, int portIndex)
{
  auto numberData = std::dynamic_pointer_cast<DecimalData>(data);

  if (numberData)
  {
    modelValidationState = NodeValidationState::Valid;
    modelValidationError = QString();
    if(portIndex == 0)
        echoLineEdit->setText(numberData->numberAsText());
    else
        echoLineEdit2->setText(numberData->numberAsText());
  }
  else
  {
    modelValidationState = NodeValidationState::Warning;
    modelValidationError = QStringLiteral("Missing or incorrect inputs");
    if(portIndex == 0)
        echoLineEdit->clear();
    else
        echoLineEdit2->clear();
  }

  echoLineEdit->adjustSize();
  echoLineEdit2->adjustSize();
}


NodeValidationState
NumberDisplayDataModel::
validationState() const
{
  return modelValidationState;
}


QString
NumberDisplayDataModel::
validationMessage() const
{
  return modelValidationError;
}
