#include "NumberSourceDataModel.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "DecimalData.hpp"
#include <QGroupBox>
#include "DecimalData.hpp"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>

NumberSourceDataModel::
NumberSourceDataModel()
    : _lineEdit(new QLineEdit()), _label2(new QLabel()), numberNodes{2}
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

    _lineEdit->setValidator(new QDoubleValidator());
    _lineEdit->setMaximumSize(_lineEdit->sizeHint());



    connect(echoLineEdit, &QLineEdit::textChanged,
          this, &NumberSourceDataModel::onTextEdited);
    connect(echoLineEdit2, &QLineEdit::textChanged,
          this, &NumberSourceDataModel::onTextEdited);

  _lineEdit->setText("0.0");
}


QJsonObject
NumberSourceDataModel::
save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number)
    modelJson["number"] = QString::number(_number->number());

  return modelJson;
}


void
NumberSourceDataModel::
restore(QJsonObject const &p)
{
  QJsonValue v = p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<DecimalData>(d);
      _lineEdit->setText(strNum);
    }
  }
}


unsigned int
NumberSourceDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = numberNodes;

    default:
      break;
  }

  return result;
}


void
NumberSourceDataModel::
onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  bool ok = false;
  bool ok2 = false;
  numberNodes = 2;

  double number = echoLineEdit->text().toDouble(&ok);
  double number2 = echoLineEdit2->text().toDouble(&ok2);

  if (ok)
  {
    _number = std::make_shared<DecimalData>(number);
    Q_EMIT dataUpdated(0);
  }
  else
  {
    Q_EMIT dataInvalidated(0);
  }
  if (ok2)
  {
    _number2 = std::make_shared<DecimalData>(number2);
    Q_EMIT dataUpdated(1);
}
else
  {
    Q_EMIT dataInvalidated(1);
  }
}


NodeDataType
NumberSourceDataModel::
dataType(PortType, PortIndex) const
{
  return DecimalData().type();
}


std::shared_ptr<NodeData>
NumberSourceDataModel::
outData(PortIndex portIndex)
{
    if(portIndex == 0)
        return _number;
    else
        return _number2;
}
