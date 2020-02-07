#include "CaseComparator.h"

bool CompareString(String first, String second)
{
  return (ConvertToLowerCase(first)==ConvertToLowerCase(second));
}

String ConvertToLowerCase(String str)
{
  char arr[str.length()];
  str.toCharArray(arr, str.length());
  for (int i = 0; i<str.length();i++)
  {
    if (arr[i]>64 &&arr[i]<90)
    {
      arr[i] = arr[i]+32;
    }
    
  }
  return arr;
}
