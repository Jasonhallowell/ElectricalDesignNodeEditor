#include "AddOperationalDataModel.h"

#include "DecimalData.hpp"

unsigned int
AddOperationalDataModel::
nPorts(PortType portType) const
{
  unsigned int result;

  if (portType == PortType::In)
    result = a;
  else
    result = 5;

  return result;
}


NodeDataType
AddOperationalDataModel::
dataType(PortType, PortIndex) const
{
  return DecimalData().type();
}


std::shared_ptr<NodeData>
AddOperationalDataModel::
outData(PortIndex)
{
  return std::static_pointer_cast<NodeData>(_result);
}


void
AddOperationalDataModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
  auto numberData =
    std::dynamic_pointer_cast<DecimalData>(data);

  if (portIndex == 0)
  {
    _number1 = numberData;
  }
  else if (portIndex == 1)
  {
    _number2 = numberData;
  }
  else if (portIndex == 2)
  {
    _number3 = numberData;
    a = a+1;
  }
  compute();

}


NodeValidationState
AddOperationalDataModel::
validationState() const
{
  return modelValidationState;
}


QString
AddOperationalDataModel::
validationMessage() const
{
  return modelValidationError;
}
