#pragma once

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
class NumberSourceDataModel
  : public NodeDataModel
{
  Q_OBJECT

public:
  NumberSourceDataModel();

  virtual
  ~NumberSourceDataModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Number Source"); }

  bool
  captionVisible() const override
  { return false; }

  QString
  name() const override
  { return QStringLiteral("NumberSource"); }

public:

  QJsonObject
  save() const override;

  void
  restore(QJsonObject const &p) override;

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override
  { }

  QWidget *
  embeddedWidget() override { return _label2; }

private Q_SLOTS:

  void
  onTextEdited(QString const &string);

private:

  std::shared_ptr<DecimalData> _number;
  std::shared_ptr<DecimalData> _number2;

  QLineEdit * _lineEdit;
  QLabel * _label2;
  QLineEdit * echoLineEdit;
  QLineEdit * echoLineEdit2;
  QLabel * echoLabel;
  QComboBox *echoComboBox;
  QGridLayout * echoLayout;
  QGroupBox * echoGroup;
  int numberNodes;
};
