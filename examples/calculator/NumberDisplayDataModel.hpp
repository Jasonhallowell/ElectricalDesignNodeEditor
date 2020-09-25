#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QLineEdit>
#include "nodes/NodeDataModel"
#include <QTextEdit>
#include <iostream>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class NumberDisplayDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  NumberDisplayDataModel();

  virtual
  ~NumberDisplayDataModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Result"); }

  bool
  captionVisible() const override
  { return false; }

  QString
  name() const override
  { return QStringLiteral("Result"); }

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType,
           PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> data, int portIndex) override;

  QWidget *
  embeddedWidget() override { return _label2; }

  NodeValidationState
  validationState() const override;

  QString
  validationMessage() const override;

private:

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QStringLiteral("Missing or incorrect inputs");

  QLabel * _label2;
  QLineEdit * echoLineEdit;
  QLineEdit * echoLineEdit2;
  QLabel * echoLabel;
  QComboBox *echoComboBox;
  QGridLayout * echoLayout;
  QGroupBox * echoGroup;
};
