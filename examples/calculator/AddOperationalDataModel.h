#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include <iostream>
#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <QGridLayout>
#include <nodes/NodeDataModel>
#include <QLabel>
#include <iostream>
#include <QGroupBox>
class DecimalData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AddOperationalDataModel : public NodeDataModel
{
  Q_OBJECT

public:

  virtual
  ~AddOperationalDataModel() {}

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType,
           PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

  QWidget *
  embeddedWidget() override { return nullptr; }

  NodeValidationState
  validationState() const override;

  QString
  validationMessage() const override;

protected:

  virtual void
  compute() = 0;

protected:

  std::weak_ptr<DecimalData> _number1;
  std::weak_ptr<DecimalData> _number2;
  std::weak_ptr<DecimalData> _number3;
  std::weak_ptr<DecimalData> _number4;
  std::weak_ptr<DecimalData> _number5;
  int a = 6;
  std::shared_ptr<DecimalData> _result;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QString("Missing or incorrect inputs");
};
