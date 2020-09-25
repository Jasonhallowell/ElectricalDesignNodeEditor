#pragma once

#include <QtCore/QObject>

#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include "AddOperationalDataModel.h"
#include "DecimalData.hpp"


/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AdditionModel : public AddOperationalDataModel
{
public:

  virtual
  ~AdditionModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Addition"); }

  QString
  name() const override
  { return QStringLiteral("Addition"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();
    auto n3 = _number3.lock();
    auto n4 = _number4.lock();


    if (n1 && n2 && n3)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();
      _result = std::make_shared<DecimalData>(n1->number() +
                                              n2->number() +
                                              n3->number());
      a=4;
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};
