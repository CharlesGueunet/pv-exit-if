#include "vtkExitIf.h"

#include "vtkDataSet.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"

#include <parallel/algorithm>

vtkStandardNewMacro(vtkExitIf);

// Public
// {{{

//----------------------------------------------------------------------------
void vtkExitIf::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

// }}}
// Protected
// {{{

//----------------------------------------------------------------------------
vtkExitIf::vtkExitIf()
{
    SetNumberOfInputPorts(2);
}

//----------------------------------------------------------------------------
vtkExitIf::~vtkExitIf()
{
}

int vtkExitIf::FillInputPortInformation(int port, vtkInformation* info)
{
  switch (port)
    {
    case 0:
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataSet");
      break;
    case 1:
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataSet");
      break;
    default:
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObject");
      break;
    }

  return 1;
}

int vtkExitIf::compare(vtkDataSet* inputData1, vtkDataSet* inputData2)
{
  // compare number of points :
  if (inputData1->GetNumberOfPoints() != inputData2->GetNumberOfPoints())
    {
      exit(1);
    }

  const auto& nbp = inputData1->GetNumberOfPoints();
  // Points equivalences
  for (int i = 0; i < nbp; i++)
    {
      double pos[3];
      inputData1->GetPoint(i, pos);
      bool find = false;
      for (int j = 0; j < nbp; j++)
        {
          double pos2[3];
          inputData2->GetPoint(j, pos2);

          // Caution, comparison between double
          // Should be equals are both of inputDatas come frome the same input mesh
          find = pos[0] == pos2[0] && pos[1] == pos2[1] && pos[2] == pos2[2];
          if (find)
            {
              break;
            }
        }

      // each point of data1 is in data2
      if (!find)
        {
          exit(2);
        }
    }
  for (int i = 0; i < nbp; i++)
    {
      double pos[3];
      inputData2->GetPoint(i, pos);
      bool find = false;
      for (int j = 0; j < nbp; j++)
        {
          double pos2[3];
          inputData1->GetPoint(j, pos2);

          // Caution, comparison between double
          // Should be equals are both of inputDatas come frome the same input mesh
          find = pos[0] == pos2[0] && pos[1] == pos2[1] && pos[2] == pos2[2];
          if (find)
            {
              break;
            }
        }

      // each point of data2 is in data1
      if (!find)
        {
          exit(3);
        }
    }

  return 0;
}

int vtkExitIf::RequestData(vtkInformation*        request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector*  outputVector)
{

  vtkDataSet* inputData1 = vtkDataSet::GetData(inputVector[0]);
  vtkDataSet* inputData2 = vtkDataSet::GetData(inputVector[1]);

  vtkInformation* outputInfo = outputVector->GetInformationObject(0);
  vtkDataSet*     outputData =
      vtkDataSet::SafeDownCast(outputInfo->Get(vtkDataObject::DATA_OBJECT()));
  // this plugin does not modify the input
  outputData->ShallowCopy(inputData1);

  // Comparison function.
  // this function exit with non 0 if problem is detected
  compare(inputData1, inputData2);

  return 1;
}

// }}}
