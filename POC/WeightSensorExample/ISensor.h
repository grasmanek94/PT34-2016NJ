#ifndef ISensor_h
#define ISensor_h

class ISensor
{

   public:
      virtual int getMeasurementData() = 0;
      virtual int getPin() = 0;
      virtual void setPin(int p) = 0;
      virtual String getKeyword() = 0;
};
#endif /* ISensor_h */