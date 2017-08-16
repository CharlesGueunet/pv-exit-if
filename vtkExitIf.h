// .NAME vtkExitIf - save a dataset on disc
// .SECTION Description
// vtkExitIf is a filter to save a dataset on the disk
// while using it. A typical example is saving a plane with
// random scalar-field when tracking a bug on a plugin.
// It will allow you to keep the problematic data-set.

#ifndef __vtkExitIf_h
#define __vtkExitIf_h

#include "vtkDataSetAlgorithm.h"

class VTK_EXPORT vtkExitIf : public vtkDataSetAlgorithm
{
public:
  static vtkExitIf* New();
  vtkTypeMacro(vtkExitIf, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkExitIf();
  ~vtkExitIf();

  int compare(vtkDataSet* inputData1, vtkDataSet* inputData2);

  // VTK Interface

  virtual int FillInputPortInformation(int port, vtkInformation* info);

  int RequestData(vtkInformation* request,
                  vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

private:
  vtkExitIf(const vtkExitIf&);  // Not implemented.
  void operator=(const vtkExitIf&);  // Not implemented.
};

#endif
